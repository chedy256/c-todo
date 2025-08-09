#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "../include/todo_core.h"

void createTodoList( TodoList *list,struct Item *parent){
    list->parent = parent;
    list->head = NULL;
    list->queue = NULL;
    list->itemID = 0;
}
unsigned int todoListEmpty( TodoList l){
    return l.head==NULL && l.queue==NULL;
}
void showTodoList( TodoList l,const unsigned cond){
    struct Item *i=l.head;
    printf("------------------------\n");
    while(i!=NULL){
        if(cond!=1 && cond!=0){
            printf("Title: %s\t", i->title);
            printf("Description: %s\t", i->description);
            printf("Priority: %d\t", i->priority);
            printf("Status: %s\n", i->completed?"completed":"uncompleted");
        }else if (cond==i->completed) {
            printf("Title: %s\t", i->title);
            printf("Description: %s\t", i->description);
            printf("Priority: %d\t", i->priority);
            printf("Status: %s\n", i->completed?"completed":"uncompleted");
        }
        i=i->next;
    }
    printf("------------------------\n");
}
struct Item * initialiseItem(){
    struct Item *i=malloc(sizeof(struct Item));
    char buffer[512];
    do{
        printf("Enter the title of the item: ");
        while (getchar() != '\n');
        fgets(buffer, sizeof(buffer), stdin);
        i->title = strdup(buffer);

        if(sizeof(i->title)>102)
            printf("Title is too long. Please enter a shorter title.\n");
        else
            break;
    }while(1);

    printf("Enter the description of the item: ");
    while (getchar() != '\n');
    fgets(buffer, sizeof(buffer), stdin);
    i->description = strdup(buffer);
    printf("Enter the priority of the item. Note: 0:low 1:default 2:high ");
    scanf("%hhu", &i->priority);
    if(i->priority<0 || i->priority>10)
        i->priority=0;
    i->next=NULL;
    return i;
}
void addItem(TodoList *l,struct Item *i){
    i->id=l->itemID++;
    i->id=l->parent?l->parent->id*100+l->itemID: l->itemID; // Assigning a new id based on the current list or parent

    if(l->head==NULL){
        l->head=i;
        l->queue=i;
    }else {
        l->queue->next=i;
        l->queue=i;
    }
}
void freeTodoList( TodoList *l){
    struct Item *current = l->head;
    while(current != NULL){
        if(current->subTasks){
            freeTodoList(current->subTasks);
            free(current->subTasks);
        }
        struct Item *next = current->next;
        free(current->title);
        free(current->description);
        free(current);
        current = next;
    }
    l->head = NULL;
    l->queue = NULL;
}
TodoList sortTodoListByPriority( TodoList* l){
    TodoList sorted;
    struct Item* current;
    createTodoList(&sorted,NULL);
    for(unsigned short i = 3;i;i--){
        current = l->head;
        while(current != NULL){
            if(current->priority==i)
                addItem(&sorted, current);
            current = current->next;
        }
    }
    return sorted;
}
TodoList searchItems( TodoList l, const char* input){
    struct Item* current = l.head;
    TodoList searched;
    createTodoList(&searched,NULL);
    while(current != NULL){
        if(!strstr(current->title, input)||(current->description && strstr(current->description, input) == 0))
            addItem(&searched,current);
        current = current->next;
    }
    return searched;
}
void reset_todo_list(TodoList *l) {
    l->head = NULL;
    l->queue = NULL;
    l->itemID = 0;
}
