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

#ifndef GUCEF_COMCORE_CUDPSOCKET_H
#define GUCEF_COMCORE_CUDPSOCKET_H

/*-------------------------------------------------------------------------//
//                                                                         //
//      INCLUDES                                                           //
//                                                                         //
//-------------------------------------------------------------------------*/

#ifndef GUCEF_MT_CMUTEX_H
#include "gucefMT_CMutex.h"       /* gucefMT mutex class */
#define GUCEF_MT_CMUTEX_H
#endif /* GUCEF_MT_CMUTEX_H ? */

#ifndef GUCEF_CORE_CDVSTRING_H
#include "CDVString.h"            /* gucefCORE platform string implementation */
#define GUCEF_CORE_CDVSTRING_H
#endif /* GUCEF_CORE_CDVSTRING_H ? */

#ifndef GUCEF_CORE_CLONEABLES_H
#include "cloneables.h"
#define GUCEF_CORE_CLONEABLES_H
#endif /* GUCEF_CORE_CLONEABLES_H ? */

#ifndef GUCEF_CORE_CTEVENTHANDLERFUNCTOR_H
#include "gucefCORE_CTEventHandlerFunctor.h"
#define GUCEF_CORE_CTEVENTHANDLERFUNCTOR_H
#endif /* GUCEF_CORE_CTEVENTHANDLERFUNCTOR_H ? */

#ifndef GUCEF_COMCORE_CSOCKET_H
#include "CSocket.h"      /* base class for all TCP and UDP related socket classes */
#define GUCEF_COMCORE_CSOCKET_H
#endif /* GUCEF_COMCORE_CSOCKET_H ? */

/*-------------------------------------------------------------------------//
//                                                                         //
//      NAMESPACE                                                          //
//                                                                         //
//-------------------------------------------------------------------------*/

namespace GUCEF {
namespace COMCORE {

/*-------------------------------------------------------------------------//
//                                                                         //
//      CLASSES                                                            //
//                                                                         //
//-------------------------------------------------------------------------*/

/**
 *      UDP Socket class that wraps the O/S UDP socket functionality.
 *      This class can act as a blocking or non-blocking UDP socket.
 *      In both cases a UDPPacketRecievedEvent will be sent when a packet
 *      is received.
 */
class GUCEF_COMCORE_EXPORT_CPP CUDPSocket : public CSocket
{
    public:

    static const CORE::CEvent UDPSocketErrorEvent;
    static const CORE::CEvent UDPSocketClosedEvent;
    static const CORE::CEvent UDPSocketOpenedEvent;
    static const CORE::CEvent UDPPacketRecievedEvent;

    static void RegisterEvents( void );

    struct SUDPPacketRecievedEventData
    {
        CIPAddress sourceAddress;                 /**< the source address of the data */
        CORE::TLinkedCloneableBuffer dataBuffer;  /**< the received packet data */
    };
    typedef struct SUDPPacketRecievedEventData TUDPPacketRecievedEventData;
    typedef CORE::CTCloneableObj< TUDPPacketRecievedEventData > UDPPacketRecievedEventData;
    typedef CORE::TCloneableInt32  TSocketErrorEventData;

    public:

    /**
     *      Creates a UDP socket object initialized to be either blocking
     *      or non-blocking. Choosing either type is a design decision.
     *
     *      @param blocking whether to construct the socket as a blocking socket
     */
    CUDPSocket( CORE::CPulseGenerator& pulseGenerator ,
                bool blocking                         );

    /**
     *      Creates a UDP socket object initialized to be either blocking
     *      or non-blocking. Choosing either type is a design decision.
     *
     *      @param blocking whether to construct the socket as a blocking socket
     */
    CUDPSocket( bool blocking );

    /**
     *      Cleans up the allocated data and closes the socket
     */
    virtual ~CUDPSocket();

    /**
     *      Returns wheter the socket is currently active
     *
     *      @return activity status of the socket
     */
    bool IsActive( void ) const;

    /**
     *      Attempts to open the UDP socket for use.
     *      The port used is left up to the operating system.
     *      This will typically be used for clients in a client-server
     *      architecture.
     */
    bool Open( void );

    /**
     *      Attempts to open the UDP socket for use on the given port.
     *      This will typically be used for a server in a client-server
     *      architecture or for an peer-to-peer architecture.
     *      Any local address can be used.
     *
     *      @param port port used for sending and/or receiving data
     */
    bool Open( UInt16 port );

    /**
     *      Attempts to open the UDP socket for use on the given local
     *      address and port. Basically the same as Open( UInt16 port )
     *      but here you binding to a specific local address mandatory.
     *
     *      @param localaddr local address to be used for this socket
     *      @param port port used for sending and/or receiving data
     */
    bool Open( const CORE::CString& localaddr ,
               UInt16 port                    );

    /**
     *      Attempts to open the UDP socket for use on the given local
     *      address and port. Basically the same as Open( UInt16 port )
     *      but here you binding to a specific local address mandatory.
     *
     *      @param localaddr local address and port to be used for this socket
     */
    bool Open( const CIPAddress& localaddr );

    /**
     *  Attempts to join the given multicast group using exclusive mode
     *  This will accept multicast data from any source.
     *  To prevent receiving data from specific sources use Block/Unblock   
     *
     *  @param multicastGroup The multicast group to join
     */
    bool Join( const CIPAddress& multicastGroup );

    /**
     *  Attempts to join the given multicast group using inclusive mode
     *  This will accept multicast data from the source specified.
     *  To add additional allowed source addresses simply invoke this repeatedly per allowed source    
     *
     *  @param multicastGroup The multicast group to join
     *  @param srcAddr The allowed source address of multicast data
     */
    bool Join( const CIPAddress& multicastGroup ,
               const CIPAddress& srcAddr        );

    /**
     *  Attempts to join the leave multicast group using exclusive mode
     *  This will stop accepting multicast data from any source. 
     *
     *  @param multicastGroup The multicast group to join
     */
    bool Leave( const CIPAddress& multicastGroup );

    /**
     *  Attempts to leave the given multicast group using inclusive mode
     *  This will stop accepting multicast data from the source specified.
     *  To leave for additional allowed source addresses simply invoke this repeatedly per allowed source    
     *
     *  @param multicastGroup The multicast group to leave
     *  @param srcAddr The allowed source address of multicast data
     */
    bool Leave( const CIPAddress& multicastGroup ,
                const CIPAddress& srcAddr        );

    /**
     *  Attempts to block data from the given multicast group for a specific source using exclusive mode
     *  This will stop accepting multicast data from the source specified.
     *  To block additional allowed source addresses simply invoke this repeatedly per allowed source    
     *
     *  @param multicastGroup The multicast group to leave
     *  @param srcAddr The allowed source address of multicast data
     */
    bool Block( const CIPAddress& multicastGroup ,
                const CIPAddress& srcAddr        );

    /**
     *   Attempts to unblock data from the given multicast group for a specific source using exclusive mode
     *  This will (re)start accepting multicast data from the source specified.
     *  To unblock additional blocked source addresses simply invoke this repeatedly per blocked source    
     *
     *  @param multicastGroup The multicast group to leave
     *  @param srcAddr The allowed source address of multicast data
     */
    bool Unblock( const CIPAddress& multicastGroup ,
                  const CIPAddress& srcAddr        );

    UInt16 GetPort( void ) const;

    /**
     *      Closes the socket connection.
     */
    void Close( bool shutdownOnly = false );

    /**
     *      Attempts to send a UDP packet to the given destination.
     *      Note that the data you send must fit within the payload
     *      space of a UDP packet.
     *      Note that this method is inefficient for regular
     *      transmissions to the same destination, use the other version
     *      for such a purpose.
     *
     *      @param dnsname DNS name of IP string of the remote host.
     *      @param port remote port that the data is to be sent to.
     *      @param data pointer to the data you wish to send
     *      @param datasize size in bytes of the data block pointed to by data
     *      @return the actual number of bytes that where sent. -1 indicates an error.
     */
    Int32 SendPacketTo( const CORE::CString& dnsname ,
                        UInt16 port                  ,
                        const void* data             ,
                        UInt16 datasize              );

    /**
     *      Attempts to send a UDP packet to the given destination.
     *      Note that the data you send must fit within the payload
     *      space of a UDP packet.
     *
     *      @param dest Information about the packet destination.
     *      @param data pointer to the data you wish to send
     *      @param datasize size in bytes of the data block pointed to by data
     *      @return the actual number of bytes that where sent. -1 indicates an error.
     */
    Int32 SendPacketTo( const CIPAddress& dest ,
                        const void* data       ,
                        UInt16 datasize        );

    /**
     *      Attempts to send a UDP packet to the given destination.
     *      Note that the data you send must fit within the payload
     *      space of a UDP packet.
     *
     *      @param dest Information about the packet destination.
     *      @param data pointer to the data you wish to send
     *      @param datasize size in bytes of the data block pointed to by data
     *      @return the actual number of bytes that where sent. -1 indicates an error.
     */
    Int32 SendPacketTo( const CIPAddress& dest ,
                        const void* data       ,
                        UInt16 datasize        ) const;

    /**
     *      For blocking sockets this call will not return until data is
     *      received. For non-blocking sockets this call returns immediately
     *      if there is no data and returns an error value.
     *
     *      Received data is written into destbuf up to bufsize bytes.
     *      If the destination buffer is not large enough to hold the entire
     *      packet data then the remaining data will be lost !!!
     *
     *      If there are more packets queued after a successful read then
     *      a new UDPPacketRecievedEvent will be sent. This cycle repeats until
     *      there are no more packets in the queue.
     *
     *      @param src structure that will hold the information about the source of the data
     *      @param destbuf buffer the received data will be written to.
     *      @param bufsize size of the destination buffer in bytes.
     *      @return the number of bytes written to the given buffer, returns -1 on error.
     */
    Int32 Recieve( CIPAddress& src ,
                   void* destbuf   ,
                   UInt16 bufsize  );

    /**
     *      Same as the other version of Recieve() except here
     *      you do not have to pass in a structure for source info.
     *      Only use this version if you don't care where the packet
     *      came from and you will use eventing to handle the payload
     *
     *      @param destbuf buffer the received data will be written to.
     *      @param bufsize size of the destination buffer in bytes.
     *      @return the number of bytes written to the given buffer, returns -1 on error.
     */
    Int32 Recieve( void* destbuf      ,
                   UInt16 bufsize     );


    /**
     *      Same as the other version of Recieve() except here
     *      you soley rely on the eventing mechanism
     *
     *      @return the number of bytes written to the given buffer, returns -1 on error.
     */
    Int32 Recieve( void );

    /**
     *      returns whether this socket is a blocking socket
     *
     *      @return whether this socket is a blocking socket
     */
    bool IsBlocking( void ) const;

    /**
     *  returns the size of the buffer used for a single received data packet
     *
     *  @return the size of the buffer for received data
     */
    UInt32 GetRecievedDataBufferSize( void ) const;

    /**
     *  sets the size of the buffer used for a single received data packet
     *  Typically you will want to set this to the exact size of your UDP packages
     *  That way you don't have to perform any additional mergers/parsing operations
     *
     *  @param newBufferSize size of the buffer for received data
     */
    void SetRecievedDataBufferSize( const UInt32 newBufferSize );

    UInt32 GetNrOfDataReceivedEvents( bool resetCounter );

    virtual UInt32 GetBytesReceived( bool resetCounter );

    virtual UInt32 GetBytesTransmitted( bool resetCounter );

    bool IsIncomingDataQueued( void );

    void SetAutoReOpenOnError( bool autoReOpen );

    bool GetAutoReOpenOnError( void ) const;

    void SetAllowMulticastLoopback( bool allowLoopback );

    bool GetAllowMulticastLoopback( void ) const;

    void SetMulticastTTL( Int32 ttl );

    Int32 GetMulticastTTL( void ) const;

    void SetAllowBroadcast( bool allowBroadcast );

    bool GetAllowBroadcast( void ) const;

    /**
     *  sets the max number of updates to perform on the socket for a given update cycle
     *  This setting applies to running a socket in non-blocking event driven mode.
     *  If you have a very busy socket you don't want the socket to get 'stuck' reading from the socket for example
     *  due to the fact that data is coming in so fast that by the time you finished reading from the socket more 
     *  data is waiting on the socket. In such cases you should use this setting to avoid this scenario.
     *
     *  @param maxUpdates number of updates to perform per update cycle
     */
    void SetMaxUpdatesPerCycle( UInt32 maxUpdates );

    UInt32 GetMaxUpdatesPerCycle( void ) const;

    private:
    typedef CORE::CTEventHandlerFunctor< CUDPSocket > TEventCallback;

    void OnPulse( CORE::CNotifier* notifier           ,
                  const CORE::CEvent& eventid         ,
                  CORE::CICloneable* eventdata = NULL );

    void OnPulseGeneratorDestruction( CORE::CNotifier* notifier           ,
                                      const CORE::CEvent& eventid         ,
                                      CORE::CICloneable* eventdata = NULL );

    bool Update( bool performRead );  /**< checks the socket for queued incoming data */

    private:

    struct SUDPSockData;            /**< forward declaration of platform data storage structure */
    typedef struct CUDPSocket::SUDPSockData TUDPSockData;

    bool m_autoReopenOnError;       /**< flag for feature to auto re-open the socket when after a socket error occurred */
    bool _blocking;                 /**< is this socket blocking ? */
    bool _checkfordata;             /**< check for data and dispatch event next update cycle ? */
    struct SUDPSockData* _data;     /**< container for platform specific data */
    CHostAddress m_hostAddress;     /**< retains the destination address and provides easy host-network conversion */
    MT::CMutex _datalock;           /**< mutex for thread-safety when manipulating the socket */
    CORE::CDynamicBuffer m_buffer;
    CORE::CPulseGenerator* m_pulseGenerator;
    UInt32 m_maxUpdatesPerCycle;    /**< setting aimed at preventing a busy socket from hogging all the processing */
    bool m_allowMulticastLoopback;
    int m_multicastTTL;
    bool m_allowBroadcast;
    mutable UInt32 m_bytesReceived;
    mutable UInt32 m_bytesTransmitted;
    mutable UInt32 m_nrOfDataReceivedEvents;
};

/*-------------------------------------------------------------------------//
//                                                                         //
//      NAMESPACE                                                          //
//                                                                         //
//-------------------------------------------------------------------------*/

}; /* namespace COMCORE */
}; /* namespace GUCEF */

/*-------------------------------------------------------------------------*/

#endif /* GUCEF_COMCORE_CUDPSOCKET_H ? */

/*-------------------------------------------------------------------------//
//                                                                         //
//      Info & Changes                                                     //
//                                                                         //
//-------------------------------------------------------------------------//

- 06-05-2005 :
        - Initial version of the new implementation using winsock directly,
          got rid of all the SDL crap.

-----------------------------------------------------------------------------*/
