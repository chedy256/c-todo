
#include <ncurses.h>
//#include <string.h>
#include <stdlib.h>
#include "../include/panels.h"
//#include "../include/windows.h"


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
    /*
    int cmd=0;
    taskswindow(w);
    do{
        PanelElement* temp = head;
        int x_pos=1;
        wattron(w, A_BOLD);
        do{
            if (temp == current) {
                wattron(w,A_BLINK);
                mvwprintw(w,0,x_pos, " %s ", temp->name);
                wattroff(w,A_BLINK);
            } else{
                wattron(w, A_REVERSE);
                mvwprintw(w,0,x_pos, " %s ", temp->name);
                wattroff(w, A_REVERSE);
            }
            x_pos +=strlen(temp->name)+3;
            temp = temp->next;
        }while(temp != NULL);
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
    if (!strcmp(current->name" Search "))
        searchWindow();
    */
    wattron(w, A_REVERSE);
    mvwprintw(w,0,1, " View ");
    wattroff(w, A_REVERSE);
}
