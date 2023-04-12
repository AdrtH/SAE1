

project(echecs)

set(SRC board.cpp main.cpp view.cpp)
set(HEADER board.hpp types.hpp view.hpp)

add_executable(main ${SRC} ${HEADER})
