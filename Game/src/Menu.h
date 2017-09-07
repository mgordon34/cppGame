#pragma once

#include <MattEngine/SpriteBatch.h>
#include <Game/src/entities/entity.h>

class Menu {
public:
    Menu();
    ~Menu();
    void render(MattEngine::SpriteBatch &sb);

    void add(Entity *item);
    void clear();

private:
    std::vector<Entity *>_items;
};
