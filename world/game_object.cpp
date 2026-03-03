#include "game_object.h"
#include "physics.h"
#include "fsm.h"
#include "input.h"

GameObject::GameObject(const Vec<float>& position, const Vec<float>& size, World& world, FSM* fsm, Input* input, Color color)
    : obj_physics{position,{0,0}, {0, 0}}, size{size}, spd{5}, fsm{fsm}, input{input}, color{color} {
    obj_physics.acceleration.y = obj_physics.gravity;
    fsm->current_state->on_enter(world, *this);
}

GameObject::~GameObject() {
    delete fsm;
    delete input;
}

void GameObject::update(World& world, double dt) {
    fsm->current_state->update(world, *this, dt);
}

std::pair<Vec<float>, Color> GameObject::get_sprite() const {
    return {obj_physics.position, color};
}