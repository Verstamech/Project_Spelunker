#pragma once
#include <utility>
#include "vec.h"
#include "graphics.h"
#include "physics.h"
#include "toggle.h"

class World;
class FSM;

class GameObject {
public:
    GameObject(const Vec<float>& position, const Vec<float>& size, World& world, FSM* fsm, Color color);
    ~GameObject();

    void input(World& world);
    void update(World& world, double dt);

    std::pair<Vec<float>, Color> get_sprite() const;

    // Player data
    Vec<float> position;
    Vec<float> size;

    Physics obj_physics;

    Toggle use_physics;
    float spd;
    float dir;

    FSM* fsm;
    Color color;
};

