cmake_minimum_required(VERSION 2.8)


if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose the type of build, options are: Debug Release RelWithDebInfo MinSizeRel." FORCE)
endif()

project(sample_2)

macro(append_linker_flags FLAGS)
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${FLAGS}")
endmacro()

if (EMSCRIPTEN)
	set(CMAKE_EXECUTABLE_SUFFIX ".html")

	# 加载配置文件
	# append_linker_flags("--js-library ${CMAKE_CURRENT_LIST_DIR}/js_library.js")

	# 链接 webGL
	append_linker_flags("-lGL")

	append_linker_flags("--closure 1")
	append_linker_flags("-sTEXTDECODER=2")
	append_linker_flags("-sMINIMAL_RUNTIME=2")
	append_linker_flags("-sMIN_WEBGL_VERSION=2 -sMAX_WEBGL_VERSION=2")

	add_definitions(-DMAX_WEBGL_VERSION=2)

	append_linker_flags("-sENVIRONMENT=web")
	append_linker_flags("-sMIN_FIREFOX_VERSION=70")
	append_linker_flags("-sMIN_SAFARI_VERSION=130000")
	append_linker_flags("-sMIN_IE_VERSION=0x7FFFFFFF")
	append_linker_flags("-sMIN_EDGE_VERSION=79") 
	append_linker_flags("-sMIN_CHROME_VERSION=80")
	append_linker_flags("-sABORTING_MALLOC=0")
	append_linker_flags("-sGL_SUPPORT_AUTOMATIC_ENABLE_EXTENSIONS=0")
	append_linker_flags("-sGL_EXTENSIONS_IN_PREFIXED_FORMAT=0")
	append_linker_flags("-sGL_EMULATE_GLES_VERSION_STRING_FORMAT=0")
	append_linker_flags("-sGL_POOL_TEMP_BUFFERS=0")
	append_linker_flags("-sGL_TRACK_ERRORS=0")
	append_linker_flags("-sGL_SUPPORT_SIMPLE_ENABLE_EXTENSIONS=0")
	append_linker_flags("-Oz")
	append_linker_flags("-sSUPPORT_ERRNO=0")
	append_linker_flags("-sFILESYSTEM=0")
endif()

file(GLOB_RECURSE sources *.cpp *.c *.h)
add_executable(sample_2 ${sources})

# copy 资源
file(GLOB_RECURSE assets *.png)
foreach(asset ${assets})
	file(COPY "${asset}" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/")
endforeach()