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

LOCAL_MODULE := gucefINPUT_TestApp

LOCAL_SRC_FILES := \
  $(MY_MODULE_PATH)/src/gucefINPUT_TestApp.cpp

LOCAL_C_INCLUDES := \
  $(MY_MODULE_PATH)/../gucefCORE/include \
  $(MY_MODULE_PATH)/../gucefINPUT/include \
  $(MY_MODULE_PATH)/../gucefMT/include


LOCAL_SHARED_LIBRARIES := \
  gucefINPUT \
  gucefCORE \
  gucefMT

include $(BUILD_EXECUTABLE)

