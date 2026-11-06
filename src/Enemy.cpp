#include "Enemy.h"
#include "Player.h"
#include "ScoreDisplay.h"
#include "bn_sprite_items_cat.h"
#include "bn_sprite_items_mouse.h"
#include "boundingBox.h"



static constexpr bn::size ENEMY_SIZE = {8, 8};

Enemy::Enemy(bn::fixed x_start, bn::fixed y_start,bn::fixed speed) : sprite(bn::sprite_items::cat.create_sprite(x_start, y_start)),
                                                   x_speed(speed), y_speed(speed),
                                                   size(ENEMY_SIZE)
    {
        //create_bounding_box(sprite, size);
    }

    void Enemy:: update(Player& player){
        if (player.sprite.x() +20 > sprite.x())
        {
            sprite.set_x(sprite.x() + x_speed);
        }
       if (player.sprite.x() -20 < sprite.x())
        {
            sprite.set_x(sprite.x() - x_speed);
             
        }
        // TODO: Add logic for up and down
        if (player.sprite.y()+20> sprite.y())
         {
            sprite.set_y(sprite.y()  + y_speed) ;
         }

         if (player.sprite.y() -20 < sprite.y())
         {
             sprite.set_y(sprite.y() - y_speed);
         }

       bounding_box = create_bounding_box(sprite, size);

       
    }
    //bn::rect bounding_box;
    
