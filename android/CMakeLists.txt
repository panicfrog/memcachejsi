cmake_minimum_required(VERSION 3.9.0)

set (PACKAGE_NAME "memcachejsi")
set (BUILD_DIR ${CMAKE_SOURCE_DIR}/build)

project(${PACKAGE_NAME})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

message(STATUS "NODE_MODULES_DIR: ${NODE_MODULES_DIR}")

include_directories(
        ${PACKAGE_NAME}
        "${NODE_MODULES_DIR}/react-native/React"
        "${NODE_MODULES_DIR}/react-native/React/Base"
        "${NODE_MODULES_DIR}/react-native/ReactCommon/jsi"
        "../cpp"
        "."
)

message(STATUS "REACT_NATIVE_VERSION: ${REACT_NATIVE_VERSION}")

if(${REACT_NATIVE_VERSION} LESS 66)
  file(
          TO_CMAKE_PATH
          "${NODE_MODULES_DIR}/react-native/ReactCommon/jsi/jsi/jsi.cpp"
          INCLUDE_JSI_CPP
  )

  message(STATUS "INCLUDE_JSI_CPP : ${INCLUDE_JSI_CPP}")
endif()

add_library(${PACKAGE_NAME}  # <-- Library name
        SHARED
        ../cpp/react-native-memcachejsi.cpp
        ./cpp-adapter.cpp
        ${INCLUDE_JSI_CPP} # only on older RN versions
)

set_target_properties(
        ${PACKAGE_NAME} PROPERTIES
        CXX_STANDARD 17
        CXX_EXTENSIONS OFF
        POSITION_INDEPENDENT_CODE ON
)

file (GLOB LIBRN_DIR "${PREBUILT_DIR}/${ANDROID_ABI}")
message(STATUS "LIBRN_DIR: ${LIBRN_DIR}")

find_library(
        LOG_LIB
        log
)

if(${REACT_NATIVE_VERSION} LESS 66)
  # JSI lib didn't exist on RN 0.65 and before. Simply omit it.
  set (JSI_LIB "")
else()
  # RN 0.66 distributes libjsi.so, can be used instead of compiling jsi.cpp manually.
  find_library(
          JSI_LIB
          jsi
          PATHS ${LIBRN_DIR}
          NO_CMAKE_FIND_ROOT_PATH
  )
endif()

find_library(
        REACT_NATIVE_JNI_LIB
        reactnativejni
        PATHS ${LIBRN_DIR}
        NO_CMAKE_FIND_ROOT_PATH
)

find_package(MemCache REQUIRED CONFIG)

target_link_libraries(
        ${PACKAGE_NAME}
        MemCache::MemCache
        ${LOG_LIB}  # <-- This line was modified
        ${JSI_LIB}
        ${REACT_NATIVE_JNI_LIB}
        android
)
