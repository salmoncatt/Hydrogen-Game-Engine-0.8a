/* date = August 28th 2021 9:31 am */

#ifndef HFLINKEDLIST_H
#define HFLINKEDLIST_H

typedef struct hf_node{
    
    void* data;
    i32 key;
    struct hf_node* next;
    
}hf_node;


typedef struct hf_linked_list{
    hf_node* head;
    hf_node* current;
}hf_linked_list;

b8 hf_linked_list_empty(const hf_linked_list* list);

void hf_linked_list_free_first(hf_linked_list* list);

hf_node* hf_linked_list_remove_first(hf_linked_list* list);

u64 hf_linked_list_length();

#endif //HFLINKEDLIST_H
