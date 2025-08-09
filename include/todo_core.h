#include<stdlib.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct  {
    struct Item* parent;
    struct Item* head;
    struct Item* queue;
    uint8_t itemID;
}TodoList;

struct Item {
    unsigned int id; //1->99 + 100 * parent_id parent->id+'.'+ id
    char* title;
    char* description;
    uint8_t priority;//1:low, 2:default, 3:high
    bool completed;
    struct Item* next;
    struct Item* parent;
    TodoList* subTasks;
};

void createTodoList(TodoList *,struct Item *parent);
void addItem( TodoList*,struct Item*);
struct Item * initialiseItem();
unsigned int todoListEmpty( TodoList);
//void removeItem( TodoList*);
//void editItem( TodoList*);
//TodoList searchItems( TodoList, const char*);

void showTodoList( TodoList,const unsigned);
void freeTodoList( TodoList *);
void reset_todo_list(TodoList *);
//TodoList sortTodoListByPriority( TodoList*);
