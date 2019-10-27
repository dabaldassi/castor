cmake_minimum_required(VERSION 2.6)
project(castor)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
#set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  set(CMAKE_CXX_FLAGS "-std=c++14 -Wall -g -pedantic ${CMAKE_CXX_FLAGS}")
endif()

find_package(SDL2 REQUIRED)
find_package(Box2D REQUIRED)

add_subdirectory(src/SANDAL2)
include_directories(src ${SDL2_INCLUDE_DIRS} src/gameEngine src/SANDAL2/src)

# file(GLOB_RECURSE sandal2_sources src/SANDAL2/src/*.c)
# add_library(sandal2 ${sandal2_sources})
# target_link_libraries(sandal2
#   ${SDL2_LIBRARIES}
#   SDL2_ttf
#   SDL2_image
#   SDL2_mixer
#   )

file(GLOB_RECURSE castor_sources src/gameEngine/*.cpp)
add_library( castor ${castor_sources})
target_link_libraries(castor
  sandal2
  SDL2_mixer
  ${BOX2D_LIBRARIES}
  )

file(GLOB_RECURSE game_sources src/game/*.cpp)
add_executable( game ${game_sources})
target_link_libraries(game
  sandal2
  castor
  ${BOX2D_LIBRARIES}
  )


file(GLOB_RECURSE pong_sources src/pong/*.cpp)
add_executable(pong ${pong_sources})
target_link_libraries(pong
  sandal2
  castor
  ${BOX2D_LIBRARIES}
  )
