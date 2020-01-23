#include "list.h"
#include <stdlib.h>
#include <stdio.h>

struct List
{
    struct Node* head;
};

struct Node
{
    int value;
    struct Node* next;
};

// typedef struct List List;
typedef struct Node Node;


List * create_list(void)
{
    #ifdef DEBUG
    printf("create_list()\n");
    #endif
    List* ptr = (List*)malloc(sizeof(List));
    ptr->head = NULL;
    return ptr;
}

// releases all memory used by list, list is set to NULL
void destroy_list(List ** list)
{
    #ifdef DEBUG
    printf("destroy_list - begin\n");
    #endif
    clear_list(*list);
    free(*list);
    *list = NULL;
    #ifdef DEBUG
    printf("destroy_list - end\n\n");
    #endif
}

// return amount of elements in list
int count_elements(List * list)
{
    #ifdef DEBUG
    printf("count_elements - begin\n");
    #endif
    if(list->head == NULL)
    {
        return 0;
    }
    else
    {
        Node* ptr = list->head;
        int counter = 1; 
        while(ptr->next)
        {
            ptr = ptr->next;
            counter++;
        }
        #ifdef DEBUG
        printf("%d elements\n", counter);
        printf("count_elements - end\n\n");
        #endif
        return counter;
    }
}

// append element to list at the end
void append_to_list(List * list, int elem)
{
    #ifdef DEBUG
    printf("append_to_list - begin\n");
    #endif
    if(list->head == NULL)
    {
        list->head = (Node*)malloc(sizeof(Node));
        Node* ptr = list->head;
        ptr->value = elem;
        ptr->next = NULL;
        #ifdef DEBUG
        printf("+ appended %d\n", ptr->value);
        #endif
    }
    else    
    {
        Node* ptr = list->head;
        while(ptr->next)
        {
            ptr = ptr->next;
        }
        ptr->next = (Node*)malloc(sizeof(Node));
        ptr = ptr->next;
        ptr->value = elem;
        #ifdef DEBUG
        printf("+ appended %d\n", ptr->value);
        #endif
        ptr->next = NULL;
    }
    #ifdef DEBUG
    printf("append_to_list - end\n\n");
    #endif
}

// elements are indexed from 0
int get_nth_element(List * list, int index)
{
    #ifdef DEBUG
    printf("get_nth_element - begin\n");
    #endif
    if(list->head == NULL)
    {
        #ifdef DEBUG
        printf("Can't get element - list is empty.");
        #endif
        return 0;
    }
    else
    {
        Node* ptr = list->head;
        int count = 0;
        while(ptr->next != NULL && count != index)
        {
            ptr = ptr->next;
            count++;
        }
        #ifdef DEBUG
        printf("\nelement[%d] = %d\n\n", count, ptr->value);
        #endif
        return ptr->value;
    }
}

// remove nth element - indexed from 0
void remove_nth_element(List * list, int index)
{
    #ifdef DEBUG
    printf("remove_nth_element - begin\n");
    #endif
    if(list->head == NULL)
    {
        #ifdef DEBUG
        printf("Can't remove element from empty list!\n");
        #endif
    }
    else
    {
        Node* prev_ptr = list->head;
        Node* ptr = list->head;
        int count = 0;
        while(ptr->next != NULL && count != index)
        {
            prev_ptr = ptr;
            ptr = ptr->next;
            count++;
        }
        if (index > count)
        {
            printf("Error - Index out of bounds.\n");
        }
        else if(ptr->next == NULL)
        {
        // IF OSTATNI ELEMENT
            prev_ptr->next = NULL;
            free(ptr);
            #ifdef DEBUG
            printf("removed last element\n");
            #endif
        }
        else if(index == 0)
        {
        // IF PIERWSZY ELEMENT
            Node* tmp = list->head->next;
            free(list->head);
            list->head = tmp;
            #ifdef DEBUG
            printf("removed first element\n");
            #endif
        }
        else
        {
        // IF POZOSTALE ELEMENTY
            prev_ptr->next = ptr->next;
            free(ptr);
            #ifdef DEBUG
            printf("removed element[%d]\n", count);
            #endif
        }
    } 
    #ifdef DEBUG
    printf("remove_nth_element - end\n\n");
    #endif
}

// clear list - remove all elements
void clear_list(List * list)
{
    int count = count_elements(list);
    // printf("%d" , count);
    for (int i = count-1; i >=0; i--)
    {
        remove_nth_element(list, i);
    }
    list->head = NULL;
}

// insert element to list at specified index,
// indexed from 0, elements are shifted
void insert_to_list(List * list, int elem, int index)
{
    if(list->head == NULL)
    {
        list->head = (Node*)malloc(sizeof(Node));
        Node* ptr = list->head;
        ptr->value = elem;
        ptr->next = NULL;
        #ifdef DEBUG
        printf("+ list is empty - insert %d at the beginning\n", ptr->value);
        #endif
    }
    else if(index == 0)
    {
        Node* ptr = list->head;
        list->head = (Node*)malloc(sizeof(Node));
        list->head->next = ptr;
        list->head->value = elem;
    }
    else
    {
        Node* ptr = list->head;
        int count = 1;
        while(ptr->next != NULL && count < index)
        {
            ptr = ptr->next;
            count++;
        }
        Node* next_item = ptr->next;
        ptr->next = (Node*)malloc(sizeof(Node));
        ptr->next->next = next_item;
        ptr->next->value = elem;
    }
}

// // sort elements in list
// void sort_list(List * list)
// {

// }

// // reverse list
// void reverse_list(List * list)
// {

// }
