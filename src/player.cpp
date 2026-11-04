#include "player.h"

#include <bn_display.h>
#include <bn_keypad.h>
#include "bn_sprite_items_dot.h"

// Screen edges, used to keep the player on screen
static constexpr int MIN_Y = -bn::display::height() / 2;
static constexpr int MAX_Y = bn::display::height() / 2;
static constexpr int MIN_X = -bn::display::width() / 2;
static constexpr int MAX_X = bn::display::width() / 2;

/**
 * Creates a rectangle centered at a sprite's location with a given size.
 * sprite the sprite to center the box around
 * box_size the dimensions of the bounding box
 */
bn::rect create_bounding_box(const bn::sprite_ptr& sprite, bn::size box_size) {
    return bn::rect(sprite.x().round_integer(),
                    sprite.y().round_integer(),
                    box_size.width(),
                    box_size.height());
}

Player::Player(bn::fixed x, bn::fixed y, bn::fixed player_speed, bn::size player_size) : 
    sprite(bn::sprite_items::dot.create_sprite(x, y)),
    speed(player_speed),
    size(player_size),
    bounding_box(create_bounding_box(sprite, player_size))
{}

void Player::update() {
    bn::fixed x = sprite.x();
    bn::fixed y = sprite.y();

    if (x > MAX_X) {
        x = MAX_X;
    }
    else if (x < MIN_X) {
        x = MIN_X;
    }
    if (y > MAX_Y) {
        y = MAX_Y;
    }
    else if (y < MIN_Y) {
        y = MIN_Y;
    }

    sprite.set_x(x);
    sprite.set_y(y);

    if(bn::keypad::right_held()) {
        sprite.set_x(sprite.x() + speed);
    }
    if(bn::keypad::left_held()) {
        sprite.set_x(sprite.x() - speed);
    }
    if(bn::keypad::up_held()) {
        sprite.set_y(sprite.y() - speed);
    }
    if(bn::keypad::down_held()) {
        sprite.set_y(sprite.y() + speed);
    }

    bounding_box = create_bounding_box(sprite, size);
}