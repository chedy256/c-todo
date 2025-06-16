#ifndef WINDOWS_H
#define WINDOWS_H

#include <ncurses.h>

void setTitleWindow(WINDOW *parent_win,char *action);//action can be "Add" or "Edit"
void setNoteWidow(WINDOW *parent_win,char *action);
void setPriorityWindow(WINDOW *parent_win,char *action);
void chooseEditWindow(WINDOW *parent_win);
void setSearchWindow(WINDOW *parent_win);

void helpWindow(WINDOW *parent_win);
void editWindow(WINDOW *parent_win);
void titleWindow(WINDOW *parent_win,char* action);
void noteWindow(WINDOW* parent_win, char* action);

#endif
