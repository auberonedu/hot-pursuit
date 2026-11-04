#pragma once

#include <bn_vector.h>
#include <bn_sprite_ptr.h>
#include <bn_sprite_text_generator.h>

// Number of characters required to show two of the longest numbers possible in an int
static constexpr int MAX_SCORE_CHARS = 22;

// Score location
static constexpr int SCORE_X = 70;
static constexpr int SCORE_Y = -70;

// High score location
static constexpr int HIGH_SCORE_X = -70;
static constexpr int HIGH_SCORE_Y = -70;

class ScoreDisplay
{
public:
    ScoreDisplay();

    void update();
    void show_number(int x, int y, int number);
    void resetScore();

    int score;
    int high_score;
    bn::vector<bn::sprite_ptr, MAX_SCORE_CHARS> score_sprites;
    bn::sprite_text_generator text_generator;
};