#include "Menu.h"

Menu::Menu() {

}

Menu::~Menu() {
    clear();
}

void Menu::add(Entity *item) {
    _items.push_back(item);
}

void Menu::clear() {
    for (int i = 0; i < _items.size(); i++) {
        delete(_items[i]);
    }
    _items.clear();
}

void Menu::render(MattEngine::SpriteBatch &sb) {
    for (int i = 0; i < _items.size(); i++) {
        _items[i]->draw(sb);
    }
}