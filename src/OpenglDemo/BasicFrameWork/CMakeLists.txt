﻿#默认使用目录名作为项目名
GET_DIR_NAME(DIRNAME)
set(TARGET_NAME "${DIRNAME}")

#多个源文件用 [空格] 分隔
file(GLOB  INCS "${CMAKE_CURRENT_SOURCE_DIR}/*.h" )
file(GLOB  SRCS "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

file(GLOB SHADERS
		"${CMAKE_CURRENT_SOURCE_DIR}/*.vs"
		"${CMAKE_CURRENT_SOURCE_DIR}/*.fs"
		"${CMAKE_CURRENT_SOURCE_DIR}/*.gs"
	)

source_group("Header Files" FILES ${INCS} )
source_group("Source Files" FILES ${SRCS} )

set(STR_TARGET_SOURCES "")
foreach(SOURCE ${INCS})
	set(STR_TARGET_SOURCES "${STR_TARGET_SOURCES} ${SOURCE}")
endforeach(SOURCE ${INCS})

foreach(SOURCE ${SRCS})
	set(STR_TARGET_SOURCES "${STR_TARGET_SOURCES} ${SOURCE}")
endforeach(SOURCE ${SRCS})

foreach(SOURCE ${SHADERS})
	set(STR_TARGET_SOURCES "${STR_TARGET_SOURCES} ${SOURCE}")
endforeach(SOURCE ${SHADERS})

set(STR_TARGET_SOURCES "${STR_TARGET_SOURCES} ${CMAKE_SOURCE_DIR}/config/config.in")


set(STR_TARGET_LIBS " ")

SETUP_PROJECT(${MODE} ${TARGET_NAME} ${STR_TARGET_SOURCES} ${STR_TARGET_LIBS})

#拷贝shader文件到目标文件夹
INSTALL_SHADERS()

#拷贝头文件到目标文件夹
INSTALL_HEADER()

