#include "Player.h"
#include <bn_sprite_ptr.h>
#include <bn_size.h>
#include <bn_rect.h>
#include <bn_keypad.h>
#include "bn_sprite_items_dot.h"

// Width and height of the the player bounding box
static constexpr bn::size PLAYER_SIZE = {8, 8};

// Player speed
static constexpr double PLAYER_SPEED = 1.5;

/**
 * Creates a rectangle centered at a sprite's location with a given size.
 * sprite the sprite to center the box around
 * box_size the dimensions of the bounding box
 */
bn::rect create_bounding_box(bn::sprite_ptr sprite, bn::size box_size)
{
    return bn::rect(sprite.x().round_integer(),
                    sprite.y().round_integer(),
                    box_size.width(),
                    box_size.height());
}

class Player
{
public:
    bn::sprite_ptr sprite; // Sprite Initializer
    bn::fixed speed;       // The speed of the player
    bn::size size;         // The width and height of the sprite
    bn::rect bounding_box; // The rectangle around the sprite for checking collision
    /**
     * Update the position and bounding box of the player based on d-pad movement.
     */
    void update()
    {
        if (bn::keypad::right_held())
        {
            sprite.set_x(sprite.x() + speed);
        }
        if (bn::keypad::left_held())
        {
            sprite.set_x(sprite.x() - speed);
        }
        if (bn::keypad::up_held())
        {
            sprite.set_y(sprite.y() - speed);
        }
        if (bn::keypad::down_held())
        {
            sprite.set_y(sprite.y() + speed);
        }

        bounding_box = create_bounding_box(sprite, size);
    }

    Player(bn::fixed x_start, bn::fixed y_start) : sprite(bn::sprite_items::dot.create_sprite(x_start, y_start)),
                                                   speed(PLAYER_SPEED),
                                                   size(PLAYER_SIZE),
                                                   bounding_box(create_bounding_box(sprite, size))
    {
    }
};