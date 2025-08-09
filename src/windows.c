
#include <ncurses.h>
#include <string.h>
#include "../include/windows.h"
#define addAction "ADD"
#define editAction "EDIT"

void setPriorityWindow(WINDOW *parent_win,char *action){
    int height = getmaxx(parent_win)>30?7:10;
    int width = getmaxx(parent_win)-8;
    WINDOW * w= newwin(height, width, 10, 8);
    box(w, 0, 0);
    wattron(w,A_BOLD);
    mvwprintw(w,1,width/2-9,"%s THE PRIORITY",action);
    wattroff(w,A_BOLD);
    mvwhline(w,2,1 , 0, getmaxx(w)-2);
    attr_t cc=COLOR_PAIR(2);
    int nav;
    //9 for spacing(2 per element before+ 1 after the last ) +2 border
    if(height ==10){
        int pos=4;
        wattron(w,COLOR_PAIR(2));
        mvwprintw(w, 4, 3, "HIGH");
        wattroff(w,COLOR_PAIR(2));
        mvwprintw(w,5,3,"DEFAULT");
        wattron(w,COLOR_PAIR(3));
        mvwprintw(w,6,3,"LOW");
        wattroff(w,COLOR_PAIR(3));
        do{//if space is tiny
            mvwprintw(w,pos,2,">");
            wrefresh(w);
            move(8,getmaxx(stdscr));
            refresh();
            nav= getch();
            if(nav==KEY_UP && pos>4)
                pos--;
            else if(nav==KEY_DOWN && pos<6)
                pos++;
        }while(nav != KEY_ENTER && nav!= '\n');
        /*switch(pos){
            case 4:
                task->priority=HIGH;
            case 6:
                task->priority=LOW;
            default:
                task->priority=DEFAULT;
                break;
        }*/
    }else{//if space is wide enough
        const int offset=(width-16)/4;
        const int op1=offset-1,
                  op2=2*offset+4,
                  op3=3*offset+7;
        int pos=op1;
        wattron(w,COLOR_PAIR(2));
        mvwprintw(w,4,offset,"HIGH");
        wattroff(w,COLOR_PAIR(2));
        mvwprintw(w,4,op2+1,"DEFAULT");
        wattron(w,COLOR_PAIR(3));
        mvwprintw(w,4,op3+1,"LOW");
        wattroff(w,COLOR_PAIR(3));
        wrefresh(w);
        do{
            wattron(w,cc);
            mvwprintw(w,4,pos,">");
            wattroff(w,cc);
            wrefresh(w);
            move(8,getmaxx(stdscr));
            refresh();
            nav= wgetch(w);
            if(nav==KEY_LEFT){
                mvwprintw(w,4,pos," ");  // Clear at current position
                if(pos!=op1)
                    mvwprintw(w,pos,2," ");
                if(pos==op2){
                    pos=op1;
                    cc=COLOR_PAIR(1);
                }
                else if (pos==op3){
                    pos=op2;
                    cc=COLOR_PAIR(3);
                }
            }else if(nav==KEY_RIGHT){
                mvwprintw(w,4,pos," ");  // Clear at current position
                if(pos!=op3)
                    mvwprintw(w,pos,2," ");
                if(pos==op1){
                    pos=op2;
                    cc=COLOR_PAIR(3);
                }
                else if (pos==op2){
                    pos=op3;
                    cc=COLOR_PAIR(4);
                }
            }wrefresh(w);
        }while(nav != KEY_ENTER && nav!= '\n');
    }
    wclear(w);
    wrefresh(w);
    delwin(w);
    touchwin(parent_win);
    wrefresh(parent_win);
}
void editWindow(WINDOW *parent_win){
    int height = getmaxx(parent_win)>36?7:10;
    int width = getmaxx(parent_win)-8;
    WINDOW *w = newwin(height, width, 10, 8);
    box(w, 0, 0);
    wattron(w,A_BOLD);
    mvwprintw(w,1,width/2-9,"CHOOSE WHAT TO EDIT");
    wattroff(w,A_BOLD);
    mvwhline(w,2,1 , 0, getmaxx(w)-2);
    int nav;
    //9 for spacing(2 per element before+ 1 after the last ) +2 border
    if(height ==10){
        mvwprintw(w, 4, 3, "All");
        mvwprintw(w,5,3,"Title");
        mvwprintw(w,6,3,"Priority");
        mvwprintw(w,7,3,"Note");
        int pos=4;
        do{//if space is tiny
            mvwprintw(w,pos,2,">");
            wrefresh(w);
            nav= wgetch(w);
            if(nav==KEY_UP && pos>4){
                mvwprintw(w,pos,2," ");
                pos--;
            }else if(nav==KEY_DOWN && pos<7){
                mvwprintw(w,pos,2," ");
                pos++;
            }
            move(8,getmaxx(stdscr));
            refresh();
        }while(nav != KEY_ENTER && nav!= '\n');
        switch(pos){
            case 4:
            titleWindow(parent_win, "EDIT");
            noteWindow(parent_win, "EDIT");
            setPriorityWindow(parent_win,"EDIT");
            break;
            case 5:
            titleWindow(parent_win,"EDIT");
            break;
            case 6:
            setPriorityWindow(parent_win,"EDIT");
            break;
            case 7:
            noteWindow(parent_win, "EDIT");
        }
    }else{//if space is wide enough
        const int offset=(width-21)/5;
        const int op1=offset-1,op2=2*offset+2,op3=3*offset+7,op4=4*offset+16;
        int pos=op1;
        mvwprintw(w,4,offset,"All");
        mvwprintw(w,4,op2+1,"Title");
        mvwprintw(w,4,op3+1,"Priority");
        mvwprintw(w,4,op4+1,"Note");
        do{
            mvwprintw(w,4,pos,">");
            wrefresh(w);
            move(8,getmaxx(stdscr));
            refresh();
            nav= wgetch(w);
            if(nav==KEY_LEFT){
                if(pos!=op1)
                    mvwprintw(w,4,pos," ");
                if(pos==op2)
                    pos=op1;
                else if (pos==op3)
                    pos=op2;
                else if(pos==op4)
                    pos=op3;
            }else if(nav==KEY_RIGHT){
                if(pos!=op4)
                    mvwprintw(w,4,pos," ");
                if(pos==op1)
                    pos=op2;
                else if (pos==op2)
                    pos=op3;
                else if(pos==op3)
                    pos=op4;
            }
        }while(nav != KEY_ENTER && nav!= '\n' && nav!=27 && nav!='q');
    }
    touchwin(parent_win);
    wrefresh(parent_win);
    wclear(w);
    wrefresh(w);
    delwin(w);
    touchwin(parent_win);
    wrefresh(parent_win);
    //save the changes to the task
    return;
}
void noteWindow(WINDOW* parent_win, char* action){
    int width = getmaxx(parent_win)-4;
    int height = 512/width +8;
    WINDOW *w = newwin(height, width, 10, 6);
    box(w, 0, 0);

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
    move(8,getmaxx(stdscr)-6);
    refresh();
    int ch = getch();
    touchwin(parent_win);
    wrefresh(parent_win);
    wclear(w);
    wrefresh(w);
    delwin(w);
    touchwin(parent_win);
    wrefresh(parent_win);
    switch(ch){
        case 'q':
        case 27:
            /*if strlen(task_input)<2 after removing any space from begining and finish skip
             * else save
             */
            return;
        case KEY_ENTER:
        case '\n':
            setPriorityWindow(parent_win,addAction);
    }
}

void titleWindow(WINDOW *parent_win,char *action) {
    int width = getmaxx(parent_win)-4;
    int height = 156/width +8;
    WINDOW *w = newwin(height, width, 10, 6);
    box(w, 0, 0);

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
    move(8,getmaxx(stdscr)-6);
    refresh();
    int ch = getch();
    touchwin(parent_win);
    wrefresh(parent_win);
    wclear(w);
    wrefresh(w);
    delwin(w);
    touchwin(parent_win);
    wrefresh(parent_win);
    switch(ch){
        case 'q':
        case 27:
            /*if strlen(task_input)<2 after removing any space from begining and finish skip
             * else save
             */
            return;
        case KEY_ENTER:
        case '\n':
            noteWindow(parent_win,addAction);
    }
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
        wattron(parent_win,A_BOLD);
        mvwprintw(parent_win,1,(COLS-21)/2, "Title");
        mvwvline(parent_win,1,COLS-20,0,getmaxy(parent_win)-2);
        mvwprintw(parent_win,1,COLS-19, "N");
        mvwvline(parent_win,1,COLS-18,0,getmaxy(parent_win)-2);
        mvwprintw(parent_win,1,COLS-14, "Created on");
        wattroff(parent_win,A_BOLD);
        /*
         * generic *
        wattron(parent_win,COLOR_PAIR(2)|A_UNDERLINE);
        wattron(parent_win,A_REVERSE);
        mvwprintw(parent_win,3,2, "1. First Task");
        wattroff(parent_win,A_REVERSE);
        wattron(parent_win,COLOR_PAIR(5));
        mvwprintw(parent_win,3,COLS-19, "V");
        wattroff(parent_win,COLOR_PAIR(5));
        mvwprintw(parent_win,3,COLS-17, "13.04.2001 10:56");
        wattroff(parent_win,COLOR_PAIR(2)|A_UNDERLINE);
        mvwprintw(parent_win,4,2, "1.1 First subTask");
        wattron(parent_win,COLOR_PAIR(2));
        mvwprintw(parent_win,4,COLS-19, "X");
        wattroff(parent_win, COLOR_PAIR(2));
        mvwprintw(parent_win,4,COLS-17, "13.04.2001 10:58");
        wattron(parent_win,COLOR_PAIR(3));
        mvwprintw(parent_win,5,2, "1.1.1 First subSubTask");
        wattron(parent_win,COLOR_PAIR(5));
        mvwprintw(parent_win,5,COLS-19, "V");
        wattroff(parent_win,COLOR_PAIR(5));
        mvwprintw(parent_win,5,COLS-17, "13.04.2001 10:58");
        mvwprintw(parent_win,6,2, "1.1.2 Second subSubTask");
        wattron(parent_win,COLOR_PAIR(5));
        mvwprintw(parent_win,6,COLS-19, "V");
        wattroff(parent_win,COLOR_PAIR(5));
        mvwprintw(parent_win,6,COLS-17, "13.04.2001 10:58");
        wattroff(parent_win,A_REVERSE);
        wattroff(parent_win,COLOR_PAIR(3));
        */
    }// "13.04.2001 10:56" :16 char +2 spacing
    mvwhline(parent_win,2,1,0,getmaxx(parent_win)-2);
    wrefresh(parent_win);
    refresh();
}
