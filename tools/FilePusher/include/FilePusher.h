/*
 *  FilePusher: service which monitors the file system and pushes files to
 *  a remote repository
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

#ifndef GUCEF_APP_FILEPUSHER_H
#define GUCEF_APP_FILEPUSHER_H

/*-------------------------------------------------------------------------//
//                                                                         //
//      INCLUDES                                                           //
//                                                                         //
//-------------------------------------------------------------------------*/

#ifndef GUCEF_CORE_CICONFIGURABLE_H
#include "CIConfigurable.h"
#define GUCEF_CORE_CICONFIGURABLE_H
#endif /* GUCEF_CORE_CICONFIGURABLE_H ? */

#ifndef GUCEF_CORE_CVALUELIST_H
#include "CValueList.h"
#define GUCEF_CORE_CVALUELIST_H
#endif /* GUCEF_CORE_CVALUELIST_H ? */

#ifndef GUCEF_CORE_CDATANODE_H
#include "CDataNode.h"
#define GUCEF_CORE_CDATANODE_H
#endif /* GUCEF_CORE_CDATANODE_H ? */

#ifndef GUCEF_CORE_CTIMER_H
#include "CTimer.h"
#define GUCEF_CORE_CTIMER_H
#endif /* GUCEF_CORE_CTIMER_H ? */

#ifndef GUCEF_CORE_CDIRECTORYWATCHER_H
#include "gucefCORE_CDirectoryWatcher.h"
#define GUCEF_CORE_CDIRECTORYWATCHER_H
#endif /* GUCEF_CORE_CDIRECTORYWATCHER_H ? */

#ifndef GUCEF_COM_CHTTPSERVER_H
#include "gucefCOM_CHTTPServer.h"
#define GUCEF_COM_CHTTPSERVER_H
#endif /* GUCEF_COM_CHTTPSERVER_H ? */

#ifndef GUCEF_COM_CHTTPCLIENT_H
#include "CHTTPClient.h"
#define GUCEF_COM_CHTTPCLIENT_H
#endif /* GUCEF_COM_CHTTPCLIENT_H ? */

#ifndef GUCEF_COM_CDEFAULTHTTPSERVERROUTER_H
#include "gucefCOM_CDefaultHTTPServerRouter.h"
#define GUCEF_COM_CDEFAULTHTTPSERVERROUTER_H
#endif /* GUCEF_COM_CDEFAULTHTTPSERVERROUTER_H ? */

#ifndef GUCEF_COM_CCODECBASEDHTTPSERVERRESOURCE_H
#include "gucefCOM_CCodecBasedHTTPServerResource.h"
#define GUCEF_COM_CCODECBASEDHTTPSERVERRESOURCE_H
#endif /* GUCEF_COM_CCODECBASEDHTTPSERVERRESOURCE_H ? */

/*-------------------------------------------------------------------------//
//                                                                         //
//      NAMESPACE                                                          //
//                                                                         //
//-------------------------------------------------------------------------*/

using namespace GUCEF;

/*-------------------------------------------------------------------------//
//                                                                         //
//      UTILITIES                                                          //
//                                                                         //
//-------------------------------------------------------------------------*/

class FilePusher;

class RestApiFilePusherInfoResource : public COM::CCodecBasedHTTPServerResource
{
    public:

    RestApiFilePusherInfoResource( FilePusher* app );

    virtual ~RestApiFilePusherInfoResource();

    virtual bool Serialize( CORE::CDataNode& output             ,
                            const CORE::CString& representation );

    private:

    FilePusher* m_app;
};

/*-------------------------------------------------------------------------*/

class RestApiFilePusherConfigResource : public COM::CCodecBasedHTTPServerResource
{
    public:

    RestApiFilePusherConfigResource( FilePusher* app, bool appConfig );

    virtual ~RestApiFilePusherConfigResource();

    virtual bool Serialize( CORE::CDataNode& output             ,
                            const CORE::CString& representation );

    private:

    FilePusher* m_app;
    bool m_appConfig;
};

/*-------------------------------------------------------------------------*/

class FilePusher : public CORE::CObservingNotifier
{
    public:

    static const CORE::UInt32 DefaultNewFileRestPeriodInSecs;

    FilePusher( void );
    virtual ~FilePusher();

    bool Start( void );

    bool LoadConfig( const CORE::CValueList& appConfig   ,
                     const CORE::CDataNode& globalConfig );

    const CORE::CValueList& GetAppConfig( void ) const;

    const CORE::CDataNode& GetGlobalConfig( void ) const;

    private:

    enum EPushStyle
    {
        PUSHSTYLE_UNKNOWN                               = 0,
        PUSHSTYLE_ROLLED_OVER_FILES                        ,
        PUSHSTYLE_MATCHING_NEW_FILES_WITH_REST_PERIOD      ,
        PUSHSTYLE_MATCHING_ALL_FILES_WITH_REST_PERIOD
    };
    typedef enum EPushStyle TPushStyle;
    typedef CORE::CTEventHandlerFunctor< FilePusher > TEventCallback;
    typedef std::map< CORE::CString, TPushStyle > TStringPushStyleMap;
    typedef std::map< CORE::CString, time_t > TStringTimeMap;
    typedef std::set< CORE::CString > TStringSet;
    typedef std::map< CORE::CString, CORE::UInt64 > TStringUInt64Map;
    typedef std::map< CORE::UInt32, CORE::CString > TUInt32StringMap;
    typedef std::map< CORE::UInt64, CORE::CString::StringVector > TUInt64StringVectorMap;

    void RegisterEventHandlers( void );

    void
    OnMetricsTimerCycle( CORE::CNotifier* notifier    ,
                         const CORE::CEvent& eventId  ,
                         CORE::CICloneable* eventData );
    
    void
    OnWatchedLocalDirFileCreation( CORE::CNotifier* notifier    ,
                                   const CORE::CEvent& eventId  ,
                                   CORE::CICloneable* eventData );

    void
    OnNewFileRestPeriodTimerCycle( CORE::CNotifier* notifier    ,
                                   const CORE::CEvent& eventId  ,
                                   CORE::CICloneable* eventData );
    
    void
    OnAllFilesDirScanTimerCycle( CORE::CNotifier* notifier    ,
                                 const CORE::CEvent& eventId  ,
                                 CORE::CICloneable* eventData );

    void
    OnFilePushTimerCycle( CORE::CNotifier* notifier    ,
                          const CORE::CEvent& eventId  ,
                          CORE::CICloneable* eventData );

    void
    OnHttpClientConnected( CORE::CNotifier* notifier    ,
                           const CORE::CEvent& eventId  ,
                           CORE::CICloneable* eventData );

    void
    OnHttpClientDisconnected( CORE::CNotifier* notifier    ,
                              const CORE::CEvent& eventId  ,
                              CORE::CICloneable* eventData );
                           
    void
    OnHttpClientConnectionError( CORE::CNotifier* notifier    ,
                                 const CORE::CEvent& eventId  ,
                                 CORE::CICloneable* eventData );

    void
    OnHttpClientHttpError( CORE::CNotifier* notifier    ,
                           const CORE::CEvent& eventId  ,
                           CORE::CICloneable* eventData );

    void
    OnHttpClientHttpRedirect( CORE::CNotifier* notifier    ,
                              const CORE::CEvent& eventId  ,
                              CORE::CICloneable* eventData );

    void
    OnHttpClientHttpContent( CORE::CNotifier* notifier    ,
                             const CORE::CEvent& eventId  ,
                             CORE::CICloneable* eventData );

    void
    OnHttpClientHttpDataSent( CORE::CNotifier* notifier    ,
                              const CORE::CEvent& eventId  ,
                              CORE::CICloneable* eventData );

    void
    OnHttpClientHttpDataRecieved( CORE::CNotifier* notifier    ,
                                  const CORE::CEvent& eventId  ,
                                  CORE::CICloneable* eventData );

    void
    OnHttpClientHttpTransferFinished( CORE::CNotifier* notifier    ,
                                      const CORE::CEvent& eventId  ,
                                      CORE::CICloneable* eventData );
    
    void
    OnAsyncVfsOperationCompleted( CORE::CNotifier* notifier    ,
                                  const CORE::CEvent& eventId  ,
                                  CORE::CICloneable* eventData );

    void
    QueueNewFileForPushingAfterUnmodifiedRestPeriod( const CORE::CString& newFilePath );

    bool
    QueueAllPreExistingFilesForDir( const CORE::CString& dir );

    bool
    DoesFilenameMatchPushAllFilesPattern( const CORE::CString& filename ) const;

    void
    TriggerRolledOverFileCheck( const CORE::CString& dirWithFiles   ,
                                const CORE::CString& patternToMatch );

    void
    TriggerRolledOverFileCheck( const CORE::CString& dirWithFiles                  ,
                                const CORE::CString::StringVector& patternsToMatch );
    
    void
    QueueFileForPushing( const CORE::CString& filePath );

    bool 
    PushFileUsingHttp( const CORE::CString& pathToFileToPus, CORE::UInt32 offsetInFileh );

    bool
    PushFileUsingVfs( const CORE::CString& pathToFileToPush, CORE::UInt32 offsetInFile );

    void
    OnFilePushFinished( void );

    static time_t GetLatestTimestampForFile( const CORE::CString& filePath );

    CORE::CString::StringVector
    GetFilePatternsForPushType( TPushStyle pushStyle ) const;
    
    private:
    
    CORE::CDirectoryWatcher m_dirWatcher;
    COM::CHTTPClient m_httpClient;
    COM::CHTTPServer m_httpServer;
    COM::CDefaultHTTPServerRouter m_httpRouter;
    CORE::CValueList m_appConfig;
    CORE::CDataNode m_globalConfig;
    CORE::CTimer m_metricsTimer;
    bool m_transmitMetrics;
    TStringPushStyleMap m_fileMatchPatterns;
    CORE::CTimer m_newFileRestPeriodTimer;
    TStringTimeMap m_newFileRestQueue;
    CORE::UInt32 m_restingTimeForNewFilesInSecs;
    TStringUInt64Map m_pushQueue;
    CORE::CTimer m_pushTimer;
    TStringSet m_dirsToWatch;
    bool m_deleteFilesAfterSuccessfullPush;
    CORE::CString m_filePushDestinationUri;
    CORE::CString m_currentFileBeingPushed;
    CORE::CDynamicBuffer m_currentFilePushBuffer;
    CORE::UInt32 m_lastPushDurationInSecs;
    CORE::CTimer m_allFilesDirScanTimer;
};

/*-------------------------------------------------------------------------*/

#endif /* GUCEF_APP_FILEPUSHER_H ? */
