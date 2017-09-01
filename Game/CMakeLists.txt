cmake_minimum_required(VERSION 3.8)

set(GAME_SRC
        game.cpp
        game.h
        main.cpp
        src/Snapshot.cpp
        src/Snapshot.h
        src/entities/Bullet.cpp
        src/entities/Bullet.h
        src/entities/entity.cpp
        src/entities/entity.h
        src/entities/Player.cpp
        src/entities/Player.h)

add_executable(game ${GAME_SRC})
target_link_libraries(game MattEngine)
target_link_libraries(game networkLib)

#target_link_libraries(game glfw3)
#
#target_link_libraries(game GLEW)
#target_link_libraries(game SOIL)
