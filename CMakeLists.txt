set(LIBRARY_NAME CFXS_Platform)

# set(CMAKE_UNITY_BUILD true)
# set(CMAKE_UNITY_BUILD_BATCH_SIZE 16)
file(GLOB_RECURSE sources CONFIGURE_DEPENDS
  "${CMAKE_CURRENT_SOURCE_DIR}/src/CPU/*.c"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/CPU/*.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/EASTL/*.c"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/EASTL/*.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/Heap/*.c"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/Heap/*.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/Print/*.c"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/Print/*.cpp"
)

file(GLOB_RECURSE asm_sources CONFIGURE_DEPENDS
  "${CMAKE_CURRENT_SOURCE_DIR}/src/*.S"
)

file(GLOB_RECURSE headers CONFIGURE_DEPENDS
  "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h"
  "${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp"
)

if("${CFXS_STARTUP_PLATFORM}" STREQUAL "TM4C129")
  file(GLOB_RECURSE tm4c129_sources CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/private/Startup/TM4C129/*.cpp"
  )
  list(APPEND sources ${tm4c129_sources})
  file(GLOB_RECURSE tm4c129_asm_sources CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/private/Startup/TM4C129/*.S"
  )
  list(APPEND asm_sources ${tm4c129_asm_sources})
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
elseif("${CFXS_STARTUP_PLATFORM}" STREQUAL "STM32G4x3")
  target_sources(${CMAKE_PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/private/Startup/STM32G4x3.cpp")
  target_sources(${CMAKE_PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/private/Platform/STM32/STM32G4x3_CoreInit.cpp")
  file(GLOB_RECURSE hal_sources CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/private/Platform/STM32/STM32G4xx_HAL/*.c"
  )
  file(GLOB_RECURSE hal_headers CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/private/Platform/STM32/STM32G4xx_HAL/*.h"
  )
  list(APPEND sources ${hal_sources})
  list(APPEND headers ${hal_headers})
else()
  message(FATAL_ERROR "CFXS-Platform unsupported CFXS_STARTUP_PLATFORM: [${CFXS_STARTUP_PLATFORM}]")
endif()

set_source_files_properties(${sources} PROPERTIES LANGUAGE CXX)
set_source_files_properties(${asm_sources} PROPERTIES LANGUAGE ASM)

add_library(${LIBRARY_NAME} ${asm_sources} ${sources}) # ${headers})
target_include_directories(${LIBRARY_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(${LIBRARY_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_include_directories(${LIBRARY_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/debug)

if(${CFXS_ARCH} STREQUAL "ARM")
  target_include_directories(${LIBRARY_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/private/ARM/CMSIS/Core/Include)
endif()

if(${CFXS_STARTUP_PLATFORM} STREQUAL "STM32H7x3")
  target_include_directories(${LIBRARY_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/private/Platform/STM32/STM32H7xx_HAL/include)
  target_include_directories(${LIBRARY_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/private/Platform/STM32/STM32H7xx/Include)
elseif(${CFXS_STARTUP_PLATFORM} STREQUAL "STM32G4x3")
  target_include_directories(${LIBRARY_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/private/Platform/STM32/STM32G4xx_HAL/include)
  target_include_directories(${LIBRARY_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/private/Platform/STM32/STM32G4xx/Include)
elseif(${CFXS_STARTUP_PLATFORM} STREQUAL "TM4C129")
  target_include_directories(${LIBRARY_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/private/Platform/TM4C)
endif()

if(${CFXS_PLATFORM} STREQUAL "TM4C")
  target_link_libraries(${LIBRARY_NAME} PUBLIC tm4c_driverlib)
else()
  message(FATAL_ERROR "CFXS_Platform unsupported platform")
endif()

target_compile_definitions(${LIBRARY_NAME} PUBLIC
  "EASTL_OPENSOURCE=1"
  "EASTL_EXCEPTIONS_ENABLED=0"
  "EASTL_RTTI_ENABLED=0"
)

target_compile_options(
  ${LIBRARY_NAME}
  PRIVATE
  -Wno-strict-aliasing
)

target_precompile_headers(
  ${LIBRARY_NAME}
  PRIVATE
  <stddef.h>
  <stdint.h>
  <stdbool.h>
  <string.h>
  <new>
  <eastl/array.h>
  <eastl/vector.h>
  <eastl/algorithm.h>
)

target_link_libraries(${LIBRARY_NAME} PRIVATE CFXS_Toolchain)
target_link_libraries(${LIBRARY_NAME} PRIVATE CFXS_Base)

if(${CFXS_PLATFORM_NETWORK})
  target_link_libraries(${LIBRARY_NAME} PRIVATE lwip)

  file(GLOB_RECURSE network_sources CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/private/Network/*.cpp"
  )
  target_sources(${CMAKE_PROJECT_NAME} PUBLIC ${network_sources})
endif()