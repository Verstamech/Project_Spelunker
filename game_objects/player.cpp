#include "player.h"
#include "physics.h"

Player::Player(const Vec<float> &position, const Vec<float> &size)
    : position{position}, size{size}, velocity{0, 0}, use_physics{false}, spd{400}, dir{1}, physics_button_hit{false} {
    acceleration.y = gravity;
}

void Player::handle_input() {
    const bool *key_states = SDL_GetKeyboardState(NULL);

    acceleration.x = 0;
    dir = 0;
    /*
     *if (key_states[SDL_SCANCODE_UP] || key_states[SDL_SCANCODE_W]) {
        velocity.y -= spd;
    }
    if (key_states[SDL_SCANCODE_DOWN] || key_states[SDL_SCANCODE_S]) {
        velocity.y += spd;
    }
    */
    if (key_states[SDL_SCANCODE_R]) {
        // Toggle physics on and off. TODO: Replace later with better handling of single key presses
        if (!physics_button_hit) {
            use_physics = !use_physics;
            physics_button_hit = true;
        }
    }
    else {
        physics_button_hit = false;
    }

    if (key_states[SDL_SCANCODE_LEFT] || key_states[SDL_SCANCODE_A]) {
        acceleration.x -= walk_acceleration;
        dir = -1;
    }
    if (key_states[SDL_SCANCODE_RIGHT] || key_states[SDL_SCANCODE_D]) {
        acceleration.x += walk_acceleration;
        dir = 1;
    }
    if (key_states[SDL_SCANCODE_SPACE] || key_states[SDL_SCANCODE_X]) {
        velocity.y = -jump_velocity;
    }
}

void Player::update() {}

std::pair<SDL_FRect, Color> Player::get_sprite() const {
    return {{position.x, position.y, size.x, size.y}, {0, 0, 255, 255}};
}