#include "hflinkedlist.h"



b8 hf_linked_list_empty(const hf_linked_list* list){
    return list->head == NULL;
}

void hf_linked_list_free_first(hf_linked_list* list){
    hf_node* temp = list->head;
    
    list->head = list->head->next;
    
    hf_free(temp);
}

hf_node* hf_linked_list_remove_first(hf_linked_list* list){
    hf_node* temp = list->head;
    
    list->head = list->head->next;
    
    return temp;
}