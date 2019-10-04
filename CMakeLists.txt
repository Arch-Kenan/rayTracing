cmake_minimum_required(VERSION 3.15)

# 宏函数定义
#---------------------------------------------------------------------------------------------------------
#---------------------------------------------------------------------------------------------------------
# add all subdirectoies
macro(ADD_ALL_SUBDIR)
	file(GLOB _children RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/*)
	set(_dirlist "")
	foreach(_child ${_children})
		if(IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${_child})
			list(APPEND _dirlist ${_child})
		endif()
	endforeach()
	#SET(${result} ${dirlist})
	foreach(_subdir ${_dirlist})
		string(REGEX MATCH "([^/]*)$" TMPDIR ${_subdir})
		if( NOT ${TMPDIR} STREQUAL "CMakeFiles" )
			add_subdirectory(${_subdir})
		endif()
	endforeach()
endmacro(ADD_ALL_SUBDIR)

#获取当前路径下文件的文件夹名称
macro(GET_DIR_NAME DIRNAME)
	string(REGEX MATCH "([^/]*)$" TMP ${CMAKE_CURRENT_SOURCE_DIR})
	set(${DIRNAME} ${TMP})
endmacro(GET_DIR_NAME DIRNAME)

# 复制shader文件到目标文件夹
macro(INSTALL_SHADERS)
	file(GLOB SHADERS
		"${CMAKE_CURRENT_SOURCE_DIR}/*.vs"
		"${CMAKE_CURRENT_SOURCE_DIR}/*.fs"
		"${CMAKE_CURRENT_SOURCE_DIR}/*.gs"
	)
	foreach(SHADER ${SHADERS})
		string(REGEX MATCH "([^/]*)$" TMP ${SHADER})
		add_custom_command(TARGET ${TARGET_NAME} PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SHADER} "${CMAKE_SOURCE_DIR}/data/shaders/${FOLDER_NAME}/${DIRNAME}/${TMP}")
		install(FILES ${SHADER} DESTINATION "data/shaders/${FOLDER_NAME}/${DIRNAME}")
	endforeach(SHADER)
endmacro(INSTALL_SHADERS)

#设置工程依名称，依赖库， 和安装路径（注意安装路径和编译路径不同）
macro(SETUP_PROJECT MODE TARGET_NAME STR_TARGET_SOURCES STR_TARGET_LIBS)
	string(REPLACE " " ";" LIST_TARGET_SOURCES ${STR_TARGET_SOURCES})
	string(REPLACE " " ";" LIST_TARGET_LIBS ${STR_TARGET_LIBS})
	
	if(${STR_TARGET_SOURCES} STREQUAL " ")
		message(WARNING "Target [${TARGET_NAME}] has no source, so it won't be generated.")
	else()
		if(${MODE} STREQUAL "EXE")
			add_executable( ${TARGET_NAME} ${LIST_TARGET_SOURCES})
			set(INSTALL_DIR "bin")
		elseif(${MODE} STREQUAL "LIB")
			add_library(${TARGET_NAME} ${LIST_TARGET_SOURCES})
			set_target_properties(${TARGET_NAME} PROPERTIES LINKER_LANGUAGE CXX)
			set(INSTALL_DIR "lib/${FOLDER_NAME}")
		else()
			message(FATAL_ERROR "Mode [${MODE}] is not supported, so target [TARGET_NAME] is not generated!")
			set(MODE_NOTSUPPORT " ")
		endif()
		if(NOT DEFINED MODE_NOTSUPPORT)
			if( NOT ${FOLDER_NAME} STREQUAL " ")
				set_target_properties(${TARGET_NAME} PROPERTIES FOLDER ${FOLDER_NAME})
			endif()
			if(NOT ${STR_TARGET_LIBS} STREQUAL " ")
				target_link_libraries( ${TARGET_NAME} ${LIST_TARGET_LIBS} )
			endif()
			install (TARGETS ${TARGET_NAME} DESTINATION ${INSTALL_DIR})
			message(STATUS "Setup Project ${Mode} ${FOLDER_NAME}/[${TARGET_NAME}] INSTALL_DIR:${INSTALL_DIR}")
		endif()
	endif()
endmacro(SETUP_PROJECT TARGET_NAME STR_TARGET_SOURCES STR_TARGET_LIBS)
#------------------------------------------------------------------------------------------------------------
#------------------------------------------------------------------------------------------------------------



#预定义设置
#------------------------------------------------------------------------------------------------------------
set(Sloution_Name "RTX_Practise")
project (${Sloution_Name})


set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR})

message("________________________________________________${PROJECT_SOURCE_DIR}_____________________________________________")

#安装配置文件
configure_file(config/config.in ${CMAKE_SOURCE_DIR}/config/config.out)
install(FILES "${CMAKE_SOURCE_DIR}/config/config.out"
  DESTINATION config)
configure_file(config/ROOT_PATH.h.in config/ROOT_PATH.h)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)




#指定可执行文件输出目录
#SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin) 
#库文件输出目录
#SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
#---------------------------------------------------
 

include_directories(
	${PROJECT_SOURCE_DIR}/include
	${PROJECT_SOURCE_DIR}/include/CppUtil
	${CMAKE_BINARY_DIR}/config # or PROJECT_BINARY_DIR
	#...
)

Link_directories(
	${PROJECT_SOURCE_DIR}/lib
	${PROJECT_SOURCE_DIR}/lib/CppUtil/Basic
	${PROJECT_SOURCE_DIR}/lib/CppUtil/OpenGL
	${PROJECT_SOURCE_DIR}/lib/CppUtil/RTX
)

#将所有lib文件存储在变量中
file(GLOB PROJECT_LIB  ${PROJECT_SOURCE_DIR}/lib/*.lib)
add_subdirectory(src)



