#include"list.h"

void add_in_front(DoubleList** head, Base* base) {        //add data 
    if (*head == NULL) {
        *head = (DoubleList*)malloc(sizeof(DoubleList));        //add copying data here
        (*head)->base = base;
        (*head)->previous = NULL;
        (*head)->next = NULL;
    }
    else {
        DoubleList* current;
        current = (DoubleList*)malloc(sizeof(DoubleList));          //add copying data here
        current->base = base;
        current->previous = NULL;
        current->next = (*head);
        (*head)->previous = current;
        *head = current;
    }
}


void add_in_back(DoubleList** head, Base* base) {        //add data
    if (*head == NULL) {
        *head = (DoubleList*)malloc(sizeof(DoubleList));            //add copying data here
        (*head)->base = base;
        (*head)->previous = NULL;
        (*head)->next = NULL;
    }
    else {
        DoubleList* current = *head;
        DoubleList* new_element;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = (DoubleList*)malloc(sizeof(DoubleList));        //add copying data here
        current->base = base;
        current->next->previous = current;
        current->next->next = NULL;
    }
}