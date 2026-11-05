#include <bn_core.h>
#include <bn_display.h>
#include <bn_rect.h>
#include <bn_sprite_ptr.h>
#include <bn_sprite_text_generator.h>
#include <bn_optional.h>
#include <bn_random.h>

#include "Player.h"
#include "Enemy.h"
#include "ScoreDisplay.h"
#include "PowerUp.h"

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

// Frames to wait before a new power-up appears
static constexpr int POWER_UP_SPAWN_DELAY = 300;

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

    // Power-up state
    bn::random rng;
    bn::optional<PowerUp> power_up; // empty until one spawns
    int spawn_timer = POWER_UP_SPAWN_DELAY;

    while (true)
    {
        // Check when to spawn an enemy
        if (enemies.size() == 0)
        {
            enemies.push_back(Enemy(E_START_X, E_START_Y, player, speed_for_index(enemies.size())));
        }
        if (scoreDisplay.score % 100 == 0 && enemies.size() < enemies.max_size())
        {
            enemies.push_back(Enemy(E_START_X, E_START_Y, player, speed_for_index(enemies.size())));
        }

        // Spawn or collect power-ups
        if (!power_up.has_value())
        {
            spawn_timer--;
            if (spawn_timer <= 0)
            {
                PowerUpType t = rng.get_int(2) == 0 ? PowerUpType::SPEED : PowerUpType::INVINCIBLE;
                power_up.emplace(rng.get_int(MIN_X + 16, MAX_X - 16),
                                 rng.get_int(MIN_Y + 16, MAX_Y - 16),
                                 t);
            }
        }
        else if (power_up->bounding_box.intersects(player.bounding_box))
        {
            player.apply_power_up(power_up->type);
            power_up.reset();
            spawn_timer = POWER_UP_SPAWN_DELAY;
        }

        for (Enemy &e : enemies)
        {
            // Skip the collision check while invincible
            if (!player.is_invincible() && e.bounding_box.intersects(player.bounding_box))
            {
                scoreDisplay.resetScore();
                player.sprite.set_x(44);
                player.sprite.set_y(22);
                enemies.clear();
                power_up.reset();
                spawn_timer = POWER_UP_SPAWN_DELAY;
                break;
            }

            e.update();
        }

        player.update();

        // Update the scores and display them
        scoreDisplay.update();

        bn::core::update();
    }
}