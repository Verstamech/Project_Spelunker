#include "player.h"
#include "physics.h"

Player::Player(const Vec<float> &position, const Vec<float> &size)
    : position{position}, size{size}, velocity{0, 0} {
    acceleration.y = gravity;
}

void Player::handle_input() {
    const bool *key_states = SDL_GetKeyboardState(NULL);

    //acceleration.x = 0;
    velocity.x = velocity.y = 0;
    float spd = 8; // TEMP
    /*
     *if (key_states[SDL_SCANCODE_UP] || key_states[SDL_SCANCODE_W]) {
        velocity.y -= spd;
    }
    if (key_states[SDL_SCANCODE_DOWN] || key_states[SDL_SCANCODE_S]) {
        velocity.y += spd;
    }
    */
    if (key_states[SDL_SCANCODE_LEFT] || key_states[SDL_SCANCODE_A]) {
        //velocity.x -= spd;
        acceleration.x += -walk_acceleration;
    }
    if (key_states[SDL_SCANCODE_RIGHT] || key_states[SDL_SCANCODE_D]) {
        //velocity.x += spd;
        acceleration.x += walk_acceleration;
    }
    if (key_states[SDL_SCANCODE_SPACE] || key_states[SDL_SCANCODE_X]) {
        velocity.y = -jump_velocity;
    }
}

void Player::update() {}

std::pair<SDL_FRect, Color> Player::get_sprite() const {
    return {{position.x, position.y, size.x, size.y}, {0, 0, 255, 255}};
}