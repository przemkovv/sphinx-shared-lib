project(SphinxSharedLib CXX)

file(GLOB_RECURSE SRC_FILES ${PROJECT_SOURCE_DIR}/*.cpp)
add_library(SphinxSharedLib ${SRC_FILES})

target_include_directories(SphinxSharedLib PUBLIC ${SphinxSharedLib_SOURCE_DIR})
# target_link_libraries(SphinxSharedLib PUBLIC ${Boost_LIBRARIES})
