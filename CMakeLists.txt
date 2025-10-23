cmake_minimum_required(VERSION 3.12)

set(ENV_ROOT_PATH "${CMAKE_CURRENT_SOURCE_DIR}")

add_subdirectory(thirdparty)

set(CMAKE_CONFIGURATION_TYPES "Debug;Release") 
set(ENV_ARCHITECTURE "x64" CACHE INTERNAL "")

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(COMPILE_OPTIONS "")
set(LINK_OPTIONS "")

set(COMPILE_OPTIONS ${COMPILE_OPTIONS} -D_CRT_SECURE_NO_WARNINGS)
set(COMPILE_OPTIONS ${COMPILE_OPTIONS} -DDS_PLATFORM_WINDOWS)
set(COMPILE_OPTIONS ${COMPILE_OPTIONS} -DDS_PLATFORM_X64)
set(COMPILE_OPTIONS ${COMPILE_OPTIONS} /Zi)

set(LINK_OPTIONS ${LINK_OPTIONS} /DEBUG)

set(DEBUG_COMPILE_OPTIONS   ${COMPILE_OPTIONS} -DDS_CONFIG_DEBUG)
set(RELEASE_COMPILE_OPTIONS ${COMPILE_OPTIONS} -DDS_CONFIG_RELEASE)

set(DEBUG_LINK_OPTIONS   ${LINK_OPTIONS})
set(RELEASE_LINK_OPTIONS ${LINK_OPTIONS})


add_compile_options(
    "$<$<CONFIG:Debug>:${DEBUG_COMPILE_OPTIONS}>"
    "$<$<CONFIG:Release>:${RELEASE_COMPILE_OPTIONS}>"
)

add_link_options(
    "$<$<CONFIG:Debug>:${DEBUG_LINK_OPTIONS}>"
    "$<$<CONFIG:Release>:${RELEASE_LINK_OPTIONS}>"
)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
add_definitions(-DNOMINMAX -DWIN32_LEAN_AND_MEAN)
add_definitions(/MP)

project(DS2OnlineFix C CXX)

enable_language(ASM_MASM)
	
set_source_files_properties(src/xinput/xinput1_3_exports.asm PROPERTIES LANGUAGE ASM_MASM)

SET(SOURCES
	src/dllmain.cpp
	src/framework.h

	src/frpg2/frpg2sv.h
	src/frpg2/frpg2sv.cpp
	src/frpg2/frpg2sv_cache.h
	src/frpg2/frpg2sv_cache.cpp
	
	src/mem/memory.h
	src/mem/memory.cpp
	src/mem/hook.h
	src/mem/hook.cpp
	
	src/xinput/xinput1_3.h
	src/xinput/xinput1_3.cpp
	src/xinput/xinput1_3.def
	src/xinput/xinput1_3_exports.asm
)

add_library(${PROJECT_NAME} SHARED ${SOURCES} ${PLATFORM_SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC 
    "${CMAKE_CURRENT_SOURCE_DIR}" 
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
)

target_compile_definitions(${PROJECT_NAME} PRIVATE -D_CRT_SECURE_NO_WARNINGS -D_WINSOCK_DEPRECATED_NO_WARNINGS)

target_link_options(${PROJECT_NAME} PRIVATE /DEF:src/xinput/xinput1_3.def)

target_link_libraries(
    ${PROJECT_NAME}
	minhook
)

set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "xinput1_3")

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES})