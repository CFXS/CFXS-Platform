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

if("${CFXS_STARTUP_PLATFORM}" STREQUAL "TM4C129X")
  target_sources(${CMAKE_PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/private/Startup/TM4C129X.cpp")
  target_sources(${CMAKE_PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/private/Platform/TM4C/TM4C_CoreInit.cpp")
elseif("${CFXS_STARTUP_PLATFORM}" STREQUAL "STM32H7x3")
  target_sources(${CMAKE_PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/private/Startup/STM32H7x3.cpp")
  target_sources(${CMAKE_PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/private/Platform/STM32/STM32H7x3_CoreInit.cpp")
  file(GLOB_RECURSE hal_sources CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/private/Platform/STM32/STM32H7xx_HAL/*.c"
  )
  file(GLOB_RECURSE hal_headers CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/private/Platform/STM32/STM32H7xx_HAL/*.h"
  )
  list(APPEND sources ${hal_sources})
  list(APPEND headers ${hal_headers})
else()
  message(FATAL_ERROR "CFXS-Platform unsupported CFXS_STARTUP_PLATFORM: [${CFXS_STARTUP_PLATFORM}]")
endif()

set_source_files_properties(${sources} PROPERTIES LANGUAGE CXX)

add_library(CFXS_Platform ${sources} ${headers})
target_include_directories(CFXS_Platform PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(CFXS_Platform PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

if(${CFXS_ARCH} STREQUAL "ARM")
  target_include_directories(CFXS_Platform PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/private/ARM/CMSIS/Core/Include)
endif()

if(${CFXS_STARTUP_PLATFORM} STREQUAL "STM32H7x3")
  target_include_directories(CFXS_Platform PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/private/Platform/STM32/STM32H7xx_HAL/include)
  target_include_directories(CFXS_Platform PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/private/Platform/STM32/STM32H7xx/Include)
endif()

target_compile_definitions(CFXS_Platform PUBLIC
  "EASTL_OPENSOURCE=1"
  "EASTL_EXCEPTIONS_ENABLED=0"
  "EASTL_RTTI_ENABLED=0"
)

target_compile_options(
  CFXS_Platform
  PRIVATE
  -Wno-strict-aliasing
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