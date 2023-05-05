
project(echecs)

set(SRC board.cpp main.cpp view.cpp mask.cpp)
set(HEADER board.hpp types.hpp view.hpp mask.hpp)

add_executable(main ${SRC} ${HEADER})
