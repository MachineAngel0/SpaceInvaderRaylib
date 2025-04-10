//
// Created by Adams Humbert on 4/9/2025.
//

#ifndef ECS_ENTITY_H
#define ECS_ENTITY_H
#include <cstdint>


using Entity = uint32_t;
static Entity max_entity_count = 0;

inline Entity CreateEntity()
{
    const Entity new_entity = max_entity_count++;
    return new_entity;
}



#endif //ECS_ENTITY_H
