#include "config_loader.h"

bool load_configurations()
{
    bool success = true;

    success = load_map_config(config_loader::CONFIG_MAP_LOCATION);
    success = load_player_config(config_loader::CONFIG_PLAYER_STATS_LOCATION);
    success = load_enemies_config(config_loader::CONFIG_ENEMIES_LOCATION);

    return success;
}

bool load_map_config(const char *file_path)
{
}

bool load_player_config(const char *file_path)
{
}

bool load_enemies_config(const char *file_path)
{
}
