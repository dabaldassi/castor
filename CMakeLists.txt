cmake_minimum_required(VERSION 2.6)
project(gameEngine)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
#set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
	set(CMAKE_CXX_FLAGS "-std=c++14 -Wall -pedantic ${CMAKE_CXX_FLAGS}")
endif()


file(GLOB_RECURSE sandal2_sources src/SANDAL2/*.c)
add_library(sandal2 ${sandal2_sources})
target_link_libraries(sandal2
  SDL2
  SDL2_ttf
  SDL2_image
  )

file(GLOB_RECURSE ${CMAKE_PROJECT_NAME}_sources src/${CMAKE_PROJECT_NAME}/*.cpp)
add_library( ${CMAKE_PROJECT_NAME} ${${CMAKE_PROJECT_NAME}_sources})
target_link_libraries(${CMAKE_PROJECT_NAME}
  sandal2
  )

file(GLOB_RECURSE game_sources src/game/*.cpp)
add_executable( game ${game_sources})
target_link_libraries(game
  sandal2
  ${CMAKE_PROJECT_NAME}
  )

