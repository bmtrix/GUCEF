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

#ifndef GUCEF_CORE_ESSENTIALS_H
#include "gucef_essentials.h"
#define GUCEF_CORE_ESSENTIALS_H
#endif /* GUCEF_CORE_ESSENTIALS_H ? */

#ifndef GUCEF_CORE_CTIMER_H
#include "CTimer.h"
#define GUCEF_CORE_CTIMER_H
#endif /* GUCEF_CORE_CTIMER_H ? */

#include "gucefCORE_CDirectoryWatcher.h"

#if GUCEF_PLATFORM == GUCEF_PLATFORM_MSWIN

    #include <windows.h>
    #include <shlwapi.h>

    #pragma comment(lib, "shlwapi.lib")

#endif /* GUCEF_PLATFORM == GUCEF_PLATFORM_MSWIN ? */

#if ( GUCEF_PLATFORM == GUCEF_PLATFORM_LINUX )



#endif /* GUCEF_PLATFORM == GUCEF_PLATFORM_LINUX ? */

/*-------------------------------------------------------------------------//
//                                                                         //
//      NAMESPACE                                                          //
//                                                                         //
//-------------------------------------------------------------------------*/

namespace GUCEF {
namespace CORE {

/*-------------------------------------------------------------------------//
//                                                                         //
//      GLOBAL VARS                                                        //
//                                                                         //
//-------------------------------------------------------------------------*/

const CEvent CDirectoryWatcher::StartedWatchingDirectoryEvent       = "GUCEF::CORE::CDirectoryWatcher::StartedWatchingDirectoryEvent";
const CEvent CDirectoryWatcher::StoppedWatchingDirectoryEvent       = "GUCEF::CORE::CDirectoryWatcher::StoppedWatchingDirectoryEvent";
const CEvent CDirectoryWatcher::FileCreatedEvent                    = "GUCEF::CORE::CDirectoryWatcher::FileCreatedEvent";
const CEvent CDirectoryWatcher::FileModifiedEvent                   = "GUCEF::CORE::CDirectoryWatcher::FileModifiedEvent";
const CEvent CDirectoryWatcher::FileRenamedEvent                    = "GUCEF::CORE::CDirectoryWatcher::FileRenamedEvent";
const CEvent CDirectoryWatcher::FileDeletedEvent                    = "GUCEF::CORE::CDirectoryWatcher::FileDeletedEvent";

/*-------------------------------------------------------------------------//
//                                                                         //
//      IMPLEMENTATION                                                     //
//                                                                         //
//-------------------------------------------------------------------------*/

#if GUCEF_PLATFORM == GUCEF_PLATFORM_MSWIN

/*-------------------------------------------------------------------------*/

class GUCEF_HIDDEN OSSpecificDirectoryWatcher : public CObserver
{
    public:

    typedef CTEventHandlerFunctor< OSSpecificDirectoryWatcher > TEventCallback;
    typedef CDirectoryWatcher::CDirWatchOptions CDirWatchOptions;


    class GUCEF_HIDDEN OverlappedIOCallbackObj
    {
        public:

        OSSpecificDirectoryWatcher* watcherObj;
        OVERLAPPED overlappedIO;
        CDynamicBuffer notifyBuffer;
        HANDLE dirHandle;
        std::wstring dirPathW;
        CString dirPath;
        DWORD notifyFilter;
        CDirWatchOptions watchOptions;

        OverlappedIOCallbackObj( void )
            : watcherObj( GUCEF_NULL )
            , overlappedIO()
            , notifyBuffer()
            , dirHandle( GUCEF_NULL )
            , dirPathW()
            , dirPath()
            , notifyFilter( 0 )
            , watchOptions()
        {GUCEF_TRACE;

            notifyBuffer.SetBufferSize( 64 * 1024 );
            ::ZeroMemory( &overlappedIO, sizeof(overlappedIO) );
            overlappedIO.hEvent = ::CreateEvent( NULL, FALSE, FALSE, NULL );
        }

        ~OverlappedIOCallbackObj()
        {GUCEF_TRACE;

            if ( NULL != overlappedIO.hEvent )
            {
                ::CloseHandle( overlappedIO.hEvent );
                overlappedIO.hEvent = NULL;
            }
        }
    };

    typedef std::map< std::wstring, OverlappedIOCallbackObj > OverlappedIOCallbackObjMap;

    CTimer m_osPollingTimer;
    CDirectoryWatcher* m_wrapper;
    OverlappedIOCallbackObjMap m_dirsToWatch;

    DWORD OptionsToNotifyFilter( const CDirWatchOptions& options ) const
    {GUCEF_TRACE;

        DWORD notifyFilter = 0;
        if ( options.watchForFileRenames || options.watchForFileCreation || options.watchForFileDeletion )
            notifyFilter |= FILE_NOTIFY_CHANGE_FILE_NAME | FILE_NOTIFY_CHANGE_CREATION;
        if ( options.watchForFileModifications )
            notifyFilter |= FILE_NOTIFY_CHANGE_SIZE | FILE_NOTIFY_CHANGE_ATTRIBUTES | FILE_NOTIFY_CHANGE_LAST_WRITE | FILE_NOTIFY_CHANGE_LAST_ACCESS | FILE_NOTIFY_CHANGE_SECURITY;
        return notifyFilter;
    }

    bool RequestDirChangeNotifications( OverlappedIOCallbackObj& watchObj )
    {GUCEF_TRACE;

        // This call needs to be reissued after every APC.
        DWORD dwBytes=0;
        BOOL success = ::ReadDirectoryChangesW( watchObj.dirHandle,                                // handle to directory
                                                watchObj.notifyBuffer.GetBufferPtr(),              // read results buffer
                                                watchObj.notifyBuffer.GetBufferSize(),             // length of buffer
                                                watchObj.watchOptions.watchSubTree ? TRUE : FALSE, // monitoring option
                                                watchObj.notifyFilter,                             // filter conditions
                                                &dwBytes,                                          // bytes returned if not using overlapped I/O. In this case its a dummy.
                                                &watchObj.overlappedIO,                            // overlapped buffer
                                                NULL );                                            // completion routine, we use a waitable event instead

        if ( success != TRUE )
        {
            DWORD error = GetLastError();
            GUCEF_ERROR_LOG( LOGLEVEL_NORMAL, "OSSpecificDirectoryWatcher:RequestDirChangeNotifications: Failed to set change notification watch for dir \"" + watchObj.dirPath + "\". ErrorCode=" + CORE::UInt32ToString( error ) );
        }
        return success == TRUE;
    }

    bool AddDirToWatch( const CString& dirToWatch       ,
                        const CDirWatchOptions& options )
    {GUCEF_TRACE;

        if ( !DirExists( dirToWatch ) )
        {
            GUCEF_ERROR_LOG( LOGLEVEL_NORMAL, "OSSpecificDirectoryWatcher:AddDirToWatch: Unable to watch dir because it cannot be accessed or doesnt exist. Dir: " + dirToWatch );
            return false;
        }

        std::wstring dirToWatchW;
        if ( !Utf8toUtf16( dirToWatch, dirToWatchW ) )
            return false;

        HANDLE dirHandle = ::CreateFileW( dirToWatchW.c_str(),
                                          FILE_LIST_DIRECTORY,
                                          FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
                                          NULL,
                                          OPEN_EXISTING,
                                          FILE_FLAG_BACKUP_SEMANTICS | FILE_FLAG_OVERLAPPED,
                                          NULL                      );
        if ( INVALID_HANDLE_VALUE == dirHandle )
        {
            DWORD error = GetLastError();
            GUCEF_ERROR_LOG( LOGLEVEL_NORMAL, "OSSpecificDirectoryWatcher:AddDirToWatch: Failed to obtain watch handle for dir \"" + dirToWatch + "\". ErrorCode=" + CORE::UInt32ToString( error ) );
            return false;
        }

        OverlappedIOCallbackObj& watchObj = m_dirsToWatch[ dirToWatchW ];
        watchObj.dirHandle = dirHandle;
        watchObj.dirPathW = dirToWatchW;
        watchObj.dirPath = dirToWatch;
        watchObj.notifyFilter = OptionsToNotifyFilter( options );
        watchObj.watchOptions = options;
        watchObj.watcherObj = this;

        if ( RequestDirChangeNotifications( watchObj ) )
        {
            GUCEF_SYSTEM_LOG( LOGLEVEL_NORMAL, "OSSpecificDirectoryWatcher:AddDirToWatch: Started watching dir: " + dirToWatch );
            m_osPollingTimer.SetEnabled( true );
            return true;
        }

        m_dirsToWatch.erase( dirToWatchW );
        ::CloseHandle( dirHandle );
        return false;
    }

    bool RemoveDirToWatch( const CString& dirToWatch )
    {GUCEF_TRACE;

        std::wstring dirToWatchW;
        if ( !Utf8toUtf16( dirToWatch, dirToWatchW ) )
            return false;

        OverlappedIOCallbackObjMap::iterator i = m_dirsToWatch.find( dirToWatchW );
        if ( i != m_dirsToWatch.end() )
        {
            OverlappedIOCallbackObj& watchObj = (*i).second;
            ::CloseHandle( watchObj.dirHandle );

            std::string dir;
            Utf16toUtf8( (*i).first, dir );
            GUCEF_SYSTEM_LOG( LOGLEVEL_NORMAL, "OSSpecificDirectoryWatcher:RemoveDirToWatch: Stopped watching dir: " + dir );

            m_dirsToWatch.erase( i );
            return true;
        }
        return false;
    }

    bool RemoveAllWatches( void )
    {GUCEF_TRACE;

        while ( !m_dirsToWatch.empty() )
        {
            OverlappedIOCallbackObjMap::iterator i = m_dirsToWatch.begin();
            OverlappedIOCallbackObj& watchObj = (*i).second;
            ::CloseHandle( watchObj.dirHandle );

            std::string dir;
            Utf16toUtf8( (*i).first, dir );
            GUCEF_SYSTEM_LOG( LOGLEVEL_NORMAL, "OSSpecificDirectoryWatcher:RemoveAllWatches: Stopped watching dir: " + dir );

            m_dirsToWatch.erase( i );
        }
        return true;
    }

    void ProcessNotifications( OverlappedIOCallbackObj& watchObj )
    {GUCEF_TRACE;

        BYTE* pBase = (BYTE*) watchObj.notifyBuffer.GetBufferPtr();

        std::string utf8OldFilenameBeforeRename;
        for (;;)
        {
            FILE_NOTIFY_INFORMATION& fni = (FILE_NOTIFY_INFORMATION&)*pBase;

            std::wstring filename( fni.FileName, fni.FileNameLength/sizeof(wchar_t) );

            // Handle a trailing backslash, such as for a root directory.
            if ( watchObj.dirPathW.size() > 1 && watchObj.dirPath[ watchObj.dirPathW.size()-1 ] != L'\\' )
                filename = watchObj.dirPathW + L'\\' + filename;
            else
                filename = watchObj.dirPathW + filename;

            // If it could be a short filename, expand it.
            LPCWSTR wszFilename = PathFindFileNameW( filename.c_str() );
            int len = lstrlenW( wszFilename );

            // The maximum length of an 8.3 filename is twelve, including the dot.
            if ( len <= 12 && wcschr( filename.c_str(), L'~') )
            {
                // Convert to the long filename form. Unfortunately, this
                // does not work for deletions, so it's an imperfect fix.
                wchar_t wbuf[ MAX_PATH ];
                if ( ::GetLongPathNameW( filename.c_str(), wbuf, _countof(wbuf) ) > 0 )
                    filename = wbuf;
            }

            std::string utf8Filename;
            if ( Utf16toUtf8( filename, utf8Filename ) )
            {
                switch ( fni.Action )
                {
                    case FILE_ACTION_ADDED :
                    {
                        GUCEF_SYSTEM_LOG( LOGLEVEL_BELOW_NORMAL, "OSSpecificDirectoryWatcher: OS Signaled FILE_ACTION_ADDED for file: " + utf8Filename );
                        if ( watchObj.watchOptions.watchForFileCreation )
                        {
                            CDirectoryWatcher::TFileCreatedEventData eData( utf8Filename );
                            if ( !m_wrapper->NotifyObservers( CDirectoryWatcher::FileCreatedEvent, &eData ) ) return;
                        }
                        break;
                    }
                    case FILE_ACTION_REMOVED :
                    {
                        GUCEF_SYSTEM_LOG( LOGLEVEL_BELOW_NORMAL, "OSSpecificDirectoryWatcher: OS Signaled FILE_ACTION_REMOVED for file: " + utf8Filename );
                        if ( watchObj.watchOptions.watchForFileDeletion )
                        {
                            CDirectoryWatcher::TFileDeletedEventData eData( utf8Filename );
                            if ( !m_wrapper->NotifyObservers( CDirectoryWatcher::FileDeletedEvent, &eData ) ) return;
                        }
                        break;
                    }
                    case FILE_ACTION_MODIFIED :
                    {
                        GUCEF_SYSTEM_LOG( LOGLEVEL_BELOW_NORMAL, "OSSpecificDirectoryWatcher: OS Signaled FILE_ACTION_MODIFIED for file: " + utf8Filename );
                        if ( watchObj.watchOptions.watchForFileModifications )
                        {
                            CDirectoryWatcher::TFileModifiedEventData eData( utf8Filename );
                            if ( !m_wrapper->NotifyObservers( CDirectoryWatcher::FileModifiedEvent, &eData ) ) return;
                        }
                        break;
                    }
                    case FILE_ACTION_RENAMED_OLD_NAME :
                    {
                        GUCEF_SYSTEM_LOG( LOGLEVEL_BELOW_NORMAL, "OSSpecificDirectoryWatcher: OS Signaled FILE_ACTION_RENAMED_OLD_NAME for file: " + utf8Filename );
                        if ( watchObj.watchOptions.watchForFileRenames )
                        {
                            utf8OldFilenameBeforeRename = utf8Filename;
                        }
                        break;
                    }
                    case FILE_ACTION_RENAMED_NEW_NAME :
                    {
                        GUCEF_SYSTEM_LOG( LOGLEVEL_BELOW_NORMAL, "OSSpecificDirectoryWatcher: OS Signaled FILE_ACTION_RENAMED_NEW_NAME for file: " + utf8Filename );
                        if ( watchObj.watchOptions.watchForFileRenames )
                        {
                            struct CDirectoryWatcher::SFileRenamedEventInfo info = { utf8OldFilenameBeforeRename, utf8Filename };
                            CDirectoryWatcher::TFileRenamedEventData eData( info );
                            if ( !m_wrapper->NotifyObservers( CDirectoryWatcher::FileRenamedEvent, &eData ) ) return;
                            utf8OldFilenameBeforeRename.clear();
                        }
                        break;
                    }
                }
            }

            if ( 0 == fni.NextEntryOffset )
                break;
            pBase += fni.NextEntryOffset;
        }
    }

    void RegisterEventHandlers( void )
    {GUCEF_TRACE;

        TEventCallback callback( this, &OSSpecificDirectoryWatcher::OnDirWatchPollingCycle );
        SubscribeTo( &m_osPollingTimer              ,
                     CORE::CTimer::TimerUpdateEvent ,
                     callback                       );
    }

    void OnDirWatchPollingCycle( CORE::CNotifier* notifier    ,
                                 const CORE::CEvent& eventId  ,
                                 CORE::CICloneable* eventData )
    {GUCEF_TRACE;

        OverlappedIOCallbackObjMap::iterator i = m_dirsToWatch.begin();
        while ( i != m_dirsToWatch.end() )
        {
            OverlappedIOCallbackObj& watchObj = (*i).second;
            DWORD waitResult = ::WaitForSingleObject( watchObj.overlappedIO.hEvent, 0 );
            if ( WAIT_OBJECT_0 == waitResult )
            {
                GUCEF_SYSTEM_LOG( LOGLEVEL_BELOW_NORMAL, "OSSpecificDirectoryWatcher: OS Signaled an overlapped IO event" );

                DWORD numberOfBytesTransferred = 0;
                if ( TRUE == ::GetOverlappedResult( watchObj.dirHandle, &watchObj.overlappedIO, &numberOfBytesTransferred, TRUE ) )
                {
                    // Check if we overflowed the notification buffer
                    // Sadly this means the notifications that were sent are now gone if this happens.
                    if ( 0 != numberOfBytesTransferred )
                    {
                        RequestDirChangeNotifications( watchObj );
                        ProcessNotifications( watchObj );
                    }
                    else
                    {
                        GUCEF_WARNING_LOG( LOGLEVEL_IMPORTANT, "OSSpecificDirectoryWatcher: The event buffer was not large enough (" +
                                CORE::UInt32ToString( watchObj.notifyBuffer.GetBufferSize() ) + " bytes) to hold all the OS notifications. Event notifications have been lost! Auto-enlarging the buffer x2" );

                        watchObj.notifyBuffer.SetBufferSize( watchObj.notifyBuffer.GetBufferSize() * 2 );
                        RequestDirChangeNotifications( watchObj );
                    }
                }
            }
            ++i;
        }
    }

    OSSpecificDirectoryWatcher( CDirectoryWatcher* wrapper )
        : m_osPollingTimer()
        , m_wrapper( wrapper )
    {GUCEF_TRACE;

        RegisterEventHandlers();
    }

    OSSpecificDirectoryWatcher( CDirectoryWatcher* wrapper      ,
                                CPulseGenerator& pulseGenerator )
        : m_osPollingTimer( pulseGenerator )
        , m_wrapper( wrapper )
    {GUCEF_TRACE;

        RegisterEventHandlers();
    }

    ~OSSpecificDirectoryWatcher()
    {GUCEF_TRACE;

        RemoveAllWatches();
    }
};

/*-------------------------------------------------------------------------*/

#elif ( GUCEF_PLATFORM == GUCEF_PLATFORM_LINUX )

/*-------------------------------------------------------------------------*/

// @TODO: Implement this
class GUCEF_HIDDEN OSSpecificDirectoryWatcher
{
    public:

    typedef CDirectoryWatcher::CDirWatchOptions CDirWatchOptions;

    bool AddDirToWatch( const CString& dirToWatch       ,
                        const CDirWatchOptions& options )
    {GUCEF_TRACE;
        return false;
    }

    bool RemoveDirToWatch( const CString& dirToWatch )
    {GUCEF_TRACE;
        return false;
    }

    bool RemoveAllWatches( void )
    {GUCEF_TRACE;
        return false;
    }

    OSSpecificDirectoryWatcher( CDirectoryWatcher* wrapper )
    {GUCEF_TRACE;

    }

    OSSpecificDirectoryWatcher( CDirectoryWatcher* wrapper      ,
                                CPulseGenerator& pulseGenerator )
    {GUCEF_TRACE;

    }
};

/*-------------------------------------------------------------------------*/

#else

/*-------------------------------------------------------------------------*/

// Dummy that doesnt do anything as a catch all for unsupported OS
class GUCEF_HIDDEN OSSpecificDirectoryWatcher
{
    public:

    typedef CDirectoryWatcher::CDirWatchOptions CDirWatchOptions;

    bool AddDirToWatch( const CString& dirToWatch       ,
                        const CDirWatchOptions& options )
    {GUCEF_TRACE;
        return false;
    }

    bool RemoveDirToWatch( const CString& dirToWatch )
    {GUCEF_TRACE;
        return false;
    }

    bool RemoveAllWatches( void )
    {GUCEF_TRACE;
        return false;
    }

    OSSpecificDirectoryWatcher( CDirectoryWatcher* wrapper )
    {GUCEF_TRACE;

    }

    OSSpecificDirectoryWatcher( CDirectoryWatcher* wrapper      ,
                                CPulseGenerator& pulseGenerator )
    {GUCEF_TRACE;

    }
};

/*-------------------------------------------------------------------------*/

#endif

/*-------------------------------------------------------------------------*/

CDirectoryWatcher::CDirWatchOptions::CDirWatchOptions( void )
    : watchSubTree( false )
    , watchForFileCreation( true )
    , watchForFileDeletion( true )
    , watchForFileRenames( true )
    , watchForFileModifications( true )
{GUCEF_TRACE;

}

/*-------------------------------------------------------------------------*/

CDirectoryWatcher::CDirWatchOptions::CDirWatchOptions( const CDirectoryWatcher::CDirWatchOptions& src )
    : watchSubTree( src.watchSubTree )
    , watchForFileCreation( src.watchForFileCreation )
    , watchForFileDeletion( src.watchForFileDeletion )
    , watchForFileRenames( src.watchForFileRenames )
    , watchForFileModifications( src.watchForFileModifications )
{GUCEF_TRACE;

}

/*-------------------------------------------------------------------------*/

CDirectoryWatcher::CDirWatchOptions&
CDirectoryWatcher::CDirWatchOptions::operator=( const CDirectoryWatcher::CDirWatchOptions& src )
{GUCEF_TRACE;

    if ( this != &src )
    {
        watchSubTree = src.watchSubTree;
        watchForFileCreation = src.watchForFileCreation;
        watchForFileDeletion = src.watchForFileDeletion;
        watchForFileRenames = src.watchForFileRenames;
        watchForFileModifications = src.watchForFileModifications;
    }
    return *this;
}

/*-------------------------------------------------------------------------*/

void
CDirectoryWatcher::RegisterEvents( void )
{GUCEF_TRACE;

    StartedWatchingDirectoryEvent.Initialize();
    StoppedWatchingDirectoryEvent.Initialize();
    FileCreatedEvent.Initialize();
    FileModifiedEvent.Initialize();
    FileRenamedEvent.Initialize();
    FileDeletedEvent.Initialize();
}

/*-------------------------------------------------------------------------*/

bool
CDirectoryWatcher::AddDirToWatch( const CString& dirToWatch       ,
                                  const CDirWatchOptions& options )
{GUCEF_TRACE;

    if ( GUCEF_NULL != m_osSpecificImpl )
        return m_osSpecificImpl->AddDirToWatch( dirToWatch, options );
    else
        return false;
}

/*-------------------------------------------------------------------------*/

bool
CDirectoryWatcher::RemoveDirToWatch( const CString& dirToWatch )
{GUCEF_TRACE;

    if ( GUCEF_NULL != m_osSpecificImpl )
        return m_osSpecificImpl->RemoveDirToWatch( dirToWatch );
    else
        return false;
}

/*-------------------------------------------------------------------------*/

bool
CDirectoryWatcher::RemoveAllWatches( void )
{GUCEF_TRACE;

    if ( GUCEF_NULL != m_osSpecificImpl )
        return m_osSpecificImpl->RemoveAllWatches();
    else
        return false;
}

/*-------------------------------------------------------------------------*/

CDirectoryWatcher::CDirectoryWatcher( void )
    : CObservingNotifier()
    , m_osSpecificImpl( new OSSpecificDirectoryWatcher( this ) )
{GUCEF_TRACE;

    RegisterEvents();
}

/*-------------------------------------------------------------------------*/

CDirectoryWatcher::CDirectoryWatcher( CPulseGenerator& pulseGenerator )
    : CObservingNotifier()
    , m_osSpecificImpl( new OSSpecificDirectoryWatcher( this, pulseGenerator ) )
{GUCEF_TRACE;

    RegisterEvents();
}

/*-------------------------------------------------------------------------*/

CDirectoryWatcher::~CDirectoryWatcher()
{GUCEF_TRACE;

    delete m_osSpecificImpl;
    m_osSpecificImpl = GUCEF_NULL;
}

/*-------------------------------------------------------------------------//
//                                                                         //
//      NAMESPACE                                                          //
//                                                                         //
//-------------------------------------------------------------------------*/

}; /* namespace CORE */
}; /* namespace GUCEF */

/*-------------------------------------------------------------------------*/
