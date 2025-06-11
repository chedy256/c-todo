#include <ncurses.h>
#include <stdio.h>
#include "../include/windows.h"

void addtask(char* task) {
    printf("%s", task); // Placeholder
}

void addwindow(WINDOW *parent_win) {
    int parent_height = getmaxy(parent_win);
    int parent_width = getmaxx(parent_win);

    WINDOW *addTask = newwin(parent_height/2, parent_width-16/2, parent_height/4, 8);
    box(addTask, 0, 0);

    wattron(addTask, A_ITALIC);
    mvwprintw(addTask, 1, 2, "Add New Task");
    wattroff(addTask, A_ITALIC);

    mvwprintw(addTask, 2, 2, "Enter task title:");
    mvwprintw(addTask, parent_height/2 - 2, parent_width - 48, "(Press ENTER to confirm, ESC to cancel)");
    wrefresh(addTask);

    echo();
    char task_input[256];
    wmove(addTask, 3, 2);
    wgetnstr(addTask, task_input, sizeof(task_input) - 1);
    noecho();

    int ch = wgetch(addTask);
    if (ch != 27) {
        addtask(task_input);
    }

    wclear(addTask);
    wrefresh(addTask);
    delwin(addTask);
    touchwin(parent_win);
    wrefresh(parent_win);
}

void helpwindow(WINDOW *parent_win) {
    int parent_height = getmaxy(parent_win);
    int parent_width = getmaxx(parent_win);

    WINDOW *help = newwin(parent_height/2, parent_width-16/2, parent_height/4, 8);
    box(help, 0, 0);
    mvwprintw(help, 2, 2, "*/Navigation:");
    mvwprintw(help, 3, 4, "LEFT/RIGHT: Switch panels");
    mvwprintw(help, 4, 4, "DOWN: Activate panel function");
    mvwprintw(help, 5, 4, "Q: Quit application");
    mvwprintw(help, 7, 2, "*/Confirm / Cancel:");
    mvwprintw(help, 8, 4, "DOWN: Confirm current action");
    mvwprintw(help, 9, 4, "UP: Cancel current action");
    wrefresh(help);
    getch();
    wclear(help);
    wrefresh(help);
    delwin(help);
    touchwin(parent_win);
    wrefresh(parent_win);
}
