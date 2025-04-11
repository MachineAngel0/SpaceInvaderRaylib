//
// Created by Adams Humbert on 4/9/2025.
//

#ifndef ECS_ENTITY_H
#define ECS_ENTITY_H
#include <cstdint>


//using Entity = uint32_t;
using Entity = uint32_t;
static Entity max_entity_count = 0;
// bad name but this is the actual max amount
//constexpr size_t max_entity_amount{1000};

inline Entity CreateEntity()
{
    const Entity new_entity = max_entity_count++;
    return new_entity;
}



#endif //ECS_ENTITY_H
