#include <bn_core.h>
#include <bn_display.h>
#include <bn_keypad.h>
#include <bn_rect.h>
#include <bn_size.h>
#include <bn_string.h>
#include <bn_sprite_ptr.h>
#include <bn_sprite_text_generator.h>
#include <bn_random.h>
#include "bn_sound_items.h"

#include "common_fixed_8x16_font.h"
#include "bn_sprite_items_dot.h"
#include "bn_sprite_items_square.h"

#include "bn_sprite_items_cat.h"
#include "bn_sprite_items_mouse.h"


#include "Player.h"
#include "ScoreDisplay.h"
#include "Enemy.h"
#include "boundingBox.h"

// Width and height of the the player bounding box
//static constexpr bn::size PLAYER_SIZE = {8, 8};
//static constexpr bn::size ENEMY_SIZE = {8, 8};

/*static constexpr int MIN_Y = -bn::display::height() / 2;
static constexpr int MAX_Y = bn::display::height() / 2;
static constexpr int MIN_X = -bn::display::width() / 2;
static constexpr int MAX_X = bn::display::width() / 2;*/

// Number of characters required to show two of the longest numer possible in an int (-2147483647)
//static constexpr int MAX_SCORE_CHARS = 22;
static constexpr int MAX_ENEMIES = 10;

// Score location
static constexpr int SCORE_X = 70;
static constexpr int SCORE_Y = -70;

// High score location
static constexpr int HIGH_SCORE_X = -70;
static constexpr int HIGH_SCORE_Y = -70;


   


int main()

{

    bn::core::init();

    bn::vector<Enemy, MAX_ENEMIES> enemies = {};
    

    // Create a new score display
    ScoreDisplay scoreDisplay;

    // Create a player and initialize it
    // TODO: we will move the initialization logic to a constructor.
    Player player (0, 0);
    
   
       bn::random rng;

    enemies.push_back(Enemy(15,35,1));
    
    int enemy_timer=0;
    

    while (true)
    {
        player.returnToScreen();
        player.speed();
       enemy_timer++;


        if (enemy_timer >=150){
            if(enemies.size()<MAX_ENEMIES){
                enemies.push_back(Enemy(rng.get_int(-150,150),rng.get_int(-80,80),rng.get_int(1,4)));

            }
            enemy_timer=0;
        }


        bool player_collision=false;



        for (Enemy& enemyy: enemies){
            
          enemyy.update(player);
    
       if(enemyy.bounding_box.intersects(player.bounding_box)){
        player_collision=true;
        bn::sound_items::victory_3.play();
       }
        }



        if(player_collision){
        scoreDisplay.resetScore();
        player.sprite.set_x(44);
        player.sprite.set_y(22);
        player.bounding_box = create_bounding_box(player.sprite, player.size);
        while(enemies.size() > 1) {
                enemies.pop_back();
        }

    }


        // Update the scores and disaply them
         scoreDisplay.update();
        
        bn::core::update();

    }

   
    
}