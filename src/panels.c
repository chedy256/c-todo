
#include <ncurses.h>
#include <string.h>
#include <stdlib.h>
#include "../include/panels.h"


PanelElement *head = NULL, *current = NULL;
PanelElement *view_panel, *trash_panel;//i will add save and load

PanelElement* createPanelElement(char* name) {
    PanelElement* newElem = (PanelElement*)malloc(sizeof(PanelElement));
    if (newElem) {
        newElem->name = strdup(name);
        newElem->next = NULL;
        newElem->prev = NULL;
    }
    return newElem;
}

PanelElement* initPanel() {
    view_panel = createPanelElement("View");
    trash_panel = createPanelElement("Trash");
    //i will add import from json file when i add support

    view_panel->next=trash_panel;
    trash_panel->prev=view_panel;
    trash_panel->next = NULL;
    return view_panel;
}
void display_title_only(int title_width){
    mvprintw(10,title_width/2-3, "Title");
}
void display_title_and_note(int available_width){
    mvprintw(10,available_width/2-5, "Title");
    mvprintw(10,available_width-3, "N");
}
void display_all_columns(int available_width){
    mvprintw(10,available_width-24-available_width/2, "Title");
    mvprintw(10,available_width-23, "N");
    mvprintw(10,available_width-14, "Created on");
}
void taskswindow(WINDOW *parent_win){
    int COLS = getmaxx(parent_win);
    int available_width = COLS - 20; // Reserve ~15 for Note + Date + spacing
    int title_width = (available_width < 64) ? available_width : 64;

    if (COLS < 40) {
        // Very narrow: show only title
        display_title_only(title_width);
    } else if (COLS < 60) {
        // Medium: title + note indicator
        display_title_and_note(available_width);
    } else {
        // Full width: all three columns
        display_all_columns(available_width);
    }
}
void freePanel() {
    current=head;
    while (current != NULL) {
        PanelElement* next = current->next;
        free(current->name);
        free(current);
        current = next;
    }
    head=NULL;
    current=NULL;
}
void panel(WINDOW *w){
    int cmd;
    /*do{
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
    */
    wattroff(w, A_REVERSE);
    mvwprintw(w,0,1, " View ");
    wattron(w, A_REVERSE);
}
