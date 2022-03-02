#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include <sys/time.h>

int position[2] = {22, 1};

char labyrith[24][80] = {
    "###############################################################################", //1
    "# ######                                  ##############                   #  #", //2
    "#      ############################  ###               #  ##  ####   ####  #  #", //3
    "# # #  #                          #    ############  ###  ##  #  #####     #  #", //4
    "# # #  #  ######################  ###    ##                   #         ####  #", //5
    "# # #  #  #     #     #######        ##      ######   ######  #  ###########  #", //6
    "# # ####  #  ####  #        #  ####  ##   ####        #       #  #            #", //7
    "# #          ####  #######  #  #  #       #     ####  #  #  ###  #  ########  #", //8
    "# ############  #     ####  #  #  #####   #  ####  #  #  #  #    #         #  #", //9
    "# #          #  #  #                      #        #  ####  ######  #####  #  #", //10
    "# # ##########  #  ##############################  #             #  #X     #  #", //11
    "# #      #####  #                               ######  ##  ###  #  ########  #", //12
    "# ######        #  ############  #############       #   #    #  #  #         #", //13
    "###  #########  #  #  ##                     #######  #  # #  #  #  #  #####  #", //14
    "# #             #  #  #####################        #  #  # #  #  #  #  #   #  #", //15
    "# #########  ####  #  #####          #########  #  #  #  # ####  #  #  #   #  #", //16
    "#         #  #  #  #         ######             #  #             #  ####      #", //17
    "# ###  #     #  #  ########################  #  #  #######  ###  #         #  #", //18
    "# # #  #######  #                       ######  #       ##  ################  #", //19
    "# # #           #  ########  #  ######          ######                 ##  #  #", //20
    "# # ##### #######  ###########  ###  #########          ##########  #      #  #", //21
    "#                                            ################   ##  ########  #", //22
    "# #########################################           #                       #", //23
    "###############################################################################" //24
};

char maze[24][80] = {
    "###############################################################################", //1
    "#       #####      #                               #                          #", //2
    "#  #  #       ###  #  #  ##################  #######  #  ###  ####  #  ########", //3
    "#  #  #########    #  #  #         #         #     #  #    #  #     #  #     @#", //4
    "#  #             ###  #  #  #####  #  ########  #  #  ###  #  ####  ####  #####", //5
    "#  ####  #########    #  #     ##  #  ##     #  #  #    #  #     #     #  ##  #", //6
    "#  ##              ####  ####  ##  #  ##  #  #  #  ###  #  ####  #  #  #O ##  #", //7
    "#      ##  #########  #        #####  ##  #     #  ##   #     #  #  ########  #", //8
    "#########  #  *       #  ########  #      #  #  #   #  ########@ #            #", //9
    "#          #  #  ######         #  ########  #  ##  #  #      #  #######  ### #", //10
    "#  #########  #  #        #  #  #            #   #  #  #  ##  #     #< #    # #", //11
    "#          #  #  #  # #   #  #  #  ########  ##  ####  #  ##  #######  ###  # #", //12
    "###  #######  #  #  # #   #  #  #  #      #  @#           ##      ###    #  # #", //13
    "#    #        #     # #   #  #  #  #   #  ##  ###  #############  #   #  #  ###", //14
    "# ####  #######  #  # #   #  #  #  #   #   #    #  #              #  ##       #", //15
    "# #     #     #  #  # #  ##  ####  #   ##  ###  #  #  ########## @#  ##########", //16
    "# #  ####  #######  # #       #    ##   #    #  #  #  #        ####  #       X#", //17
    "# #  ####  #     #  # #  ######  ####  #######  #  #  # ###### #  #  #   ###  #", //18
    "# #        #  #     # #  #       #     #        #  #  #     O# #     #   #    #", //19
    "# #######  #  ####### #  # #######  #  # #####  #  #  ######## #######   #  # #", //20
    "#       #  #        # #  # #     #  #    # X #  #  #                 # O #  # #", //21
    "#*################  ###  # ####  #  ######@ @####*########################  ###", //22
    "#O@                      #          #             #                           #", //23
    "###############################################################################" //24
};

void setPosition(int y, int x){
    position[0] = y;
    position[1] = x;
}

int getHorizontal(){
    return position[1];
}

int getVertical(){
    return position[0];
}

void lose(){
    clear();
    mvprintw(LINES/2, COLS/2 - 5, "YOU LOST!");
    refresh();
}

void won(){
    clear();
    mvprintw(LINES/2, COLS/2, "YOU WON!");
    refresh();
}

void generate_map(){
    struct timespec ts = {
        .tv_sec = 0,                    // nr of secs
        .tv_nsec = (long)(0.001 * 1000000000L)  // nr of nanosecs
    };
    for(int i = 0; i < 80; i++){
        for(int j = 0; j < 24; j++){
            if(j == 12 && i == 1){
                init_pair(1, COLOR_BLACK, COLOR_GREEN);
                attron(COLOR_PAIR(1));
                mvaddch(j, i, '1');
                attroff(COLOR_PAIR(1));
                nanosleep(&ts, NULL);
                refresh();
            }
            else if(j == 22 && i == 1){
                init_pair(3, COLOR_WHITE, COLOR_BLUE);
                attron(COLOR_PAIR(3));
                mvaddch(j, i, '^');
                attroff(COLOR_PAIR(3));
                nanosleep(&ts, NULL);
                refresh();
            }
            else if(j == 10 && i == 69){
                init_pair(2, COLOR_BLACK, COLOR_RED);
                attron(COLOR_PAIR(2));
                mvaddch(j, i, 'X');
                attroff(COLOR_PAIR(2));
                nanosleep(&ts, NULL);
                refresh();
            }
            else{
                if(labyrith[j][i] == ' '){
                    mvprintw(j, i, &labyrith[j][i]);
                }
                else{
                    init_pair(15, COLOR_WHITE, COLOR_WHITE);
                    attron(COLOR_PAIR(15));
                    mvaddch(j, i, ' ');
                    attroff(COLOR_PAIR(15));
                }

                nanosleep(&ts, NULL);
                refresh();
            }
        }
    }
    refresh();
}

void generate_second(){
    struct timespec ts = {
        .tv_sec = 0,                    // nr of secs
        .tv_nsec = (long)(0.001 * 1000000000L)  // nr of nanosecs
    };
    for(int i = 0; i < 80; i++){
        for(int j = 0; j < 24; j++){
            if((j == 10 && i == 67) || (j == 20 && i == 77)){
                init_pair(1, COLOR_BLACK, COLOR_GREEN);
                attron(COLOR_PAIR(1));
                mvaddch(j, i, '1');
                attroff(COLOR_PAIR(1));
                nanosleep(&ts, NULL);
                refresh();
            }
            else if(j == getVertical() && i == getHorizontal()){
                init_pair(3, COLOR_WHITE, COLOR_BLUE);
                attron(COLOR_PAIR(3));
                mvaddch(j, i, '<');
                attroff(COLOR_PAIR(3));
                nanosleep(&ts, NULL);
                refresh();
            }
            else if((j == 16 && i == 77) || (j == 20 && i == 43)){
                init_pair(2, COLOR_BLACK, COLOR_RED);
                attron(COLOR_PAIR(2));
                mvaddch(j, i, 'X');
                attroff(COLOR_PAIR(2));
                nanosleep(&ts, NULL);
                refresh();
            }
            else{
                if(maze[j][i] == ' '){
                    mvprintw(j, i, &maze[j][i]);
                }
                else if(maze[j][i] == '#'){
                    init_pair(16, COLOR_WHITE, COLOR_WHITE);
                    attron(COLOR_PAIR(16));
                    mvaddch(j, i, ' ');
                    attroff(COLOR_PAIR(16));
                }
                else if (maze[j][i] == 'O'){
                    init_pair(17, COLOR_WHITE, COLOR_MAGENTA);
                    attron(COLOR_PAIR(17));
                    mvaddch(j, i, 'O');
                    attroff(COLOR_PAIR(17));
                }

                else if (maze[j][i] == '@'){
                    init_pair(18, COLOR_BLACK, COLOR_YELLOW);
                    attron(COLOR_PAIR(18));
                    mvaddch(j, i, '@');
                    attroff(COLOR_PAIR(18));
                }

                else if (maze[j][i] == '*'){
                    init_pair(19, COLOR_YELLOW, COLOR_WHITE);
                    attron(COLOR_PAIR(19));
                    mvaddch(j, i, '*');
                    attroff(COLOR_PAIR(19));
                }

                nanosleep(&ts, NULL);
                refresh();
            }
        }
    }
    refresh();
}

int main(){
    srand( (unsigned int) time(NULL) );
    initscr();
    start_color();
    init_pair(3, COLOR_BLACK, COLOR_WHITE);
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(false);
    nodelay(stdscr, TRUE);
    refresh();
    int win = 0;
    int beeper = 0;
    generate_map();
    refresh();
    int input;;
    while(!win){
        input = getch();
        switch(input){
            case KEY_UP:
                if((!(labyrith[getVertical()-1][getHorizontal()] == '#')) && (!(labyrith[getVertical()-1][getHorizontal()] == 'X' && beeper == 0))){
                    mvaddch(getVertical(), getHorizontal(), ' ');
                    setPosition(getVertical()-1, getHorizontal());
                    attron(COLOR_PAIR(3));
                    mvaddch(getVertical(), getHorizontal(), '^');
                    attroff(COLOR_PAIR(3));

                }
                else{
                    attron(COLOR_PAIR(3));
                    mvaddch(getVertical(), getHorizontal(), '^');
                    attroff(COLOR_PAIR(3));
                }
                if(getVertical() == 12 && getHorizontal() == 1){
                    beeper = 1;
                    init_pair(3, COLOR_BLACK, COLOR_GREEN);
                }
                if(getVertical() == 10 && getHorizontal() == 69){
                    win = 1;
                    beeper = 0;
                    init_pair(3, COLOR_BLACK, COLOR_WHITE);
                }
                break;
            case KEY_DOWN:
                if((!(labyrith[getVertical()+1][getHorizontal()] == '#')) && (!(labyrith[getVertical()+1][getHorizontal()] == 'X' && beeper == 0))){
                    mvaddch(getVertical(), getHorizontal(), ' ');
                    setPosition(getVertical()+1, getHorizontal());
                    attron(COLOR_PAIR(3));
                    mvaddch(getVertical(), getHorizontal(), 'v');
                    attroff(COLOR_PAIR(3));
                }
                else{
                    attron(COLOR_PAIR(3));
                    mvaddch(getVertical(), getHorizontal(), 'v');
                    attroff(COLOR_PAIR(3));
                }
                if(getVertical() == 12 && getHorizontal() == 1){
                    beeper = 1;
                    init_pair(3, COLOR_BLACK, COLOR_GREEN);
                }
                if(getVertical() == 10 && getHorizontal() == 69){
                    win = 1;
                    beeper = 0;
                    init_pair(3, COLOR_BLACK, COLOR_WHITE);
                }
                break;
            case KEY_LEFT:
                if((!(labyrith[getVertical()][getHorizontal()-1] == '#')) && (!(labyrith[getVertical()][getHorizontal()-1] == 'X' && beeper == 0))){
                    mvaddch(getVertical(), getHorizontal(), ' ');
                    setPosition(getVertical(), getHorizontal()-1);
                    attron(COLOR_PAIR(3));
                    mvaddch(getVertical(), getHorizontal(), '<');
                    attroff(COLOR_PAIR(3));
                }
                else{
                    attron(COLOR_PAIR(3));
                    mvaddch(getVertical(), getHorizontal(), '<');
                    attroff(COLOR_PAIR(3));
                }
                if(getVertical() == 12 && getHorizontal() == 1){
                    beeper = 1;
                    init_pair(3, COLOR_BLACK, COLOR_GREEN);
                }
                if(getVertical() == 10 && getHorizontal() == 69){
                    win = 1;
                    beeper = 0;
                    init_pair(3, COLOR_BLACK, COLOR_WHITE);
                }
                break;
            case KEY_RIGHT:
                if((!(labyrith[getVertical()][getHorizontal()+1] == '#')) && (!(labyrith[getVertical()][getHorizontal()+1] == 'X' && beeper == 0))){
                    mvaddch(getVertical(), getHorizontal(), ' ');
                    setPosition(getVertical(), getHorizontal()+1);
                    attron(COLOR_PAIR(3));
                    mvaddch(getVertical(), getHorizontal(), '>');
                    attroff(COLOR_PAIR(3));
                }
                else{
                    attron(COLOR_PAIR(3));
                    mvaddch(getVertical(), getHorizontal(), '>');
                    attroff(COLOR_PAIR(3));
                }
                if(getVertical() == 12 && getHorizontal() == 1){
                    beeper = 1;
                    init_pair(3, COLOR_BLACK, COLOR_GREEN);
                }
                if(getVertical() == 10 && getHorizontal() == 69){
                    win = 1;
                    beeper = 0;
                    init_pair(3, COLOR_BLACK, COLOR_WHITE);
                }
                break;
        }
        input = '0';
    }
    win = 0;
    int first = 0; int second = 0;
    int put = 0;
    generate_second();
    refresh();
    while(!win){
        input = getch();
        switch(input){
            case KEY_UP:
                if(maze[getVertical()-1][getHorizontal()] == '@'){
                    mvaddch(getVertical(), getHorizontal(), ' ');
                    attron(COLOR_PAIR(3));
                    mvaddch(getVertical(), getHorizontal(), '^');
                    attroff(COLOR_PAIR(3));
 //                   win=1;
                    lose();
                    break;
                }
                if(maze[getVertical()-1][getHorizontal()] == 'O'){
                    mvaddch(getVertical(), getHorizontal(), ' ');
                    if(getVertical()-1 == 22 && getHorizontal() == 1){
                        setPosition(19, 71);
                        attron(COLOR_PAIR(3));
                        mvaddch(getVertical(), getHorizontal(), '^');
                        attroff(COLOR_PAIR(3));
                        break;
                    }
                    else if(getVertical()-1 == 20 && getHorizontal() == 71){
                        setPosition(21, 1);
                        attron(COLOR_PAIR(3));
                        mvaddch(getVertical(), getHorizontal(), '^');
                        attroff(COLOR_PAIR(3));
                        break;
                    }
                    else if(getVertical()-1 == 18 && getHorizontal() == 60){
                        setPosition(5, 72);
                        attron(COLOR_PAIR(3));
                        mvaddch(getVertical(), getHorizontal(), '^');
                        attroff(COLOR_PAIR(3));
                        break;
                    }
                    else if(getVertical()-1 == 6 && getHorizontal() == 72){
                        setPosition(18, 59);
                        attron(COLOR_PAIR(3));
                        mvaddch(getVertical(), getHorizontal(), '<');
                        attroff(COLOR_PAIR(3));
                        break;
                    }
                }
                if((!(maze[getVertical()-1][getHorizontal()] == '#')) && (!(maze[getVertical()-1][getHorizontal()] == 'X' && beeper == 0))){
                    mvaddch(getVertical(), getHorizontal(), ' ');
                    setPosition(getVertical()-1, getHorizontal());
                    attron(COLOR_PAIR(3));
                    mvaddch(getVertical(), getHorizontal(), '^');
                    attroff(COLOR_PAIR(3));

                }
                else{
                    attron(COLOR_PAIR(3));
                    mvaddch(getVertical(), getHorizontal(), '^');
                    attroff(COLOR_PAIR(3));
                }
                if((getVertical() == 10 && getHorizontal() == 67) || (getVertical() == 20 && getHorizontal() == 77)){
                    beeper += 1;
                    init_pair(3, COLOR_BLACK, COLOR_GREEN);
                }
                   if((getVertical() == 16 && getHorizontal() == 77 && first == 0)){
                       beeper -= 1;
		       maze[16][77] = ' ';
                       first = 1;
                       if(beeper == 0) init_pair(3, COLOR_WHITE, COLOR_BLUE);
                       put += 1;
                       if(put == 2){
                           won();
                           win = 1;
                       }
                   }
                   if(getVertical() == 20 && getHorizontal() == 43 && second == 0){
                       beeper -= 1;
		       maze[20][43] = ' ';
                       second = 1;
                       put += 1;
                       if(beeper == 0) init_pair(3, COLOR_WHITE, COLOR_BLUE);
                       if(put == 2){
                           won();
                           win = 1;
                       }
                   }
                break;
            case KEY_DOWN:
                if(maze[getVertical()+1][getHorizontal()] == '@'){
                    mvaddch(getVertical(), getHorizontal(), ' ');
                    setPosition(getVertical()-1, getHorizontal());
                    attron(COLOR_PAIR(3));
                    mvaddch(getVertical(), getHorizontal(), '^');
                    attroff(COLOR_PAIR(3));
                    lose();
                    break;
                }
                if(maze[getVertical()+1][getHorizontal()] == 'O'){
                    mvaddch(getVertical(), getHorizontal(), ' ');
                    if(getVertical()+1 == 22 && getHorizontal() == 1){
                        setPosition(19, 71);
                        attron(COLOR_PAIR(3));
                        mvaddch(getVertical(), getHorizontal(), '^');
                        attroff(COLOR_PAIR(3));
                        break;
                    }
                    else if(getVertical()+1 == 20 && getHorizontal() == 71){
                        setPosition(21, 1);
                        attron(COLOR_PAIR(3));
                        mvaddch(getVertical(), getHorizontal(), '^');
                        attroff(COLOR_PAIR(3));
                        break;
                    }
                    else if(getVertical()+1 == 18 && getHorizontal() == 60){
                        setPosition(5, 72);
                        attron(COLOR_PAIR(3));
                        mvaddch(getVertical(), getHorizontal(), '^');
                        attroff(COLOR_PAIR(3));
                        break;
                    }
                    else if(getVertical()+1 == 6 && getHorizontal() == 72){
                        setPosition(18, 59);
                        attron(COLOR_PAIR(3));
                        mvaddch(getVertical(), getHorizontal(), '<');
                        attroff(COLOR_PAIR(3));
                        break;
                    }
                }
                if((!(maze[getVertical()+1][getHorizontal()] == '#')) && (!(maze[getVertical()+1][getHorizontal()] == 'X' && beeper == 0))){
                    mvaddch(getVertical(), getHorizontal(), ' ');
                    setPosition(getVertical()+1, getHorizontal());
                    attron(COLOR_PAIR(3));
                    mvaddch(getVertical(), getHorizontal(), 'v');
                    attroff(COLOR_PAIR(3));
                }
                else{
                    attron(COLOR_PAIR(3));
                    mvaddch(getVertical(), getHorizontal(), 'v');
                    attroff(COLOR_PAIR(3));
                }
                if((getVertical() == 10 && getHorizontal() == 67) || (getVertical() == 20 && getHorizontal() == 77)){
                    beeper += 1;
                    init_pair(3, COLOR_BLACK, COLOR_GREEN);
                }
                   if((getVertical() == 16 && getHorizontal() == 77 && first == 0)){
                       beeper -= 1;
		       maze[16][77] = ' ';
                       first = 1;
                       put += 1;
                       if(beeper == 0) init_pair(3, COLOR_WHITE, COLOR_BLUE);
                       if(put == 2){
                           won();
                           win = 1;
                       }
                   }
                   if(getVertical() == 20 && getHorizontal() == 43 && second == 0){
                       beeper -= 1;
		       maze[20][43] = ' ';
                       second = 1;
                       put += 1;
                       if(beeper == 0) init_pair(3, COLOR_WHITE, COLOR_BLUE);
                       if(put == 2){
                           won();
                           win = 1;
                       }
                   }
                break;
            case KEY_LEFT:
                if(maze[getVertical()][getHorizontal()-1] == '@'){
                       mvaddch(getVertical(), getHorizontal(), ' ');
                       setPosition(getVertical()-1, getHorizontal());
                       attron(COLOR_PAIR(3));
                       mvaddch(getVertical(), getHorizontal(), '^');
                       attroff(COLOR_PAIR(3));
                       lose();
                    break;
                }
                if(maze[getVertical()][getHorizontal()-1] == 'O'){
                    mvaddch(getVertical(), getHorizontal(), ' ');
                    if(getVertical() == 22 && getHorizontal()-1 == 1){
                        setPosition(19, 71);
                        attron(COLOR_PAIR(3));
                        mvaddch(getVertical(), getHorizontal(), '^');
                        attroff(COLOR_PAIR(3));
                        break;
                    }
                    else if(getVertical() == 20 && getHorizontal()-1 == 71){
                        setPosition(21, 1);
                        attron(COLOR_PAIR(3));
                        mvaddch(getVertical(), getHorizontal(), '^');
                        attroff(COLOR_PAIR(3));
                        break;
                    }
                    else if(getVertical() == 18 && getHorizontal()-1 == 60){
                        setPosition(5, 72);
                        attron(COLOR_PAIR(3));
                        mvaddch(getVertical(), getHorizontal(), '^');
                        attroff(COLOR_PAIR(3));
                        break;
                    }
                    else if(getVertical() == 6 && getHorizontal()-1 == 72){
                        setPosition(18, 59);
                        attron(COLOR_PAIR(3));
                        mvaddch(getVertical(), getHorizontal(), '<');
                        attroff(COLOR_PAIR(3));
                        break;
                    }
                }
                if((!(maze[getVertical()][getHorizontal()-1] == '#')) && (!(maze[getVertical()][getHorizontal()-1] == 'X' && beeper == 0))){
                    mvaddch(getVertical(), getHorizontal(), ' ');
                    setPosition(getVertical(), getHorizontal()-1);
                    attron(COLOR_PAIR(3));
                    mvaddch(getVertical(), getHorizontal(), '<');
                    attroff(COLOR_PAIR(3));
                }
                else{
                    attron(COLOR_PAIR(3));
                    mvaddch(getVertical(), getHorizontal(), '<');
                    attroff(COLOR_PAIR(3));
                }
                if((getVertical() == 10 && getHorizontal() == 67) || (getVertical() == 20 && getHorizontal() == 77)){
                    beeper += 1;
                    init_pair(3, COLOR_BLACK, COLOR_GREEN);
                }
                   /*if((getVertical() == 16 && getHorizontal() == 77) || (getVertical() == 20 && getHorizontal() == 43)){
                       beeper -= 1;
		       maze[16][77] = ' ';
                       put += 1;
                       if(beeper == 0) init_pair(3, COLOR_BLACK, COLOR_WHITE);
                       if(put == 2){
                           won();
                           win = 1;
                       }
                   }*/
                   if((getVertical() == 16 && getHorizontal() == 77 && first == 0)){
                       beeper -= 1;
                       maze[16][77] = ' ';
		       first = 1;
                       if(beeper == 0) init_pair(3, COLOR_WHITE, COLOR_BLUE);
                       put += 1;
                       if(put == 2){
                           won();
                           win = 1;
                       }
                   }
                   if(getVertical() == 20 && getHorizontal() == 43 && second == 0){
                       beeper -= 1;
                       second = 1;
                       put += 1;
                       if(put == 2){
                           won();
                           win = 1;
                       }
                   }
                break;
            case KEY_RIGHT:
                if(maze[getVertical()][getHorizontal()+1] == '@'){
                       mvaddch(getVertical(), getHorizontal(), ' ');
                       setPosition(getVertical()+1, getHorizontal());
                       attron(COLOR_PAIR(3));
                       mvaddch(getVertical(), getHorizontal(), '^');
                       attroff(COLOR_PAIR(3));
                       lose();
                    break;
                }
                if(maze[getVertical()][getHorizontal()+1] == 'O'){
                    mvaddch(getVertical(), getHorizontal(), ' ');
                    if(getVertical() == 22 && getHorizontal()+1 == 1){
                        setPosition(19, 71);
                        attron(COLOR_PAIR(3));
                        mvaddch(getVertical(), getHorizontal(), '^');
                        attroff(COLOR_PAIR(3));
                        break;
                    }
                    else if(getVertical() == 20 && getHorizontal()+1 == 71){
                        setPosition(21, 1);
                        attron(COLOR_PAIR(3));
                        mvaddch(getVertical(), getHorizontal(), '^');
                        attroff(COLOR_PAIR(3));
                        break;
                    }
                    else if(getVertical() == 18 && getHorizontal()+1 == 60){
                        setPosition(5, 72);
                        attron(COLOR_PAIR(3));
                        mvaddch(getVertical(), getHorizontal(), '^');
                        attroff(COLOR_PAIR(3));
                        break;
                    }
                    else if(getVertical() == 6 && getHorizontal()+1 == 72){
                        setPosition(18, 59);
                        attron(COLOR_PAIR(3));
                        mvaddch(getVertical(), getHorizontal(), '<');
                        attroff(COLOR_PAIR(3));
                        break;
                    }
                }
                if((!(maze[getVertical()][getHorizontal()+1] == '#')) && (!(maze[getVertical()][getHorizontal()+1] == 'X' && beeper == 0))){
                    mvaddch(getVertical(), getHorizontal(), ' ');
                    setPosition(getVertical(), getHorizontal()+1);
                    attron(COLOR_PAIR(3));
                    mvaddch(getVertical(), getHorizontal(), '>');
                    attroff(COLOR_PAIR(3));
                }
                else{
                    attron(COLOR_PAIR(3));
                    mvaddch(getVertical(), getHorizontal(), '>');
                    attroff(COLOR_PAIR(3));
                }
                if((getVertical() == 10 && getHorizontal() == 67) || (getVertical() == 20 && getHorizontal() == 77)){
                    beeper += 1;
                    init_pair(3, COLOR_BLACK, COLOR_GREEN);
                }
                if((getVertical() == 16 && getHorizontal() == 77 && first == 0)){
                    beeper -= 1;
		    maze[16][77] = ' ';
                    first = 1;
                    if(beeper == 0) init_pair(3, COLOR_WHITE, COLOR_BLUE);
                    put += 1;
                    if(put == 2){
                        won();
                        win = 1;
                    }
                }
                if(getVertical() == 20 && getHorizontal() == 43 && second == 0){
                    beeper -= 1;
		    maze[20][43] = ' ';
                    second = 1;
                    if(beeper == 0) init_pair(3, COLOR_WHITE, COLOR_BLUE);
                    put += 1;
                    if(put == 2){
                        won();
                        win = 1;
                    }
                }
                break;
        }
        input = '0';
    }

    getchar();
    delwin(stdscr);
    endwin();
}

