#pragma once
#include <SDL3/SDL.h>
#include <utility>
#include "graphics.h"
#include "vec.h"

class Player {
public:
    Player(const Vec<float>& position, const Vec<float>& size);
    void handle_input();
    void update();
    std::pair<SDL_FRect, Color> get_sprite() const;

    // data
    Vec<float> position;
    Vec<float> size;
    Vec<float> velocity;
    Vec<float> acceleration;

    bool use_physics;
    float spd;
    float dir;
    bool physics_button_hit;
};
