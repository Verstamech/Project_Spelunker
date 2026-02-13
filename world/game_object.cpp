#include "game_object.h"
#include "physics.h"

GameObject::GameObject(const Vec<float>& position, const Vec<float>& size, World& world)
    : position{position}, size{size}, spd{4} {
    acceleration.y = obj_physics.gravity;
}

GameObject::~GameObject() {}

void GameObject::input(World& world) {
    const bool *key_states = SDL_GetKeyboardState(NULL);

    acceleration.x = 0;
    dir = 0;

    if (key_states[SDL_SCANCODE_R]) {
        use_physics.flip();
    }

    if (key_states[SDL_SCANCODE_LEFT] || key_states[SDL_SCANCODE_A]) {
        acceleration.x += -obj_physics.walk_acceleration;
        dir = -1;
    }
    if (key_states[SDL_SCANCODE_RIGHT] || key_states[SDL_SCANCODE_D]) {
        acceleration.x += obj_physics.walk_acceleration;
        dir = 1;
    }
    if (key_states[SDL_SCANCODE_SPACE] || key_states[SDL_SCANCODE_X]) {
        velocity.y = obj_physics.jump_velocity;
    }
}

void GameObject::update(World& world, double dt) {}

std::pair<Vec<float>, Color> GameObject::get_sprite() const {
    return {position, {0, 0, 255, 255}};
}