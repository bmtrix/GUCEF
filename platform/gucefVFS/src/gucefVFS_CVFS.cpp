/*
 *  gucefVFS: GUCEF module implementing a Virtual File System
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
//      INCLUDE                                                            //
//                                                                         //
//-------------------------------------------------------------------------*/

#ifndef GUCEF_MT_CSCOPEMUTEX_H
#include "gucefMT_CScopeMutex.h"
#define GUCEF_MT_CSCOPEMUTEX_H
#endif /* GUCEF_MT_CSCOPEMUTEX_H ? */ 

#ifndef GUCEF_MT_COBJECTSCOPELOCK_H
#include "gucefMT_CObjectScopeLock.h"
#define GUCEF_MT_COBJECTSCOPELOCK_H
#endif /* GUCEF_MT_COBJECTSCOPELOCK_H ? */

#ifndef DVFILEUTILS_H
#include "dvfileutils.h"                /* Needed for dir itteration */
#define DVFILEUTILS_H
#endif /* DVFILEUTILS_H ? */

#ifndef DVCPPSTRINGUTILS_H
#include "dvcppstringutils.h"     
#define DVCPPSTRINGUTILS_H
#endif /* DVCPPSTRINGUTILS_H ? */

#ifndef GUCEF_CORE_CCOREGLOBAL_H
#include "gucefCORE_CCoreGlobal.h"
#define GUCEF_CORE_CCOREGLOBAL_H
#endif /* GUCEF_CORE_CCOREGLOBAL_H ? */

#ifndef GUCEF_CORE_CTASKMANAGER_H
#include "gucefCORE_CTaskManager.h"
#define GUCEF_CORE_CTASKMANAGER_H
#endif /* GUCEF_CORE_CTASKMANAGER_H ? */

#ifndef GUCEF_CORE_CDYNAMICBUFFER_H
#include "CDynamicBuffer.h"
#define GUCEF_CORE_CDYNAMICBUFFER_H
#endif /* GUCEF_CORE_CDYNAMICBUFFER_H ? */

#ifndef GUCEF_CORE_CDYNAMICBUFFERACCESS_H
#include "CDynamicBufferAccess.h"
#define GUCEF_CORE_CDYNAMICBUFFERACCESS_H
#endif /* GUCEF_CORE_CDYNAMICBUFFERACCESS_H ? */

#ifndef CMFILEACCESS_H
#include "CMFileAccess.h"
#define CMFILEACCESS_H
#endif /* CMFILEACCESS_H ? */

#ifndef CFILEACCESS_H
#include "CFileAccess.h"
#define CFILEACCESS_H
#endif /* CFILEACCESS_H ? */

#ifndef CDATANODE_H
#include "CDataNode.h"          /* node for data storage */
#define CDATANODE_H
#endif /* CDATANODE_H ? */

#ifndef GUCEF_CORE_CONFIGSTORE_H
#include "CConfigStore.h"
#define GUCEF_CORE_CONFIGSTORE_H
#endif /* GUCEF_CORE_CONFIGSTORE_H ? */

#ifndef DVCPPSTRINGUTILS_H
#include "dvcppstringutils.h"           /* C++ string utils */
#define DVCPPSTRINGUTILS_H
#endif /* DVCPPSTRINGUTILS_H ? */

#ifndef GUCEF_CORE_DVMD5UTILS_H
#include "dvmd5utils.h"
#define GUCEF_CORE_DVMD5UTILS_H
#endif /* GUCEF_CORE_DVMD5UTILS_H ? */

#ifndef GUCEF_VFS_CASYNCVFSOPERATION_H
#include "gucefVFS_CAsyncVfsOperation.h"
#define GUCEF_VFS_CASYNCVFSOPERATION_H
#endif /* GUCEF_VFS_CASYNCVFSOPERATION_H ? */

#include "gucefVFS_CVFS.h"           /* definition of the file implemented here */

#ifdef ACTIVATE_MEMORY_MANAGER
  #ifndef GUCEF_NEW_ON_H
  #include "gucef_new_on.h"   /* Use the GUCEF memory manager instead of the standard manager ? */
  #define GUCEF_NEW_ON_H
  #endif /* GUCEF_NEW_ON_H ? */
#endif /* ACTIVATE_MEMORY_MANAGER ? */

/*-------------------------------------------------------------------------//
//                                                                         //
//      NAMESPACE                                                          //
//                                                                         //
//-------------------------------------------------------------------------*/

namespace GUCEF {
namespace VFS {

/*-------------------------------------------------------------------------//
//                                                                         //
//      GLOBAL VARS                                                        //
//                                                                         //
//-------------------------------------------------------------------------*/

const CORE::CEvent CVFS::AsyncVfsOperationCompletedEvent = "GUCEF::VFS::CVFS::AsyncVfsOperationCompletedEvent";
const CORE::CString CVFS::FileSystemArchiveTypeName = "FileSystem";

/*-------------------------------------------------------------------------//
//                                                                         //
//      IMPLEMENTATION                                                     //
//                                                                         //
//-------------------------------------------------------------------------*/

void 
CVFS::RegisterEvents( void )
{GUCEF_TRACE;

    AsyncVfsOperationCompletedEvent.Initialize();
}

/*-------------------------------------------------------------------------*/

CVFS::CVFS( void )
    : CORE::CTSGNotifier()
    , CORE::CIConfigurable( true )
    , m_mountList()
    , _maxmemloadsize( 1024 ) 
    , m_abstractArchiveFactory()
    , m_fileSystemArchiveFactory()
    , m_delayMountedArchiveSettings()
{GUCEF_TRACE;

    RegisterEvents();
    RegisterEventHandlers();
    RegisterArchiveFactory( FileSystemArchiveTypeName, m_fileSystemArchiveFactory );
}

/*-------------------------------------------------------------------------*/

CVFS::~CVFS()
{GUCEF_TRACE;

    UnregisterArchiveFactory( FileSystemArchiveTypeName );
}

/*-------------------------------------------------------------------------*/

void
CVFS::RegisterEventHandlers( void )
{GUCEF_TRACE;

    // Success or fail we use the config load finish event messages to trigger delayed mounting
    TEventCallback callback( this, &CVFS::OnGlobalConfigLoadFinished );
    SubscribeTo( &CORE::CCoreGlobal::Instance()->GetConfigStore()   ,
                 CORE::CConfigStore::GlobalConfigLoadCompletedEvent ,
                 callback                                           );
    TEventCallback callback2( this, &CVFS::OnGlobalConfigLoadFinished );
    SubscribeTo( &CORE::CCoreGlobal::Instance()->GetConfigStore() ,
                 CORE::CConfigStore::GlobalConfigLoadFailedEvent  ,
                 callback2                                        );
}

/*-------------------------------------------------------------------------*/

bool 
CVFS::StoreAsFileAsync( const CORE::CString& filepath    ,
                        const CORE::CDynamicBuffer& data ,
                        const CORE::UInt64 offset        ,
                        const bool overwrite             ,
                        CORE::CICloneable* requestorData )
{GUCEF_TRACE;

    CStoreAsFileTaskData operationData;
    operationData.operationType = ASYNCVFSOPERATIONTYPE_STOREDATAASFILE;
    operationData.filepath = filepath;
    operationData.data.LinkTo( &data );
    operationData.offset = offset;
    operationData.overwrite = overwrite;
    operationData.SetRequestorData( requestorData );

    CORE::CCoreGlobal::Instance()->GetTaskManager().QueueTask( CAsyncVfsOperation::TaskType, &operationData, GUCEF_NULL, &AsObserver() );
    return true;
}

/*-------------------------------------------------------------------------*/

bool 
CVFS::MountArchiveAsync( const CArchiveSettings& settings ,
                         CORE::CICloneable* requestorData )
{GUCEF_TRACE;

    CMountArchiveTaskData operationData;
    operationData.operationType = ASYNCVFSOPERATIONTYPE_MOUNTARCHIVE;
    operationData.settings = settings;
    operationData.SetRequestorData( requestorData );

    CORE::CCoreGlobal::Instance()->GetTaskManager().QueueTask( CAsyncVfsOperation::TaskType, &operationData, GUCEF_NULL, &AsObserver() );
    return true;
}

/*-------------------------------------------------------------------------*/

void 
CVFS::OnPumpedNotify( CORE::CNotifier* notifier    ,
                      const CORE::CEvent& eventid  ,
                      CORE::CICloneable* eventdata )
{GUCEF_TRACE;

    if ( CAsyncVfsOperation::AsyncVfsOperationCompletedEvent == eventid )
    {
        GUCEF_DEBUG_LOG( CORE::LOGLEVEL_BELOW_NORMAL, "CVFS:OnPumpedNotify: Async operation completed, passing on event notification" );
        NotifyObservers( AsyncVfsOperationCompletedEvent, eventdata );
    }
}

/*-------------------------------------------------------------------------*/

void 
CVFS::MountAllDelayMountedArchives( void )
{GUCEF_TRACE;

    while ( !m_delayMountedArchiveSettings.empty() )
    {
        TArchiveSettingsVector::iterator i = m_delayMountedArchiveSettings.begin();
        GUCEF_SYSTEM_LOG( CORE::LOGLEVEL_BELOW_NORMAL, "CVFS:MountAllDelayMountedArchives: Commencing delayed mounting of archive with name: " + (*i).GetArchiveName() );
        if ( MountArchive( (*i) ) )
        {
            GUCEF_SYSTEM_LOG( CORE::LOGLEVEL_BELOW_NORMAL, "CVFS:MountAllDelayMountedArchives: Succeeded in delayed mounting of archive with name: " + (*i).GetArchiveName() );
        }
        else
        {
            GUCEF_ERROR_LOG( CORE::LOGLEVEL_BELOW_NORMAL, "CVFS:MountAllDelayMountedArchives: Failed delayed mounting of archive with name: " + (*i).GetArchiveName() );
        }
        m_delayMountedArchiveSettings.erase( i );
    }
}

/*-------------------------------------------------------------------------*/

void 
CVFS::OnGlobalConfigLoadFinished( CORE::CNotifier* notifier    ,
                                  const CORE::CEvent& eventid  ,
                                  CORE::CICloneable* eventdata )
{GUCEF_TRACE;

    MountAllDelayMountedArchives();
}

/*-------------------------------------------------------------------------*/

bool 
CVFS::StoreAsFile( const CORE::CString& filepath    ,
                   const CORE::CDynamicBuffer& data ,
                   const CORE::UInt64 offset        ,
                   const bool overwrite             )
{GUCEF_TRACE;

    MT::CObjectScopeLock lock( this );
    
    // Get a list of all eligable mounts
    TConstMountLinkVector mountLinks;
    GetEligableMounts( filepath, true, mountLinks );

    // Try to store using the available archives
    TConstMountLinkVector::iterator i = mountLinks.begin();
    while ( i != mountLinks.end() )
    {
        TConstMountLink& mountLink = (*i);

        if ( mountLink.mountEntry->archive->StoreAsFile( mountLink.remainder  ,
                                                         data                 ,
                                                         offset               ,
                                                         overwrite            ) )
        {
            GUCEF_DEBUG_LOG( CORE::LOGLEVEL_NORMAL, "Vfs: Stored " + CORE::UInt32ToString( data.GetDataSize() )  +
                    " bytes as file content at offset " + CORE::UInt64ToString( offset ) + " using archive mounted at: " + mountLink.remainder );
            return true;
        }
        else
        {
            GUCEF_DEBUG_LOG( CORE::LOGLEVEL_NORMAL, "Vfs: Stored " + CORE::UInt32ToString( data.GetDataSize() )  +
                    " bytes as file content at offset " + CORE::UInt64ToString( offset ) + " using archive mounted at: " + mountLink.remainder );
        }

        ++i;
    }

    if ( mountLinks.empty() )
    {
        GUCEF_DEBUG_LOG( CORE::LOGLEVEL_NORMAL, "Vfs: Unable to store " + CORE::UInt32ToString( data.GetDataSize() )  +
                " bytes as file content at offset " + CORE::UInt64ToString( offset ) + ". No eligible archives mounted" );
    }
    return false;
}

/*-------------------------------------------------------------------------*/

CVFS::CVFSHandlePtr
CVFS::GetFile( const CORE::CString& file          ,
               const char* mode /* = "rb" */      ,
               const bool overwrite /* = false */ )
{GUCEF_TRACE;

    CString filepath( file.ReplaceChar( GUCEF_DIRSEPCHAROPPOSITE, GUCEF_DIRSEPCHAR ) );
    bool fileMustExist = *mode == 'r';

    MT::CObjectScopeLock lock( this );
    
    // Get a list of all eligable mounts
    TConstMountLinkVector mountLinks;
    GetEligableMounts( filepath, overwrite, mountLinks );

    // Find the file in the available archives
    TConstMountLinkVector::iterator i = mountLinks.begin();
    while ( i != mountLinks.end() )
    {
        TConstMountLink& mountLink = (*i);

        bool tryToGetFile = true;
        if ( fileMustExist )
        {
            if ( !mountLink.mountEntry->archive->FileExists( mountLink.remainder ) )
            {
                tryToGetFile = false;
            }
        }

        if ( tryToGetFile )
        {
            GUCEF_DEBUG_LOG( CORE::LOGLEVEL_NORMAL, "Vfs: Found requested file using mount link remainder: " + mountLink.remainder );
            CVFSHandlePtr filePtr = mountLink.mountEntry->archive->GetFile( mountLink.remainder ,
                                                                            mode                ,
                                                                            _maxmemloadsize     ,
                                                                            overwrite           );

            if ( NULL == filePtr )
            {
                GUCEF_ERROR_LOG( CORE::LOGLEVEL_BELOW_NORMAL, "Vfs: Requested file exists but could not be loaded using mount link remainder: " + mountLink.remainder );
            }
            return filePtr;
        }

        ++i;
    }

    // Unable to load file
    GUCEF_ERROR_LOG( CORE::LOGLEVEL_BELOW_NORMAL, "Vfs: Unable to locate a mount which can provide the file: " + file );
    return CVFSHandlePtr();
}

/*-------------------------------------------------------------------------*/

bool
CVFS::MountArchive( const CString& archiveName  ,
                    const CString& archivePath  ,
                    const bool writeableRequest )
{GUCEF_TRACE;

    // Mount the archive using the archive path
    return MountArchive( archiveName      ,
                         archivePath      ,
                         archivePath      ,
                         writeableRequest );
}

/*-------------------------------------------------------------------------*/

bool
CVFS::MountArchive( const CString& archiveName  ,
                    const CString& archivePath  ,
                    const CString& mountPoint   ,
                    const bool writeableRequest )
{GUCEF_TRACE;

    // Use the archive file extension as the archive type
    CString archiveType( archivePath.SubstrToChar( '.', false ) );
    return MountArchive( archiveName      ,
                         archivePath      ,
                         archiveType      ,
                         mountPoint       ,
                         writeableRequest ,
                         false            );
}

/*-------------------------------------------------------------------------*/

bool
CVFS::MountArchive( const CString& archiveName              ,
                    const CString& archivePath              ,
                    const CString& archiveType              ,
                    const CString& mountPoint               ,
                    const bool writeableRequest             ,
                    const bool autoMountSubArchives         ,
                    const CString& actualNonVfsPathOverride )
{GUCEF_TRACE;

    CArchiveSettings settings;
    settings.SetActualArchivePath( actualNonVfsPathOverride );
    settings.SetArchiveName( archiveName );
    settings.SetArchivePath( archivePath );
    settings.SetArchiveType( archiveType );
    settings.SetAutoMountSubArchives( autoMountSubArchives );
    settings.SetMountPath( mountPoint );
    settings.SetWriteableRequested( writeableRequest );
    return MountArchive( settings );
}

/*-------------------------------------------------------------------------*/

bool 
CVFS::DelayMountArchive( const CArchiveSettings& settings )
{GUCEF_TRACE;

    MT::CObjectScopeLock lock( this );
    m_delayMountedArchiveSettings.push_back( settings );
    return true;
}

/*-------------------------------------------------------------------------*/

bool 
CVFS::MountArchive( const CArchiveSettings& settings )
{GUCEF_TRACE;

    MT::CObjectScopeLock lock( this );

    // Either determine the actual non-vfs path based on previously loaded/mounted archives or use the given explicit path if any
    CString actualArchivePath = settings.GetActualArchivePath();
    if ( !actualArchivePath.IsNULLOrEmpty() || GetActualFilePath( settings.GetArchivePath(), actualArchivePath ) )
    {
        // Found a compatible type,.. create an archive for the type
        CIArchive* archive = m_abstractArchiveFactory.Create( settings.GetArchiveType() );
        if ( NULL != archive )
        {
            // Try to load from the resource
            CArchiveSettings updatedSettings( settings );
            if ( actualArchivePath != settings.GetActualArchivePath() )
                updatedSettings.SetActualArchivePath( actualArchivePath );

            if ( archive->LoadArchive( updatedSettings ) )
            {
                // Successfully loaded/linked the archive
                // We will add it to our mount list
                TMountEntry archiveEntry;
                archiveEntry.abspath = actualArchivePath;

                //// Get the path where the archive is located relative to the root mount
                //archiveEntry.path = archiveEntry.abspath.CutChars( mountEntry.abspath.Length(), true );

                //// Git rid of any directory seperator prefix
                //if ( archiveEntry.path.Length() > 0 )
                //{
                //    if ( ( archiveEntry.path[ 0 ] == '\\' ) ||
                //            ( archiveEntry.path[ 0 ] == '/' )   )
                //    {
                //        archiveEntry.path = archiveEntry.path.CutChars( 1, true );
                //    }
                //}

                archiveEntry.path = actualArchivePath;
                archiveEntry.writeable = settings.GetWriteableRequested();
                archiveEntry.archive = archive;
                archiveEntry.mountPath = settings.GetMountPath();

                m_mountList.push_back( archiveEntry );
                return true;
            }
            else
            {
                delete archive;
            }
        }
    }

    return false;
}

/*-------------------------------------------------------------------------*/

bool 
CVFS::MountArchive( const CString& archiveName    ,
                    CVFSHandlePtr archiveResource ,
                    const CString& archiveType    ,
                    const CString& mountPoint     ,
                    const bool writeableRequest   )
{GUCEF_TRACE;

    if ( archiveResource.IsNULL() )
        return false;
    
    MT::CObjectScopeLock lock( this );
    
    // create an archive for the type
    CIArchive* archive = m_abstractArchiveFactory.Create( archiveType );
    if ( GUCEF_NULL != archive )
    {
        // Try to load from the resource
        if ( archive->LoadArchive( archiveName      ,
                                   archiveResource  ,
                                   writeableRequest ) )
        {
            // Successfully loaded/linked the archive
            // We will add it to our mount list
            TMountEntry archiveEntry;
            archiveEntry.path = archiveResource->GetFilename();
            archiveEntry.abspath = archiveResource->GetFilePath();
            archiveEntry.writeable = writeableRequest;
            archiveEntry.archive = archive;
            archiveEntry.mountPath = mountPoint;

            m_mountList.push_back( archiveEntry );
            return true;
        }
        else
        {
            delete archive;
        }
    }

    return false;
}

/*-------------------------------------------------------------------------*/

bool
CVFS::IsMountedArchive( const CString& location ) const
{GUCEF_TRACE;

    MT::CObjectScopeLock lock( this );

    TMountVector::const_iterator i = m_mountList.begin();
    while ( i != m_mountList.end() )
    {
        const TMountEntry& archiveEntry = (*i);
        if ( archiveEntry.mountPath == location )
        {
            return true;
        }
        ++i;
    }

    return false;
}

/*-------------------------------------------------------------------------*/

void
CVFS::GetMountedArchiveList( const CString& location ,
                             const CString& filter   ,
                             const bool recursive    ,
                             TStringSet& outputList  ) const
{GUCEF_TRACE;

    MT::CObjectScopeLock lock( this );

    TMountVector::const_iterator i = m_mountList.begin();
    while ( i != m_mountList.end() )
    {
        const TMountEntry& archiveEntry = (*i);

        if ( archiveEntry.mountPath.Length() > 0 )
        {
            // Check if the location is a root for the mount path
            Int32 subSection = archiveEntry.mountPath.HasSubstr( location, true );
            if ( 0 == subSection )
            {
                // We now know the archive is mounted in either the root of "location"
                // or a sub directory
                if ( !recursive )
                {
                    // Check if we have multiple subdirs beyond the "location" to get to
                    // the archive. If so then we cannot add this archive because recursive
                    // searching is not allowed.
                    CString remainder = archiveEntry.mountPath.CutChars( subSection, true );
                    if ( remainder.Length() > 0 )
                    {
                        // make sure we are using a single directory seperator scheme
                        remainder = remainder.ReplaceChar( '\\', '/' );

                        // Dont count a starting directory seperator
                        if ( remainder[ 0 ] == '/' )
                        {
                            remainder = remainder.CutChars( 1, true );
                        }

                        Int32 dirDelimter = remainder.HasChar( '/', true );
                        if ( dirDelimter > -1 )
                        {
                            // We found a directory seperator so now me must check if it happens
                            // to be the last character
                            if ( remainder.Length() != dirDelimter+1 )
                            {
                                // The directory seperator was not the last character so we have multiple
                                // sub-dirs which is not allowed, we cannot add this item
                                ++i;
                                continue;
                            }
                        }
                    }
                }

                // Now we must validate the filename with the given filter
                CString filename = GUCEF::CORE::ExtractFilename( archiveEntry.mountPath );
                if ( FilterValidation( filename ,
                                       filter   ) )
                {
                    // Everything checks out, we have found a mounted archive that meets
                    // the criterea so we add it to the list
                    outputList.insert( archiveEntry.mountPath );
                }
            }
        }
        ++i;
    }
}

/*-------------------------------------------------------------------------*/

bool
CVFS::GetActualFilePath( const CString& file ,
                         CString& path       ) const
{GUCEF_TRACE;

    MT::CObjectScopeLock lock( this );

    // Get a list of all eligable mounts
    TConstMountLinkVector mountLinks;
    GetEligableMounts( file, false, mountLinks );

    // Find the file in the available archives
    TConstMountLinkVector::iterator i = mountLinks.begin();
    while ( i != mountLinks.end() )
    {
        TConstMountLink& mountLink = (*i);
        if ( mountLink.mountEntry->archive->FileExists( mountLink.remainder ) )
        {
            path = mountLink.mountEntry->abspath;
            CORE::AppendToPath( path, mountLink.remainder );
            return true;
        }
        ++i;
    }

    return false;
}

/*-------------------------------------------------------------------------*/

bool
CVFS::GetVfsPathForAbsolutePath( const CString& absolutePath ,
                                 CString& relativePath       ) const
{GUCEF_TRACE;

    // Make sure there are no more variables in the given absolute path
    CString realAbsPath = CORE::RelativePath( absolutePath );

    MT::CObjectScopeLock lock( this );

    // Try to match a mount entry
    TMountVector::const_iterator i = m_mountList.begin();
    while ( i != m_mountList.end() )
    {
        const TMountEntry& mountEntry = (*i);
        Int32 subStrIndex = realAbsPath.HasSubstr( mountEntry.abspath, true );
        if ( subStrIndex == 0 )
        {
            // This mount entry has at least a partially matching path
            CString remainder = realAbsPath.CutChars( mountEntry.abspath.Length(), true );

            // Now we will try to locate a resource given that path so we can validate
            // that this is not a coincidence
            if ( mountEntry.archive->FileExists( remainder ) )
            {
                // We found a file given this remainer
                // Now we construct the full relative path including mount path
                relativePath = mountEntry.mountPath;
                CORE::AppendToPath( relativePath, remainder );
                return true;
            }
        }
        ++i;
    }

    return false;
}

/*-------------------------------------------------------------------------*/

bool
CVFS::FileExists( const CString& file ) const
{GUCEF_TRACE;

    CString actualPath;
    return GetActualFilePath( file       ,
                              actualPath );
}

/*-------------------------------------------------------------------------*/

bool
CVFS::UnmountArchiveByName( const CString& archiveName )
{GUCEF_TRACE;

    MT::CObjectScopeLock lock( this );

    TMountVector::iterator i = m_mountList.begin();
    while ( i != m_mountList.end() )
    {
        TMountEntry& mountEntry = (*i);
        if ( mountEntry.archive->GetArchiveName() == archiveName )
        {
            if ( mountEntry.archive->UnloadArchive() )
            {
                m_mountList.erase( i );
                return true;
            }
            return false;
        }
        ++i;
    }

    return false;
}

/*-------------------------------------------------------------------------*/

void
CVFS::AddRoot( const CORE::CString& rootpath                                ,
               const CString& archiveName                                   ,
               const bool writeable                                         ,
               const bool autoMountArchives /* = false */                   ,
               const CString& mountPoint /* = "" */                         ,
               const CString& archiveType /* = FileSystemArchiveTypeName */ )
{GUCEF_TRACE;

    CArchiveSettings settings;
    settings.SetArchiveName( archiveName );
    settings.SetActualArchivePath( rootpath );
    settings.SetWriteableRequested( writeable );
    settings.SetAutoMountSubArchives( autoMountArchives );
    settings.SetMountPath( mountPoint );
    settings.SetArchiveType( archiveType );

    MountArchive( settings );
}

/*-------------------------------------------------------------------------*/

void 
CVFS::GetListOfSupportedArchiveTypes( TAbstractArchiveFactory::TKeySet& outList ) const
{GUCEF_TRACE;

    MT::CObjectScopeLock lock( this );
    m_abstractArchiveFactory.ObtainKeySet( outList );
}

/*-------------------------------------------------------------------------*/

void
CVFS::SetMemloadSize( UInt32 bytesize )
{GUCEF_TRACE;

    MT::CObjectScopeLock lock( this );

    _maxmemloadsize = bytesize;
    GUCEF_SYSTEM_LOG( CORE::LOGLEVEL_NORMAL, "VFS maximum memory load size set to " + CORE::UInt32ToString( bytesize ) + " Bytes" );
}

/*-------------------------------------------------------------------------*/

UInt32
CVFS::GetMemloadSize( void ) const
{GUCEF_TRACE;

    return _maxmemloadsize;
}

/*-------------------------------------------------------------------------*/

bool
CVFS::SaveConfig( CORE::CDataNode& tree ) const
{GUCEF_TRACE;

    MT::CObjectScopeLock lock( this );
    
    CORE::CDataNode* n = tree.Structure( "GUCEF%VFS%CVFS" ,
                                         '%'              );
    CORE::CString maxmem;
    maxmem.SetInt( _maxmemloadsize );
    n->SetAttribute( "maxmemload" ,
                     maxmem       );

    n->DelSubTree();
    UInt32 count = (UInt32) m_mountList.size();
    CORE::CDataNode pathnode( "vfsroot" );
    for ( UInt32 i=0; i<count; ++i )
    {
        pathnode.SetAttribute( "path", m_mountList[ i ].path );
        if ( m_mountList[ i ].archive->IsWriteable() )
        {
            pathnode.SetAttribute( "writeable", "true" );
        }
        else
        {
            pathnode.SetAttribute( "writeable", "false" );
        }
        n->AddChild( pathnode );
    }

    GUCEF_SYSTEM_LOG( CORE::LOGLEVEL_NORMAL, "VFS configuration successfully saved" );
    return true;
}

/*-------------------------------------------------------------------------*/

bool
CVFS::LoadConfig( const CORE::CDataNode& tree )
{GUCEF_TRACE;

    bool globalConfigLoadInProgress = IsGlobalConfigLoadInProgress();
    const CORE::CDataNode* n = tree.Search( "GUCEF%VFS%CVFS" ,
                                            '%'              ,
                                            false            );

    if ( n )
    {
        CString value = n->GetAttributeValueOrChildValueByName( "maxmemload" );
        if ( 0 < value.Length() )
        {
            SetMemloadSize( StringToUInt32( value ) );
        }

        CORE::CDataNode::TConstDataNodeSet rootNodeList = n->FindChildrenOfType( "VfsRoot" );
        CORE::CDataNode::TConstDataNodeSet::iterator i = rootNodeList.begin();
        while( i != rootNodeList.end() )
        {
            const CORE::CDataNode* legacySettingsNode = (*i);
            CArchiveSettings settings;
            settings.LoadConfig( *legacySettingsNode );
            if ( !globalConfigLoadInProgress )
                MountArchive( settings );
            else
                DelayMountArchive( settings );
            ++i;
        }

        GUCEF_SYSTEM_LOG( CORE::LOGLEVEL_NORMAL, "VFS legacy configuration loaded" );
    }
    
    n = tree.Find( "VFS" );
    if ( n )
    {
        CORE::CDataNode::TConstDataNodeSet rootNodeList = n->FindChildrenOfType( "ArchiveSettings" );
        CORE::CDataNode::TConstDataNodeSet::iterator i = rootNodeList.begin();
        while( i != rootNodeList.end() )
        {
            const CORE::CDataNode* settingsNode = (*i);
            CArchiveSettings settings;
            settings.LoadConfig( *settingsNode );
            if ( !globalConfigLoadInProgress )
                MountArchive( settings );
            else
                DelayMountArchive( settings );
            ++i;
        }

        GUCEF_SYSTEM_LOG( CORE::LOGLEVEL_NORMAL, "VFS archive configuration loaded" );
    }
    return true;
}

/*-------------------------------------------------------------------------*/

const CORE::CString& 
CVFS::GetClassTypeName( void ) const
{GUCEF_TRACE;

    static CORE::CString classTypeName = "GUCEF::VFS::CVFS";
    return classTypeName; 
}

/*-------------------------------------------------------------------------*/

bool
CVFS::FilterValidation( const CORE::CString& filename ,
                        const CORE::CString& filter   )
{GUCEF_TRACE;

    if ( filter.Length() > 0 )
    {
        CVFS::TStringList segs = filter.ParseElements( '*', false );
        VFS::Int32 lastSeg = 0;
        CVFS::TStringList::iterator i = segs.begin();
        while ( i != segs.end() )
        {
            lastSeg = filename.HasSubstr( (*i), lastSeg, true );
            if ( 0 > lastSeg ) 
                return false;
            ++i;
        }
        return true;
    }
    return true;
}

/*-------------------------------------------------------------------------*/

void
CVFS::GetEligableMounts( const CString& location                ,
                         bool mustBeWritable                    ,
                         TConstMountLinkVector& mountLinkVector ) const
{GUCEF_TRACE;

    TMountVector::const_iterator i = m_mountList.begin();
    while ( i != m_mountList.end() )
    {
        const TMountEntry& mountEntry = (*i);

        // Exclude non-writeable archives right away for 'mustBeWritable' scenarios
        if ( !mustBeWritable || mustBeWritable == mountEntry.writeable )
        {
            if ( mountEntry.mountPath.Length() > 0 )
            {
                // Check to see if the mount path is the starting sub string of the location
                if ( location.HasSubstr( mountEntry.mountPath, true ) == 0 )
                {
                    TConstMountLink mountLink;
                    mountLink.remainder = location.CutChars( mountEntry.mountPath.Length(), true );

                    // make sure the remainder does not have a path seperator prefix
                    if ( mountLink.remainder.Length() > 0 )
                    {
                        if ( ( mountLink.remainder[ 0 ] == '/' ) ||
                             ( mountLink.remainder[ 0 ] == '\\' ) )
                        {
                            // remove the dir seperator prefix
                            mountLink.remainder = mountLink.remainder.CutChars( 1, true );
                        }
                    }

                    mountLink.mountEntry = &mountEntry;
                    mountLinkVector.push_back( mountLink );

                    GUCEF_DEBUG_LOG( CORE::LOGLEVEL_NORMAL, "VFS: Found eligable mount link using archive of type \"" + 
                        mountEntry.archive->GetType() + "\" with remainder \"" + location + "\". mustBeWritable=" + CORE::BoolToString( mustBeWritable ) );
                }
            }
            else
            {
                TConstMountLink mountLink;
                mountLink.remainder = location;
                mountLink.mountEntry = &mountEntry;
                mountLinkVector.push_back( mountLink );

                GUCEF_DEBUG_LOG( CORE::LOGLEVEL_NORMAL, "VFS: Found eligable mount link using archive of type \"" + 
                    mountEntry.archive->GetType() + "\" with remainder \"" + location + "\". mustBeWritable=" + CORE::BoolToString( mustBeWritable ) );
            }
        }
        ++i;
    }

    GUCEF_DEBUG_LOG( CORE::LOGLEVEL_NORMAL, "VFS: Found a total of " + CORE::UInt32ToString( mountLinkVector.size() ) + " eligable mounts for location \"" + location + "\"" );
}

/*-------------------------------------------------------------------------*/

void
CVFS::GetList( TStringSet& outputList                   ,
               const CString& location                  ,
               bool recursive             /* = false */ ,
               bool includePathInFilename /* = false */ ,
               const CString& filter /* = "" */         ,
               bool addFiles /* = true */               ,
               bool addDirs /* = false */               ) const
{GUCEF_TRACE;

    // Switch dir separator chars if needed
    CString path( location.ReplaceChar( GUCEF_DIRSEPCHAROPPOSITE, GUCEF_DIRSEPCHAR ) );

    MT::CObjectScopeLock lock( this );
    
    // Get a list of all eligable mounts
    TConstMountLinkVector mountLinks;
    GetEligableMounts( path, false, mountLinks );

    // Get a list from each mount
    TConstMountLinkVector::iterator i = mountLinks.begin();
    while ( i != mountLinks.end() )
    {
        TConstMountLink& mountLink = (*i);
        mountLink.mountEntry->archive->GetList( outputList            ,
                                                mountLink.remainder   ,
                                                recursive             ,
                                                includePathInFilename ,
                                                filter                ,
                                                addFiles              ,
                                                addDirs               );
        ++i;
    }
}

/*-------------------------------------------------------------------------*/

void
CVFS::GetList( CORE::CDataNode& outputDataTree        ,
               const CORE::CString& location          ,
               bool recursive  /* = false */          ,
               const CORE::CString& filter /* = "" */ ,
               const bool addHash /* = false */       ) const
{GUCEF_TRACE;

    // First we get a list of files and their path
    TStringSet outputList;
    GetList( outputList ,
             location   ,
             recursive  ,
             true       ,
             filter     ,
             true       ,
             false      );

    // First we clear the tree
    outputDataTree.Clear();

    // Now we build our data tree using the list we obtained
    TStringSet::iterator i = outputList.begin();
    while ( i != outputList.end() )
    {
        // First we build the path structure in the data tree
        CString path = (*i).SubstrToChar( GUCEF_DIRSEPCHAR, false );
        CORE::CDataNode* pathRootNode = outputDataTree.Structure( "DIR", "Name", path, GUCEF_DIRSEPCHAR );

        // Extract the filename from the path
        CORE::CString filename( (*i).C_String() + path.Length() ,
                                (*i).Length() - path.Length()   );

        // Create the file node and set all the attributes
        CORE::CDataNode fileNode( "FILE" );
        fileNode.SetAttribute( "Name", filename );
        fileNode.SetAttribute( "Size", CORE::UInt32ToString( GetFileSize( (*i) ) ) );

        if ( addHash )
        {
            // Obtain the hash for the file, this can be a lengthy operation
            fileNode.SetAttribute( "Hash", GetFileHash( (*i) ) );
        }

        // Create a copy child node thus storing the file properties in the tree
        pathRootNode->AddChild( fileNode );

        ++i;
    }
}

/*-------------------------------------------------------------------------*/

time_t
CVFS::GetFileModificationTime( const CString& filename ) const
{GUCEF_TRACE;

    // Switch dir separator chars if needed
    CString path( filename.ReplaceChar( GUCEF_DIRSEPCHAROPPOSITE, GUCEF_DIRSEPCHAR ) );

    MT::CObjectScopeLock lock( this );

    // Get a list of all eligable mounts
    TConstMountLinkVector mountLinks;
    GetEligableMounts( path, false, mountLinks );

    // Search for a file and then get the hash
    TConstMountLinkVector::iterator i = mountLinks.begin();
    while ( i != mountLinks.end() )
    {
        TConstMountLink& mountLink = (*i);
        if ( mountLink.mountEntry->archive->FileExists( mountLink.remainder ) )
        {
            time_t modificationTime = mountLink.mountEntry->archive->GetFileModificationTime( mountLink.remainder );
            return modificationTime;
        }
        ++i;
    }

    return -1;
}

/*-------------------------------------------------------------------------*/

CORE::CString
CVFS::GetFileHash( const CORE::CString& file ) const
{GUCEF_TRACE;

    // Switch dir separator chars if needed
    CString path( file.ReplaceChar( GUCEF_DIRSEPCHAROPPOSITE, GUCEF_DIRSEPCHAR ) );

    MT::CObjectScopeLock lock( this );

    // Get a list of all eligable mounts
    TConstMountLinkVector mountLinks;
    GetEligableMounts( path, false, mountLinks );

    // Search for a file and then get the hash
    CString hash;
    TConstMountLinkVector::iterator i = mountLinks.begin();
    while ( i != mountLinks.end() )
    {
        TConstMountLink& mountLink = (*i);
        if ( mountLink.mountEntry->archive->FileExists( mountLink.remainder ) )
        {
            CString hash = mountLink.mountEntry->archive->GetFileHash( mountLink.remainder );
            return hash;
        }
        ++i;
    }

    return CString();
}

/*-------------------------------------------------------------------------*/

UInt32
CVFS::GetFileSize( const CORE::CString& file ) const
{GUCEF_TRACE;

    // Switch dir separator chars if needed
    CString path( file.ReplaceChar( GUCEF_DIRSEPCHAROPPOSITE, GUCEF_DIRSEPCHAR ) );

    MT::CObjectScopeLock lock( this );
    
    // Get a list of all eligable mounts
    TConstMountLinkVector mountLinks;
    GetEligableMounts( path, false, mountLinks );

    // Search for a file and then get its size
    CString hash;
    TConstMountLinkVector::iterator i = mountLinks.begin();
    while ( i != mountLinks.end() )
    {
        TConstMountLink& mountLink = (*i);
        if ( mountLink.mountEntry->archive->FileExists( mountLink.remainder ) )
        {
            UInt32 fileSize = mountLink.mountEntry->archive->GetFileSize( mountLink.remainder );
            return fileSize;
        }
        ++i;
    }

    return 0;
}

/*-------------------------------------------------------------------------*/

void
CVFS::RegisterArchiveFactory( const CString& archiveType      ,
                              TArchiveFactory& archiveFactory )
{GUCEF_TRACE;

    MT::CObjectScopeLock lock( this );

    m_abstractArchiveFactory.RegisterConcreteFactory( archiveType     ,
                                                      &archiveFactory );

    GUCEF_SYSTEM_LOG( CORE::LOGLEVEL_NORMAL, "Registered VFS archive factory for type \"" + archiveType + "\"" );
}

/*-------------------------------------------------------------------------*/

void
CVFS::UnregisterArchiveFactory( const CString& archiveType )
{GUCEF_TRACE;

    MT::CObjectScopeLock lock( this );

    m_abstractArchiveFactory.UnregisterConcreteFactory( archiveType );

    GUCEF_SYSTEM_LOG( CORE::LOGLEVEL_NORMAL, "Unregistered VFS archive factory for type \"" + archiveType + "\"" );
}

/*-------------------------------------------------------------------------//
//                                                                         //
//      NAMESPACE                                                          //
//                                                                         //
//-------------------------------------------------------------------------*/

}; /* namespace VFS */
}; /* namespace GUCEF */

/*-------------------------------------------------------------------------*/
