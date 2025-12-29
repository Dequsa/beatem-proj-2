#pragma once
#include "player.h"

namespace camera_constants
{
    constexpr float BACKGROUND_SIZE_RATIO = (1920.0f/2816.0f); // background size ratio compared to screen size |   SCREEN_WIDTH / BACKGROUND_WIDTH
}

// camera is going to be moving everything in the game world based on player position e.g background positionand other entities
class Camera
{
private:
    position_t position_;
    float zoom_;
    float speed_;

public:
    Camera(float x, float y, float zoom ); // this sets the camera position and dimensions

    ~Camera();

    void move(direction_t current_move_direction, float current_player_speed);

    // getters
    position_t get_position() { return position_};
    float get_zoom() { return zoom_; }
};