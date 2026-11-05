#include "PowerUp.h"
#include "bn_sprite_items_powerup.h"

// Width and height of the power-up bounding box
static constexpr int POWER_UP_SIZE = 8;

PowerUp::PowerUp(int x, int y, PowerUpType type) : type(type),
                                                   sprite(bn::sprite_items::powerup.create_sprite(x, y)),
                                                   bounding_box(x, y, POWER_UP_SIZE, POWER_UP_SIZE)
{
}