#include "stockclerk.h"
#include "perishableproducts.h"
#include "Date.h"

StockClerk::StockClerk(int n, string x, double s) : Employee(n, x, "STOCK CLERK", s) {}
StockClerk::StockClerk() {}
StockClerk::~StockClerk() {}

string StockClerk::GetEmployeeType()
{
    return EmployeeType;
}

bool StockClerk::CheckExpiry(PerishableProducts* p, Date today)
{
    return *p < today;
}

void StockClerk::getinput(string &result, int Y, int X)
{
    clear();
    mvwprintw(stdscr, Y, X, result.c_str());
    refresh();
    //int ch;
    while(true) {
        int ch = getch();
        //if(ch == '\n') break;
        curs_set(1);
        wmove(stdscr, Y, X);
        if(ch == 8) {
            if (!result.empty()) {
                result.pop_back();
                int x, y;
                getyx(stdscr, y, x);
                if(x > 0) {
                    mvaddch(y, x, ' ');
                    move(y, x - 1);
                }
            }
        }
        else
            result += ch;
    }
}


bool StockClerk::UpdateExpiryDateByID(Database& db, int ID, string Exp)
{
    string expDate = "'" + Exp + "'";
    string query = "UPDATE PRODUCTS SET EXPIRY_DATE = " + expDate + " WHERE ID = " + to_string(ID) + ";";

    return db.executeQuery(query);
}


bool StockClerk::UpdateExpiryDateByID(Database& db, PerishableProducts &Exp, int ID)
{
    string expDate = "'" + Exp.GetExpiryDate().ToString() + "'";
    string query = "UPDATE PRODUCTS SET EXPIRY_DATE = " + expDate + " WHERE ID = " + to_string(ID) + ";";


    //mvwprintw(stdscr, 25, 10, query.c_str());

    return db.executeQuery(query);
}

bool StockClerk::UpdateStockByID(Database& db, int ID, double amount)
{
    string query = "UPDATE PRODUCTS SET IN_STOCK = " + to_string(amount) + " WHERE ID = " + to_string(ID) + ";";

    return db.executeQuery(query);
}

bool StockClerk::ShowExpiredProducts(Database& db)
{
    int start_line;
    if(!db.displayTable("SELECT * FROM PRODUCTS WHERE EXPIRY_DATE < DATE('now');", &start_line)) {
        return false;
    }

    string hold1 = "", hold2 = "", hold3 = "";
    int productID;
    hold1 = "Enter product ID to update: ";
    mvwprintw(stdscr, start_line + 1, 2, hold1.c_str());
    while(true) {
        curs_set(1);
        echo();

        move(start_line + 1, 2 + hold1.size());
        clrtoeol();
        char temp[200];
        getnstr(temp, sizeof(temp) - 1);
        productID = stoi(string(temp));

        if (productID == -1) {
            curs_set(0);
            noecho();
            return true;
        }

        if(Product::IsProductInTable(db, productID, Expired)) {
            float amount;
            hold2 = "Enter new stock amount: ";
            mvwprintw(stdscr, start_line + 3, 2, hold2.c_str());

            string pID = to_string(productID);

            move(start_line + 3, 2 + hold2.size() + 1);
            clrtoeol();
            getnstr(temp, sizeof(temp) - 1);
            amount = stof(string(temp));
            while(true) {
                if(amount <= 0) {
                    hold2 = "Input invalid, try again: ";
                    mvwprintw(stdscr, start_line + 3, 2, hold2.c_str());
                    move(start_line + 3, 2 + hold2.size());
                    clrtoeol();
                    getnstr(temp, sizeof(temp) - 1);
                    amount = stof(string(temp));
                }
                else
                    break;
            }
        // first digit 1 indicates regular product, 21 indicates perishable but bought in kg and 22 indicates perishable but bought in unit
            if(pID[0] == '1' || (pID[0] == '2' && pID[1] == '2')) {
                while(1){
                    if(floor(amount) != amount)
                    {
                        hold2 = "Input invalid, try again: ";
                        mvwprintw(stdscr, start_line + 3, 2, hold2.c_str());
                        move(start_line + 3, 2 + hold2.size());
                        clrtoeol();
                        getnstr(temp, sizeof(temp) - 1);
                        amount = stof(string(temp));
                    }
                    else
                        break;
                }
            }
            double cur_profit = Manager::GetProfit();
            double loss = GetExpiredStockAmount(db,productID);
            Manager::SetProfit(cur_profit-loss);
            UpdateStockByID(db, productID, amount);

            bool notfirst = false;
            Date dt, today;
            today.GetTodaysDate();
            PerishableProducts Exp;
            do{
                hold3 = "Enter new expiry date : ";
                if(notfirst)
                    mvwprintw(stdscr, start_line + 4, 2, "Invalid Expiry Date! ");
                mvwprintw(stdscr, start_line + 5, 2, hold3.c_str());
                move(start_line + 5, 2 + hold3.size());
                clrtoeol();
                getnstr(temp, sizeof(temp) - 1);
                string date(temp);
                dt.ToDate(date.c_str());
                Exp.SetExpiryDate(dt);
            } while(notfirst = CheckExpiry(&Exp, today));

            UpdateExpiryDateByID(db, Exp, productID);
            move(start_line + 5, 2);
            clrtoeol();
            move(start_line + 4, 2);
            clrtoeol();
            move(start_line + 3, 2);
            clrtoeol();
            move(start_line + 1, 2);
            clrtoeol();
            if(!db.displayTable("SELECT * FROM PRODUCTS WHERE EXPIRY_DATE < DATE('now');", &start_line)) return false;
            hold1 = "Enter product ID to update or -1 finish: ";
            mvwprintw(stdscr, start_line + 1, 2, hold1.c_str());
        }
        else {
            if(!db.displayTable("SELECT * FROM PRODUCTS WHERE EXPIRY_DATE < DATE('now');", &start_line)) return false;
            hold1 = "Product could not be found, try again: ";
            mvwprintw(stdscr, start_line + 1, 2, hold1.c_str());
        }
    }
    curs_set(0);
    noecho();
}

bool StockClerk::ShowOutOfStockProducts(Database& db)
{
    int start_line;
    if(!db.displayTable("SELECT * FROM PRODUCTS WHERE IN_STOCK = 0;", &start_line)) {
        return false;
    }

    string hold1 = "", hold2 = "";
    int productID;
    hold1 = "Enter product ID to update: ";
    mvwprintw(stdscr, start_line + 1, 2, hold1.c_str());

    while(true) {
        curs_set(1);
        echo();

        move(start_line + 1, 2 + hold1.size());
        clrtoeol();
        char temp[200];
        getnstr(temp, sizeof(temp) - 1);
        productID = stoi(string(temp));

        if (productID == -1) {
            curs_set(0);
            noecho();
            return true;
        }

        if(Product::IsProductInTable(db, productID, OutOfStock)) {
            float amount;
            hold2 = "Enter new stock amount: ";
            mvwprintw(stdscr, start_line + 3, 2, hold2.c_str());

            string pID = to_string(productID);

            move(start_line + 3, 2 + hold2.size() + 1);
            clrtoeol();
            getnstr(temp, sizeof(temp) - 1);
            amount = stof(string(temp));

            while(true) {
                if(amount <= 0) {
                    hold2 = "Input invalid, try again: ";
                    mvwprintw(stdscr, start_line + 3, 2, hold2.c_str());
                    move(start_line + 3, 2 + hold2.size());
                    clrtoeol();
                    getnstr(temp, sizeof(temp) - 1);
                    amount = stof(string(temp));
                }
                else
                    break;
            }

        // first digit 1 indicates regular product, 21 indicates perishable but bought in kg and 22 indicates perishable but bought in unit
            if(pID[0] == '1' || (pID[0] == '2' && pID[1] == '2')) {
                while(1){
                    if(floor(amount) != amount)
                    {
                        hold2 = "Input invalid, try again: ";
                        mvwprintw(stdscr, start_line + 3, 2, hold2.c_str());
                        move(start_line + 3, 2 + hold2.size());
                        clrtoeol();
                        getnstr(temp, sizeof(temp) - 1);
                        amount = stof(string(temp));
                    }
                    else
                        break;
                }
            }
            UpdateStockByID(db,productID,amount);

            move(start_line + 3, 2);
            clrtoeol();
            move(start_line + 1, 2);
            clrtoeol();
            if(!db.displayTable("SELECT * FROM PRODUCTS WHERE IN_STOCK = 0;", &start_line)) return false;
            hold1 = "Enter product ID to update or -1 to finish: ";
            mvwprintw(stdscr, start_line + 1, 2, hold1.c_str());
        }
        else {
            if(!db.displayTable("SELECT * FROM PRODUCTS WHERE IN_STOCK = 0;", &start_line)) return false;
            hold1 = "Product could not be found, try again: ";
            mvwprintw(stdscr, start_line + 1, 2, hold1.c_str());
        }
    }
    curs_set(0);
    noecho();
}

bool StockClerk::ShowAllProducts(Database& db)
{
    int start_line;
    if(!db.displayTable("SELECT * FROM PRODUCTS;", &start_line)) return false;

    string hold = "press enter to continue";
    mvprintw(start_line + 1, (COLS - (int)hold.size()) / 2, hold.c_str());
    int ch = getch();
    if(ch == '\n') {
        return true;
    }
}

double StockClerk::GetExpiredStockAmount(Database& db, int ID)
{
    double loss;
    string query = "SELECT IN_STOCK*BUYING_COST FROM PRODUCTS WHERE ID = " + to_string(ID) + ";";
    sqlite3_stmt* stmt = db.fetchQuery(query);
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        loss = sqlite3_column_double(stmt, 0);
    }
    sqlite3_finalize(stmt);
    return loss;
}


