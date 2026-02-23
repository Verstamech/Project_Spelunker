#include "game_object.h"

#include "action.h"
#include "physics.h"
#include "fsm.h"

GameObject::GameObject(const Vec<float>& position, const Vec<float>& size, World& world, FSM *fsm, Color color)
    : obj_physics{position,{0,0}, {0, 0}}, size{size}, spd{4}, fsm{fsm}, color{color} {
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

    ActionType action_type = ActionType::None;
    if (key_states[SDL_SCANCODE_SPACE] || key_states[SDL_SCANCODE_X]) {
        action_type = ActionType::Jump;
    }
    else if (key_states[SDL_SCANCODE_RIGHT] || key_states[SDL_SCANCODE_D]) {
        action_type = ActionType::MoveRight;
        dir = 1;
    }

    Action* action = fsm->current_state->input(world, *this, action_type);
    if (action != nullptr) {
        action->perform(world, *this);
        delete action;
    }
}

void GameObject::update(World& world, double dt) {
    fsm->current_state->update(world, *this, dt);
}

std::pair<Vec<float>, Color> GameObject::get_sprite() const {
    return {obj_physics.position, color};
}