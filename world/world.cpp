#include "world.h"
#include <algorithm>
#include "physics.h"
#include "game_object.h"

World::World(int width, int height)
    : tilemap{width, height} {}

void World::add_platform(float x, float y, float width, float height) {
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            tilemap(x+j, y+i) = Tile::Platform;
        }
    }
}

bool World::collides(const Vec<float> &position) const {
    int x = std::floor(position.x);
    int y = std::floor(position.y);

    return tilemap(x, y) == Tile::Platform;
}

GameObject* World::create_player(World& world) {
    player = std::make_unique<GameObject>(Vec<float>{10, 5}, Vec<float>{1, 1}, world);
    return player.get();
}

void World::update(float dt) {
    // currently only updating player because we have no other game objects
    auto position = player->position;
    auto velocity = player->velocity;
    auto acceleration = player->acceleration;

    if (!player->use_physics.on) {
        auto spd = player->spd;
        auto dir = player->dir;
        velocity.x = spd * dir;
        velocity.y += 0.5f * acceleration.y * dt;
        position += velocity * dt;
    }
    else {
        velocity += 0.5f * acceleration * dt;
        position += velocity * dt;
        velocity += 0.5f * acceleration * dt;
        velocity.x *= world_physics.damping;
    }

    velocity.x = std::clamp(velocity.x, -world_physics.terminal_velocity, world_physics.terminal_velocity);
    velocity.y = std::clamp(velocity.y, -world_physics.terminal_velocity, world_physics.terminal_velocity);

    // ... the code to update velocity and position

    // check for collisions in the world - x direction
    Vec<float> future_position{position.x, player->position.y};
    Vec<float> future_velocity{velocity.x, 0};
    move_to(future_position, player->size, future_velocity);

    // now y direction after (maybe) moving in x
    future_velocity.y = velocity.y;
    future_position.y = position.y;
    move_to(future_position, player->size, future_velocity);

    // update the player position and velocity
    player->position = future_position;
    player->velocity = future_velocity;
}

void World::move_to(Vec<float>& position, const Vec<float>& size, Vec<float>& velocity) {
    // test for collisions on the bottom or top first
    if (collides({position.x, position.y}) && collides({position.x + size.x, position.y})) {
        position.y = std::ceil(position.y);
        velocity.y = 0;
    }
    else if (collides({position.x, position.y + size.y}) && collides({position.x + size.x, position.y + size.y})) {
        position.y = std::floor(position.y);
        velocity.y = 0;
    }

    // then test for collisions on the left and right sides
    if (collides({position.x, position.y}) && collides({position.x, position.y + size.y})) {
        position.x = std::ceil(position.x);
        velocity.x = 0;
    }
    else if (collides({position.x + size.x, position.y}) && collides({position.x + size.x, position.y + size.y})) {
        position.x = std::floor(position.x);
        velocity.x = 0;
    }

    // now test each corner
    float dx = std::ceil(position.x) - position.x;
    float dy = std::ceil(position.y) - position.y;
    // BOX'S BOTTOM LEFT TOUCHING TOP RIGHT OF AN OBJECT
    if (collides({position.x, position.y})) {
        if (dx > dy) {
            position.y = std::ceil(position.y);
            velocity.y = 0;
        }
        else {
            position.x = std::ceil(position.x);
            velocity.x = 0;
        }
    }
    // BOX'S TOP LEFT TOUCHING BOTTOM RIGHT OF AN OBJECT
    else if (collides({position.x, position.y + size.y})) {
        dx = std::ceil(position.x) - position.x;
        dy = position.y - std::floor(position.y);

        if (dx > dy) {
            position.y = std::floor(position.y);
            velocity.y = 0;
        }
        else {
            position.x = std::ceil(position.x);
            velocity.x = 0;
        }
    }
    // BOX'S TOP RIGHT TOUCHING BOTTOM LEFT OF AN OBJECT
    else if (collides({position.x + size.x, position.y + size.y})) {
        dx = position.x - std::floor(position.x);
        dy = position.y - std::floor(position.y);

        if (dx > dy) {
            position.y = std::floor(position.y);
            velocity.y = 0;
        }
        else {
            position.x = std::floor(position.x);
            velocity.x = 0;
        }
    }
    // BOX'S BOTTOM RIGHT TOUCHING TOP LEFT OF AN OBJECT
    else if (collides({position.x + size.x, position.y})) {
        dx = position.x - std::floor(position.x);
        dy = std::ceil(position.y) - position.y;

        if (dx > dy) {
            position.y = std::ceil(position.y);
            velocity.y = 0;
        }
        else {
            position.x = std::floor(position.x);
            velocity.x = 0;
        }
    }

}