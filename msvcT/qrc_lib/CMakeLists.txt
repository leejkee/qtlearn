set(CMAKE_AUTORCC ON)
add_library(qrc_lib STATIC qrc.qrc)

target_link_libraries(qrc_lib PUBLIC
	Qt6::Core
)

target_compile_features(qrc_lib PRIVATE cxx_std_17)

target_include_directories(qrc_lib PUBLIC 
	${CMAKE_CURRENT_SOURCE_DIR}
)
