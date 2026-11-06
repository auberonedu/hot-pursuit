#pragma once
#include <bn_fixed_point.h>
#include <bn_sprite_ptr.h>
#include <bn_display.h>
#include <bn_sprite_text_generator.h>
#include <bn_keypad.h>
#include <bn_string.h>

static constexpr int MAX_SCORE_CHARS = 22;


class ScoreDisplay {
    int score;                                                 // current score
    int high_score;                                            // best core
    bn::vector<bn::sprite_ptr, MAX_SCORE_CHARS> score_sprites; // Sprites to display scores
    bn::sprite_text_generator text_generator; 

    public:
    ScoreDisplay();


    /**
     * Increases score by 1 and updates high score if needed. Displays score and high score.
     */
    void update();

     /**
     * Displays a number at the given position
     */
    void show_number(int x, int y, int number);


     /**
     * Sets score back to 0. Does NOT reset high score.
     */
    void resetScore();
};

    


