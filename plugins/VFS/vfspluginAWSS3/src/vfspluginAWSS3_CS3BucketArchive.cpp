/*
 *  vfspluginAWSS3: Generic GUCEF VFS plugin for dealing with S3 storage in AWS
 *
 *  Copyright (C) 1998 - 2020.  Dinand Vanvelzen
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

/*-------------------------------------------------------------------------//
//                                                                         //
//      INCLUDES                                                           //
//                                                                         //
//-------------------------------------------------------------------------*/

#ifndef GUCEF_CORE_DVMD5UTILS_H
#include "dvmd5utils.h"
#define GUCEF_CORE_DVMD5UTILS_H
#endif /* GUCEF_CORE_DVMD5UTILS_H ? */

#ifndef GUCEF_CORE_CDYNAMICBUFFER_H
#include "CDynamicBuffer.h"
#define GUCEF_CORE_CDYNAMICBUFFER_H
#endif /* GUCEF_CORE_CDYNAMICBUFFER_H ? */

#ifndef GUCEF_CORE_CDYNAMICBUFFERACCESS_H
#include "CDynamicBufferAccess.h"
#define GUCEF_CORE_CDYNAMICBUFFERACCESS_H
#endif /* GUCEF_CORE_CDYNAMICBUFFERACCESS_H ? */

#ifndef GUCEF_CORE_CSUBFILEACCESS_H
#include "gucefCORE_CSubFileAccess.h"
#define GUCEF_CORE_CSUBFILEACCESS_H
#endif /* GUCEF_CORE_CSUBFILEACCESS_H ? */

#ifndef GUCEF_CORE_CFILEACCESS_H
#include "CFileAccess.h"
#define GUCEF_CORE_CFILEACCESS_H
#endif /* GUCEF_CORE_CFILEACCESS_H ? */

#ifndef GUCEF_CORE_LOGGING_H
#include "gucefCORE_Logging.h"
#define GUCEF_CORE_LOGGING_H
#endif /* GUCEF_CORE_LOGGING_H ? */

#ifndef GUCEF_CORE_DVCPPSTRINGUTILS_H
#include "dvcppstringutils.h"
#define GUCEF_CORE_DVCPPSTRINGUTILS_H
#endif /* GUCEF_CORE_DVCPPSTRINGUTILS_H ? */

#ifndef GUCEF_VFSPLUGIN_AWSS3_CAWSS3GLOBAL_H
#include "vfspluginAWSS3_CAwsS3Global.h"
#define GUCEF_VFSPLUGIN_AWSS3_CAWSS3GLOBAL_H
#endif /* GUCEF_VFSPLUGIN_AWSS3_CAWSS3GLOBAL_H ? */

#include "vfspluginAWSS3_CS3BucketArchive.h"

/*-------------------------------------------------------------------------//
//                                                                         //
//      NAMESPACE                                                          //
//                                                                         //
//-------------------------------------------------------------------------*/

namespace GUCEF {
namespace VFSPLUGIN {
namespace AWSS3 {

/*-------------------------------------------------------------------------//
//                                                                         //
//      UTILITIES                                                          //
//                                                                         //
//-------------------------------------------------------------------------*/

CS3BucketArchive::CS3BucketArchive( void )
    : CIArchive() 
    , m_objects()
    , m_archiveName()
    , m_autoMountBuckets( false )
    , m_writeableRequest( false )
{GUCEF_TRACE;

}

/*-------------------------------------------------------------------------*/

CS3BucketArchive::~CS3BucketArchive()
{GUCEF_TRACE;

    UnloadArchive();
}

/*-------------------------------------------------------------------------*/

VFS::CIArchive::CVFSHandlePtr
CS3BucketArchive::GetFile( const VFS::CString& file      ,
                           const char* mode              ,
                           const VFS::UInt32 memLoadSize ,
                           const bool overwrite          )
{GUCEF_TRACE;

    return VFS::CVFS::CVFSHandlePtr();
}

/*-------------------------------------------------------------------------*/

void
CS3BucketArchive::GetList( TStringSet& outputList       ,
                           const VFS::CString& location ,
                           bool recursive               ,
                           bool includePathInFilename   ,
                           const VFS::CString& filter   ,
                           bool addFiles                ,
                           bool addDirs                 ) const
{GUCEF_TRACE;


}

/*-------------------------------------------------------------------------*/

bool
CS3BucketArchive::FileExists( const VFS::CString& filePath ) const
{GUCEF_TRACE;

    return false;
}

/*-------------------------------------------------------------------------*/

VFS::UInt32
CS3BucketArchive::GetFileSize( const VFS::CString& filePath ) const
{GUCEF_TRACE;

    return 0;
}

/*-------------------------------------------------------------------------*/

time_t
CS3BucketArchive::GetFileModificationTime( const VFS::CString& filePath ) const
{
    return 0;
}

/*-------------------------------------------------------------------------*/

VFS::CString
CS3BucketArchive::GetFileHash( const VFS::CString& file ) const
{GUCEF_TRACE;

    return VFS::CString();
}

/*-------------------------------------------------------------------------*/

const VFS::CString&
CS3BucketArchive::GetArchiveName( void ) const
{GUCEF_TRACE;

    return m_archiveName;
}

/*-------------------------------------------------------------------------*/

bool
CS3BucketArchive::IsWriteable( void ) const
{GUCEF_TRACE;

    return m_writeableRequest;
}

/*-------------------------------------------------------------------------*/

bool
CS3BucketArchive::LoadArchive( const VFS::CString& archiveName ,
                               const VFS::CString& archivePath ,
                               const bool writeableRequest     ,
                               const bool autoMountSubArchives )
{GUCEF_TRACE;

    try
    {
        m_archiveName = archiveName;
        m_autoMountBuckets = autoMountSubArchives;
        m_writeableRequest = writeableRequest; 
        
        Aws::S3::S3Client* s3Client = CAwsS3Global::Instance()->GetS3Client();
        if ( GUCEF_NULL == s3Client )
            return false;

        Aws::S3::Model::ListObjectsRequest objectsRequest;
        objectsRequest.WithBucket( m_archiveName );

        auto listObjectsOutcome = s3Client->ListObjects( objectsRequest );
        if ( listObjectsOutcome.IsSuccess() )
        {
            // Get up to 1000 objects

            #ifdef GUCEF_DEBUG_MODE
            CORE::CString objectKeys;
            #endif

            Aws::Vector< Aws::S3::Model::Object > objectList = listObjectsOutcome.GetResult().GetContents();
            for (auto const& s3Object : objectList )
            {
                auto const& key = s3Object.GetKey();

                #ifdef GUCEF_DEBUG_MODE
                objectKeys += key + ", ";
                #endif
                
                m_objects[ key ] = s3Object;
            }
            GUCEF_DEBUG_LOG( CORE::LOGLEVEL_BELOW_NORMAL, "S3BucketArchive: Bucket \"" + m_archiveName + "\"has the following objects: " + objectKeys );
        }
        else
        {
            GUCEF_ERROR_LOG( CORE::LOGLEVEL_NORMAL, "S3BucketArchive: ListObjects error: " + 
                listObjectsOutcome.GetError().GetExceptionName() + " - " + listObjectsOutcome.GetError().GetMessage() );
        }
    }
    catch ( const std::exception& e )
    {
        GUCEF_EXCEPTION_LOG( CORE::LOGLEVEL_IMPORTANT, CORE::CString( "S3BucketArchive: Exception trying to S3 load bucket object index: " ) + e.what() );
    }
    catch ( ... )
    {
        GUCEF_EXCEPTION_LOG( CORE::LOGLEVEL_CRITICAL, "S3BucketArchive: Unknown exception trying to S3 load bucket object index" );
    }
    return false;
}

/*-------------------------------------------------------------------------*/

bool
CS3BucketArchive::LoadArchive( const VFS::CString& archiveName ,
                               CVFSHandlePtr vfsResource       ,
                               const bool writeableRequest     )
{GUCEF_TRACE;

    return false;
}

/*-------------------------------------------------------------------------*/

bool
CS3BucketArchive::UnloadArchive( void )
{GUCEF_TRACE;

    return true;
}

/*-------------------------------------------------------------------------*/

const VFS::CString& 
CS3BucketArchive::GetType( void ) const
{GUCEF_TRACE;

    return CAwsS3Global::AwsS3ArchiveType;
}

/*-------------------------------------------------------------------------*/

void
CS3BucketArchive::DestroyObject( VFS::CVFSHandle* objectToBeDestroyed )
{GUCEF_TRACE;

    delete objectToBeDestroyed;
}

/*-------------------------------------------------------------------------//
//                                                                         //
//      NAMESPACE                                                          //
//                                                                         //
//-------------------------------------------------------------------------*/

}; /* namespace AWSS3 */
}; /* namespace VFSPLUGIN */
}; /* namespace GUCEF */

/*-------------------------------------------------------------------------*/
