cmake_minimum_required(VERSION 3.16)

set(SOURCES 
  myproject1_impl.cpp
  myproject.cpp
  )

file(GLOB_RECURSE HEADERS LIST_DIRECTORIES true *.h)
file(GLOB_RECURSE INLINES LIST_DIRECTORIES true *.inl)
set(HEADERS ${HEADERS})
list(APPEND ${HEADERS} ${INLINES})

add_library(${PROJECT_NAME}_lib ${SOURCES} ${HEADERS})
add_library(${PROJECT_NAME}::lib ALIAS ${PROJECT_NAME}_lib)

target_include_directories(${PROJECT_NAME}_lib
  PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include/"
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
)
