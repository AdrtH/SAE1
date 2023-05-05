
project(echecs)

set(SRC board.cpp main.cpp view.cpp mask.cpp)
set(SRC board.cpp test.cpp view.cpp mask.cpp)
set(HEADER board.hpp types.hpp view.hpp mask.hpp)

add_executable(main ${SRC} ${HEADER})
add_executable(test ${SRC} ${HEADER})
