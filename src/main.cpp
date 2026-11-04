#include <bn_core.h>
#include <bn_display.h>
#include <bn_rect.h>
#include <bn_sprite_ptr.h>
#include <bn_sprite_text_generator.h>

#include "Player.h"
#include "Enemy.h"
#include "ScoreDisplay.h"

static constexpr int MIN_Y = -bn::display::height() / 2;
static constexpr int MAX_Y = bn::display::height() / 2;
static constexpr int MIN_X = -bn::display::width() / 2;
static constexpr int MAX_X = bn::display::width() / 2;

// The maximum number of enemys
static constexpr int MAX_ENEMIES = 6;

// Start enemy speed
static constexpr double ENEMY_SPEED = 1;
static constexpr double ENEMY_SPEED_BUMP = 0.1;
static constexpr int FIRST_FAST_ENEMY_INDEX = 2;

// Starting location
static constexpr int START_X = 44;
static constexpr int START_Y = 22;

static constexpr int E_START_X = 0;
static constexpr int E_START_Y = 0;

// Helper function to get the required enemy speed per enemy spawned
double speed_for_index(int index)
{
    if (index < FIRST_FAST_ENEMY_INDEX)
    {
        return ENEMY_SPEED;
    }

    int enemies_past_max = index - FIRST_FAST_ENEMY_INDEX + 1;
    return ENEMY_SPEED + ENEMY_SPEED_BUMP * enemies_past_max;
}

int main()
{
    bn::core::init();

    // Create a new score display
    ScoreDisplay scoreDisplay = ScoreDisplay();

    // Create a player and initialize it
    Player player = Player(START_X, START_Y);

    bn::vector<Enemy, MAX_ENEMIES> enemies = {};

    while (true)
    {
        // Check when to spawn an enemy
        if (enemies.size() == 0)
        {
            // Add to the enemies array and apply correct speed
            enemies.push_back(Enemy(E_START_X, E_START_Y, player, speed_for_index(enemies.size())));
        }
        if (scoreDisplay.score % 100 == 0 && enemies.size() < enemies.max_size())
        {
            // Add to the enemies array and apply correct speed
            enemies.push_back(Enemy(E_START_X, E_START_Y, player, speed_for_index(enemies.size())));
        }

        for (Enemy &e : enemies)
        {
            // Reset the current score and player position if the player collides with any enemy
            if (e.bounding_box.intersects(player.bounding_box))
            {
                scoreDisplay.resetScore();
                player.sprite.set_x(44);
                player.sprite.set_y(22);
                enemies.clear();
                break;
            }

            e.update();
        }

        player.update();

        // Update the scores and disaply them
        scoreDisplay.update();

        bn::core::update();
    }
}