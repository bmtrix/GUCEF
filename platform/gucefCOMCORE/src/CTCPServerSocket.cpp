/*
 *  gucefCOMCORE: GUCEF module providing basic communication facilities
 *  Copyright (C) 2002 - 2007.  Dinand Vanvelzen
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

/*-------------------------------------------------------------------------//
//                                                                         //
//      INCLUDES                                                           //
//                                                                         //
//-------------------------------------------------------------------------*/

#include <string.h>                     /* standard string utils */
#include <malloc.h>                     /* Memory management */

#include "dvstrutils.h"                 /* my own string utils */
#include "tsprinting.h"			/* threadsafe printing */

#ifndef GUCEF_CORE_CGUCEFAPPLICATION_H
#include "CGUCEFApplication.h"
#define GUCEF_CORE_CGUCEFAPPLICATION_H
#endif /* GUCEF_CORE_CGUCEFAPPLICATION_H ? */

#ifndef GUCEF_CORE_CLOGMANAGER_H
#include "CLogManager.h"              /* we want the log manager for its defines */
#define GUCEF_CORE_CLOGMANAGER_H
#endif /* GUCEF_CORE_CLOGMANAGER_H ? */

#ifndef GUCEF_COMCORE_SOCKETUTILS_H
#include "socketutils.h"
#define GUCEF_COMCORE_SOCKETUTILS_H
#endif /* GUCEF_COMCORE_SOCKETUTILS_H ? */

#include "CTCPServerSocket.h"           /* this file's header */

/*-------------------------------------------------------------------------//
//                                                                         //
//      NAMESPACE                                                          //
//                                                                         //
//-------------------------------------------------------------------------*/

namespace GUCEF {
namespace COMCORE {

/*-------------------------------------------------------------------------//
//                                                                         //
//      CONSTANTS                                                          //
//                                                                         //
//-------------------------------------------------------------------------*/

/*
 *      This is a value used internally for reading into a buffer between
 *      events. If this value is set to small you will get inefficient code
 *      due to unnecessary memory allocation operations, however if you set it
 *      to large you will allocate memory that is never used.
 *      So what you need to do is find out what the average length is of your
 *      communication and adapt the value to that
 */
#define BUFFER_READ_SIZE        25

#define DEFAULT_MAX_CONNECTIONS 100UL
#define HEAP_RESIZE_AMOUNT	5UL

/*-------------------------------------------------------------------------//
//                                                                         //
//      GLOBAL VARS                                                        //
//                                                                         //
//-------------------------------------------------------------------------*/

const CORE::CEvent CTCPServerSocket::ClientConnectedEvent = "GUCEF::COMCORE::CTCPServerSocket::ClientConnectedEvent";
const CORE::CEvent CTCPServerSocket::ClientDisconnectedEvent = "GUCEF::COMCORE::CTCPServerSocket::ClientDisconnectedEvent";
const CORE::CEvent CTCPServerSocket::ClientErrorEvent = "GUCEF::COMCORE::CTCPServerSocket::ClientErrorEvent";
const CORE::CEvent CTCPServerSocket::ServerSocketOpenedEvent = "GUCEF::COMCORE::CTCPServerSocket::ServerSocketOpenedEvent";
const CORE::CEvent CTCPServerSocket::ServerSocketClosedEvent = "GUCEF::COMCORE::CTCPServerSocket::ServerSocketClosedEvent";
const CORE::CEvent CTCPServerSocket::ServerSocketErrorEvent = "GUCEF::COMCORE::CTCPServerSocket::ServerSocketErrorEvent";
const CORE::CEvent CTCPServerSocket::ServerSocketClientErrorEvent = "GUCEF::COMCORE::CTCPServerSocket::ServerSocketClientErrorEvent";
const CORE::CEvent CTCPServerSocket::ServerSocketMaxConnectionsChangedEvent = "GUCEF::COMCORE::CTCPServerSocket::ServerSocketMaxConnectionsChangedEvent";

/*-------------------------------------------------------------------------//
//                                                                         //
//      TYPES                                                              //
//                                                                         //
//-------------------------------------------------------------------------*/

struct STCPServerConData
{
    SOCKET sockid;
    CORE::CString clientip;
    struct sockaddr_in clientaddr;
    struct timeval timeout;         /* timeout for blocking operations */
};
typedef struct STCPServerConData TTCPServerConData;

/*-------------------------------------------------------------------------*/

struct STCPServerSockData
{
    SOCKET sockid;           /* Winsock socket number */
    UInt32 connectcount;     /* number of clients connected to the server socket */
    UInt32 maxcon;           /* maximum number of connections for this server socket */
    bool blocking;           /* is this a blocking or non-blocking server ? */
    SOCKADDR_IN serverinfo;  /* winsock info on the listening socket */
    struct timeval timeout;  /* timeout for blocking operations */
};
typedef struct STCPServerSockData TTCPServerSockData;

/*-------------------------------------------------------------------------//
//                                                                         //
//      UTILITIES                                                          //
//                                                                         //
//-------------------------------------------------------------------------*/

CTCPServerSocket::CTCPServerSocket( CORE::CPulseGenerator& pulseGenerator ,
                                    bool blocking                         )
    : CSocket()                               
    , _connections( DEFAULT_MAX_CONNECTIONS ) 
    , _active( false )                        
    , _blocking( blocking )                   
    , m_port( 0 )                             
    , _datalock()
    , _timeout( 0 )
    , _acount( 0 )
    , m_pulseGenerator( &pulseGenerator )
    , m_maxUpdatesPerCycle( 10 )
    , m_autoReopenOnError( false )
    , m_lastListenFailed( false )
{GUCEF_TRACE;

    _data = new TTCPServerSockData;
    _data->blocking = blocking;
    _data->sockid = 0;
    _data->connectcount = 0;
    _data->maxcon = DEFAULT_MAX_CONNECTIONS;

    _connections.reserve( DEFAULT_MAX_CONNECTIONS );
    for ( UInt32 i=0; i<DEFAULT_MAX_CONNECTIONS; ++i )
    {
        _connections[ i ] = new CTCPServerConnection( this, i );
    }

    TEventCallback callback( this, &CTCPServerSocket::OnPulse );
    SubscribeTo( m_pulseGenerator                  ,
                 CORE::CPulseGenerator::PulseEvent ,
                 callback                          );
}

/*-------------------------------------------------------------------------*/

CTCPServerSocket::CTCPServerSocket( bool blocking )
    : CSocket()                               
    , _connections( DEFAULT_MAX_CONNECTIONS ) 
    , _active( false )                        
    , _blocking( blocking )                   
    , m_port( 0 )      
    , _datalock()                       
    , _timeout( 0 )
    , _acount( 0 )
    , m_pulseGenerator( &CORE::CCoreGlobal::Instance()->GetPulseGenerator() )
    , m_maxUpdatesPerCycle( 10 )
    , m_autoReopenOnError( false )
    , m_lastListenFailed( false )
{GUCEF_TRACE;

    _data = new TTCPServerSockData;
    _data->blocking = blocking;
    _data->sockid = 0;
    _data->connectcount = 0;
    _data->maxcon = DEFAULT_MAX_CONNECTIONS;

    _connections.reserve( DEFAULT_MAX_CONNECTIONS );
    for ( UInt32 i=0; i<DEFAULT_MAX_CONNECTIONS; ++i )
    {
        _connections[ i ] = new CTCPServerConnection( this, i );
    }

    TEventCallback callback( this, &CTCPServerSocket::OnPulse );
    SubscribeTo( m_pulseGenerator                  ,
                 CORE::CPulseGenerator::PulseEvent ,
                 callback                          );
}

/*-------------------------------------------------------------------------*/

CTCPServerSocket::~CTCPServerSocket()
{GUCEF_TRACE;

    /*
     *      Clean everything up
     */
    Close();

    /*
     *      Cleanup connection data
     */
    for ( UInt32 i=0; i<_connections.size(); ++i )
    {
        delete _connections[ i ];
    }
    _connections.clear();
}

/*-------------------------------------------------------------------------*/

void
CTCPServerSocket::RegisterEvents( void )
{GUCEF_TRACE;

    ClientConnectedEvent.Initialize();
    ClientDisconnectedEvent.Initialize();
    ClientErrorEvent.Initialize();
    ServerSocketOpenedEvent.Initialize();
    ServerSocketClosedEvent.Initialize();
    ServerSocketErrorEvent.Initialize();
    ServerSocketClientErrorEvent.Initialize();
    ServerSocketMaxConnectionsChangedEvent.Initialize();
}

/*-------------------------------------------------------------------------*/

CTCPServerConnection*
CTCPServerSocket::GetConnectionBySocketId( UInt32 socketId )
{GUCEF_TRACE;

    for ( UInt32 i=0; i<_connections.size(); ++i )
    {
        if ( socketId == _connections[ i ]->GetSocketID() )
        {
            return _connections[ i ];
        }
    }
	return NULL;
}

/*-------------------------------------------------------------------------*/

CTCPServerConnection*
CTCPServerSocket::GetConnection( UInt32 index )
{GUCEF_TRACE;

	return _connections[ index ];
}

/*-------------------------------------------------------------------------*/

void
CTCPServerSocket::OnPulse( CORE::CNotifier* notifier                 ,
                           const CORE::CEvent& eventid               ,
                           CORE::CICloneable* eventdata /* = NULL */ )
{GUCEF_TRACE;

    if ( !_active && m_autoReopenOnError && m_lastListenFailed )
    {
        Listen();
    }     
    
    if ( _active )
    {
        /*
         *      Accept new incoming connections
         */
        AcceptClients();

        /*
         *      Update the client connections
         */
        if ( !_blocking )
        {
            for ( UInt32 i=0; i<_connections.size(); ++i )
            {
                _connections[ i ]->Update( m_maxUpdatesPerCycle );
            }
        }
    }
}

/*-------------------------------------------------------------------------*/

void
CTCPServerSocket::SetAutoReOpenOnError( bool autoReOpen )
{GUCEF_TRACE;

    m_autoReopenOnError = autoReOpen;
}

/*-------------------------------------------------------------------------*/

bool
CTCPServerSocket::GetAutoReOpenOnError( void ) const
{GUCEF_TRACE;

    return m_autoReopenOnError;
}

/*-------------------------------------------------------------------------*/

void
CTCPServerSocket::SetMaxUpdatesPerCycle( UInt32 maxUpdates )
{GUCEF_TRACE;

    m_maxUpdatesPerCycle = maxUpdates;
}

/*-------------------------------------------------------------------------*/


UInt32
CTCPServerSocket::GetMaxUpdatesPerCycle( void ) const
{GUCEF_TRACE;

    return m_maxUpdatesPerCycle;
}

/*-------------------------------------------------------------------------*/

void
CTCPServerSocket::AcceptClients( void )
{GUCEF_TRACE;

    if ( _data->connectcount < _data->maxcon )
    {
        int s = 0;           /* s is where the data is stored from the select function */
        int nfds = 0;        /* This is used for Compatibility */
    
        fd_set conn;         /* Setup the read variable for the Select function */
        fd_set exceptfds;    /* Setup the except variable for the select function */

        FD_ZERO( &conn );       // Set the data in conn to nothing
        FD_ZERO( &exceptfds );

        FD_SET( _data->sockid, &conn );   // Tell it to get the data from the Listening Socket
        FD_SET( _data->sockid, &exceptfds );

        if ( !_data->blocking )
        {
            /*
             *  Because we are in non-blocking mode we must make sure the timeout
             *  structure is zero'd or it will block
             */
            memset( &_data->timeout, 0, sizeof( struct timeval ) );

            /*
             *      Up the nfds value by one, shouldnt be the same for each
             *      client that connects for compatibility reasons
             *      Doing a select first will ensure that we don't block on accept()
             */
            nfds = (int)_data->sockid+1;
            s = select( nfds            ,
                        &conn           ,
                        NULL            ,
                        &exceptfds      ,
                        &_data->timeout ); // Is there any data coming in?

            if ( s > 0 ) /* Someone is trying to Connect */
            {
                CTCPServerConnection* clientcon;
                int aint;
                for ( UInt32 i=0; i<_data->maxcon; ++i )
                {
                    clientcon = (CTCPServerConnection*)(_connections[ i ]);
                    if ( !clientcon->IsActive() )
                    {
                        int error = 0;
                        aint = sizeof( struct sockaddr );
                        clientcon->_data->sockid = dvsocket_accept( _data->sockid                                    ,
                                                                    (struct sockaddr*) &clientcon->_data->clientaddr ,
                                                                    &aint                                            ,
                                                                    &error                                           );

                        /*
                         *      Client Connected
                         *      Store the Ip of the Client that Just Connected.
                         */
                        char clientip[ 20 ];
                        dvsocket_inet_ntoa( clientcon->_data->clientaddr.sin_addr ,
                                            clientip                              );
                        clientcon->_data->clientip = clientip;

                        /*
                         *      Set the socket into the desired mode of operation
                         *      ie blocking or non-blocking mode
                         */
                        if ( !SetBlockingMode( _data->sockid ,
                                               _blocking     ) )
                        {
                            clientcon->_data->sockid = 0;
                            return;
                        }
                        clientcon->_blocking = _blocking;
                        if ( !_blocking )
                        {
                            /*
                             *  Because we are in non-blocking mode we must make sure the timeout
                             *  structure is zero'd or it will block
                             */
                            memset( &clientcon->_data->timeout, 0, sizeof( struct timeval ) );
                        }

                        ++_data->connectcount;
                        clientcon->_active = true;

                        /*
                         *      Call the on client connect event handler
                         */
                        struct SConnectionInfo eData;
                        eData.hostAddress.SetHostname( clientcon->_data->clientip );
                        #if ( GUCEF_PLATFORM == GUCEF_PLATFORM_MSWIN )
                        eData.hostAddress.SetAddress( clientcon->_data->clientaddr.sin_addr.S_un.S_addr );
                        #elif ( ( GUCEF_PLATFORM == GUCEF_PLATFORM_LINUX ) || ( GUCEF_PLATFORM == GUCEF_PLATFORM_ANDROID ) )
                        eData.hostAddress.SetAddress( clientcon->_data->clientaddr.sin_addr.s_addr );
                        #endif
                        eData.hostAddress.SetPort( clientcon->_data->clientaddr.sin_port );
                        eData.connection = clientcon;
                        eData.connectionIndex = i;

                        ++_acount;

                        TClientConnectedEventData cloneableEventData( eData );
                        NotifyObservers( ClientConnectedEvent, &cloneableEventData );

                        return;
                    }
                }
            }
        }
    }
}

/*-------------------------------------------------------------------------*/

bool
CTCPServerSocket::IsActive( void ) const
{GUCEF_TRACE;

    return _active;
}

/*-------------------------------------------------------------------------*/

bool
CTCPServerSocket::IsBlocking( void ) const
{GUCEF_TRACE;

    return _blocking;
}

/*-------------------------------------------------------------------------*/

bool
CTCPServerSocket::Listen( void )
{GUCEF_TRACE;

    return ListenOnPort( m_port );
}

/*-------------------------------------------------------------------------*/

bool
CTCPServerSocket::ListenOnPort( UInt16 servport )
{GUCEF_TRACE;

    /*
     *      Close all existing connections
     */
    if ( IsActive() )
    {
            Close();
    }
    m_port = servport;

    int error = 0;
    _data->sockid = dvsocket_socket( AF_INET     ,    /* Go over TCP/IP */
                                     SOCK_STREAM ,    /* This is a stream-oriented socket */
                                     IPPROTO_TCP ,    /* Use TCP rather than UDP */
                                     &error      );

    if ( _data->sockid == INVALID_SOCKET )
    {
        m_lastListenFailed = true;
        if ( m_autoReopenOnError ) 
            m_pulseGenerator->RequestPeriodicPulses( this, 10 );

        GUCEF_ERROR_LOG( 1, "CTCPServerSocket: Socket error: " + CORE::Int32ToString( error ) );
        TServerSocketErrorEventData eData( error );
        NotifyObservers( ServerSocketErrorEvent, &eData );
        return false;
    }

    /* Set the desired blocking mode */
    if ( !SetBlockingMode( _data->sockid ,
                           _blocking     ) )
    {
        m_lastListenFailed = true;
        if ( m_autoReopenOnError ) 
            m_pulseGenerator->RequestPeriodicPulses( this, 10 );

        NotifyObservers( ServerSocketErrorEvent );
        return false;
    }

	/*
	 *      We set the protocol family to TCP/IP
	 */
	_data->serverinfo.sin_family = AF_INET;

	/*
	 *      Since this socket is listening for connections, any local address will do
	 */
	_data->serverinfo.sin_addr.s_addr = INADDR_ANY;

        /*
         *      Convert integer servport to network-byte order
         *      and insert into the port field
         */
	_data->serverinfo.sin_port = htons( servport );

        /*
         *      Bind the socket to our local server address
         */
	int retval = dvsocket_bind( _data->sockid                  ,
	                            (LPSOCKADDR)&_data->serverinfo ,
	                            sizeof( _data->serverinfo )    ,
	                            &error                         );

	if ( retval == SOCKET_ERROR )
	{
        m_lastListenFailed = true;
        if ( m_autoReopenOnError ) 
            m_pulseGenerator->RequestPeriodicPulses( this, 10 );

        GUCEF_ERROR_LOG( 1, "CTCPServerSocket: Socket error: " + CORE::Int32ToString( error ) );
	    TServerSocketErrorEventData eData( error );
	    NotifyObservers( ServerSocketErrorEvent, &eData );
	    return false;
	}

    // Before we actually open the socket lets give observers the change to pre-allocate things if needed
    // based on the max number of connections.
    TServerSocketMaxConnectionsChangedEventData maxConEData( _data->maxcon );
    NotifyObservers( ServerSocketMaxConnectionsChangedEvent, &maxConEData );

    /*
     *      Make the socket listen
     *
     *      Up to maxcon connections may wait at any
     *      one time to be accept()'ed
     */
	retval = dvsocket_listen( _data->sockid      ,
	                          _data->maxcon      ,
	                          &error             );

	if ( retval == SOCKET_ERROR )
	{
		m_lastListenFailed = true;
        if ( m_autoReopenOnError ) 
            m_pulseGenerator->RequestPeriodicPulses( this, 10 );

        TServerSocketErrorEventData eData( error );
		NotifyObservers( ServerSocketErrorEvent, &eData );
		return false;
	}
	_active = true;
    m_lastListenFailed = false;
    NotifyObservers( ServerSocketOpenedEvent );

	/*
	 *      Accept new connections if there are any.
	 */
    AcceptClients();

    m_pulseGenerator->RequestPeriodicPulses( this, 10 );

    return true;
}

/*-------------------------------------------------------------------------*/

UInt32
CTCPServerSocket::GetMaxConnections( void ) const
{GUCEF_TRACE;

    return (UInt32) _connections.size();
}

/*-------------------------------------------------------------------------*/

UInt32
CTCPServerSocket::GetActiveCount( void ) const
{GUCEF_TRACE;

    return _acount;
}

/*-------------------------------------------------------------------------*/

UInt32
CTCPServerSocket::GetBytesReceived( bool resetCounter )
{GUCEF_TRACE;

    UInt32 bytesReceived = 0;
    _datalock.Lock();
    for( UInt32 i=0; i<_connections.size(); ++i )
    {
        bytesReceived += _connections[ i ]->GetBytesReceived( resetCounter );
    }
    _datalock.Unlock();
    return bytesReceived;
}

/*-------------------------------------------------------------------------*/

UInt32 
CTCPServerSocket::GetBytesTransmitted( bool resetCounter )
{GUCEF_TRACE;

    UInt32 bytesTransmitted = 0;
    _datalock.Lock();
    for( UInt32 i=0; i<_connections.size(); ++i )
    {
        bytesTransmitted += _connections[ i ]->GetBytesTransmitted( resetCounter );
    }
    _datalock.Unlock();
    return bytesTransmitted;
}

/*-------------------------------------------------------------------------*/

void
CTCPServerSocket::Close( void )
{GUCEF_TRACE;

    /*
     *      Close the socket
     *      By setting active to false the thread will terminate
     */
    _datalock.Lock();

    if ( IsActive() )
    {
	    //StopAndWait();

        int errorCode;
        dvsocket_closesocket( _data->sockid, &errorCode );

        NotifyObservers( ServerSocketClosedEvent );

        for( UInt32 i=0; i<_connections.size(); ++i )
        {
            _connections[ i ]->Close();
        }
    }
    _datalock.Unlock();

    m_pulseGenerator->RequestStopOfPeriodicUpdates( this );
}

/*-------------------------------------------------------------------------*/

bool 
CTCPServerSocket::SetPort( UInt16 port )
{GUCEF_TRACE;

    if ( !IsActive() )
    {
        m_port = port;
        return true;
    }
    return false;
}

/*-------------------------------------------------------------------------*/

UInt16
CTCPServerSocket::GetPort( void ) const
{GUCEF_TRACE;

    return m_port;
}

/*-------------------------------------------------------------------------*/

void
CTCPServerSocket::OnClientConnectionClosed( CTCPServerConnection* connection ,
                                            const UInt32 connectionid        ,
                                            bool closedByClient              )
{GUCEF_TRACE;

    TClientDisconnectedEventData cloneableEventData;    
    struct SDisconnectInfo& eData = cloneableEventData.GetData();
    eData.connectionInfo.hostAddress = connection->GetRemoteHostAddress();
    eData.connectionInfo.connection = connection;
    eData.connectionInfo.connectionIndex = connectionid;
    eData.closedByClient = closedByClient;

    --_acount;

    NotifyObservers( ClientDisconnectedEvent, &cloneableEventData );
}

/*-------------------------------------------------------------------------*/

void
CTCPServerSocket::GetListenAddress( CHostAddress& listenAddress ) const
{GUCEF_TRACE;

    _datalock.Lock();
    listenAddress.SetPortInHostByteOrder( m_port );
    listenAddress.SetHostname( "localhost" );
    _datalock.Unlock();
}

/*-------------------------------------------------------------------------*/

bool
CTCPServerSocket::SendToAllClients( const void* dataSource , 
                                    const UInt32 dataSize  )
{GUCEF_TRACE;

    bool totalSuccess = true;
    _datalock.Lock();
    if ( IsActive() )
    {
        for( UInt32 i=0; i<_connections.size(); ++i )
        {
            totalSuccess = totalSuccess && _connections[ i ]->Send( dataSource, dataSize );
        }
    }
    _datalock.Unlock();
    return totalSuccess;
}

/*-------------------------------------------------------------------------//
//                                                                         //
//      NAMESPACE                                                          //
//                                                                         //
//-------------------------------------------------------------------------*/

}; /* namespace COMCORE */
}; /* namespace GUCEF */

/*-------------------------------------------------------------------------*/
