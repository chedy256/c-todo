#include <ncurses.h>
#include "../include/panels.h"
#include "../include/input_handler.h"

int main() {
    initscr();
    start_color();
    box(stdscr, 0, 0);
    init_pair(1, COLOR_BLUE, COLOR_WHITE);
    attron(COLOR_PAIR(1));
    attron(A_BOLD);
    mvprintw(1, (getmaxx(stdscr)-36)/2, " /*** Welcome To My Todo App ***/ ");
    attroff(A_BOLD);
    attroff(COLOR_PAIR(1));
    mvprintw(3, 2, "Use Arrows to navigate: (note: Trash is still the works)");
    mvprintw(4, 3, "* use R/L arrows to navigate between tabs in the tab panel");
    mvprintw(5, 3, "* use UP/DOWN arrow to navigate inside the chosen tab");
    mvprintw(7, 2, "Press h for help");
    mvprintw(8,getmaxx(stdscr)-16,"command : ");
    refresh();

    short int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);
    static short int yoffset = 9, xoffset = 4;
    WINDOW *win = newwin(yMax - yoffset - xoffset/2, xMax - (xoffset * 2), yoffset, xoffset);
    box(win, 0, 0);
    taskswindow(win);
    head = initPanel();
    current = head;
    panel(win);
    move(8,getmaxx(stdscr)-6);
    wrefresh(win);
    int ch;
    do{
        move(8,getmaxx(stdscr)-6);
        ch=getch();
    }while(handle_input(ch, win));
    freePanel();
    endwin();
    return 0;
}
