#ifndef UI_H
#define UI_H


#include <ntdef.h>
#include <bcrypt.h>
#include <curses.h>
#include <vector>
#include <cstring>
#include <string>
#include <manager.h>
#include <cashier.h>
#include <stockclerk.h>
#include <iostream>

#pragma comment(lib, "bcrypt.lib")  // Link bcrypt library

#define HASH_ALGORITHM BCRYPT_SHA256_ALGORITHM  // Use SHA-256
#define HASH_SIZE 32  // 32-byte hash output

using namespace std;

// Colors
#define FG 7
#define BG 29
// sizes
#define tot_screen 6
#define select_W_width 30
#define select_W_height 9
#define login_W_width 40
#define login_W_height 10
#define manual_W_width 80
#define manual_W_height 28
#define manager_W_width 40
#define manager_W_height 17
#define cashier_W_width 40
#define cashier_W_height 15
#define stock_clerk_W_width 40
#define stock_clerk_W_height 11
// Button positions
#define MY_MART_BUTTON_X (COLS - 33)/2
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
    Login,
    Manager_S,
    Cashier_S,
    Stock_Clerk_S
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
        void DrawWindow(WINDOW* win, int highlight, const vector<string>& choices, int width, int height, const string title, bool prft);
        void DrawLogin(WINDOW* win, int wrong, int width, int height);

        void Engine(Database& db, Manager &M, Cashier &C, StockClerk &SC);
        void Show_Main();
        void Show_Select(WINDOW* win, int *active, int *login_type, const vector<string>& choices);
        string hashPassword(const string &password);
        void Show_Login(Database& db, Manager &M, WINDOW* win, int *active, int *wrong, int *login_type, string &id, string &password, string &encrypted);
        void Show_Manager(Database& db, Manager &M, WINDOW* win, WINDOW* prft_win, int *active, int *manual_W, string &table, const vector<string>& manual, const vector<string>& functions);
        void Show_Cashier(Database& db, Cashier& C, WINDOW* win, int *active, bool *manual_W, const vector<string>& manual, const vector<string>& functions);
        void Show_Stock_Clerk(Database& db, StockClerk& SC, WINDOW* win, int *active, int *manual_W, string &table, const vector<string>& manual, const vector<string>& functions);

    protected:

    private:
        bool screens[tot_screen];
};

#endif // UI_H
