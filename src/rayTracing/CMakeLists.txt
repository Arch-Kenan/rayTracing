
set( PROJECT_rayTracing "rayTracing")

include_directories(
	${CMAKE_CURRENT_SOURCE_DIR}
	#...
)

# 查找当前目录下的所有源文件
# 并将名称保存到 DIR_SRCS 变量
aux_source_directory(.  DIR_SRCS)

#打开USE_FOLDERS的配置
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

#分组
file(GLOB  INCS *.h )
file(GLOB  SRCS *.cpp )

#file(GLOB_RECURSE INCS "*.h")
#add_library(myLib ${SRCS} ${INCS})

source_group("Header Files" FILES ${INCS} )
source_group("Source Files" FILES ${SRCS} )


# 指定生成目标
add_executable( ${PROJECT_rayTracing} ${DIR_SRCS} ${INCS})

#aux_source_directory( .  SourceFils)
