#include "camera.h"
#include "cstdio"

Camera::Camera(float x, float y, float zoom, float speed) : position_{x, y, 0.0f}, zoom_(zoom), speed_{speed}
{
    // put camera in the middle so the player is in the middle of the screen
    size_.height = utility::SCREEN_HEIGHT / 2;
    size_.width = utility::SCREEN_WIDTH / 2 - 200.0f;
}

Camera::~Camera()
{
    // nothing to clean up for now
}

void Camera::bound_x(float map_width)
{
    // left side bound
    if (position_.x < 0)
    {
        position_.x = 0;
    }

    // right side bound
    if (position_.x + utility::SCREEN_WIDTH > map_width)
    {
        position_.x = map_width - utility::SCREEN_WIDTH;
    }
}

void Camera::bound_y(float map_heigth)
{
    // top bound
    if (position_.y < 0)
    {
        position_.y = 0;
    }

    // bottom bound
    if (position_.y + utility::SCREEN_HEIGHT > map_heigth)
    {
        position_.y = map_heigth - utility::SCREEN_HEIGHT;
    }
}

void Camera::update(position_t player, float map_width, float map_heigth)
{
    position_.x = player.x - size_.width;
    position_.y = player.y - size_.height;

    // check sides
    bound_x(map_width);

    // check top bottom
    bound_y(map_heigth);
}