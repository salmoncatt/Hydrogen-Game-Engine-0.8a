#include "hfecs.h"

void hf_ecs_init(hf_ecs* ecs){
    hf_vector_init(&ecs->component_types);
    hf_vector_init(&ecs->component_arrays);
    
    ecs->entity_array.init_capacity = HF_ECS_MAX_ENITIES + 5;
    hf_vector_init(&ecs->entity_array);
    
    for(u32 i = HF_ECS_MAX_ENITIES - 1; i-- > 0;){
        u32* x = malloc(sizeof(u32));
        *x = i;
        
        //if(i == 1)
        //printf("0x%pS\n", x);
        
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
    hf_vector_free_double_vector(&ecs->component_arrays);
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
    u32 out = ecs->component_ammount;
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
    
    hf_vector* component_array = (hf_vector*)hf_malloc(sizeof(hf_vector));
    memset(component_array, 0, sizeof(hf_vector));
    component_array->init_capacity = HF_ECS_MAX_ENITIES;
    hf_vector_init(component_array);
    
    /* 
        printf("size: %u\n", component_array->size);
        printf("capacity: %u\n", component_array->capacity);
     */
    
    
    u32 id = component->id;
    
    hf_vector_set(&ecs->component_arrays, id, component_array);
    
    hf_vector* component_array2 = (hf_vector*)hf_vector_get(&ecs->component_arrays, id);
    
    /* 
        printf("component array2 size: %u\n", component_array2->size);
        printf("component array2 capacity: %u\n", component_array2->capacity);
     */
    
    return id;
}

void hf_ecs_internal_add_component(hf_ecs* ecs, hf_entity entity, const char* name, u64 size, void* data){
    for(u32 i = 0; i < ecs->component_types.size; i++){
        if(((hf_ecs_component*)hf_vector_get(&ecs->component_types, i))->name == name){
            
            u32 id = ((hf_ecs_component*)hf_vector_get(&ecs->component_types, i))->id;
            size = ((hf_ecs_component*)hf_vector_get(&ecs->component_types, i))->size;
            
            /* 
                        printf("id: %u\n", id);
                        printf("size: %u\n", size);
                        printf("entity: %u\n", entity);
             */
            
            void* component_data = malloc(size);
            hf_memcpy(component_data, data, size);
            
            hf_vector* component_array = (hf_vector*)hf_vector_get(&ecs->component_arrays, id);
            
            
            /* 
                        printf("component array size: %u\n", component_array->size);
                        printf("component array capacity: %u\n", component_array->capacity);
             */
            
            hf_vector_set(component_array, entity, component_data);
            
            //hf_log("[HF ECS] found component %s\n", name);
            return;
        }
    }
    
    // NOTE(salmoncatt): auto register component if it is not registered
    //-------------
    u32 id = hf_ecs_internal_register_component(ecs, hf_ecs_internal_create_component_id(ecs, name, size));
    void* component_data = malloc(size);
    hf_memcpy(component_data, data, size);
    
    hf_vector* component_array = (hf_vector*)hf_vector_get(&ecs->component_arrays, id);
    
    hf_vector_set(component_array, entity, component_data);
    //------------
    return;
    
    hf_err("[HF ECS] couldn't add component of type %s because it was not registered\n", name);
}

void* hf_ecs_internal_get_component(hf_ecs* ecs, hf_entity entity, const char* name){
    for(u32 i = 0; i < ecs->component_types.size; i++){
        if(((hf_ecs_component*)hf_vector_get(&ecs->component_types, i))->name == name){
            
            u32 id = ((hf_ecs_component*)hf_vector_get(&ecs->component_types, i))->id;
            
            /* 
                        printf("id: %u\n", id);
                        printf("entity: %u\n", entity);
                        printf("size of component arrays: %u\n", ecs->component_arrays.size);
                        printf("size of poopy array: %u\n", ((hf_vector*)hf_vector_get(&ecs->component_arrays, id))->size);
             */
            
            return hf_vector_get((hf_vector*)hf_vector_get(&ecs->component_arrays, id), entity);
            
            //hf_log("[HF ECS] found component %s\n", name);
            //return;
        }
    }
    
    hf_err("[HF ECS] couldn't get component of type %s because it was not registered\n", name);
    
    return NULL;
}

void hf_ecs_internal_remove_component(hf_ecs* ecs, hf_entity entity, const char* name){
    for(u32 i = 0; i < ecs->component_types.size; i++){
        if(((hf_ecs_component*)hf_vector_get(&ecs->component_types, i))->name == name){
            
            u32 id = ((hf_ecs_component*)hf_vector_get(&ecs->component_types, i))->id;
            hf_vector* component_array = (hf_vector*)hf_vector_get(&ecs->component_arrays, id);
            
            if(component_array->data != NULL){
                if(component_array->data[entity] != NULL){
                    hf_free(component_array->data[entity]);
                    component_array->data[entity] = NULL;
                }
            }
            
            return;
        }
    }
    
    hf_err("[HF ECS] couldn't remove component of type %s because it was not registered\n", name);
}