
project(echecs)

set(SRC2 board.cpp test.cpp view.cpp mask.cpp)
set(SRC3 board.cpp test2.cpp view.cpp mask.cpp game.cpp historique.cpp)
set(SRC board.cpp main.cpp view.cpp mask.cpp)
set(HEADER board.hpp types.hpp view.hpp mask.hpp game.hpp historique.hpp)

add_executable(main ${SRC} ${HEADER})
add_executable(test ${SRC2} ${HEADER})
add_executable(test2 ${SRC3} ${HEADER})
