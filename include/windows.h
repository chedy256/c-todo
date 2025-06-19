#ifndef WINDOWS_H
#define WINDOWS_H

#include <ncurses.h>

void setPriorityWindow(WINDOW *parent_win,char *action);
void helpWindow(WINDOW *parent_win);
void editWindow(WINDOW *parent_win);
void titleWindow(WINDOW *parent_win,char* action);
void noteWindow(WINDOW* parent_win, char* action);
/*** Panel Windows ***/
void taskswindow(WINDOW *parent_win);
void searchWindow(WINDOW *parent_win);

#endif
