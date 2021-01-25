# Install script for directory: C:/Users/user/Desktop/Nassim/assimp-3.1.1/code

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/Assimp")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "C:/Users/user/Desktop/Nassim/assimpbuild/code/libassimp.dll.a")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xlibassimp3.1.1x" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "C:/Users/user/Desktop/Nassim/assimpbuild/code/libassimp.dll")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/libassimp.dll" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/libassimp.dll")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "C:/Program Files (x86)/CodeBlocks/MinGW/bin/strip.exe" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/libassimp.dll")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xassimp-devx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/assimp" TYPE FILE FILES
    "C:/Users/user/Desktop/Nassim/assimp-3.1.1/code/../include/assimp/anim.h"
    "C:/Users/user/Desktop/Nassim/assimp-3.1.1/code/../include/assimp/ai_assert.h"
    "C:/Users/user/Desktop/Nassim/assimp-3.1.1/code/../include/assimp/camera.h"
    "C:/Users/user/Desktop/Nassim/assimp-3.1.1/code/../include/assimp/color4.h"
    "C:/Users/user/Desktop/Nassim/assimp-3.1.1/code/../include/assimp/color4.inl"
    "C:/Users/user/Desktop/Nassim/assimp-3.1.1/code/../include/assimp/config.h"
    "C:/Users/user/Desktop/Nassim/assimp-3.1.1/code/../include/assimp/defs.h"
    "C:/Users/user/Desktop/Nassim/assimp-3.1.1/code/../include/assimp/cfileio.h"
    "C:/Users/user/Desktop/Nassim/assimp-3.1.1/code/../include/assimp/light.h"
    "C:/Users/user/Desktop/Nassim/assimp-3.1.1/code/../include/assimp/material.h"
    "C:/Users/user/Desktop/Nassim/assimp-3.1.1/code/../include/assimp/material.inl"
    "C:/Users/user/Desktop/Nassim/assimp-3.1.1/code/../include/assimp/matrix3x3.h"
    "C:/Users/user/Desktop/Nassim/assimp-3.1.1/code/../include/assimp/matrix3x3.inl"
    "C:/Users/user/Desktop/Nassim/assimp-3.1.1/code/../include/assimp/matrix4x4.h"
    "C:/Users/user/Desktop/Nassim/assimp-3.1.1/code/../include/assimp/matrix4x4.inl"
    "C:/Users/user/Desktop/Nassim/assimp-3.1.1/code/../include/assimp/mesh.h"
    "C:/Users/user/Desktop/Nassim/assimp-3.1.1/code/../include/assimp/postprocess.h"
    "C:/Users/user/Desktop/Nassim/assimp-3.1.1/code/../include/assimp/quaternion.h"
    "C:/Users/user/Desktop/Nassim/assimp-3.1.1/code/../include/assimp/quaternion.inl"
    "C:/Users/user/Desktop/Nassim/assimp-3.1.1/code/../include/assimp/scene.h"
    "C:/Users/user/Desktop/Nassim/assimp-3.1.1/code/../include/assimp/metadata.h"
    "C:/Users/user/Desktop/Nassim/assimp-3.1.1/code/../include/assimp/texture.h"
    "C:/Users/user/Desktop/Nassim/assimp-3.1.1/code/../include/assimp/types.h"
    "C:/Users/user/Desktop/Nassim/assimp-3.1.1/code/../include/assimp/vector2.h"
    "C:/Users/user/Desktop/Nassim/assimp-3.1.1/code/../include/assimp/vector2.inl"
    "C:/Users/user/Desktop/Nassim/assimp-3.1.1/code/../include/assimp/vector3.h"
    "C:/Users/user/Desktop/Nassim/assimp-3.1.1/code/../include/assimp/vector3.inl"
    "C:/Users/user/Desktop/Nassim/assimp-3.1.1/code/../include/assimp/version.h"
    "C:/Users/user/Desktop/Nassim/assimp-3.1.1/code/../include/assimp/cimport.h"
    "C:/Users/user/Desktop/Nassim/assimp-3.1.1/code/../include/assimp/importerdesc.h"
    "C:/Users/user/Desktop/Nassim/assimp-3.1.1/code/../include/assimp/Importer.hpp"
    "C:/Users/user/Desktop/Nassim/assimp-3.1.1/code/../include/assimp/DefaultLogger.hpp"
    "C:/Users/user/Desktop/Nassim/assimp-3.1.1/code/../include/assimp/ProgressHandler.hpp"
    "C:/Users/user/Desktop/Nassim/assimp-3.1.1/code/../include/assimp/IOStream.hpp"
    "C:/Users/user/Desktop/Nassim/assimp-3.1.1/code/../include/assimp/IOSystem.hpp"
    "C:/Users/user/Desktop/Nassim/assimp-3.1.1/code/../include/assimp/Logger.hpp"
    "C:/Users/user/Desktop/Nassim/assimp-3.1.1/code/../include/assimp/LogStream.hpp"
    "C:/Users/user/Desktop/Nassim/assimp-3.1.1/code/../include/assimp/NullLogger.hpp"
    "C:/Users/user/Desktop/Nassim/assimp-3.1.1/code/../include/assimp/cexport.h"
    "C:/Users/user/Desktop/Nassim/assimp-3.1.1/code/../include/assimp/Exporter.hpp"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xassimp-devx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/assimp/Compiler" TYPE FILE FILES
    "C:/Users/user/Desktop/Nassim/assimp-3.1.1/code/../include/assimp/Compiler/pushpack1.h"
    "C:/Users/user/Desktop/Nassim/assimp-3.1.1/code/../include/assimp/Compiler/poppack1.h"
    "C:/Users/user/Desktop/Nassim/assimp-3.1.1/code/../include/assimp/Compiler/pstdint.h"
    )
endif()

