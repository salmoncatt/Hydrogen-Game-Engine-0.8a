#include "hfecs.h"

void hf_ecs_init(hf_ecs* ecs){
    hf_vector_init(&ecs->component_types);
    
    ecs->entity_array.init_capacity = HF_ECS_MAX_ENITIES;
    hf_vector_init(&ecs->entity_array);
    
    for(u32 i = HF_ECS_MAX_ENITIES - 1; i > 0; i--){
        u32* x = malloc(sizeof(u32));
        *x = i - 1;
        hf_vector_push_back(&ecs->entity_array, x);
    }
    
    hf_log("[HF ECS] ecs created\n");
    
    /* 
        printf("size: %u\n", ecs->entity_array.size);
        printf("element 0: %u\n", *(u32*)hf_vector_get(&ecs->entity_array, 0));
        printf("element 500: %u\n", *(u32*)hf_vector_get(&ecs->entity_array, 500));
        printf("element 4500: %u\n", *(u32*)hf_vector_get(&ecs->entity_array, 4500));
     */
    
    /* 
        for(u32 i = 0; i < 5000; ++i){
            //printf("test\n");
            //hf_queue_push(&ecs->entity_array, NULL);
            //printf("%u", i);
            //hf_print_errors();
            
            u32* x = malloc(sizeof(u32*));
            *x = i;
            hf_queue_push(&ecs->entity_array, x);
        }
        
        
        printf("empty: %u\n", ecs->entity_array.size);
     */
    //printf("%u\n", ecs->entity_array->front);
    
}

void hf_ecs_destroy(hf_ecs* ecs){
    hf_vector_free(&ecs->component_types);
    hf_vector_free(&ecs->entity_array);
    hf_log("[HF ECS] ecs destroyed\n");
}

hf_entity hf_ecs_create_entity(hf_ecs* ecs){
    //printf("front: %u\n", ecs->entity_array.front);
    //if(ecs->){
    if(ecs->entity_amount < HF_ECS_MAX_ENITIES){
        // NOTE(salmoncatt): get last element in case we put any released id's there
        u32 id = *(u32*)hf_vector_get(&ecs->entity_array, ecs->entity_array.size - 1);
        hf_vector_erase(&ecs->entity_array, ecs->entity_array.size - 1, 1);
        
        if(id == -1)
            hf_err("[HF ECS] couldn't register new entity id\n");
        
        ecs->entity_amount += 1;
        return id;
    }else
        hf_err("[HF ECS] couldn't register new entity id, max amount in use\n");
    return -1;
}

void hf_ecs_destroy_entity(hf_ecs* ecs, hf_entity entity){
    if(entity < HF_ECS_MAX_ENITIES){
        u32* id = malloc(sizeof(u32));
        *id = entity;
        
        hf_vector_push_back(&ecs->entity_array, id);
        ecs->entity_amount -= 1;
    }else
        hf_err("[HF ECS] couldn't destroy entity because the id was out of range\n");
}

u32 hf_ecs_generate_new_component_id(hf_ecs* ecs){
    u32 out = ecs->component_ammount + 1;
    ecs->component_ammount += 1;
    return out;
}

hf_ecs_component* hf_ecs_internal_create_component_id(hf_ecs* ecs, const char* name, u64 size){
    hf_ecs_component* comp = hf_malloc(sizeof(hf_ecs_component));
    comp->id = hf_ecs_generate_new_component_id(ecs);
    comp->name = name;
    comp->size = size;
    
    return comp;
}

u32 hf_ecs_internal_register_component(hf_ecs* ecs, hf_ecs_component* component){
    hf_vector_push_back(&ecs->component_types, component);
    
    hf_vector component_array = {};
    component_array.init_capacity = 500;
    hf_vector_init(&component_array);
    
    hf_vector_push_back(&ecs->component_arrays, &component_array);
    
    u32 id = component->id;
    
    hf_free(component);
    
    return id;
}

void hf_ecs_internal_add_component(hf_ecs* ecs, hf_entity entity, const char* name, void* data){
    for(u32 i = 0; i < ecs->component_types.size; i++){
        if(((hf_ecs_component*)hf_vector_get(&ecs->component_types, i))->name == name){
            hf_log("[HF ECS] found component %s\n", name);
            return;
        }
    }
    
    hf_err("[HF ECS] couldn't add component of type %s because it was not registered\n", name);
}