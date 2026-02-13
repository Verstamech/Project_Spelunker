#pragma once
#include "camera.h"
#include "game_object.h"
#include "world.h"

class Game {
public:
    Game(std::string title, int width, int height);
    void input();
    void update();
    void render();

private:
    GameObject* player;
    World world;
    Graphics graphics;
    Camera camera;

    // timing
    float dt;
    Uint64 performance_frequency;
    Uint64 prev_counter;
    float lag;
};
