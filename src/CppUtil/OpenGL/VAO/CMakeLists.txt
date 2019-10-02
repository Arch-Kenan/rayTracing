#项目名，默认为目录名
GET_DIR_NAME(DIRNAME)
set(TARGET_NAME ${DIRNAME})

#多个源文件用 [空格] 分隔
file(GLOB  INCS "${CMAKE_CURRENT_SOURCE_DIR}/*.h" )
file(GLOB  SRCS "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp" )

source_group("Header Files" FILES ${INCS} )
source_group("Source Files" FILES ${SRCS} )

set(STR_TARGET_SOURCES "")
foreach(SOURCE ${INCS})
	set(STR_TARGET_SOURCES "${STR_TARGET_SOURCES} ${SOURCE}")
endforeach(SOURCE ${INCS})

foreach(SOURCE ${SRCS})
	set(STR_TARGET_SOURCES "${STR_TARGET_SOURCES} ${SOURCE}")
endforeach(SOURCE ${SRCS})


set(STR_TARGET_LIBS " ")

SETUP_PROJECT(${MODE} ${TARGET_NAME} ${STR_TARGET_SOURCES} ${STR_TARGET_LIBS})
