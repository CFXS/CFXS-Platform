set(CMAKE_UNITY_BUILD true)
set(CMAKE_UNITY_BUILD_BATCH_SIZE 16)

file(GLOB_RECURSE sources CONFIGURE_DEPENDS
  "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

file(GLOB_RECURSE headers CONFIGURE_DEPENDS
  "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h"
  "${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp"
)

set_source_files_properties(${sources} PROPERTIES LANGUAGE CXX)

add_library(CFXS_Platform ${sources} ${headers})
target_include_directories(CFXS_Platform PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(CFXS_Platform PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

if(${CFXS_STARTUP_PLATFORM} STREQUAL "TM4C129X")
  target_sources(${CMAKE_PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/private/Startup/TM4C129X.cpp")
else()
  message(FATAL_ERROR "CFXS-Platform unsupported CFXS_STARTUP_PLATFORM")
endif()

target_compile_definitions(CFXS_Platform PUBLIC
  "EASTL_OPENSOURCE=1"
  "EASTL_EXCEPTIONS_ENABLED=0"
  "EASTL_RTTI_ENABLED=0"
)

target_precompile_headers(
  CFXS_Platform
  PUBLIC
  <stddef.h>
  <stdint.h>
  <stdbool.h>
  <string.h>
  <new>
)