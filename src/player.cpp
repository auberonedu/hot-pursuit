#pragma once

#include "player.h"

// Helper function declaration (assuming this is defined somewhere or in a utility header)
bn::rect create_bounding_box(const bn::sprite_ptr& sprite, bn::size size);

// Screen border constants (adjust these if yours are defined elsewhere)
constexpr bn::fixed MAX_X = 112;
constexpr bn::fixed MIN_X = -112;
constexpr bn::fixed MAX_Y = 72;
constexpr bn::fixed MIN_Y = -72;

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