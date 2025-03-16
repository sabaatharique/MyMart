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

void Ui::DrawWindow(WINDOW* win, int highlight, const vector<string>& choices, int width, int height, const string title, bool prft = false) {
    werase(win);
    BackgroundClr(win);
    box(win, 0, 0);

    // Print title
    mvwprintw(win, 0, (width - (int)title.size()) / 2, title.c_str());

    // Print items
    for(int i = 0; i < choices.size(); i++) {
        if (i == highlight) {
            wattron(win, A_REVERSE); // Highlight selection
        }
        if(!prft)
            mvwprintw(win, 2 + i * 2, 2, choices[i].c_str());
        else
            mvwprintw(win, i + 1, 1, choices[i].c_str());
        if (i == highlight) {
            wattroff(win, A_REVERSE);
        }
    }

    wrefresh(win);
}

void Ui::DrawLogin(WINDOW* win, int wrong, int width, int height) {
    werase(win);
    BackgroundClr(win);
    box(win, 0, 0);

    mvwprintw(win, 0, (width - 6) / 2, "Login");
    mvwprintw(win, 3, 2, "Enter ID      : ");
    mvwprintw(win, 5, 2, "Enter Password: ");
    if(wrong == 1) {
        mvwprintw(win, 4, 19, "Wrong id!");
    }
    if(wrong == 4) {
        mvwprintw(win, 6, 19, "Wrong id!");
    }
    if(wrong == 2) {
        mvwprintw(win, 4, 19, "Invalid input!");
    }
    if(wrong == 3) {
        mvwprintw(win, 6, 19, "Invalid input!");
    }

    wrefresh(win);
}

void Ui::Engine(Database& db, Manager &M, Cashier &C, StockClerk &SC)
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

    // Login

    string id = "", password = "", encrypted = "";
    int active = 0;
    int login_type = -1;
    int wrong = 0;
    WINDOW* win_login = newwin(login_W_height, login_W_width, (LINES - login_W_height) / 2, (COLS - login_W_width) / 2);
    keypad(win_login, TRUE);

    //  Manager

    int active_manager = -1;
    int manager_manual_W = 0;
    string table_manager;
    WINDOW* win_manager_manual = newwin(manual_W_height, manual_W_width, (LINES - manual_W_height) / 2, (COLS - manual_W_width) / 2);
    WINDOW* win_prft = newwin(3, 10, LINES - 4, COLS - 11);
    keypad(win_manager_manual, TRUE);
    keypad(win_prft, TRUE);
    vector<string> manual_manager = {};
    vector<string> manager_functions = {
        "1. AddNewProducts",
        "2. DeleteProduct",
        "3. AddNewEmployee",
        "4. RemoveEmployee",
        "5. SetSalary",
        "6. showFeedback",
        "7. Logout"
    };

    //  Cashier

    int active_cashier = -1;
    bool cashier_manual_W = true;
    WINDOW* win_cashier_manual = newwin(manual_W_height, manual_W_width, (LINES - manual_W_height) / 2, (COLS - manual_W_width) / 2);
    keypad(win_cashier_manual, TRUE);
    vector<string> manual_cashier = {};
    vector<string> cashier_functions = {
        "1. AddNewProducts",
        "2. DeleteProduct",
        "3. AddNewEmployee",
        "4. RemoveEmployee",
        "5. SetSalary",
        "6. showFeedback",
    };

    //  Stock_Clerk

    int active_Stock_Clerk = -1;
    int Stock_Clerk_manual_W = 0;
    string table_stock_clerk;
    WINDOW* win_Stock_Clerk_manual = newwin(manual_W_height, manual_W_width, (LINES - manual_W_height) / 2, (COLS - manual_W_width) / 2);
    keypad(win_Stock_Clerk_manual, TRUE);
    vector<string> manual_Stock_Clerk = {};
    vector<string> Stock_Clerk_functions = {
        "1. Expired Products",
        "2. Out Of Stock Products",
        "3. All Products",
        "4. Logout"
    };

    while(true) {
        BackgroundClr(stdscr);
        if(GetScreen(Main)) Show_Main();
        if(GetScreen(Select)) Show_Select(win_select, &active_select, &login_type, choices_select);
        if(GetScreen(Login)) Show_Login(db, M, win_login, &active, &wrong, &login_type, id, password, encrypted);
        if(GetScreen(Manager_S)) Show_Manager(db, M, win_manager_manual, win_prft, &active_manager, &manager_manual_W, table_manager, manual_manager, manager_functions);
        if(GetScreen(Cashier_S)) Show_Cashier(db, C, win_cashier_manual, &active_cashier, &cashier_manual_W, manual_cashier, cashier_functions);
        if(GetScreen(Stock_Clerk_S)) Show_Stock_Clerk(db, SC, win_Stock_Clerk_manual, &active_Stock_Clerk, &Stock_Clerk_manual_W, table_stock_clerk, manual_Stock_Clerk, Stock_Clerk_functions);
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
    mvwprintw(stdscr, MY_MART_BUTTON_Y, MY_MART_BUTTON_X, " __  __      __  __          _");
    mvwprintw(stdscr, MY_MART_BUTTON_Y+1, MY_MART_BUTTON_X, "|  \\/  |_  _|  \\/  |__ _ _ _| |_");
    mvwprintw(stdscr, MY_MART_BUTTON_Y+2, MY_MART_BUTTON_X, "| |\\/| | || | |\\/| / _` | '_|  _|");
    mvwprintw(stdscr, MY_MART_BUTTON_Y+3, MY_MART_BUTTON_X, "|_|  |_|\\_, |_|  |_\\__,_|_|  \\__|");
    mvwprintw(stdscr, MY_MART_BUTTON_Y+4, MY_MART_BUTTON_X, "        |__/");
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

void Ui::Show_Select(WINDOW* win, int *active, int *login_type, const vector<string>& choices)
{
    int N = choices.size();
    clear();
    mvhline(0, 1, ACS_HLINE, COLS-2);
    attron(A_REVERSE);
    mvprintw(0, (COLS - 6) / 2, "MyMart");
    attroff(A_REVERSE);
    refresh();
    //mvprintw(4, 1, "Enter your employee type");

    DrawWindow(win, *active, choices, select_W_width, select_W_height, "SELECT");
    refresh();

    int ch = wgetch(win);

    switch(ch) {
        case '1':
            screens[Select] = false;
            screens[Login] = true;
            *login_type = 1;
            break;
        case '2':
            screens[Select] = false;
            screens[Login] = true;
            *login_type = 2;
            break;
        case '3':
            screens[Select] = false;
            screens[Login] = true;
            *login_type = 3;
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
            if(*active == 0) {
                screens[Select] = false;
                screens[Login] = true;
                *login_type = 1;
            }
            else if(*active == 1) {
                screens[Select] = false;
                screens[Login] = true;
                *login_type = 2;
            }
            else if(*active == 2) {
                screens[Select] = false;
                screens[Login] = true;
                *login_type = 3;
            }
            break;
    }
}

// Function to hash a password using bcrypt (SHA-256)
string Ui::hashPassword(const string &password) {
    BCRYPT_ALG_HANDLE hAlgorithm;
    BCRYPT_HASH_HANDLE hHash;
    NTSTATUS status;
    unsigned char hash[HASH_SIZE];  // Using unsigned char instead of BYTE
    string hashHex;

    // Open bcrypt algorithm provider
    status = BCryptOpenAlgorithmProvider(&hAlgorithm, HASH_ALGORITHM, NULL, 0);
    if (status != 0) {
        cerr << "Error: Unable to open algorithm provider (0x" << hex << status << ")\n";
        return "";
    }

    // Create hash object
    status = BCryptCreateHash(hAlgorithm, &hHash, NULL, 0, NULL, 0, 0);
    if (status != 0) {
        cerr << "Error: Unable to create hash (0x" << hex << status << ")\n";
        BCryptCloseAlgorithmProvider(hAlgorithm, 0);
        return "";
    }

    // Hash the password
    status = BCryptHashData(hHash, (unsigned char*)password.c_str(), (ULONG)password.length(), 0);
    if (status != 0) {
        cerr << "Error: Unable to hash data (0x" << hex << status << ")\n";
        BCryptDestroyHash(hHash);
        BCryptCloseAlgorithmProvider(hAlgorithm, 0);
        return "";
    }

    // Get the final hash value
    status = BCryptFinishHash(hHash, hash, HASH_SIZE, 0);
    if (status != 0) {
        cerr << "Error: Unable to finish hash (0x" << hex << status << ")\n";
        BCryptDestroyHash(hHash);
        BCryptCloseAlgorithmProvider(hAlgorithm, 0);
        return "";
    }

    // Convert hash bytes to hex string
    for (int i = 0; i < HASH_SIZE; i++) {
        char buffer[3];
        snprintf(buffer, sizeof(buffer), "%02x", hash[i]);
        hashHex += buffer;
    }

    // Cleanup
    BCryptDestroyHash(hHash);
    BCryptCloseAlgorithmProvider(hAlgorithm, 0);

    return hashHex;
}

void Ui::Show_Login(Database& db, Manager &M, WINDOW* win, int *active, int *wrong, int *login_type, string &id, string &password, string &encrypted)
{
    clear();
    mvhline(0, 1, ACS_HLINE, COLS-2);
    attron(A_REVERSE);
    mvprintw(0, (COLS - 6) / 2, "MyMart");
    attroff(A_REVERSE);
    refresh();

    DrawLogin(win, *wrong, 40, 20);
    if(*active >= 1) mvwprintw(win, 3, 19, id.c_str());
    if(*active >= 2) mvwprintw(win, 5, 19, encrypted.c_str());
    refresh();

    int ch = wgetch(win);

    switch(ch) {
        case KEY_ENTER:
            if(*active == 0) {
                *active = 1; // id write mode enabled
                *wrong = 0; // no warning
                wmove(win, 3, 19);
                curs_set(1);
            }
            else if(*active == 1) {
                //curs_set(0);
                if(*login_type == 1 && M.IsEmployeeIdValid(db, id, *login_type)) {
                    *active = 2;
                    *wrong = 0;
                    wmove(win, 5, 19);
                    curs_set(1);
                }
                else if(*login_type == 2 && M.IsEmployeeIdValid(db, id, *login_type)) {
                    *active = 2;
                    *wrong = 0;
                    wmove(win, 5, 19);
                    curs_set(1);
                }
                else if(*login_type == 3 && M.IsEmployeeIdValid(db, id, *login_type)) {
                    *active = 2;
                    *wrong = 0;
                    wmove(win, 5, 19);
                    curs_set(1);
                }
                else {
                    id = "";
                    *wrong = 1; // wrong id
                    *active = 1; // id write mode disabled
                    wmove(win, 3, 19);
                    curs_set(1);
                    break;
                }
            }
            else if(*active == 2) {
                curs_set(0);
                if(*login_type == 1 && M.IsEmployeePassValid(db, id, password, *login_type)) {
                    *wrong = 0;
                    *active = 0;
                    *login_type = -1;
                    id = "";
                    password = "";
                    encrypted = "";
                    screens[Login] = false;
                    screens[Manager_S] = true;
                }
                else if(*login_type == 2 && M.IsEmployeePassValid(db, id, password, *login_type)) {
                    *wrong = 0;
                    *active = 0;
                    *login_type = -1;
                    id = "";
                    password = "";
                    encrypted = "";
                    screens[Login] = false;
                    screens[Cashier_S] = true;
                }
                else if(*login_type == 3 && M.IsEmployeePassValid(db, id, password, *login_type)) {
                    *wrong = 0;
                    *active = 0;
                    *login_type = -1;
                    id = "";
                    password = "";
                    encrypted = "";
                    screens[Login] = false;
                    screens[Stock_Clerk_S] = true;
                }
                else {
                    password = "";
                    encrypted = "";
                    *wrong = 4; // wrong id
                    *active = 2; // id write mode disabled
                    wmove(win, 5, 19);
                    curs_set(1);
                    break;
                }
            }
            //password = hashPassword(password);
            break;
        case KEY_ESC:
            if(*active == 0) {
                screens[Login] = false;
                screens[Select] = true;
            }
            break;
        case KEY_BACKSPACE:
            if(*active == 1) {
                if (!id.empty()) {
                    id.pop_back();
                    int x, y;
                    getyx(win, y, x);
                    if(x > 0) {
                        mvwaddch(win, y, x - 1, ' ');
                        wmove(win, y, x - 1);
                    }
                }
            }
            else if(*active == 2) {
                if (!password.empty()) {
                    password.pop_back();
                    encrypted.pop_back();
                    int x, y;
                    getyx(win, y, x);
                    if(x > 0) {
                        mvwaddch(win, y, x - 1, ' ');
                        wmove(win, y, x - 1);
                    }
                }
            }
            break;
        default:
            if(*active == 1) {
                if(ch >= '0' && ch <= '9') {
                    *wrong = 0;
                    id += ch;
                }
                else {
                    *wrong = 2;
                }
            }
            else if(*active == 2) {
                if(ch != ' ') {
                    *wrong = 0;
                    password += ch;
                    encrypted += '*';
                }
                else {
                    *wrong = 3;
                }
            }
            break;
    }
}

void Ui::Show_Manager(Database& db, Manager& M, WINDOW* win, WINDOW* prft_win, int *active, int *manual_W, string &table, const vector<string>& manual, const vector<string>& functions)
{
    int N = functions.size();
    clear();
    mvhline(0, 1, ACS_HLINE, COLS-2);
    attron(A_REVERSE);
    mvprintw(0, (COLS - 6) / 2, "MyMart");
    attroff(A_REVERSE);
    refresh();

    vector<string> prft;
    prft.push_back(to_string(M.GetProfit()));

    DrawWindow(prft_win, false, prft, 4, 1, "", true);

    if(*manual_W == 0) DrawWindow(win, -1, manual, manual_W_width, manual_W_height, "Manual");

    if(*manual_W == 8) {
        mvwprintw(stdscr, LINES/2, (COLS - 22) / 2, "press enter to return!");
        int ch = getch();
        if(ch == KEY_ENTER) {
            *active = -1;
            *manual_W = 1;
        }
    }

    if(*manual_W == 1) {
        wresize(win, manager_W_height, manager_W_width);
        mvwin(win, (LINES - manager_W_height) / 2, (COLS - manager_W_width) / 2);
        DrawWindow(win, *active, functions, manager_W_width, manager_W_height, "Manager");
    }

    if(*manual_W == 9) {
        int trash;
        db.displayTable("SELECT * FROM " + table + ";", &trash);
        int ch = getch();
        if(ch == KEY_ENTER) {
            *manual_W = 8;
        }
    }

    if(*manual_W == 2) {
        if(M.AddNewProducts(db)) {
            table = "PRODUCTS";
            *manual_W = 9;
        }
    }

    if(*manual_W == 3) {
        int line;
        if(db.displayTable("SELECT * FROM PRODUCTS;", &line) && M.DeleteProduct(db, line)) {
            table = "PRODUCTS";
            *manual_W = 9;
        }
    }

    if(*manual_W == 4) {
        if(M.AddNewEmployee(db)) {
            table = "EMPLOYEES";
            *manual_W = 9;
        }
    }

    if(*manual_W == 5) {
        int line;
        if(db.displayTable("SELECT * FROM EMPLOYEES;", &line) && M.RemoveEmployee(db, line)) {
            table = "EMPLOYEES";
            *manual_W = 9;
        }
    }

    if(*manual_W == 6) {
        int line;
        if(db.displayTable("SELECT * FROM EMPLOYEES;", &line) && M.SetSalary(db, line)) {
            table = "EMPLOYEES";
            *manual_W = 9;
        }
    }

    if(*manual_W == 7) {
        if(M.showFeedback()) {
            int ch = getch();
            if(ch == KEY_ENTER) {
                *manual_W = 8;
            }
        }
    }


    if(*manual_W == 0 || *manual_W == 1) {
        int ch = wgetch(win);

        switch(ch) {
            case '1':
                if(*manual_W == 1) {
                    *manual_W = 2;
                }
                break;
            case '2':
                if(*manual_W == 1) {
                    *manual_W = 3;
                }
                break;
            case '3':
                if(*manual_W == 1) {
                    *manual_W = 4;
                }
                break;
            case '4':
                if(*manual_W == 1) {
                    *manual_W = 5;
                }
                break;
            case '5':
                if(*manual_W == 1) {
                    *manual_W = 6;
                }
                break;
            case '6':
                if(*manual_W == 1) {
                    *manual_W = 7;
                }
                break;
            case '7':
                if(*manual_W == 1) {
                    *active = -1;
                    *manual_W = 1;
                    table = "";
                    screens[Manager_S] = false;
                    screens[Select] = true;
                }
                break;
            case KEY_ENTER:
                if(*manual_W == 0) {
                    *manual_W = 1;
                }
                else if(*manual_W == 1 && *active == 0) {
                    *manual_W = 2;
                }
                else if(*manual_W == 1 && *active == 1) {
                    *manual_W = 3;
                }
                else if(*manual_W == 1 && *active == 2) {
                    *manual_W = 4;
                }
                else if(*manual_W == 1 && *active == 3) {
                    *manual_W = 5;
                }
                else if(*manual_W == 1 && *active == 4) {
                    *manual_W = 6;
                }
                else if(*manual_W == 1 && *active == 5) {
                    *manual_W = 7;
                }
                else if(*manual_W == 1 && *active == 6) {
                    *active = -1;
                    *manual_W = 1;
                    table = "";
                    screens[Manager_S] = false;
                    screens[Select] = true;
                }
                break;
            case KEY_UP:
                if(*manual_W == 1) {
                    if(*active > 0) {
                        *active = (*active - 1);
                    }
                }
                break;
            case KEY_DOWN:
                if(*manual_W == 1) {
                    if(*active < N-1) {
                        *active = (*active + 1);
                    }
                }
                break;
            case KEY_TAB:
                if(*manual_W == 1) {
                    *active = (*active + 1) % N;
                }
                break;
            case KEY_BTAB:
                if(*manual_W == 1) {
                    *active = (*active - 1 + N) % N;
                }
                break;
        }
    }


    refresh();
}

void Ui::Show_Cashier(Database& db, Cashier& C, WINDOW* win, int *active, bool *manual_W, const vector<string>& manual, const vector<string>& functions)
{
    int N = functions.size();
    clear();
    mvhline(0, 1, ACS_HLINE, COLS-2);
    attron(A_REVERSE);
    mvprintw(0, (COLS - 6) / 2, "MyMart");
    attroff(A_REVERSE);
    refresh();

    if(*manual_W) DrawWindow(win, -1, manual, manual_W_width, manual_W_height, "Manual");

    if(!*manual_W) {
        wresize(win, manager_W_height, manager_W_width);
        mvwin(win, (LINES - manager_W_height) / 2, (COLS - manager_W_width) / 2);
        DrawWindow(win, *active, functions, manager_W_width, manager_W_height, "Manager");
    }

    refresh();

    int ch = wgetch(win);

    switch(ch) {
        case KEY_ENTER:
            if(*manual_W) {
                *manual_W = false;
            }
            break;
        case KEY_UP:
            if(!*manual_W) {
                if(*active > 0) {
                    *active = (*active - 1);
                }
            }
            break;
        case KEY_DOWN:
            if(!*manual_W) {
                if(*active < N-1) {
                    *active = (*active + 1);
                }
            }
            break;
    }
}

void Ui::Show_Stock_Clerk(Database& db, StockClerk& SC, WINDOW* win, int *active, int *manual_W, string &table, const vector<string>& manual, const vector<string>& functions)
{
    int N = functions.size();
    clear();
    mvhline(0, 1, ACS_HLINE, COLS-2);
    attron(A_REVERSE);
    mvprintw(0, (COLS - 6) / 2, "MyMart");
    attroff(A_REVERSE);
    refresh();

    if(*manual_W == 0) DrawWindow(win, -1, manual, manual_W_width, manual_W_height, "Manual");

    if(*manual_W == 8) {
        mvwprintw(stdscr, LINES/2, (COLS - 22) / 2, "press enter to return!");
        int ch = getch();
        if(ch == KEY_ENTER) {
            *active = -1;
            *manual_W = 1;
        }
    }

    if(*manual_W == 1) {
        wresize(win, stock_clerk_W_height, stock_clerk_W_width);
        mvwin(win, (LINES - stock_clerk_W_height) / 2, (COLS - stock_clerk_W_width) / 2);
        DrawWindow(win, *active, functions, stock_clerk_W_width, stock_clerk_W_height, "Stock Clerk");
    }

    if(*manual_W == 9) {
        int trash;
        db.displayTable("SELECT * FROM " + table + ";", &trash);
        int ch = getch();
        if(ch == KEY_ENTER) {
            *manual_W = 8;
        }
    }

    if(*manual_W == 2) {
        if(SC.ShowExpiredProducts(db)) {
            table = "PRODUCTS WHERE EXPIRY_DATE < DATE('now')";
            *manual_W = 9;
        }
        else {
            clear();
            mvhline(0, 1, ACS_HLINE, COLS-2);
            attron(A_REVERSE);
            mvprintw(0, (COLS - 6) / 2, "MyMart");
            attroff(A_REVERSE);
            refresh();
            string hold = "No expired products! press enter to continue";
            mvprintw(LINES / 2, (COLS - (int)hold.size()) / 2, hold.c_str());
            int ch = getch();
            if(ch == KEY_ENTER) {
                *manual_W = 8;
            }
        }
    }

    if(*manual_W == 3) {
        if(SC.ShowOutOfStockProducts(db)) {
            table = "PRODUCTS WHERE IN_STOCK = 0";
            *manual_W = 9;
        }
        else {
            clear();
            mvhline(0, 1, ACS_HLINE, COLS-2);
            attron(A_REVERSE);
            mvprintw(0, (COLS - 6) / 2, "MyMart");
            attroff(A_REVERSE);
            refresh();
            string hold = "No out of stock products! press enter to continue";
            mvprintw(LINES / 2, (COLS - (int)hold.size()) / 2, hold.c_str());
            int ch = getch();
            if(ch == KEY_ENTER) {
                *manual_W = 8;
            }
        }
    }

    if(*manual_W == 4) {
        if(SC.ShowAllProducts(db)) {
            *manual_W = 8;
        }
    }


    if(*manual_W == 0 || *manual_W == 1) {
        int ch = wgetch(win);

        switch(ch) {
            case '1':
                if(*manual_W == 1) {
                    *manual_W = 2;
                }
                break;
            case '2':
                if(*manual_W == 1) {
                    *manual_W = 3;
                }
                break;
            case '3':
                if(*manual_W == 1) {
                    *manual_W = 4;
                }
                break;
            case '4':
                if(*manual_W == 1) {
                    *active = -1;
                    *manual_W = 1;
                    table = "";
                    screens[Stock_Clerk_S] = false;
                    screens[Select] = true;
                }
                break;
            case KEY_ENTER:
                if(*manual_W == 0) {
                    *manual_W = 1;
                }
                else if(*manual_W == 1 && *active == 0) {
                    *manual_W = 2;
                }
                else if(*manual_W == 1 && *active == 1) {
                    *manual_W = 3;
                }
                else if(*manual_W == 1 && *active == 2) {
                    *manual_W = 4;
                }
                else if(*manual_W == 1 && *active == 3) {
                    *active = -1;
                    *manual_W = 1;
                    table = "";
                    screens[Stock_Clerk_S] = false;
                    screens[Select] = true;
                }
                break;
            case KEY_UP:
                if(*manual_W == 1) {
                    if(*active > 0) {
                        *active = (*active - 1);
                    }
                }
                break;
            case KEY_DOWN:
                if(*manual_W == 1) {
                    if(*active < N-1) {
                        *active = (*active + 1);
                    }
                }
                break;
            case KEY_TAB:
                if(*manual_W == 1) {
                    *active = (*active + 1) % N;
                }
                break;
            case KEY_BTAB:
                if(*manual_W == 1) {
                    *active = (*active - 1 + N) % N;
                }
                break;
        }
    }


    refresh();
}


