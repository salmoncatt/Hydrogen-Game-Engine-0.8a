/* date = November 13th 2021 0:12 pm */

#ifndef HFQUEUE_H
#define HFQUEUE_H

#include "hflinkedlist.h"

typedef struct hf_queue{
    
    u64 size;
    hf_node* front;
    hf_node* back;
    
    
}hf_queue;

void hf_queue_init(hf_queue* queue);

void hf_queue_free(hf_queue* queue);

b8 hf_queue_is_empty(hf_queue* queue);

void hf_queue_push(hf_queue* queue, void* data);

void hf_queue_push_node(hf_queue* queue, hf_node* data);

void hf_queue_pop(hf_queue* queue);

#endif //HFQUEUE_H
