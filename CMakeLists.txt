cmake_minimum_required(VERSION 3.31)
project(cookbook)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)

add_executable(cookbook
        src/Node.h
        src/Recipe.h
        src/RecipeList.cpp
        src/RecipeList.h
        src/test.cpp)
