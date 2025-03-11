#ifndef UI_H
#define UI_H

#include <curses.h>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

// Colors
#define FG 0
#define BG 248
// Button positions
#define tot_screen 5
#define select_W_width 30
#define select_W_height 9
#define login_signup_W_width 30
#define login_signup_W_height 6
#define MY_MART_BUTTON_X (COLS - 43)/2
#define MY_MART_BUTTON_Y (LINES-5)/2
#define Press_Enter_X (COLS - 24)/2
#define Press_Enter_Y (LINES-5)/2+7
// Keys
#define KEY_TAB '\t'
#define KEY_ENTER '\n'
#define KEY_BACKSPACE 8
#define KEY_ESC 27

enum Screen {
    Main,
    Select,
    Login_SignUp,
    Login,
    SignUp
};

class Ui
{
    public:
        Ui();
        ~Ui();

        bool GetScreen(const int val);
        void BackgroundClr(WINDOW* win, short fg, short bg);
        bool IsInBox(const int val_x, const int val_y, const int x, const int y, const int length);
        void DrawBox(WINDOW* win, const int x, const int y, string line, const bool active);
        void DrawWindow(WINDOW* win, int highlight, const vector<string>& choices, int width, int height, const string title, short fg, short bg, int line_ch);
        void GetUsername(WINDOW* win, string &username, int startX, int startY);
        void GetPassword(WINDOW* win, string &password, int startX, int startY);
        void DrawSignUp(WINDOW* win, bool highlight, int width, int height, string &username, string &password);

        void Engine();
        void Show_Main();
        void Show_Select(WINDOW* win, int *active, const vector<string>& choices);
        void Show_Login_SignUp(WINDOW* win, int *active, const vector<string>& choices);
        void Show_SignUp(WINDOW* win, bool *active);

    protected:

    private:
        bool screens[tot_screen];
};

#endif // UI_H
