cmake_minimum_required(VERSION 2.8)


if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose the type of build, options are: Debug Release RelWithDebInfo MinSizeRel." FORCE)
endif()

project(wechat)

macro(append_linker_flags FLAGS)
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${FLAGS}")
endmacro()

if (EMSCRIPTEN)
	set(CMAKE_EXECUTABLE_SUFFIX ".html")

	# 链接 webGL
	append_linker_flags("-lGL")

	# 优先生成设置代码包体积
	append_linker_flags("-sTEXTDECODER=2")
	append_linker_flags("-sMIN_WEBGL_VERSION=2 -sMAX_WEBGL_VERSION=2")

	# Tell the example code in webgl.c that we are only targeting WebGL 2.
	add_definitions(-DMAX_WEBGL_VERSION=2)

	# 生成的生成输出只能在web浏览器中运行
	append_linker_flags("-sENVIRONMENT=web")
endif()

file(GLOB_RECURSE sources *.cpp *.c *.h)
add_executable(wechat ${sources})

# copy 资源
file(GLOB_RECURSE assets *.png)
foreach(asset ${assets})
	file(COPY "${asset}" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/")
endforeach()