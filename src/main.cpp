#include <bn_core.h>
#include <bn_color.h>
#include <bn_backdrop.h>
#include <bn_log.h>

#include "Player.h"
#include "enemy.h"
#include "scoredisplay.h"


int main() {
    bn::core::init();
    //background
    bn::backdrop::set_color(bn::color(5,17,7));

    bn::random random;

    bn::vector<Enemy, MAX_ENEMIES> enemies = {};

    // Create a new score display
    ScoreDisplay scoreDisplay = ScoreDisplay();

    // Create a player and initialize it
    // TODO: we will move the initialization logic to a constructor.
    Player player = Player();

    // Enemy enemy = Enemy(80, 40);
    // enemies.push_back(Enemy(random.get_unbiased_fixed(MIN_X, MIN_Y), random.get_unbiased_fixed(MIN_X, MIN_Y)));
    // enemies.push_back(Enemy(random.get_unbiased_fixed(MIN_X, MIN_Y), random.get_unbiased_fixed(MIN_X, MIN_Y)));
    // enemies.push_back(Enemy(random.get_unbiased_fixed(MIN_X, MIN_Y), random.get_unbiased_fixed(MIN_X, MIN_Y)));
    
    // player.sprite.set_x(44);
    // player.sprite.set_y(22);
    // player.speed = 1.5;
    // player.size = PLAYER_SIZE;
    // player.bounding_box = create_bounding_box(player.sprite, player.size);

    //bn::sprite_ptr enemy_sprite = bn::sprite_items::square.create_sprite(-30, 22);
    //bn::rect enemy_bounding_box = create_bounding_box(enemy_sprite, ENEMY_SIZE);


    //define timer for additional enemies
    int addTimer = 0;

    while(true) {
        player.update();
        
        //enemy.update(player);

        //add the for loop to loop over enemies
        for(int i = 0; i< enemies.size(); i++){
            //update the vector to the players location using the index
            enemies[i].update(player);

            // Reset the current score and player position if the player collides with enemy
            if(enemies[i].player_caught == true) {
                scoreDisplay.resetScore();
                player.sprite.set_x(44);
                player.sprite.set_y(22);  
                
                while(enemies.size() >1){
                    enemies.pop_back();
                }
                
                //update the player bounding box
                player.bounding_box = create_bounding_box(player.sprite, player.size);
            }
        }
        
        //When timer hits 0, add an enemy and reset to 60;
        if(addTimer == 0) {
            addTimer = 180;

            //move add_enemy to main

            if(enemies.size() < enemies.max_size()) {
                bn::fixed start_x = random.get_unbiased_fixed(MIN_X, MAX_X);
                bn::fixed start_y = random.get_unbiased_fixed(MIN_Y, MAX_Y);

                bn::fixed enemySpeed = 0.7 + (enemies.size() * bn::fixed(0.2));
                BN_LOG(enemySpeed);


                enemies.push_back(Enemy(start_x, start_y, enemySpeed));

            }
        } else if(addTimer > 0) {
            addTimer -= 1;
        }


        // Update the scores and disaply them
        scoreDisplay.update();
        

        bn::core::update();
    }
}