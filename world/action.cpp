#include "action.h"
#include "game_object.h"
#include "world.h"

void Jump::perform(World&, GameObject& obj) {
    obj.obj_physics.velocity.y = obj.obj_physics.jump_velocity;
}

void MoveRight::perform(World&, GameObject& obj) {
    obj.obj_physics.acceleration.x = obj.obj_physics.walk_acceleration;
}