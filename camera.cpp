#include "camera.h"

Camera::Camera(float x, float y, float zoom) : x_(x), y_(y), zoom_(zoom)
{
    speed_ = player_constants::SPEED_WALKING;
}

Camera::~Camera()
{
    // nothing to clean up for now
}

void Camera::move(direction_t current_move_dirrection, float current_player_speed)
{
    speed_ = current_player_speed;

    switch (current_move_dirrection)
    {
    case direction_t::DIRECTION_LEFT:
        x_ -= speed_;
        break;

    case direction_t::DIRECTION_RIGHT:
        x_ += speed_;
        break;
    default:
        break;
    }
}
