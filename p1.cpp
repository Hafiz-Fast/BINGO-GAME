#include <curses.h>
#include <iostream>
#include <ctime>
#include <string>
using namespace std;

void Generate_P1_Board(int[100][100], int);
void Generate_P2_Board(int[100][100], int);
void Change_Num_on_Board(int[100][100], int[100][100], int, int, int);
void Checking_Win_Condition(int[100][100], int[100][100], int, int&, int&);
void GettingInput(int&, int&);
void NewGame() {
    clear();
    char key;     // player input and char datatype is used for exit also
    int gameid, Player1Game[100][100] = { 0 }, Player2Game[100][100] = { 0 }, turn;
    int choice = 0, stop, Player1Score = 0, Player2Score = 0;//Stop is used if the user wants to stop the game
    int size; // for dynamic game
    bool Player1Win = false, Player2Win = false;
    string Player1Name, Player2Name;

    attron(COLOR_PAIR(1)); //To turn on an attribute
    printw("Enter the size of the game:");  //To display this message
    refresh();
    echo();  //to show the input on the screen
    scanw("%d", &size);  // Use scanw for input and mod d for taking integer
    while (size < 5 || size>100) {
        attron(COLOR_PAIR(4));
        printw("Invalid Size.Please try again");
        scanw("%d", &size);
    }
    clear();
    refresh();
    gameid = 1000 + rand() % 9000;

    // Cards generation
    // player 1 card
    for (int j = 0; j < size; j++) {
        for (int i = 0; i < size; i++) {
            Player1Game[j][i] = 1 + rand() % (size * size);
            for (int k = 0; k <= j; k++) {
                for (int l = 0; l < size; l++) {
                    while ((Player1Game[k][l] == Player1Game[j][i]) && (j != k || i != l)) {
                        Player1Game[j][i] = 1 + rand() % (size * size);
                        k = 0;
                        l = -1;
                    }
                }
            }
        }
    }
    // player 2 card
    for (int j = 0; j < size; j++) {
        for (int i = 0; i < size; i++) {
            Player2Game[j][i] = 1 + rand() % (size * size);
            for (int k = 0; k <= j; k++) {
                for (int l = 0; l < size; l++) {
                    while ((Player2Game[k][l] == Player2Game[j][i]) && (j != k || i != l)) {
                        Player2Game[j][i] = 1 + rand() % (size * size);
                        k = 0;
                        l = -1;
                    }
                }
            }
        }
    }

    // Ignore newline character similar to cin.ignore
    flushinp();
    attron(COLOR_PAIR(1));
    mvprintw(0, 0, "Player 1 Name: ");
    refresh();
    echo(); // Enable echo for input i.e. typing would be shown now
    getnstr(&Player1Name[0], Player1Name.capacity()); // Use getnstr for string input i.e similar to cin.getline

    mvprintw(1, 0, "Player 2 Name: ");
    refresh();
    getnstr(&Player2Name[0], Player2Name.capacity());
    noecho(); // Disable echo after input
    attroff(COLOR_PAIR(1));
    clear();
    attron(COLOR_PAIR(2));
    turn = rand() % 2;
    attron(COLOR_PAIR(14));
    refresh();

    while (true) {
        if (turn == 0) {
            clear();
            attron(COLOR_PAIR(1));
            mvprintw(0, 0, "Game Id: %d", gameid); //to display the gameid
            move(1, 0);//to move the cursor about
            Generate_P1_Board(Player1Game, size);
            attron(COLOR_PAIR(1));
            // getcury for y axis position and stdscr is a constant which stores current position of cursor
            mvprintw(getcury(stdscr) + 1, 0, "%s select any number from the card:", Player1Name.c_str()); //getcury get the cursor's y position and stdscr is a constant containing the position of cursor 
            refresh();
            GettingInput(choice, stop);
            if (stop == 1) {
                break;
            }

            Change_Num_on_Board(Player1Game, Player2Game, choice, size, stop);
            Checking_Win_Condition(Player1Game, Player2Game, size, Player1Score, Player2Score);

            if (Player1Score == 5) {
                Player1Win = true;
                break;
            }
            else if (Player2Score == 5) {
                Player2Win = true;
                break;
            }
            Player1Score = 0;
            Player2Score = 0;

            clear();
            attron(COLOR_PAIR(1));
            mvprintw(0, 0, "Game Id: %d", gameid);
            move(1, 0);
            Generate_P2_Board(Player2Game, size);
            attron(COLOR_PAIR(1));
            mvprintw(getcury(stdscr) + 1, 0, "%s select any number from the card:", Player2Name.c_str());
            refresh();
            GettingInput(choice, stop);
            if (stop == 1) {
                break;
            }

            Change_Num_on_Board(Player1Game, Player2Game, choice, size, stop);
            Checking_Win_Condition(Player1Game, Player2Game, size, Player1Score, Player2Score);

            if (Player2Score == 5) {
                Player2Win = true;
                break;
            }
            else if (Player1Score == 5) {
                Player1Win = true;
                break;
            }
            Player1Score = 0;
            Player2Score = 0;
        }
        else if (turn == 1) {
            clear();
            attron(COLOR_PAIR(1));
            mvprintw(0, 0, "Game Id: %d", gameid);
            move(1, 0);
            Generate_P2_Board(Player2Game, size);
            attron(COLOR_PAIR(1));
            mvprintw(getcury(stdscr) + 1, 0, "%s select any number from the card:", Player2Name.c_str());
            refresh();
            GettingInput(choice, stop);
            if (stop == 1) {
                break;
            }

            Change_Num_on_Board(Player1Game, Player2Game, choice, size, stop);
            Checking_Win_Condition(Player1Game, Player2Game, size, Player1Score, Player2Score);

            if (Player2Score == 5) {
                Player2Win = true;
                break;
            }
            else if (Player1Score == 5) {
                Player1Win = true;
                break;
            }
            Player1Score = 0;
            Player2Score = 0;

            clear();
            attron(COLOR_PAIR(1));
            mvprintw(0, 0, "Game Id: %d", gameid);
            move(1, 0);
            Generate_P1_Board(Player1Game, size);
            attron(COLOR_PAIR(1));
            mvprintw(getcury(stdscr) + 1, 0, "%s select any number from the card:", Player1Name.c_str());
            refresh();
            GettingInput(choice, stop);
            if (stop == 1) {
                break;
            }

            Change_Num_on_Board(Player1Game, Player2Game, choice, size, stop);
            Checking_Win_Condition(Player1Game, Player2Game, size, Player1Score, Player2Score);

            if (Player1Score == 5) {
                Player1Win = true;
                break;
            }
            else if (Player2Score == 5) {
                Player2Win = true;
                break;
            }
            Player1Score = 0;
            Player2Score = 0;
        }
    }
    clear();
    attron(COLOR_PAIR(2));
    if (Player1Win) {
        mvprintw(15, 45, "%s won!", Player1Name.c_str());
        refresh();
        getch();
    }
    else if (Player2Win) {
        mvprintw(15, 45, "%s won!", Player2Name.c_str());
        refresh();
        getch();
    }
}

void LoadGame() {}
void GameHistory() {}
void ViewHighScore() {}
void HowToPlay() {
    clear();
    attron(COLOR_PAIR(1));
    mvprintw(0, 1, "1) select any number from your card except zero");
    mvprintw(1, 1, "2) Do not repeat a number");
    mvprintw(2, 1, "3) Size of the game ranges from 5 to 100");
    mvprintw(3, 1, "4) You can exit a game by pressing the Esc key in your turn");
    mvprintw(4, 1, "5) A player wins when five lines(either rows columns or diagonals) become zero");
    mvprintw(20, 30, "Press any button to return to main menu");
    getch();
}
void Option_a() {
    char option;
    clear();
    while (true) {
        attron(COLOR_PAIR(1));
        mvprintw(1, 1, "a)Start New Game");
        mvprintw(2, 1, "b)Continue Previous Game");
        refresh();
        option = getch();
        switch (option) {
        case 'a':
            NewGame();
            break;
        case 'b':
            LoadGame();
            break;
        }
        if (option == 'a' || option == 'b') {
            break;
        }
    }
}
void Main_Menu() {
    char option;
    while (true) {
        clear();
        attron(COLOR_PAIR(2));  //turning on color of text
        mvprintw(1, 1, "BINGO");
        attron(COLOR_PAIR(1));
        mvprintw(2, 1, "a)Play Game");
        mvprintw(3, 1, "b)Game History");
        mvprintw(4, 1, "c)View High Score");
        mvprintw(5, 1, "d)How to Play?");
        mvprintw(6, 1, "e)Exit");
        refresh();

        option = getch();      //we just press option once thanks to pdcurses
        switch (option) {
        case 'a':
            clear();
            Option_a();
            break;
        case 'b':
            GameHistory();
            break;
        case 'c':
            ViewHighScore();
            break;
        case 'd':
            HowToPlay();
            break;
        case 'e':
            clear();
            refresh();
            attron(COLOR_PAIR(2));
            mvprintw(15, 35, "Thank You for Playing!!");
            refresh();
            napms(1000);//to stop for some time
            break;
        }
        if (option == 'e') {
            break;
        }
    }
}
int main() {
    srand(time(0));

    initscr();  // Initialize the curses library
    start_color();//initialize color mode
    init_pair(1, COLOR_YELLOW, COLOR_BLACK);//initializing color pair
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_BLUE, COLOR_BLACK);
    init_pair(4, COLOR_RED, COLOR_BLACK);
    keypad(stdscr, true);  // Enable special keys
    curs_set(0); //to hide the cursor
    noecho();  // Do not display characters when typed
    mvprintw(10, 30, "Loading: "); // Initial message mvprintw is used to display on specified location
    //Loading screen
    for (int i = 0; i <= 50; ++i) {
        addch('.');
        refresh();  // to show the changes made on the screen
        napms(100); // Sleep for the specified duration in milliseconds
    }

    printw("....Completed\n");
    refresh();
    napms(1000);
    clear();//to clear the screen of all outputs
    refresh();
    Main_Menu();
    endwin();//end the curses library
    system("pause");

    return 0;
}
void GettingInput(int& choice, int& stop) {
    choice = 0;
    char key;
    while (true) {
        key = getch();

        if (key == 27) {  // ASCII code for Esc key
            stop = 1;
            break;
        }
        else if ((key == KEY_BACKSPACE || key == 8) && choice != 0) { //To remove a digit when backspace is pressed
            choice /= 10;
            move(getcury(stdscr), getcurx(stdscr) - 1);
            printw(" ");
            move(getcury(stdscr), getcurx(stdscr) - 1);
            refresh();
        }
        else if (key == 10) {  // ASCII code for Enter key
            break;
        }
        else if (key >= '0' && key <= '9') {
            choice = choice * 10 + (key - '0');
            printw("%d", key - '0');  // Print the digit
        }
        refresh();  // Refresh the screen
    }
}
void Generate_P1_Board(int Player1Game[100][100], int size) {
    attron(COLOR_PAIR(3));  // Use attron for setting text color to blue

    for (int j = 0; j < size; j++) {
        if (size < 18) {
            printw("\t\t\t\t");
        }
        for (int i = 0; i < size; i++) {  //displaying the board
            if (Player1Game[j][i] < 10) {
                printw("|  %d|", Player1Game[j][i]);
            }
            else if (Player1Game[j][i] < 100) {
                printw("| %d|", Player1Game[j][i]);
            }
            else {
                printw("|%d|", Player1Game[j][i]);
            }
        }
        printw("\n");
    }
    attroff(COLOR_PAIR(3));
    refresh();
}

void Generate_P2_Board(int Player2Game[100][100], int size) {
    attron(COLOR_PAIR(3));

    for (int j = 0; j < size; j++) {
        if (size < 18) {
            printw("\t\t\t\t");
        }
        for (int i = 0; i < size; i++) {
            if (Player2Game[j][i] / 10 == 0) {
                printw("|  %d|", Player2Game[j][i]);
            }
            else if (Player2Game[j][i] < 100) {
                printw("| %d|", Player2Game[j][i]);
            }
            else {
                printw("|%d|", Player2Game[j][i]);
            }
        }
        printw("\n");
    }
    attroff(COLOR_PAIR(3));
    refresh();
}
void Change_Num_on_Board(int Player1Game[100][100], int Player2Game[100][100], int choice, int size, int stop) {
    int present1 = 0;
    for (int j = 0; j < size; j++) {
        for (int i = 0; i < size; i++) {
            if (Player1Game[j][i] == choice && choice != 0) {
                Player1Game[j][i] = 0;
            }
            else {
                present1++;
                if (present1 == size * size) {
                    attron(COLOR_PAIR(4));
                    mvprintw(getcury(stdscr) + 1, 0, "Error:Invalid input,try again\n");
                    GettingInput(choice, stop);
                    j = 0;
                    i = -1;
                    present1 = 0;
                    attroff(COLOR_PAIR(4));
                }
            }
            if (Player2Game[j][i] == choice) {
                Player2Game[j][i] = 0;
            }
        }
    }
}
void Checking_Win_Condition(int Player1Game[100][100], int Player2Game[100][100], int size, int& Player1Score, int& Player2Score) {
    int Tempcount = 0;
    for (int j = 0; j < size; j++) {           //for rows
        for (int i = 0; i < size; i++) {
            if (Player1Game[j][i] == 0) {
                Tempcount++;
            }
        }
        if (Tempcount == size) {
            Player1Score++;
        }
        Tempcount = 0;
    }
    Tempcount = 0;
    for (int j = 0; j < size; j++) {              //for columns
        for (int i = 0; i < size; i++) {
            if (Player1Game[i][j] == 0) {
                Tempcount++;
            }
        }
        if (Tempcount == size) {
            Player1Score++;
        }
        Tempcount = 0;
    }
    Tempcount = 0;
    for (int i = 0; i < size; i++) {            //for main diagonal
        if (Player1Game[i][i] == 0) {
            Tempcount++;
        }
    }
    if (Tempcount == size) {
        Player1Score++;
    }
    Tempcount = 0;
    for (int i = size - 1; i >= 0; i--) {          //for secondary diagnal
        if (Player1Game[(size - 1) - i][i] == 0) {
            Tempcount++;
        }
    }
    if (Tempcount == size) {
        Player1Score++;
    }
    Tempcount = 0;
    for (int j = 0; j < size; j++) {          //for rows
        for (int i = 0; i < size; i++) {
            if (Player2Game[j][i] == 0) {
                Tempcount++;
            }
        }
        if (Tempcount == size) {
            Player2Score++;
        }
        Tempcount = 0;
    }
    Tempcount = 0;
    for (int j = 0; j < size; j++) {           //for columns
        for (int i = 0; i < size; i++) {
            if (Player2Game[i][j] == 0) {
                Tempcount++;
            }
        }
        if (Tempcount == size) {
            Player2Score++;
        }
        Tempcount = 0;
    }
    Tempcount = 0;
    for (int i = 0; i < size; i++) {         //for main diagonal
        if (Player2Game[i][i] == 0) {
            Tempcount++;
        }
    }
    if (Tempcount == size) {
        Player2Score++;
    }
    Tempcount = 0;
    for (int i = size - 1; i >= 0; i--) {      //for secondary diagonal
        if (Player2Game[(size - 1) - i][i] == 0) {
            Tempcount++;
        }
    }
    if (Tempcount == size) {
        Player2Score++;
    }
}