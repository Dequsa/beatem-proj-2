#pragma once
#include "utility.h"
#include "structs.h"

namespace CameraConstants 
{
    const float BACKGROUND_SIZE_RATIO = (utility::SCREEN_WIDTH / 2816.0f); // background size ratio compared to screen size |   SCREEN_WIDTH / BACKGROUND_WIDTH
}

// camera is going to be moving everything in the game world based on player position e.g background positionand other entities
class Camera
{
private:
    bool is_moving_;
    position_t position_;
    dimensions_t size_;
    float zoom_;
    float speed_;
    void bound_x(float map_width);
    void bound_y(float map_height);
public:
    Camera(float x, float y, float zoom, float speed); // this sets the camera position and dimensions

    ~Camera();

    // update camera position
    void update(position_t player, float map_width, float map_height);

    // getters
    position_t get_position() { return position_; }
    float get_zoom() { return zoom_; }
    bool get_state() { return is_moving_; }
};