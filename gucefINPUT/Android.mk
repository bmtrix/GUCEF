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

include $(CLEAR_VARS)

LOCAL_MODULE := gucefINPUT

LOCAL_SRC_FILES := \
  $(MY_MODULE_PATH)/src/CGUCEFINPUTModule.cpp \
  $(MY_MODULE_PATH)/src/CInputActionMap.cpp \
  $(MY_MODULE_PATH)/src/CInputContext.cpp \
  $(MY_MODULE_PATH)/src/CInputController.cpp \
  $(MY_MODULE_PATH)/src/CInputDriverPlugin.cpp \
  $(MY_MODULE_PATH)/src/gucefINPUT_CActionEventData.cpp \
  $(MY_MODULE_PATH)/src/gucefINPUT_CInputDriver.cpp \
  $(MY_MODULE_PATH)/src/gucefINPUT_CInputObserverSwitch.cpp \
  $(MY_MODULE_PATH)/src/gucefINPUT_CKeyboard.cpp \
  $(MY_MODULE_PATH)/src/gucefINPUT_CKeyModStateChangedEventData.cpp \
  $(MY_MODULE_PATH)/src/gucefINPUT_CKeyStateChangedEventData.cpp \
  $(MY_MODULE_PATH)/src/gucefINPUT_CMouse.cpp \
  $(MY_MODULE_PATH)/src/gucefINPUT_CMouseButtonEventData.cpp \
  $(MY_MODULE_PATH)/src/gucefINPUT_CMouseMovedEventData.cpp \
  $(MY_MODULE_PATH)/src/gucefINPUT_keyboard.cpp

LOCAL_C_INCLUDES := \
  $(MY_MODULE_PATH)/include \
  $(MY_MODULE_PATH)/../gucefCORE/include \
  $(MY_MODULE_PATH)/../gucefMT/include


LOCAL_SHARED_LIBRARIES := \
  gucefCORE \
  gucefMT

include $(BUILD_SHARED_LIBRARY)

