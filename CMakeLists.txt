cmake_minimum_required(VERSION 3.31)
project(cookbook)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)

add_executable(cookbook
        src/Node.h
        src/Recipe.h
        src/RecipeList.cpp
        src/RecipeList.h
        src/t.cpp
        src/cookbook.cpp
        src/Cookbook.h
        src/test.cpp
)

if (WIN32)
    # Windows - PDCurses
    include_directories("C:/Users/jtmil/PDCurses-master")
    link_directories("C:/Users/jtmil/PDCurses-master/wincon")
    set(CURSES_LIB pdcurses)
else()
    # Linux/Unix - ncurses
    find_package(Curses REQUIRED)
    include_directories(${CURSES_INCLUDE_DIR})
    set(CURSES_LIB ${CURSES_LIBRARIES})
endif()

#add_executable(CrossPlatformTUI main.cpp)
#target_link_libraries(CrossPlatformTUI ${CURSES_LIB})
