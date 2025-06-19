#ifndef PANELS_H
#define PANELS_H

#include <ncurses.h>

typedef struct elem {
    char* name;
    struct elem *next;
    struct elem *prev;
} PanelElement;

extern PanelElement *view_panel, *search_panel, *sort_panel;//*save_panel ,*load_panel
extern PanelElement *head, *current;

PanelElement* createPanelElement(char* name);
PanelElement* initPanel();
void freePanel();
void panel(WINDOW *);

#endif
