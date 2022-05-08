/* date = November 13th 2021 11:08 am */

#ifndef HFECS_H
#define HFECS_H

#include "../datatypes/hfvector.h"
#include "../datatypes/hfqueue.h"

#define HF_ECS_MAX_ENITIES (u32)(10000)

typedef struct hf_ecs_component{
    const char* name;
    u64 size;
    u32 id;
    
}hf_ecs_component;

typedef u32 hf_entity;

typedef struct hf_ecs{
    hf_vector entity_array;
    u32 entity_amount;
    
    hf_vector component_arrays;
    hf_vector component_types;
    u64 component_ammount;
    u64 current_component_id;
    
}hf_ecs;

void hf_ecs_init(hf_ecs* ecs);

void hf_ecs_destroy(hf_ecs* ecs);

u32 hf_ecs_generate_new_component_id(hf_ecs* ecs);

u32 hf_ecs_internal_register_component(hf_ecs* ecs, hf_ecs_component* component);

hf_entity hf_ecs_create_entity(hf_ecs* ecs);

void hf_ecs_destroy_entity(hf_ecs* ecs, hf_entity entity);

hf_ecs_component* hf_ecs_internal_create_component_id(hf_ecs* ecs, const char* name, u64 size);

#define hf_ecs_register_component(ecs, component) hf_ecs_internal_register_component(ecs, hf_ecs_internal_create_component_id(ecs, #component, sizeof(component)));
void hf_ecs_internal_add_component(hf_ecs* ecs, hf_entity entity, const char* name, u64 size, void* data);
#define hf_ecs_add_component(ecs, entity, component, data) hf_ecs_internal_add_component(ecs, entity, #component, sizeof(component), data)

void* hf_ecs_internal_get_component(hf_ecs* ecs, hf_entity entity, const char* name);
#define hf_ecs_get_component(ecs, entity, component) hf_ecs_internal_get_component(ecs, entity, #component)

void hf_ecs_internal_remove_component(hf_ecs* ecs, hf_entity entity, const char* name);
#define hf_ecs_remove_component(ecs, entity, component) hf_ecs_internal_remove_component(ecs, entity, #component)



#endif //HFECS_H
