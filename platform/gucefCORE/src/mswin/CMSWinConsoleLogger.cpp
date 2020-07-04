/*
 *  gucefCORE: GUCEF module providing O/S abstraction and generic solutions
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

#include <assert.h>

#ifndef GUCEF_CORE_DVCPPSTRINGUTILS_H
#include "dvcppstringutils.h"
#define GUCEF_CORE_DVCPPSTRINGUTILS_H
#endif /* GUCEF_CORE_DVCPPSTRINGUTILS_H ? */

#ifndef GUCEF_CORE_CIOACCESS_H
#include "CIOAccess.h"
#define GUCEF_CORE_CIOACCESS_H
#endif /* GUCEF_CORE_CIOACCESS_H ? */

#ifndef GUCEF_CORE_CILOGGINGFORMATTER_H
#include "gucefCORE_CILoggingFormatter.h"
#define GUCEF_CORE_CILOGGINGFORMATTER_H
#endif /* GUCEF_CORE_CILOGGINGFORMATTER_H ? */

#ifndef GUCEF_CORE_CCOREGLOBAL_H
#include "gucefCORE_CCoreGlobal.h"
#define GUCEF_CORE_CCOREGLOBAL_H
#endif /* GUCEF_CORE_CCOREGLOBAL_H ? */

#ifndef GUCEF_CORE_ESSENTIALS_H
#include "gucef_essentials.h"
#define GUCEF_CORE_ESSENTIALS_H
#endif /* GUCEF_CORE_ESSENTIALS_H ? */

#ifdef GUCEF_MSWIN_BUILD
#include <windows.h>
#include <wincon.h>          /* for COORD */
#include <conio.h>           /* need conio.h under WIN32 for clrscr() */
#endif /* GUCEF_MSWIN_BUILD ? */

#include "CMSWinConsoleLogger.h"

#ifdef GUCEF_MSWIN_BUILD
/*-------------------------------------------------------------------------//
//                                                                         //
//      NAMESPACE                                                          //
//                                                                         //
//-------------------------------------------------------------------------*/

namespace GUCEF {
namespace CORE {

/*-------------------------------------------------------------------------//
//                                                                         //
//      UTILITIES                                                          //
//                                                                         //
//-------------------------------------------------------------------------*/

CMSWinConsoleLogger::CMSWinConsoleLogger( void )
    : CIConsoleLogger()                          
    , m_minimalLogLevel( LOGLEVEL_BELOW_NORMAL )                       
    , m_formatForUiPurpose( false )              
    , m_consoleHandle( NULL )
    , m_ownedConsole( false )
    , m_logFormatter( CCoreGlobal::Instance()->GetLogManager().CreateDefaultLoggingFormatter() )
{GUCEF_TRACE;

    HWND consoleWindow = ::GetConsoleWindow();
    if ( NULL == consoleWindow )
    {
        ::AllocConsole();
        m_ownedConsole = true;
    }
    m_consoleHandle = ::GetStdHandle( STD_OUTPUT_HANDLE );

    //if ( consoleHandle != NULL )
    //{
    //    HMENU hMenu = ::GetSystemMenu( consoleHandle, FALSE);
    //    if (hMenu != NULL) DeleteMenu(hMenu, SC_CLOSE, MF_BYCOMMAND);
    //}
}

/*-------------------------------------------------------------------------*/

CMSWinConsoleLogger::~CMSWinConsoleLogger()
{GUCEF_TRACE;

    CCoreGlobal::Instance()->GetLogManager().RemoveLogger( this );
    FlushLog();

    if ( m_ownedConsole )
        ::FreeConsole();

    delete m_logFormatter;
    m_logFormatter = GUCEF_NULL;
}

/*-------------------------------------------------------------------------*/

void
CMSWinConsoleLogger::SetFormatAsConsoleUI( bool formatForUiPurpose )
{GUCEF_TRACE;
    
    m_formatForUiPurpose = formatForUiPurpose;
}

/*-------------------------------------------------------------------------*/
    
bool
CMSWinConsoleLogger::GetFormatAsConsoleUI( void ) const
{GUCEF_TRACE;

    return m_formatForUiPurpose;
}

/*-------------------------------------------------------------------------*/

void
CMSWinConsoleLogger::Log( const TLogMsgType logMsgType ,
                          const Int32 logLevel         ,
                          const CString& logMessage    ,
                          const UInt32 threadId        )
{GUCEF_TRACE;

    if ( !m_formatForUiPurpose )
    {
        if ( logLevel >= m_minimalLogLevel )
        {
            CString actualLogMsg( m_logFormatter->FormatLogMessage( logMsgType ,
                                                                    logLevel   ,
                                                                    logMessage ,
                                                                    threadId   ) + "\n" );

            DWORD charsWritten = 0;
            ::WriteConsoleA( m_consoleHandle, actualLogMsg.C_String(), (DWORD)actualLogMsg.Length(), &charsWritten, NULL );
        }
    }
    else
    {
        if ( logMsgType == CORE::CLogManager::LOG_CONSOLE )
        {
            DWORD charsWritten = 0;
            ::WriteConsoleA( m_consoleHandle, logMessage.C_String(), (DWORD)logMessage.Length(), &charsWritten, NULL );
        }
    }
}

/*-------------------------------------------------------------------------*/

void
CMSWinConsoleLogger::LogWithoutFormatting( const TLogMsgType logMsgType ,
                                           const Int32 logLevel         ,
                                           const CString& logMessage    ,
                                           const UInt32 threadId        )
{GUCEF_TRACE;

    if ( !m_formatForUiPurpose )
    {
        if ( logLevel >= m_minimalLogLevel || m_formatForUiPurpose )
        {
            DWORD charsWritten = 0;
            ::WriteConsoleA( m_consoleHandle, logMessage.C_String(), (DWORD)logMessage.Length(), &charsWritten, NULL );
        }
    }
    else
    {
        if ( logMsgType == CORE::CLogManager::LOG_CONSOLE )
        {
            DWORD charsWritten = 0;
            ::WriteConsoleA( m_consoleHandle, logMessage.C_String(), (DWORD)logMessage.Length(), &charsWritten, NULL );
        }
    }
}

/*-------------------------------------------------------------------------*/

void
CMSWinConsoleLogger::FlushLog( void )
{GUCEF_TRACE;

    ::FlushConsoleInputBuffer( m_consoleHandle );
}

/*-------------------------------------------------------------------------*/

void
CMSWinConsoleLogger::SetMinimalLogLevel( const Int32 minimalLogLevel )
{GUCEF_TRACE;

    m_minimalLogLevel = minimalLogLevel;
}

/*-------------------------------------------------------------------------*/

Int32
CMSWinConsoleLogger::GetMinimalLogLevel( void ) const
{GUCEF_TRACE;

    return m_minimalLogLevel;
}

/*-------------------------------------------------------------------------//
//                                                                         //
//      NAMESPACE                                                          //
//                                                                         //
//-------------------------------------------------------------------------*/

}; /* namespace CORE */
}; /* namespace GUCEF */

/*-------------------------------------------------------------------------*/
#endif /* GUCEF_MSWIN_BUILD ? */
