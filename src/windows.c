#include <ncurses.h>
#include <string.h>
#include "../include/windows.h"
#define addAction "ADD"
#define editAction "EDIT"

void setPriorityWindow(WINDOW *parent_win,char *action){
    int height = getmaxx(parent_win)>30?7:10;
    int width =getmaxx(parent_win)>30?30:getmaxx(parent_win)-8;
    WINDOW *w = newwin(height, width, 10, 8);
    box(w, 0, 0);
    wattron(w,A_BOLD);
    mvwprintw(w,1,width/2-9,"%s THE PRIORITY",action);
    wattroff(w,A_BOLD);
    mvwhline(w,2,1 , 0, getmaxx(w)-2);
    int nav;
    //9 for spacing(2 per element before+ 1 after the last ) +2 border
    if(height ==10){
        int pos=4;
        do{//if space is tiny
            mvwprintw(w,pos,2,">");
            mvwprintw(w, 4, 3, "All");
            mvwprintw(w,5,3,"Title");
            mvwprintw(w,6,3,"Priority");
            mvwprintw(w,7,3,"Note");
            nav= wgetch(w);
            if(nav==KEY_UP && pos>4)
                pos--;
            else if(nav==KEY_DOWN && pos>7)
                pos++;
        }while(nav != KEY_ENTER && nav!= '\n');
        switch(pos){
            case 4:
            titleWindow(w, "EDIT");
            noteWindow(w, "EDIT");
            setPriorityWindow(w,"EDIT");
            break;
            case 5:
            titleWindow(w,"EDIT");
            break;
            case 6:
            setPriorityWindow(w,"EDIT");
            break;
            case 7:
            noteWindow(w, "EDIT");
        }
    }else{//if space is wide enough
        const int offset=(width-15)/3;
        const int op1=offset-1,op2=2*offset+2,op3=3*offset+7,op4=4*offset+16;
        int pos=op1;
        do{
            mvwprintw(w,4,pos,">");
            mvwprintw(w,4,offset,"HIGH");
            mvwprintw(w,4,op2+1,"DEFAULT");
            mvwprintw(w,4,op3+1,"LOW");
            nav= wgetch(w);
            if(nav==KEY_LEFT){
                if(pos==op2)
                    pos=op1;
                else if (pos==op3)
                    pos=op2;
                else if(pos==op4)
                    pos=op3;
            }else if(nav==KEY_RIGHT){
                if(pos==op1)
                    pos=op2;
                else if (pos==op2)
                    pos=op3;
                else if(pos==op3)
                    pos=op4;
            }
        }while(nav != KEY_ENTER && nav!= '\n');
    }
}
void editWindow(WINDOW *parent_win){
    int height = getmaxx(parent_win)>36?7:10;
    int width =getmaxx(parent_win)>38?getmaxx(parent_win)-8:30;
    WINDOW *w = newwin(height, width, 10, 8);
    box(w, 0, 0);
    wattron(w,A_BOLD);
    mvwprintw(w,1,width/2-9,"CHOOSE WHAT TO EDIT");
    wattroff(w,A_BOLD);
    mvwhline(w,2,1 , 0, getmaxx(w)-2);
    int nav;
    //9 for spacing(2 per element before+ 1 after the last ) +2 border
    if(height ==10){
        int pos=4;
        do{//if space is tiny
            mvwvline(w,4,2,' ',5 );
            mvwprintw(w,pos,2,">");
            mvwprintw(w, 4, 3, "All");
            mvwprintw(w,5,3,"Title");
            mvwprintw(w,6,3,"Priority");
            mvwprintw(w,7,3,"Note");
            wrefresh(w);
            noecho();
            nav= wgetch(w);
            if(nav==KEY_UP && pos>4)
                pos--;
            else if(nav==KEY_DOWN && pos>7)
                pos++;
            echo();
        }while(nav != KEY_ENTER && nav!= '\n');
        switch(pos){
            case 4:
            titleWindow(w, "EDIT");
            noteWindow(w, "EDIT");
            setPriorityWindow(w,"EDIT");
            break;
            case 5:
            titleWindow(w,"EDIT");
            break;
            case 6:
            setPriorityWindow(w,"EDIT");
            break;
            case 7:
            noteWindow(w, "EDIT");
        }
    }else{//if space is wide enough
        const int offset=(width-21)/5;
        const int op1=offset-1,op2=2*offset+2,op3=3*offset+7,op4=4*offset+16;
        int pos=op1;
        do{
            mvwhline(w,4,1,' ',op4 );
            mvwprintw(w,4,pos,">");
            mvwprintw(w,4,offset,"All");
            mvwprintw(w,4,op2+1,"Title");
            mvwprintw(w,4,op3+1,"Priority");
            mvwprintw(w,4,op4+1,"Note");
            noecho();
            wrefresh(w);
            nav= wgetch(w);
            if(nav==KEY_LEFT){
                if(pos==op2)
                    pos=op1;
                else if (pos==op3)
                    pos=op2;
                else if(pos==op4)
                    pos=op3;
            }else if(nav==KEY_RIGHT){
                if(pos==op1)
                    pos=op2;
                else if (pos==op2)
                    pos=op3;
                else if(pos==op3)
                    pos=op4;
            }
            echo();
        }while(nav != KEY_ENTER && nav!= '\n');
    }
}
void noteWindow(WINDOW* parent_win, char* action){
    WINDOW *w = newwin(getmaxy(parent_win)-20, getmaxx(parent_win)-8, 10, 8);
    box(w, 0, 0);
    int height = getmaxy(w);
    int width = getmaxx(w);

    wattron(w,A_BOLD);
    mvwprintw(w,1,width/2-5,"%s A NOTE",action);
    wattroff(w,A_BOLD);
    mvwhline(w,2,1 , 0, getmaxx(w)-2);
    mvwprintw(w, 3, 2, "Enter the note:");
    mvwprintw(w, height - 2, width - 48, "(Press ENTER to confirm, q to skip th rest)");
    wrefresh(w);

    echo();
    char note_input[512];
    wmove(w, 4, 2);
    wgetnstr(w, note_input, sizeof(note_input) - 1);
    noecho();

    // if it's an edit Title it should return as it is manipulated by the editWindow logic based on the user input
    if(strcmp(action,editAction)==0) return;
    move(8,getmaxy(stdscr)-16);
    int ch = getch();
    refresh();
    wclear(w);
    wrefresh(w);
    delwin(w);
    switch(ch){
        case 'q':
        case 27:
            touchwin(parent_win);
            wrefresh(parent_win);
            return;
        case KEY_ENTER:
        case '\n':
            move(8,getmaxx(stdscr)-6);
        /*overwrite the task to the todo list
         * store a copy to restore if the user want to and that will be for all the data inputed
         **(keep track of  the task id ,what changed: title note status priority, and the last value)*/
            return;//setPriorityWindow(w, action);
    }
}

void titleWindow(WINDOW *parent_win,char *action) {
    WINDOW *w = newwin(10, getmaxx(parent_win)-4, 11, 6);
    box(w, 0, 0);
    int height = getmaxy(w);// will be calculated 156 /width +5;
    int width = getmaxx(w);

    wattron(w,A_BOLD);
    mvwprintw(w,1,width/2-4,"%s TASK",action);
    wattroff(w,A_BOLD);
    mvwhline(w,2,1 , 0, getmaxx(w)-2);

    mvwprintw(w, 3, 2, "Enter task title:");
    mvwprintw(w, height - 2, width - 48, "(Press ENTER to confirm, ESC to cancel)");
    wrefresh(w);

    echo();
    char task_input[128];//i will handle return to new line when reaching the border
    wmove(w, 4, 2);
    wgetnstr(w, task_input, sizeof(task_input) - 1);
    noecho();

    /*overwrite the task to the todo list
     * store a copy to restore if the user want to and that will be for all the data inputed
     **(keep track of  the task id ,what changed: title note status priority, and the last value)*/
    // if it's an edit Title it should return as it is manipulated by the editWindow logic based on the user input
    if(strcmp(action,editAction)==0) return;
    move(8,getmaxy(stdscr)-16);
    refresh();
    int ch = getch();
    touchwin(parent_win);
    wrefresh(parent_win);
    switch(ch){
        case 'q':
        case 27:
            /*if strlen(task_input)<2 after removing any space from begining and finish
             *  skip
             * else: save
             */
            return;
        case KEY_ENTER:
        case '\n':
            noteWindow(w,addAction);
    }
    wclear(w);
    wrefresh(w);
    delwin(w);
    touchwin(parent_win);
    wrefresh(parent_win);
}
// made it dynamic if width less then 72 it will be in one page
void helpWindow(WINDOW *parent_win) {
    int width = getmaxx(parent_win);

    WINDOW *help = newwin((width<74)?21:17, (width<74)?38:75, 11 ,(width-((width<74)?38:75)+8)/2);
    box(help, 0, 0);

    wattron(help,A_BOLD);
    mvwprintw(help,1,((width<74)?40:75)/2-2,"HELP");
    wattroff(help,A_BOLD);
    mvwhline(help,2,1 , 0, getmaxx(help)-2);
    int offset=4;
    wattron(help,A_BOLD);
    mvwprintw(help, 4, offset-1, "*/Base commands:");
    wattroff(help,A_BOLD);
    mvwprintw(help, 5,offset,"a : add a task");
    mvwprintw(help, 6,offset,"s : add a subtask");
    mvwprintw(help, 7,offset,"e : edit the current task");
    mvwprintw(help, 8,offset,"n : add note");
    mvwprintw(help, 9,offset,"v : view the note");
    mvwprintw(help, 10,offset,"d : delete a task");
    mvwprintw(help, 11,offset,"r : revert the last change");
    mvwprintw(help, 12,offset,"f : change the current status");
    mvwprintw(help, 13,offset,"p : change priority");
    mvwprintw(help, 14,offset,"q : to fast exit/skip");
    int second_start_line = width>74 ? 4:16;
    offset = width<74 ? offset:42;
    wattron(help,A_BOLD);
    mvwprintw(help, second_start_line++,offset-1,"*/More commands:");
    wattroff(help,A_BOLD);
    mvwprintw(help, second_start_line++,offset,"ot : add only a task title");
    mvwprintw(help, second_start_line++,offset,"st : add only a subtask title");
    wrefresh(help);
    move(8,getmaxx(stdscr)-6);
    refresh();
    getch();
    noecho();
    wclear(help);
    wrefresh(help);
    delwin(help);
    touchwin(parent_win);
    wrefresh(parent_win);
}
