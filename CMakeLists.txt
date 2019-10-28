cmake_minimum_required(VERSION 3.0)
project(castor)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(INCLUDE_EXAMPLE OFF)

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  set(CMAKE_CXX_FLAGS "-Wall -Wextra -g ${CMAKE_CXX_FLAGS}")
endif()

find_package(SDL2 REQUIRED)
find_package(Box2D REQUIRED)

add_subdirectory(src/SANDAL2)
include_directories(src ${SDL2_INCLUDE_DIRS} src/gameEngine src/SANDAL2/src)

file(GLOB_RECURSE castor_sources src/gameEngine/*.cpp)
add_library( castor ${castor_sources})
target_link_libraries(castor
  sandal2
  SDL2_mixer
  ${BOX2D_LIBRARIES}
  )

if(INCLUDE_EXAMPLE)
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
endif()
