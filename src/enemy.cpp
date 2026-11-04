#include "enemy.h"
#include "Player.h"
#include "bn_sprite_items_cop.h"

Enemy::Enemy(bn::fixed x_start, bn::fixed y_start, bn::fixed enemySpeed) : 
    sprite(bn::sprite_items::cop.create_sprite(x_start, y_start)),
     speed(enemySpeed), size(PLAYER_SIZE), 
    enemy_bounding_box(create_bounding_box(sprite, size))
    {}


void Enemy::update(Player& player){
        /*  
        Move the enemy towards the player. 
        Think about how you can achieve this! 
        Consider adding a speed instance variable to the enemy
        Update the bounding box of the enemy
        */

        if(sprite.x() < player.sprite.x()){
            sprite.set_x(sprite.x() + speed);
        }

        if(sprite.x() > player.sprite.x()){
            sprite.set_x(sprite.x() - speed);
        }

        if(sprite.y() > player.sprite.y()){
            sprite.set_y(sprite.y() - speed);
        }

        if(sprite.y() < player.sprite.y()){
            sprite.set_y(sprite.y() + speed);
        }

        enemy_bounding_box = create_bounding_box(sprite, size);

        //make a new boolean to check if player has been caught
        player_caught = false;
        if(enemy_bounding_box.intersects(player.bounding_box)) {
            sprite.set_x(random.get_int(MIN_X, MAX_X));
            sprite.set_y(random.get_int(MIN_Y, MAX_Y));
            enemy_bounding_box = create_bounding_box(sprite, size);

            player_caught = true;
        }

}