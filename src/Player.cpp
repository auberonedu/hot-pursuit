#include "Player.h"
#include <bn_sprite_ptr.h>
#include <bn_size.h>
#include <bn_rect.h>
#include <bn_keypad.h>
#include <bn_display.h> // NEW
#include "bn_sprite_items_player.h"

// Width and height of the the player bounding box
static constexpr bn::size PLAYER_SIZE = {8, 8};

// Player speed
static constexpr double PLAYER_SPEED = 1.5;

// Boost Variables
static constexpr double BOOST_SPEED = 3.0;
static constexpr int POWER_UP_FRAMES = 300;

// Half the screen plus half the sprite, so the player fully leaves before wrapping
static constexpr int WRAP_X = bn::display::width() / 2 + 4;
static constexpr int WRAP_Y = bn::display::height() / 2 + 4;

/**
 * Creates a rectangle centered at a sprite's location with a given size.
 * sprite the sprite to center the box around
 * box_size the dimensions of the bounding box
 */
static bn::rect create_bounding_box(bn::sprite_ptr sprite, bn::size box_size)
{
    return bn::rect(sprite.x().round_integer(),
                    sprite.y().round_integer(),
                    box_size.width(),
                    box_size.height());
}

// Wraps a position to the opposite edge if it goes past the limit.
static bn::fixed wrap(bn::fixed value, int limit)
{
    if (value > limit)
    {
        return -limit;
    }
    if (value < -limit)
    {
        return limit;
    }
    return value;
}

/**
 * Update the position and bounding box of the player based on d-pad movement.
 */
void Player::update()
{
    // Speed boost countdown
    if (speed_timer > 0)
    {
        speed_timer--;
        speed = BOOST_SPEED;
    }
    else
    {
        speed = PLAYER_SPEED;
    }

        // Invincibility countdown and blink effect
    if (invincible_timer > 0)
    {
        invincible_timer--;

        // Visible for 4 frames, hidden for 4 frames, and so on
        sprite.set_visible((invincible_timer / 4) % 2 == 0);
    }
    else
    {
        sprite.set_visible(true);
    }

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

    // Wrap around the screen edges
    sprite.set_x(wrap(sprite.x(), WRAP_X));
    sprite.set_y(wrap(sprite.y(), WRAP_Y));

    bounding_box = create_bounding_box(sprite, size);
}

void Player::apply_power_up(PowerUpType type)
{
    if (type == PowerUpType::SPEED)
    {
        speed_timer = POWER_UP_FRAMES;
    }
    else if (type == PowerUpType::INVINCIBLE)
    {
        invincible_timer = POWER_UP_FRAMES;
    }
}

bool Player::is_invincible() const
{
    return invincible_timer > 0;
}

Player::Player(bn::fixed x_start, bn::fixed y_start) : sprite(bn::sprite_items::player.create_sprite(x_start, y_start)),
                                                       speed(PLAYER_SPEED),
                                                       size(PLAYER_SIZE),
                                                       bounding_box(create_bounding_box(sprite, size)),
                                                       speed_timer(0),
                                                       invincible_timer(0)
{
}