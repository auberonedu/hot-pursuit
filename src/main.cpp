#include <bn_core.h>
#include <bn_rect.h>
#include <bn_size.h>
#include <bn_sprite_ptr.h>
#include <bn_vector.h>

//to create random values
#include <bn_random.h>

#include "player.h"
#include "enemy.h"
#include "score.h"

//music
#include "bn_sound_items.h"

// Width and height of the the player bounding box
static constexpr bn::size PLAYER_SIZE = {8, 8};
static constexpr bn::size ENEMY_SIZE = {8, 8};

int main() {
    bn::core::init();

    bn::random rand;
    //random spawn for new enemys
    bn::random rand_spawn;

    // Create a new score display
    ScoreDisplay scoreDisplay = ScoreDisplay();

    // Create a player and initialize it
    // TODO: we will move the initialization logic to a constructor.
    Player player = Player(44, 22, 1.5, PLAYER_SIZE);

    //frame counter
    int frames = 0;
    int spawn_time = 600;

    //enemy speed settings
    bn::fixed Espeed = 0.75;
    bn::fixed Eincrease = 0.25;
    bn::fixed Emax = 2;    

    //Enemy vector
    bn::vector<Enemy, 5> enemies;

    // Manually add a few enemies
    enemies.push_back(Enemy(-40, 30, 0.5, ENEMY_SIZE));
    
    while(true) {
        player.update();

        frames++;

        if (frames >= spawn_time) {
            frames = 0;

            if (!enemies.full()) {
                int random_x = rand_spawn.get_int(-150, 150);
                int random_y = rand_spawn.get_int(-150, 150);

                enemies.push_back(Enemy(random_x, random_y, Espeed, ENEMY_SIZE));

                //Increases new incoming enemy speed
                if (Espeed < Emax) {
                    Espeed += Eincrease;
                }
            }   
        }

        for(int i = 0; i < enemies.size(); i++) {
            enemies[i].update(player);

            // Reset the current score and player position if the player collides with any enemy
            if(enemies[i].bounding_box.intersects(player.bounding_box)) {
                scoreDisplay.resetScore();
                player.sprite.set_x(44);
                player.sprite.set_y(22);

                bn::sound_items::oink.play();

                //Resets the 10 second timer
                frames = 0;

                //Resets enemy speed
                Espeed = 0.75;
                
                //Resets enemy size when colliding with the player
                while(enemies.size() > 1) {
                    enemies.pop_back();
                }

                enemy_position(enemies[0], rand);
            }
        }

        // Update the scores and disaply them
        scoreDisplay.update();

        bn::core::update();
    }
}