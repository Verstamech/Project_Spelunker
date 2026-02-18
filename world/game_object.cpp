#include "game_object.h"
#include "physics.h"
#include "fsm.h"

GameObject::GameObject(const Vec<float>& position, const Vec<float>& size, World& world, FSM *fsm, Color color)
    : position{position}, size{size}, spd{4} {
    obj_physics.acceleration.y = obj_physics.gravity;
    fsm->current_state->on_enter(world, *this);
}

GameObject::~GameObject() {
    delete fsm;
}

void GameObject::input(World& world) {
    const bool *key_states = SDL_GetKeyboardState(NULL);

    obj_physics.acceleration.x = 0;
    dir = 0;

    if (key_states[SDL_SCANCODE_R]) {
        use_physics.flip();
    }

    if (key_states[SDL_SCANCODE_LEFT] || key_states[SDL_SCANCODE_A]) {
        obj_physics.acceleration.x += -obj_physics.walk_acceleration;
        dir = -1;
    }
    if (key_states[SDL_SCANCODE_RIGHT] || key_states[SDL_SCANCODE_D]) {
        obj_physics.acceleration.x += obj_physics.walk_acceleration;
        dir = 1;
    }
    if (key_states[SDL_SCANCODE_SPACE] || key_states[SDL_SCANCODE_X]) {
        obj_physics.velocity.y = obj_physics.jump_velocity;
    }
}

void GameObject::update(World& world, double dt) {}

std::pair<Vec<float>, Color> GameObject::get_sprite() const {
    return {position, color};
}