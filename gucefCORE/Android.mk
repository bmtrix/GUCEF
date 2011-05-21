#-------------------------------------------------------------------
# This file has been automatically generated by ProjectGenerator    
# which is part of a build system designed for GUCEF                
#     (Galaxy Unlimited Framework)                                  
# For the latest info, see http://www.VanvelzenSoftware.com/        
#                                                                   
# The contents of this file are placed in the public domain. Feel   
# free to make use of it in any way you like.                       
#-------------------------------------------------------------------


ifndef $(MY_MODULE_PATH)
  MY_MODULE_PATH := $(call my-dir)
endif
LOCAL_PATH := $(MY_MODULE_PATH)

include $(CLEAR_VARS)

@echo Module path: $(MY_MODULE_PATH)
LOCAL_MODULE := gucefCORE
@echo Module name: $(LOCAL_MODULE)

LOCAL_SRC_FILES := \
  src/callstack.c \
  src/CBlockStack.cpp \
  src/CCodecChain.cpp \
  src/CCodecRegistry.cpp \
  src/CConfigStore.cpp \
  src/CCPPWrapFileAccess.cpp \
  src/CCyclicDynamicBuffer.cpp \
  src/CDataNode.cpp \
  src/CDataQueue.cpp \
  src/CDStoreCodec.cpp \
  src/CDStoreCodecPlugin.cpp \
  src/CDStoreCodecPluginManager.cpp \
  src/CDStoreCodecRegistry.cpp \
  src/CDVString.cpp \
  src/CDynamicArray.cpp \
  src/CDynamicBuffer.cpp \
  src/CDynamicBufferAccess.cpp \
  src/CEvent.cpp \
  src/CException.cpp \
  src/CExclusiveActivationManager.cpp \
  src/CExclusiveActiveObj.cpp \
  src/CFileAccess.cpp \
  src/CFileURLHandler.cpp \
  src/CGenericPlugin.cpp \
  src/CGenericPluginManager.cpp \
  src/CGUCEFApplication.cpp \
  src/CGUCEFCOREModule.cpp \
  src/CICloneable.cpp \
  src/CICodec.cpp \
  src/CICodecPlugin.cpp \
  src/CIConfigurable.cpp \
  src/CILogger.cpp \
  src/CINamedInstance.cpp \
  src/CINumericIDGeneratorBase.cpp \
  src/CIOAccess.cpp \
  src/CIPlugin.cpp \
  src/CIStreamable.cpp \
  src/CITypeNamed.cpp \
  src/CIURLEvents.cpp \
  src/CLLNode.cpp \
  src/CLogManager.cpp \
  src/cloneables.cpp \
  src/CMachineState.cpp \
  src/CMemoryBlockPool.cpp \
  src/CMFileAccess.cpp \
  src/CMsgException.cpp \
  src/CNode.cpp \
  src/CNotificationIDRegistry.cpp \
  src/CNotifier.cpp \
  src/CNotifierImplementor.cpp \
  src/CNotifierObservingComponent.cpp \
  src/CNotifyingMapEvents.cpp \
  src/CObserver.cpp \
  src/CObservingNotifier.cpp \
  src/CPFileAccess.cpp \
  src/CPFileChunkAccess.cpp \
  src/CPluginControl.cpp \
  src/CPluginManager.cpp \
  src/CPropertyList.cpp \
  src/CPumpedObserver.cpp \
  src/CROIOAccess.cpp \
  src/CStack.cpp \
  src/CStateHandler.cpp \
  src/CStateMachine.cpp \
  src/CStateMachineComponent.cpp \
  src/CStdCodecPlugin.cpp \
  src/CStdCodecPluginItem.cpp \
  src/CStdCodecPluginManager.cpp \
  src/CStdLogger.cpp \
  src/CSTDOStreamAdapter.cpp \
  src/CStreamerEvents.cpp \
  src/CStringList.cpp \
  src/CStringMap.cpp \
  src/CSysConsole.cpp \
  src/CSysConsoleClient.cpp \
  src/CTAbstractFactory.cpp \
  src/CTAbstractFactoryWithParam.cpp \
  src/CTBasicSharedPtr.cpp \
  src/CTCloneableObj.cpp \
  src/CTCodecPluginItem.cpp \
  src/CTDynamicDestructor.cpp \
  src/CTDynamicDestructorBase.cpp \
  src/CTFactory.cpp \
  src/CTFactoryBase.cpp \
  src/CTFactoryBaseWithParam.cpp \
  src/CTFactoryWithParam.cpp \
  src/CTimer.cpp \
  src/CTLinkedCloneableObj.cpp \
  src/CTNotifyingMap.cpp \
  src/CTNumericID.cpp \
  src/CTNumericIDGenerator.cpp \
  src/CTObservingNotifierComponent.cpp \
  src/CTObservingNotifierExpansion.cpp \
  src/CTONRegistry.cpp \
  src/CTracer.cpp \
  src/CTransactionEventControl.cpp \
  src/CTRegistry.cpp \
  src/CTSGNotifier.cpp \
  src/CTSGObserver.cpp \
  src/CTSharedPtr.cpp \
  src/CTSingleton.cpp \
  src/CURL.cpp \
  src/CURLDataRetriever.cpp \
  src/CURLHandler.cpp \
  src/CURLHandlerRegistry.cpp \
  src/CValueList.cpp \
  src/dvcppstringutils.cpp \
  src/dvfileutils.c \
  src/dvmd5utils.c \
  src/DVOSWRAP.c \
  src/dvstrutils.c \
  src/ExceptionMacros.cpp \
  src/gucefCORE.cpp \
  src/gucefCORE_CAbstractFactoryBase.cpp \
  src/gucefCORE_CBusyWaitPulseGeneratorDriver.cpp \
  src/gucefCORE_CForwardingNotifier.cpp \
  src/gucefCORE_CIEventHandlerFunctorBase.cpp \
  src/gucefCORE_CIniDataStoreCodec.cpp \
  src/gucefCORE_CIniParser.cpp \
  src/gucefCORE_CIObserver.cpp \
  src/gucefCORE_CIPulseGeneratorDriver.cpp \
  src/gucefCORE_CITaskConsumer.cpp \
  src/gucefCORE_CLinkedTransferBuffer.cpp \
  src/gucefCORE_CLoggingTask.cpp \
  src/gucefCORE_CObserverSwitch.cpp \
  src/gucefCORE_CPlatformNativeConsoleLogger.cpp \
  src/gucefCORE_CPulseData.cpp \
  src/gucefCORE_CPulseGenerator.cpp \
  src/gucefCORE_CSingleTaskDelegator.cpp \
  src/gucefCORE_CSubFileAccess.cpp \
  src/gucefCORE_CTaskDelegator.cpp \
  src/gucefCORE_CTaskManager.cpp \
  src/gucefCORE_CTEventHandlerFunctor.cpp \
  src/IOACCESS.c \
  src/md5.c \
  src/MemoryManager.cpp \
  src/MemoryPool.cpp \
  src/MemorySegment.cpp \
  src/MFILE.c \
  src/PAFILE.c \
  src/streamables.cpp \
  src/streamers.cpp \
  src/tsprinting.c

LOCAL_C_INCLUDES := \
  $(MY_MODULE_PATH)/include \
  $(MY_MODULE_PATH)/../common/include \
  $(MY_MODULE_PATH)/../gucefMT/include


LOCAL_SHARED_LIBRARIES := \
  gucefMT

include $(BUILD_SHARED_LIBRARY)

