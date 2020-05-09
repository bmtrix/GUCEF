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

#ifndef VFSPLUGIN_AWSS3_CS3Archive_H
#define VFSPLUGIN_AWSS3_CS3Archive_H

/*-------------------------------------------------------------------------//
//                                                                         //
//      INCLUDES                                                           //
//                                                                         //
//-------------------------------------------------------------------------*/

#include <map>

#undef GetObject
#include <aws/core/Aws.h>
#include <aws/s3/model/Object.h>
#include <aws/s3/model/GetObjectResult.h>
#include <aws/s3/model/GetObjectRequest.h>
#include <aws/s3/model/ListObjectsRequest.h>
#include <aws/s3/S3Client.h>

#ifndef GUCEF_CORE_COBSERVINGNOTIFIER_H
#include "CObservingNotifier.h"
#define GUCEF_CORE_COBSERVINGNOTIFIER_H
#endif /* GUCEF_CORE_COBSERVINGNOTIFIER_H ? */

#ifndef GUCEF_VFS_CVFS_H
#include "gucefVFS_CVFS.h"
#define GUCEF_VFS_CVFS_H
#endif /* GUCEF_VFS_CVFS_H ? */

#ifndef GUCEF_VFSPLUGIN_AWSS3_MACROS_H
#include "vfspluginAWSS3_macros.h"
#define GUCEF_VFSPLUGIN_AWSS3_MACROS_H
#endif /* GUCEF_VFSPLUGIN_AWSS3_MACROS_H ? */

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
//      CLASSES                                                            //
//                                                                         //
//-------------------------------------------------------------------------*/

class GUCEF_HIDDEN CS3Archive : public CORE::CObservingNotifier ,
                                public VFS::CIArchive
{
    public:

    CS3Archive( void );

    virtual ~CS3Archive();

    virtual CVFSHandlePtr GetFile( const VFS::CString& file          ,
                                   const char* mode = "rb"           ,
                                   const VFS::UInt32 memLoadSize = 0 ,
                                   const bool overwrite = false      );

    virtual void GetList( TStringSet& outputList             ,
                          const VFS::CString& location       ,
                          bool recursive = false             ,
                          bool includePathInFilename = false ,
                          const VFS::CString& filter = ""    ,
                          bool addFiles = true               ,
                          bool addDirs  = false              ) const;

    virtual bool FileExists( const VFS::CString& filePath ) const;

    virtual VFS::UInt32 GetFileSize( const VFS::CString& filePath ) const;

    virtual VFS::CString GetFileHash( const VFS::CString& file ) const;

    virtual time_t GetFileModificationTime( const VFS::CString& filePath ) const;

    virtual const VFS::CString& GetArchiveName( void ) const;

    virtual bool IsWriteable( void ) const;

    virtual bool LoadArchive( const VFS::CArchiveSettings& settings );

    virtual bool LoadArchive( const VFS::CString& archiveName ,
                              CVFSHandlePtr vfsResource       ,
                              const bool writeableRequest     );

    virtual bool UnloadArchive( void );

    virtual const VFS::CString& GetType( void ) const;

    virtual void DestroyObject( VFS::CVFSHandle* objectToBeDestroyed );

    private:

    typedef CORE::CTEventHandlerFunctor< CS3Archive >   TEventCallback;
    typedef Aws::Vector< Aws::S3::Model::Bucket >       TBucketList;

    CS3Archive( const CS3Archive& src );
    CS3Archive& operator=( const CS3Archive& src );

    void
    OnAwsS3Initialized( CORE::CNotifier* notifier    ,
                        const CORE::CEvent& eventId  ,
                        CORE::CICloneable* eventData );

    void RegisterEventHandlers( void );

    bool LoadBucketList( const bool autoMountBuckets ,
                         const bool writeableRequest );
    
    private:

    TBucketList m_bucketList;
    VFS::CString m_archiveName;
    bool m_autoMountBuckets;
    bool m_writeableRequest;
};

/*-------------------------------------------------------------------------//
//                                                                         //
//      NAMESPACE                                                          //
//                                                                         //
//-------------------------------------------------------------------------*/

}; /* namespace AWSS3 */
}; /* namespace VFSPLUGIN */
}; /* namespace GUCEF */

/*-------------------------------------------------------------------------*/

#endif /* VFSPLUGIN_AWSS3_CS3Archive_H ? */

/*-------------------------------------------------------------------------//
//                                                                         //
//      Info & Changes                                                     //
//                                                                         //
//-------------------------------------------------------------------------//

- 04-05-2005 :
        - Dinand: Initial version.

-----------------------------------------------------------------------------*/
