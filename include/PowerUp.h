#pragma once

#include <bn_sprite_ptr.h>
#include <bn_rect.h>

enum class PowerUpType
{
    SPEED,
    INVINCIBLE
};

class PowerUp
{
public:
    PowerUp(int x, int y, PowerUpType type);

    PowerUpType type;
    bn::sprite_ptr sprite;
    bn::rect bounding_box;
};