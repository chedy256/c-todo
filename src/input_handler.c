#include "../include/input_handler.h"
//#include "../include/todo_core.h"
#include "../include/windows.h"
//#include "../include/panels.h"//added this to return to panel
//#include "../include/app_ui.h"

// Undo state
//static undo_state_t last_action = {0};
#include "../include/input_handler.h"
#include <ncurses.h>

unsigned int handle_input(int ch, WINDOW* win) {
    /*switch (ch) {
        case KEY_UP:
            navigate_up(ui_state);
            break;

        case KEY_DOWN:
            navigate_down(ui_state);
            break;

        case KEY_LEFT:
            switch_tab_left(ui_state);
            break;

        case KEY_RIGHT:
            switch_tab_right(ui_state);
            break;

        case '\n':  // Enter key
        case KEY_ENTER:
            handle_enter_key(list, ui_state, win);
            break;

        case 'd':
        case KEY_DC:  // Delete key
            handle_delete_task(list, ui_state);
            break;

        case 'u':
            handle_undo(list, ui_state);
            break;

        case 'e':
            handle_edit_task(list, ui_state, win);
            break;

        case ' ':  // Toggle completion
            handle_toggle_completion(list, ui_state);
            break;

        case 'h':
            show_help_window(win);
            break;
            }*/
    switch(ch){
        case KEY_RESIZE:
            taskswindow(win);
            break;
        case 'h':
            helpWindow(win);
            break;
        case 'a':
            titleWindow(win,"ADD");
            break;
        case 'e':
            editWindow(win);
            break;
        case 'n':
            noteWindow(win,"TEST");
            break;
        case 'p':
            setPriorityWindow(win,"TEST");
            break;
        /*case 'o':
            panel(win);
            break;*/
        default:
            return 0;
    }
    move(1,8);
    return 1;
}

/*void handle_enter_key(TodoList* list, ui_state_t* ui_state, WINDOW* win) {
    if (ui_state->selected_task == NULL) {
        // No selection, add new root task
        char* title = get_task_input(win, "Enter task title:");
        if (title) {
            Item* new_item = createItem(title, "", PRIORITY_LOW);
            addItem(list, new_item);
            save_undo_add(new_item);
            free(title);
        }
    } else {
        // Add subtask to selected task
        char* title = get_task_input(win, "Enter subtask title:");
        if (title) {
            Item* new_subtask = createItem(title, "", PRIORITY_LOW);
            // Add as subtask to selected task
            add_subtask(ui_state->selected_task, new_subtask);
            save_undo_add(new_subtask);
            free(title);
        }
    }
}

void handle_delete_task(TodoList* list, ui_state_t* ui_state) {
    if (ui_state->selected_task) {
        save_undo_delete(ui_state->selected_task);
        removeItem(list, ui_state->selected_task->id);
        ui_state->selected_task = NULL;
    }
}

void handle_undo(TodoList* list, ui_state_t* ui_state) {
    switch (last_action.action_type) {
        case ACTION_ADD:
            removeItem(list, last_action.task_id);
            break;
        case ACTION_DELETE:
            restore_deleted_task(list, &last_action);
            break;
        case ACTION_EDIT:
            restore_task_text(list, &last_action);
            break;
    }
    clear_undo_state();
}

void save_undo_add(Item* item) {
    last_action.action_type = ACTION_ADD;
    last_action.task_id = item->id;
}

void save_undo_delete(Item* item) {
    last_action.action_type = ACTION_DELETE;
    last_action.task_id = item->id;
    // Store task data for restoration
    last_action.saved_title = strdup(item->title);
    last_action.saved_priority = item->priority;
}
*/
