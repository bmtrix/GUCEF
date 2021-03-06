#-------------------------------------------------------------------
# This file is part of the CMake build system for OGRE
#     (Object-oriented Graphics Rendering Engine)
# For the latest info, see http://www.ogre3d.org/
#
# The contents of this file are placed in the public domain. Feel
# free to make use of it in any way you like.
#-------------------------------------------------------------------

############################################################
# Paging optional component
############################################################

PROJECT(OgreProperty)

# define header and source files for the library
set (HEADER_FILES
	include/OgreProperty.h
	include/OgrePropertyPrerequisites.h
)

set (SOURCE_FILES
	src/OgreProperty.cpp
)

# Add needed definitions 
add_definitions(-DOGRE_PROPERTY_EXPORTS)

# include headers
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${OGRE_SOURCE_DIR}/OgreMain/include)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
endif()

# setup target
ogre_add_library_to_folder(Components OgreProperty ${OGRE_COMP_LIB_TYPE} ${HEADER_FILES} ${SOURCE_FILES} ${PLATFORM_HEADER_FILES} ${PLATFORM_SOURCE_FILES})
set_target_properties(OgreProperty PROPERTIES VERSION ${OGRE_SOVERSION} SOVERSION ${OGRE_SOVERSION})
target_link_libraries(OgreProperty OgreMain)

# install 
ogre_config_framework(OgreProperty)
ogre_config_component(OgreProperty)

install(FILES ${HEADER_FILES}
  DESTINATION include/OGRE/Property
)

