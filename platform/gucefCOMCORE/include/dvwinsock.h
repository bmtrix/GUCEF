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

#ifndef GUCEF_COMCORE_DVSOCKET_H
#define GUCEF_COMCORE_DVSOCKET_H

/*-------------------------------------------------------------------------//
//                                                                         //
//      INCLUDES                                                           //
//                                                                         //
//-------------------------------------------------------------------------*/

#ifndef GUCEF_COMCORE_MACROS_H
#include "gucefCOMCORE_macros.h"       /* library build defines & macros */
#define GUCEF_COMCORE_MACROS_H
#endif /* GUCEF_COMCORE_MACROS_H ? */

#if ( GUCEF_PLATFORM == GUCEF_PLATFORM_MSWIN )

  #undef FD_SETSIZE
  #define FD_SETSIZE 1      /* should set the size of the FD set struct to 1 for VC */
  #include <winsock2.h>
  #include <Ws2tcpip.h>
  #include <Wspiapi.h>

#elif ( ( GUCEF_PLATFORM == GUCEF_PLATFORM_LINUX ) || ( GUCEF_PLATFORM == GUCEF_PLATFORM_ANDROID ) )

  #include <errno.h>
  #include <unistd.h>
  #include <sys/socket.h>
  #include <sys/types.h>
  #include <netdb.h>
  #include <arpa/inet.h>

#endif

/*-------------------------------------------------------------------------//
//                                                                         //
//      TYPES                                                              //
//                                                                         //
//-------------------------------------------------------------------------*/

#if ( GUCEF_PLATFORM == GUCEF_PLATFORM_MSWIN )

struct hostent;

#if !defined( _WINSOCKAPI_ ) && !defined( _WINSOCK2API_ )
typedef UINT_PTR        SOCKET;
typedef struct hostent HOSTENT;
typedef struct hostent *PHOSTENT;
typedef struct hostent FAR *LPHOSTENT;
#endif

struct fd_set;
struct sockaddr;
struct in_addr;
struct timeval;

#define DVSOCKET_EWOULDBLOCK    WSAEWOULDBLOCK

#elif ( ( GUCEF_PLATFORM == GUCEF_PLATFORM_LINUX ) || ( GUCEF_PLATFORM == GUCEF_PLATFORM_ANDROID ) )

typedef struct hostent*         LPHOSTENT;
typedef struct in_addr*         LPIN_ADDR;
typedef struct sockaddr*        LPSOCKADDR;
typedef struct timeval          TIMEVAL;
typedef int SOCKET;

#define INVALID_SOCKET          (SOCKET)(~0)
#define SOCKET_ERROR            (-1)
#define DVSOCKET_EWOULDBLOCK    EWOULDBLOCK
#define SOCKADDR_IN             struct sockaddr_in

#endif

/*-------------------------------------------------------------------------//
//                                                                         //
//      NAMESPACE                                                          //
//                                                                         //
//-------------------------------------------------------------------------*/

#ifdef __cplusplus
namespace GUCEF {
namespace COMCORE {
#endif /* __cplusplus ? */

/*-------------------------------------------------------------------------//
//                                                                         //
//      UTILITIES                                                          //
//                                                                         //
//-------------------------------------------------------------------------*/

/*
 *      Prevent C++ Name mangeling
 */
#ifdef __cplusplus
   extern "C" {
#endif   /* __cplusplus */

/*--------------------------------------------------------------------------*/

        /* MSWIN specific functions */

#if ( GUCEF_PLATFORM == GUCEF_PLATFORM_MSWIN )
/*--------------------------------------------------------------------------*/

/**
 *      Checks whether winsock has already been initialized.
 *
 *      @return boolean indicating true (>0) or false (0)
 */
UInt32
IsWinsockInitialized( void );

/*-------------------------------------------------------------------------*/

/**
 *      Returns the global winsock
 *
 *      @return returns the global WSADATA* winsock data structure information
 */
const void*
GetWinsockData( void );

/*-------------------------------------------------------------------------*/

/**
 *      Initializes winsock if winsock has not yet been initialized
 *      Should be called before each instance of use for winsock.
 *      ie for each socket. Each call increments a counter that is
 *      decremented with a call to ShutdownWinsock().
 *
 *      @param desiredversion the winsock version you require
 */
void
InitWinsock( UInt16 desiredversion );

/*-------------------------------------------------------------------------*/

void
ShutdownWinsock( void );

/*-------------------------------------------------------------------------*/
#endif /* GUCEF_PLATFORM_MSWIN ? */

        /* End of MSWIN specific functions */

/*-------------------------------------------------------------------------*/

int
dvsocket_bind( SOCKET s                    ,
               const struct sockaddr* type ,
               int namelen                 ,
               int* error                  );

/*-------------------------------------------------------------------------*/

SOCKET
dvsocket_socket( int af       ,
                 int type     ,
                 int protocol ,
                 int* error   );

/*-------------------------------------------------------------------------*/

int
dvsocket_select( int nfds                      ,
                 fd_set* readfds               ,
                 fd_set* writefds              ,
                 fd_set* exceptfds             ,
                 const struct timeval* timeout ,
                 int* error                    );

 /*-------------------------------------------------------------------------*/

int
dvsocket_listen( SOCKET s    ,
                 int backlog ,
                 int* error  );

/*-------------------------------------------------------------------------*/

SOCKET
dvsocket_accept( SOCKET s              ,
                 struct sockaddr* addr ,
                 int* addrlen          ,
                 int* error            );

/*-------------------------------------------------------------------------*/

int
dvsocket_connect( SOCKET s                    ,
                  const struct sockaddr* addr ,
                  int namelen                 ,
                  int* error                  );

/*-------------------------------------------------------------------------*/

int
dvsocket_send( SOCKET s        ,
               const void* buf ,
               int len         ,
               int flags       ,
               int* error      );

/*-------------------------------------------------------------------------*/

int
dvsocket_sendto( SOCKET s                  ,
                 const void* buf           ,
                 int len                   ,
                 int flags                 ,
                 const struct sockaddr* to ,
                 int tolen                 ,
                 int* error                );

/*-------------------------------------------------------------------------*/

int
dvsocket_recv( SOCKET s   ,
               void* buf  ,
               int len    ,
               int flags  ,
               int* error );

/*-------------------------------------------------------------------------*/

int
dvsocket_recvfrom( SOCKET s                  ,
                   void* buf                 ,
                   int len                   ,
                   int flags                 ,
                   struct sockaddr* fromaddr ,
                   socklen_t* fromlen        ,
                   int* error                );

/*-------------------------------------------------------------------------*/

void
dvsocket_inet_ntoa( struct in_addr in ,
                    char* ip          );

/*-------------------------------------------------------------------------*/

LPHOSTENT
dvsocket_gethostbyname( const char* name ,
                        int* error       );

/*-------------------------------------------------------------------------*/

LPHOSTENT
dvsocket_gethostbyaddr( const char* addr ,
                        int len          ,
                        int type         ,
                        int* error       );

/*-------------------------------------------------------------------------*/

int
dvsocket_closesocket( SOCKET s   ,
                      int* error );

/*-------------------------------------------------------------------------*/

int
dvsocket_setsockopt( SOCKET s           ,
                     int level          ,
                     int optname        ,
                     const char* optval ,
                     int optlen         ,
                     int* error         );

/*--------------------------------------------------------------------------*/

#ifdef __cplusplus
   }
#endif /* __cplusplus */

/*-------------------------------------------------------------------------//
//                                                                         //
//      NAMESPACE                                                          //
//                                                                         //
//-------------------------------------------------------------------------*/

#ifdef __cplusplus
}; /* namespace COMCORE */
}; /* namespace GUCEF */
#endif /* __cplusplus ? */

/*--------------------------------------------------------------------------*/

#endif /* GUCEF_COMCORE_DVSOCKET_H ? */

/*-------------------------------------------------------------------------//
//                                                                         //
//      Info & Changes                                                     //
//                                                                         //
//-------------------------------------------------------------------------//

- 05-02-2004 :
        - Initial implementation.

-----------------------------------------------------------------------------*/
