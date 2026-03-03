#pragma once
#include <utility>
#include "vec.h"
#include "graphics.h"
#include "physics.h"

class World;
class FSM;
class Input;

class GameObject {
public:
    GameObject(const Vec<float>& position, const Vec<float>& size, World& world, FSM* fsm, Input* input, Color color);
    ~GameObject();

    void update(World& world, double dt);

    std::pair<Vec<float>, Color> get_sprite() const;

    // GameObject Data
    Physics obj_physics;
    Vec<float> size;
    FSM* fsm;
    Input* input;
    Color color;
    Sprite sprite;

    float spd;
    float dir;
    double jump_length = 0;
};
