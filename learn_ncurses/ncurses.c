#include <ncurses.h>
#include <unistd.h>

int main1(){
    int x,y;
    x=y=10;

    //initialize the screen and sets up memory and clears screen
    initscr();
    WINDOW * win=newwin(10, 30, y, x); //height, width, y, x
    /*
     * A_NORMAL
     * A_STANDOUT
     * A_REVERSE //highlight the text (inverse colors)
     * A_BLINK
     * A_DIM
     * A_BOLD
     * A_PROTECT
     * A_INVIS
     * A_ALTHCHARSET
     * A_CHARTEXT
     */
    attron(A_REVERSE);
    attron(A_BLINK);
    printw(" enter a char ");
    attroff(A_REVERSE);
    attroff(A_BLINK);
    /*
     *
     */
    refresh();
    char m='m';
    //box(win,0,(int)m);//left and right, app and down
    //wborder(WINDOW *, left, right, top, bottom, tlc, trc, blc, brc)
    wborder(win, 0, 0, 104, 104, (int)'+', (int)'+', (int)'+', (int)'+');

    mvwprintw(win,1,1,"this is my box");//    wprintw(win,"this is my box");

    wrefresh(win);
    //mvprintw(y,x,"welcome");//moves than prints


    //whats for user input, return int value of that key
    //int c= getch();


    //prints a string char * to a window:
    //wprintw(win,"%c %d",c,c);

    getch();
    endwin();
    //free up th memory and ends ncurses
    return 0;
}
//inputwindow
int main(){
    initscr();
    WINDOW * inputwin=newwin(10, 30, 0, 0);
    box(inputwin,0,0);

}
/*** Docs ***/
/*** initialize ***
initscr(); initialize the screen and sets up memory and clears screen
*** refresh ***
refresh(); refresh the screen
wrefresh(win); a specific window
*** Input ***
int c = wgetch(input); //reads in windpw
wprintw(win, "you entered %c§§§", c);
getch(); eq scanf('%c');
noecho(): hides out the input
raw(); gets any input even ^C
*** Output ***
printw("string too"); prints a string char * to a window
//.
refresh();
printw("enter anthing to quit");
//moves the cursor to a specific location:
move(y,x);
printw("string too");
cbreak(); ^C
*/
/*
getyx();
getbegyx();
getmaxyx();
*/
void main5(){
    initscr();
    noecho();

    int y,x,yBeg,xBeg,yMax,xMax;
    move(10,10);
    getyx(stdscr,y,x);//returns cursor pos
    getbegyx(stdscr,yBeg,xBeg);//returns cursor pos
    getmaxyx(stdscr,yMax,xMax);//returns cursor Max pos
    printw("y=%d x=%d yBeg=%d xBeg=%d yMax=%d xMax=%d",y,x,yBeg,xBeg,yMax,xMax);


    getch();
}
int main2(){
    /* NCURCES START */
    initscr();
    if(!has_colors()){
        printw("terminal doesn't support color");
        getch();
        return -1;
    }
    start_color();
    /*
     * COLOR_PAIR(n)
     * COLOR_BLACK   0
     * COLOR_RED     1
     * COLOR_GREEN   2
     * COLOR_YELLOW  3
     * COLOR_BLUE    4
     * COLOR_MAGENTA 5
     * COLOR_CYAN    6
     * COLOR_WHITE   7
    */

    init_pair(1, COLOR_CYAN, COLOR_WHITE); //number id,forground,background
    init_color(COLOR_WHITE,200,255,255); //ovewrite  the color values
    attron(COLOR_PAIR(1));
    printw(" enter a char ");
    attroff(COLOR_PAIR(1));
    mvprintw(1,0,"A TEXT");
    refresh();
    getch();
    endwin();
    return 1;
}
