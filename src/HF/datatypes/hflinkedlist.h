/* date = August 28th 2021 9:31 am */

#ifndef HFLINKEDLIST_H
#define HFLINKEDLIST_H

typedef struct hf_node{
    
    void* data;
    i32 key;
    struct hf_node* next;
    
}hf_node;


typedef struct hf_linked_list{
    node* head = NULL;
    node* current = NULL;
}

b8 hf_linked_list_empty(const hf_linked_list* list){
    return list->head == NULL;
}

void hf_linked_list_free_first(const hf_linked_list* list){
    hf_node* temp = list->head;
    
    list->head = list->head->next;
    
    hf_free(temp);
}

hf_node* hf_linked_list_remove_first(const hf_linked_list* list){
    hf_node* temp = list->head;
    
    list->head = list->head->next;
    
    return temp;
}

u64 hf_linked_list_length(){
    
}

#endif //HFLINKEDLIST_H
