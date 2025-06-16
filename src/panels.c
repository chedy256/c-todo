
#include <ncurses.h>
#include <string.h>
#include <stdlib.h>
#include "../include/panels.h"


PanelElement *head = NULL, *current = NULL;
PanelElement *view_panel, *search_panel;//i will add : sort save and load

PanelElement* createPanelElement(char* input) {
    PanelElement* newElem = (PanelElement*)malloc(sizeof(PanelElement));
    if (newElem) {
        newElem->name = input;
        newElem->next = NULL;
        newElem->prev = NULL;
    }
    return newElem;
}

PanelElement* initPanel() {
    view_panel = createPanelElement("View");
    search_panel = createPanelElement("Search");
    //i will add import from json file when i add support

    view_panel->next=search_panel;
    search_panel->prev=view_panel;
    search_panel->next = NULL;
    return view_panel;
}

void taskswindow(WINDOW *parent_win){//will add what todolist to write
    int COLS = getmaxx(parent_win);
    if (COLS < 40) {
        // Very narrow: show only title
        mvwprintw(parent_win,1,(COLS-3)/2, "Title");
    } else if (COLS < 60) {
        // Medium: title + note indicator
        mvwprintw(parent_win,1,(COLS-4)/2, "Title");
        mvwvline(parent_win,1,COLS-3,0,getmaxy(parent_win)-2);
        mvwprintw(parent_win,1,COLS-2, "N");
    } else {
        // Full width: all three columns
        mvwprintw(parent_win,1,(COLS-20)/2, "Title");
        mvwvline(parent_win,1,COLS-19,0,getmaxy(parent_win)-2);
        mvwprintw(parent_win,1,COLS-18, "N");
        mvwvline(parent_win,1,COLS-17,0,getmaxy(parent_win)-2);
        mvwprintw(parent_win,1,COLS-13, "Created on");
    }// 13.04.2001 16:10
    wrefresh(parent_win);
}
void freePanel() {
    current=head;
    while (current != NULL) {
        PanelElement* next = current->next;
        free(current);
        current = next;
    }
    head=NULL;
    current=NULL;
}
void panel(WINDOW *w){
    int cmd;
    taskswindow(w);
    do{
        PanelElement* temp = head;
        int x_pos=1;
        wmove(w, 0, 1);
        wattron(w, A_BOLD);

        while (temp != NULL) {
            if (temp == current) {
                wattroff(w, A_REVERSE);
                mvwprintw(w,0,x_pos, " %s ", temp->name);
                wattron(w, A_REVERSE);
            } else
                mvwprintw(w,0,x_pos, " %s ", temp->name);

            x_pos +=strlen(temp->name)+3;
            temp = temp->next;
        }
        wattroff(w, A_BOLD);
        wmove(w,2,2);
        wrefresh(w);
        keypad(w, TRUE);
        cmd =wgetch(w);
        if(cmd== KEY_RIGHT)
            current=(current->next)?current->next:current;
        else if(cmd== KEY_LEFT)
            current=(current->prev)?current->prev:current;
    }while(cmd!= KEY_DOWN);
    wattroff(w, A_REVERSE);
    mvwprintw(w,0,1, " View ");
    wattron(w, A_REVERSE);
}
