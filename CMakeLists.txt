cmake_minimum_required(VERSION 3.31)
project(cookbook)

set(CMAKE_CXX_STANDARD 17)

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
    include_directories("C:/Users/jtmil/PDCurses-master")  # points to root where curses.h is
    # Link directly to the static library file instead of using -lpdcurses
    target_link_libraries(cookbook "C:/Users/jtmil/PDCurses-master/wincon/pdcurses.a")
else()
    # Linux/Unix - ncurses
    find_package(Curses REQUIRED)
    include_directories(${CURSES_INCLUDE_DIR})
    target_link_libraries(cookbook ${CURSES_LIBRARIES})
endif()
