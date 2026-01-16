#pragma once

namespace ConfigConstants
{
    constexpr char* CONFIG_MAP_LOCATION = "/configs/maps.cfg";
    constexpr char* CONFIG_PLAYER_STATS_LOCATION = "/config/player.cfg";
    constexpr char* CONFIG_ENEMIES_LOCATION = "/config/enemies.cfg";
}

bool load_configurations();

bool load_map_config(const char* file_path);

bool load_player_config(const char* file_path);

bool load_enemies_config(const char* file_path);