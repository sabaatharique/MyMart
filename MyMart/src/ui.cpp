#include "ui.h"

Ui::Ui()
{
    screens[Main] = true;
    for(int i=1; i<tot_screen; i++) {
        screens[i] = false;
    }
    initscr();
    curs_set(0);
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    mousemask(ALL_MOUSE_EVENTS, NULL);
}

Ui::~Ui()
{
    endwin();
}


bool Ui::GetScreen(const int val)
{
    return screens[val];
}

void Ui::BackgroundClr(WINDOW* win, short fg = FG, short bg = BG)
{
    start_color();
    init_pair(1, fg, bg);
    wbkgd(win, COLOR_PAIR(1));
}

bool Ui::IsInBox(const int val_x, const int val_y, const int x, const int y, const int length) {
    return val_y == y && val_x >= x && val_x <= x+length;
}

void Ui::DrawBox(WINDOW* win, const int x, const int y, string line, const bool active)
{
    if(active) wattron(win, A_REVERSE);
    mvwprintw(win, x, y, line.c_str());
    if(active) wattroff(win, A_REVERSE);
}

void Ui::DrawWindow(WINDOW* win, int highlight, const vector<string>& choices, int width, int height, const string title, short fg = FG, short bg = BG, int line_ch = 0) {
    werase(win);
    BackgroundClr(win, fg, bg);
    box(win, 0, 0);

    // Print title
    mvwprintw(win, 0, (width - (int)title.size()) / 2, title.c_str());

    // Print items
    for(size_t i = 0; i < choices.size(); i++) {
        if (i == highlight) {
            wattron(win, A_REVERSE); // Highlight selection
        }
        mvwprintw(win, 2 + i * 2, 2, choices[i].c_str());
        if (i == highlight) {
            wattroff(win, A_REVERSE);
        }
    }

    wrefresh(win);
}

void Ui::GetUsername(WINDOW* win, string &username, int startX, int startY) {
    char ch;
    username = "";
    wmove(win, startY, startX);
    while ((ch = wgetch(win)) != KEY_ENTER) { // Enter key to stop
        if (ch == KEY_BACKSPACE) { // Handle Backspace
            if (!username.empty()) {
                username.pop_back();
                int x, y;
                getyx(win, y, x);
                mvwaddch(win, y, x - 1, ' ');
                wmove(win, y, x - 1);
            }
        } else {
            username += ch;
        }
        mvwprintw(win, startY, startX, username.c_str());
    }
}

void Ui::GetPassword(WINDOW* win, string &password, int startX, int startY) {
    char ch;
    password = "";
    string encrypted = "";
    wmove(win, startY, startX);
    while ((ch = wgetch(win)) != KEY_ENTER) { // Enter key to stop
        if (ch == KEY_BACKSPACE) { // Handle Backspace
            if (!password.empty()) {
                password.pop_back();
                encrypted.pop_back();
                int x, y;
                getyx(win, y, x);
                mvwaddch(win, y, x - 1, ' ');
                wmove(win, y, x - 1);
            }
        } else {
            password += ch;
            encrypted += '*';
            //wechochar(win, '*');
        }
        mvwprintw(win, startY, startX, encrypted.c_str());
    }
}

void Ui::DrawSignUp(WINDOW* win, bool highlight, int width, int height, string &username, string &password) {
    werase(win);
    BackgroundClr(win);
    box(win, 0, 0);

    mvwprintw(win, 0, (width - 6) / 2, "MyMart");
    mvwprintw(win, 1, (width - 17) / 2, "Create an account");
    mvwprintw(win, 3, 2, "Enter Username: ");
    mvwprintw(win, 5, 2, "Enter Password: ");
    mvwprintw(win, 7, 2, "Already have an account?");
    wattron(win, A_BOLD);
    DrawBox(win, 7, 27, "Login", (highlight == true));
    wattroff(win, A_BOLD);

    wrefresh(win);
}

void Ui::Engine()
{
    // Select
    int active_select = -1;
    vector<string> choices_select = {
        "1. Manager",
        "2. Cashier",
        "3. Stock Clerk",
    };
    WINDOW* win_select = newwin(select_W_height, select_W_width, (LINES-select_W_height)/2, (COLS-select_W_width)/2);
    keypad(win_select, TRUE);

    // login_signup
    int active_login_signup = -1;
    vector<string> choices_login_signup = {
        "Log in",
        "Sign up",
    };
    WINDOW* win_login_signup = newwin(login_signup_W_height, login_signup_W_width, (LINES-login_signup_W_height)/2, (COLS-login_signup_W_width)/2);
    keypad(win_login_signup, TRUE);

    // Sign_Up

    bool active_signup = false;
    WINDOW* win_signup = newwin(10, 40, (LINES - 10) / 2, (COLS - 40) / 2);
    keypad(win_signup, TRUE);

    while(true) {
        BackgroundClr(stdscr);
        if(GetScreen(Main)) Show_Main();
        if(GetScreen(Select)) Show_Select(win_select, &active_select, choices_select);
        if(GetScreen(Login_SignUp)) Show_Login_SignUp(win_login_signup, &active_login_signup, choices_login_signup);
        if(GetScreen(SignUp)) Show_SignUp(win_signup, &active_signup);
    }
}

void Ui::Show_Main()
{
    MEVENT event;
    clear();

    vector<string> choices = {};
    DrawWindow(stdscr, false, choices, COLS, LINES, "");
    //mvhline(1, 1, ACS_HLINE, COLS-2);
    init_pair(2, 7, BG);
    attron(COLOR_PAIR(2) | A_BOLD);
    mvwprintw(stdscr, MY_MART_BUTTON_Y, MY_MART_BUTTON_X, "##   ##         ##   ##");
    mvwprintw(stdscr, MY_MART_BUTTON_Y+1, MY_MART_BUTTON_X, "# # # #  #   #  # # # #    #    ###   #####");
    mvwprintw(stdscr, MY_MART_BUTTON_Y+2, MY_MART_BUTTON_X, "#  #  #   # #   #  #  #   # #   #  #    #");
    mvwprintw(stdscr, MY_MART_BUTTON_Y+3, MY_MART_BUTTON_X, "#     #    #    #     #  #####  ###     #");
    mvwprintw(stdscr, MY_MART_BUTTON_Y+4, MY_MART_BUTTON_X, "#     #    #    #     #  #   #  #  #    #");
    mvwprintw(stdscr, Press_Enter_Y, Press_Enter_X, "press enter to continue!");
    attroff(COLOR_PAIR(2) | A_BOLD);
    //DrawBox(stdscr, MY_MART_BUTTON_Y, MY_MART_BUTTON_X, "MY MART", (*active == true));
    //mvhline(3, 1, ACS_HLINE, COLS-2);

    refresh();

    int ch = getch();

    switch(ch) {
        case KEY_ENTER:
            screens[Main] = false;
            screens[Select] = true;
            break;
    }
}

void Ui::Show_Select(WINDOW* win, int *active, const vector<string>& choices)
{
    int N = choices.size();
    clear();
    vector<string> chcs = {};
    DrawWindow(stdscr, false, chcs, COLS, LINES, "");
    //mvprintw(4, 1, "Enter your employee type");

    DrawWindow(win, *active, choices, select_W_width, select_W_height, "SELECT");
    refresh();

    int ch = wgetch(win);

    switch(ch) {
        case '1':
            screens[Select] = false;
            screens[Login_SignUp] = true;
            break;
        case '2':
            screens[Select] = false;
            screens[Login_SignUp] = true;
            break;
        case '3':
            screens[Select] = false;
            screens[Login_SignUp] = true;
            break;
        case KEY_TAB:
            *active = (*active + 1)%N;
            break;
        case KEY_BTAB:
            *active = (*active - 1 + N) % N;
            break;
        case KEY_DOWN:
            if(*active < N-1) {
                *active = (*active + 1);
            }
            break;
        case KEY_UP:
            if(*active > 0) {
                *active = (*active - 1);
            }
            break;
        case KEY_ENTER:
            if(*active == 0 || *active == 1 || *active == 2) {
                screens[Select] = false;
                screens[Login_SignUp] = true;
            }
            else if(*active == N-1) {
                screens[Select] = false;
                screens[Main] = true;
            }
            break;
    }
}

void Ui::Show_Login_SignUp(WINDOW* win, int *active, const vector<string>& choices)
{
    clear();
    vector<string> chcs = {};
    DrawWindow(stdscr, false, chcs, COLS, LINES, "");
    DrawWindow(win, *active, choices, login_signup_W_width, login_signup_W_height, "Welcome");
    refresh();

    int ch = wgetch(win);

    switch(ch) {
        case KEY_TAB:
            *active = (*active + 1) % 2;
            break;
        case KEY_BTAB:
            *active = (*active - 1 + 3) % 2;
            break;
        case KEY_DOWN:
            if(*active < 1) {
                *active = (*active + 1);
            }
            break;
        case KEY_UP:
            if(*active > 0) {
                *active = (*active - 1);
            }
            break;
        case KEY_ENTER:
            if(*active == 0) {
                screens[Login_SignUp] = false;
                screens[Login] = true;
            }
            else if(*active == 1) {
                screens[Login_SignUp] = false;
                screens[SignUp] = true;
            }
            break;
        case KEY_ESC:
            *active = -1;
            screens[Login_SignUp] = false;
            screens[Select] = true;
            break;
    }
}

void Ui::Show_SignUp(WINDOW* win, bool *active)
{
    string username, password;
    clear();
    vector<string> chcs = {};
    DrawWindow(stdscr, false, chcs, COLS, LINES, "");
    DrawSignUp(win, *active, 40, 10, username, password);
    refresh();

    int ch = wgetch(win);

    switch(ch) {
        case KEY_TAB:
            *active ^= true;
            break;
        case KEY_ENTER:
            if(*active == false) {
                curs_set(1);
                GetUsername(win, username, 19, 3);
                GetPassword(win, password, 19, 5);
                curs_set(0);
            }
            else {
                screens[SignUp] = false;
                screens[Login] = true;
            }
            break;
        case KEY_ESC:
            *active = false;
            screens[SignUp] = false;
            screens[Login_SignUp] = true;
            break;
    }
}

