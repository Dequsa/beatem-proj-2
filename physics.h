
enum class direction_t
{
    DIRECTION_NONE = 0,
    DIRECTION_UP,
    DIRECTION_DOWN,
    DIRECTION_LEFT,
    DIRECTION_RIGHT
};

class Movement
{
private:
    float velocit_; // overall velocity pythorean theorem sqrt(vx^2 + vy^2)
    float velocity_x_;
    float velocity_y_;
    float speed_multiplier_; // multiplier for speed (e.g., running vs walking)
public:
    void calculate_velocity(direction_t direction);
    void set_speed_multiplier(float multiplier) { speed_multiplier_ = multiplier; }

    // getters
    float get_velocity() {return velocit_; }
};