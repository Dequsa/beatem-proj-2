#include "config_loader.h"

bool load_configurations()
{
    bool success = true;

    // WIP
    success = load_map_config(ConfigConstants::CONFIG_MAP_LOCATION);
    success = load_player_config(ConfigConstants::CONFIG_PLAYER_STATS_LOCATION);
    success = load_enemies_config(ConfigConstants::CONFIG_ENEMIES_LOCATION);

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
