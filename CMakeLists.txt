cmake_minimum_required(VERSION 3.15)

#---------------------------------------
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
		add_subdirectory(${_subdir})
	endforeach()
endmacro(ADD_ALL_SUBDIR)

#---------------------------------------
set(Sloution_Name "RTX_Practise")
project (${Sloution_Name})

#------------------------------------------------
#指定可执行文件输出目录
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin) 

#库文件输出目录
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
#---------------------------------------------------
 

include_directories(
	${PROJECT_SOURCE_DIR}/include
	${CMAKE_BINARY_DIR}/config # or PROJECT_BINARY_DIR
	#...
)

Link_directories(
	${PROJECT_SOURCE_DIR}/lib
)

#将所有lib文件存储在变量中
file(GLOB PROJECT_LIB  ${PROJECT_SOURCE_DIR}/lib/*.lib)
add_subdirectory(src)

#message("veue is : ${EXECUTABLE_OUTPUT_PATH}")


