#include <bn_sprite_ptr.h>
#include <bn_size.h>
#include <bn_rect.h>
#include <bn_keypad.h>
#include "bn_sprite_items_square.h"
#include "Enemy.h"
#include "Player.h"

// Enemy speed
static constexpr double ENEMY_SPEED = 1;

// Width and height of the the enemy bounding box
static constexpr bn::size ENEMY_SIZE = {8, 8};

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

class Enemy
{
public:
    bn::sprite_ptr sprite; // Sprite Initializer
    bn::fixed speed;       // The speed of the enemy
    bn::size size;         // The width and height of the sprite
    bn::rect bounding_box; // The rectangle around the sprite for checking collision
    Player &player;

    void update()
    {

        bn::fixed player_x = player.sprite.x();
        bn::fixed player_y = player.sprite.y();

        bn::fixed enemy_x = sprite.x();
        bn::fixed enemy_y = sprite.y();

        if (player_x > enemy_x)
        {
            sprite.set_x(enemy_x + speed);
        }

        if (player_x < enemy_x)
        {
            sprite.set_x(enemy_x - speed);
        }

        if (player_y > enemy_y)
        {
            sprite.set_y(enemy_y + speed);
        }

        if (player_y < enemy_y)
        {
            sprite.set_y(enemy_y - speed);
        }

        bounding_box = create_bounding_box(sprite, size);
    }

    Enemy(bn::fixed x_start, bn::fixed y_start, Player &player_ref) : sprite(bn::sprite_items::square.create_sprite(x_start, y_start)),
                                                                      speed(ENEMY_SPEED),
                                                                      size(ENEMY_SIZE),
                                                                      bounding_box(create_bounding_box(sprite, size)),
                                                                      player(player_ref)
    {
    }
};