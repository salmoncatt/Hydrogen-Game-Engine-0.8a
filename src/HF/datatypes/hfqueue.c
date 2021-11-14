#include "hfqueue.h"

void hf_queue_init(hf_queue* queue){
    if(queue == NULL){
        queue = (hf_queue*)hf_malloc(sizeof(hf_queue));
    }
    queue->size = 0;
    queue->front = NULL;
    queue->back = NULL;
}

void hf_queue_free(hf_queue* queue){
    if(queue != NULL){
        while(!hf_queue_is_empty(queue)){
            hf_queue_pop(queue);
        }
        queue->size = 0;
        queue->front = NULL;
        queue->back = NULL;
    }
}

b8 hf_queue_is_empty(hf_queue* queue){
    if(queue != NULL)
        return (queue->back == NULL);
    else
        return 0;
}

void hf_queue_push(hf_queue* queue, void* data){
    if(queue != NULL){
        hf_node* node;
        node = hf_malloc(sizeof(node));
        node->data = data;
        node->next = NULL;
        
        if(!hf_queue_is_empty(queue)){
            queue->back->next = node;
            queue->back = node;
        }else
            queue->front = queue->back = node;
        
        queue->size += 1;
    }
}

void hf_queue_pop(hf_queue* queue){
    if(queue != NULL){
        hf_node* node;
        node = queue->front;
        
        queue->front = queue->front->next;
        queue->size -= 1;
        
        hf_free(node);
    }
}