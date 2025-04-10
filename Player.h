//
// Created by Adams Humbert on 4/7/2025.
//

#ifndef PLAYER_H
#define PLAYER_H
#include "ECS.h"
#include "GameWindow.h"


inline Entity init_player(ComponentRegistry& component_registry)
{
    // player

    Entity entity_player = CreateEntity();
    component_registry.sprite_atlus[entity_player] = SpriteAtlusComponent{
        .sprite_UV_location = {0, 50},
        .sprite_size = {17, 10},
        .sprite_scale = {2, 2},
    };
    const int ScreenHeightOffset = 20;
    component_registry.transforms[entity_player] = Transform2DComponent{
        .position = Vector2(ScreenWidth / 2 - component_registry.sprite_atlus[entity_player].sprite_size.y,
                              ScreenHeight - component_registry.sprite_atlus[entity_player].sprite_size.y - ScreenHeightOffset),
        .Velocity = {0, 0},
    };
    component_registry.inputs[entity_player] = InputComponent{};

    return entity_player;
}



#endif //PLAYER_H
