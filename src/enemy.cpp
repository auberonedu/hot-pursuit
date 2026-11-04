#include "enemy.h"
#include "player.h"

#include "bn_sprite_items_square.h"

Enemy::Enemy(bn::fixed x, bn::fixed y, bn::fixed mob_speed, bn::size mob_size) :
    mob(bn::sprite_items::square.create_sprite(x, y)),
    speed(mob_speed),
    size(mob_size),
    bounding_box(create_bounding_box(mob, mob_size))
    {}

void update(Player& player) {
    //Just remembered to update the hitbox of the enemy for every frame it moves
    //Also hitbox logic should be at the top so that the hitbox doesn't feel
    //delayed and is more reactive.
    bounding_box = create_bounding_box(mob, size);

    //Current enemy x/y coordinates. (simplifies code)
    bn::fixed current_x = mob.x();
    bn::fixed current_y = mob.y();

    //Current player x/y coordinates
    bn::fixed goal_x = player.sprite.x();
    bn::fixed goal_y = player.sprite.y();

    //Looks at the x coordinate of the enemy
    if(current_x < goal_x) {
            mob.set_x(mob.x() + speed);
    }
    if(current_x > goal_x) {
            mob.set_x(mob.x() - speed);
    }
    //Looks at the y coordinate of the enemy
    if(current_y < goal_y) {
            mob.set_y(mob.y() + speed);
    }
    if(current_y > goal_y) {
            mob.set_y(mob.y() - speed);
    }
}

void enemy_position(Enemy& enemy, bn::random& rand) {
    int rand_v = rand.get_int(-50, 50);

    enemy.mob.set_x(rand_v);
    enemy.mob.set_y(rand_v);
}