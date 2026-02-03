#include "player.h"

Player::Player(const Vec<float> &position, const Vec<float> &size)
    : position{position}, size{size}, velocity{0, 0} {}

void Player::handle_input() {
    const bool *key_states = SDL_GetKeyboardState(NULL);

    velocity.x = velocity.y = 0;
    float spd = 8; // TEMP
    if (key_states[SDL_SCANCODE_UP]) {
        velocity.y -= spd;
    }
    if (key_states[SDL_SCANCODE_DOWN]) {
        velocity.y += spd;
    }
    if (key_states[SDL_SCANCODE_LEFT]) {
        velocity.x -= spd;
    }
    if (key_states[SDL_SCANCODE_RIGHT]) {
        velocity.x += spd;
    }
}

void Player::update() {}

std::pair<SDL_FRect, Color> Player::get_sprite() const {
    return {{position.x, position.y, size.x, size.y}, {0, 0, 255, 255}};
}