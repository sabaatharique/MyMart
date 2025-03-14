#include "Manager.h"

using namespace std;

double Manager::profit = 0;
double Manager::totalBalance = 1000000;

Manager::Manager(int n, string x, double s) : Employee(n, x, "MANAGER", s) {}

Manager::Manager(){}

Manager::~Manager(){}

string Manager::GetEmployeeType()
{
    return EmployeeType;
}

double Manager::GetProfit()
{
    return profit;
}

double Manager::GetTotalBalance()
{
    return totalBalance;
}

void Manager::SetProfit(const double p)
{
    profit = p;
}

void Manager::SetTotalBalance(const double b)
{
    totalBalance = b;
}

bool Manager::SetSalary(Database& db)
{
    int emp_salary, choice;
    string emp_type;
    bool first = true;

    cout << "Enter employee type:\n1.Cashier\n2.Stock Clerk\n " << endl;
    do{
        if(!first)
            cout << "Invalid input , try again." << endl;
        cin >> choice;
        first = false;

    } while(choice != 1 || choice != 2);

    if(choice == 1)
        emp_type = "CASHIER";
    else if(choice == 2)
        emp_type = "STOCK CLERK";

    cout << "Enter new salary : " << endl;
    first = true;
    do{
        if(!first)
            cout << "Invalid input , try again." << endl;
        cin >> emp_salary;
        first = false;

    } while(emp_salary <= 0);

    string query = "UPDATE EMPLOYEES SET SALARY = " + to_string(emp_salary) + " WHERE TYPE = " + emp_type + ";";

    return db.executeQuery(query);
}

bool Manager::IsEmployeeIdValid(Database& db, string& id, int login_type)
{
    string query = "SELECT ID FROM EMPLOYEES WHERE ID = " + id + ";";
    sqlite3_stmt* stmt = db.fetchQuery(query);
    if (!(sqlite3_step(stmt) == SQLITE_ROW)) {
        sqlite3_finalize(stmt);
        return false;
    }
    int first_digit = to_string(sqlite3_column_int(stmt, 0))[0] - '0';
    if(first_digit != login_type) {
        return false;
    }
    sqlite3_finalize(stmt);
    return true;
}

bool Manager::IsEmployeePassValid(Database& db, string& id, string& password, int login_type)
{
    string query = "SELECT PASSWORD FROM EMPLOYEES WHERE ID = " + id + ";";
    sqlite3_stmt* stmt = db.fetchQuery(query);
    if (!(sqlite3_step(stmt) == SQLITE_ROW)) {
        sqlite3_finalize(stmt);
        return false;
    }
    string pass = string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0)));
    if(pass != password) {
        return false;
    }
    sqlite3_finalize(stmt);
    return true;
}


bool Manager::AddNewProducts(Database& db)
{
    clear();

    Product* prdct;
    int type,p_id;
    string p_name;
    const char* date;
    double sell_price, buying_cost,stock;

    mvwprintw(stdscr, 1, 2, "Enter Product Type: ");
    mvwprintw(stdscr, 2, 2, "1. Non-Perishable");
    mvwprintw(stdscr, 3, 2, "2. Perishable");
    //wmove(stdscr, 1, 21);
    //curs_set(1);

    //echo();
    type = getch();

    //cout << "Enter Product Type: \n1.Non-Perishable\n2.Perishable\n" << endl;
//    cin >> type;
    if(type == '2')
    {
        mvwprintw(stdscr, 5, 2, "Enter PerishableProduct Type: ");
        mvwprintw(stdscr, 6, 2, "1. Sold in units");
        mvwprintw(stdscr, 7, 2, "2. Sold in kilograms");
        int choice;
        choice = getch();
        //cin >> choice;
        if(choice == '1')
        {
            string query = "SELECT ID FROM PRODUCTS WHERE ID LIKE '21%' ORDER BY ID DESC LIMIT 1";
            sqlite3_stmt* stmt = db.fetchQuery(query);
            if (sqlite3_step(stmt) == SQLITE_ROW) {
                p_id = sqlite3_column_int(stmt, 0) + 1 ;
                if(p_id == 22000)
                    return false;
            }
            else {
                sqlite3_finalize(stmt);
                p_id = 21000 + 1;
            }
            sqlite3_finalize(stmt);
        }
        else if(choice == '2')
        {
            string query = "SELECT ID FROM PRODUCTS WHERE ID LIKE '22%' ORDER BY ID DESC LIMIT 1";
            sqlite3_stmt* stmt = db.fetchQuery(query);
            if (sqlite3_step(stmt) == SQLITE_ROW) {
                p_id = sqlite3_column_int(stmt, 0) + 1 ;
                if(p_id == 23000)
                    return false;
            }
            else {
                sqlite3_finalize(stmt);
                p_id = 22000 + 1;
            }
            sqlite3_finalize(stmt);
        }
        mvwprintw(stdscr, 9, 2, "Enter Product Name: ");
        curs_set(1);
        //cout << "Enter Product Name: " << endl;
        echo();
        char temp[200];
        getnstr(temp, sizeof(temp) - 1);
        p_name = string(temp);
        //cin >> p_name;
        mvwprintw(stdscr, 10, 2, "Enter Sell Price: ");
        //wmove(stdscr, 4, 21);
        //curs_set(1);
        //cout << "Enter Sell Price: " << endl;
        getnstr(temp, sizeof(temp) - 1);
        sell_price = stod(string(temp));
        //cin >> sell_price;
        mvwprintw(stdscr, 11, 2, "Enter Buying Cost: ");
        //wmove(stdscr, 4, 21);
        //curs_set(1);
        //cout << "Enter Buying Cost: " << endl;
        getnstr(temp, sizeof(temp) - 1);
        buying_cost = stod(string(temp));
        //cin >> buying_cost;
        stock = 0;
        date = "0000-00-00";
        prdct = new PerishableProducts(p_id,p_name,sell_price,buying_cost,stock,date);
        prdct->AddProduct(db);
    }
    else if(type == 1)
    {
        string query = "SELECT ID FROM PRODUCTS WHERE ID LIKE '1%' ORDER BY ID DESC LIMIT 1";
        sqlite3_stmt* stmt = db.fetchQuery(query);
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            p_id = sqlite3_column_int(stmt, 0) + 1 ;
            if(p_id == 20000)
                return false;
        }
        else {
            sqlite3_finalize(stmt);
            p_id = 10000 + 1;
        }
        sqlite3_finalize(stmt);
        mvwprintw(stdscr, 5, 2, "Enter Product Name: ");
        curs_set(1);
        //cout << "Enter Product Name: " << endl;
        echo();
        char temp[200];
        getnstr(temp, sizeof(temp) - 1);
        p_name = string(temp);
        //cin >> p_name;
        mvwprintw(stdscr, 6, 2, "Enter Sell Price: ");
        //wmove(stdscr, 4, 21);
        //curs_set(1);
        //cout << "Enter Sell Price: " << endl;
        getnstr(temp, sizeof(temp) - 1);
        sell_price = stod(string(temp));
        //cin >> sell_price;
        mvwprintw(stdscr, 7, 2, "Enter Buying Cost: ");
        //wmove(stdscr, 4, 21);
        //curs_set(1);
        //cout << "Enter Buying Cost: " << endl;
        getnstr(temp, sizeof(temp) - 1);
        buying_cost = stod(string(temp));
        //cin >> buying_cost;
        stock = 0;
        prdct = new Product(p_id, p_name, sell_price, buying_cost, stock);
        prdct->AddProduct(db);
    }
    refresh();
    return true;
}

bool Manager::DeleteProduct(Database& db)
{
    int productID;
    bool first = true;
    cout << "Enter product ID to delete: " << endl;
    do{
        if(!first)
            cout << "Product ID not found, enter again: " << endl;
        cin >> productID;
        first = false;
    }while(!Product::IsProductInTable(db,productID,All));

    string query = "DELETE FROM PRODUCTS WHERE ID = " + to_string(productID) + ";";
    return db.executeQuery(query);
}

bool Manager::AddNewEmployee(Database& db)
{
    Employee* emp;
    int e_type,e_id;
    string e_name, e_username, e_password;
    double e_salary;

    cout << "Enter Employee Type: \n1.Cashier\n2.Stock Clerk" << endl;
    cin >> e_type;
    cout << "Enter Employee Name: " << endl;
    cin >> e_name;
    cout << "Enter Salary: " << endl;
    cin >> e_salary;
    if(e_type == 1)
    {
        string query = "SELECT ID FROM EMPLOYEES WHERE ID LIKE '2%' ORDER BY ID DESC LIMIT 1";
        sqlite3_stmt* stmt = db.fetchQuery(query);
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            e_id = sqlite3_column_int(stmt, 0) + 1 ;
        if(e_id == 3000)
            return false;
        }
        else {
            sqlite3_finalize(stmt);
            e_id = 2000 + 1;
        }
        sqlite3_finalize(stmt);

        emp = new Cashier(e_id,e_name,e_salary);
        emp->AddEmployee(db,e_type);
    }
    else if(e_type == 2)
    {
        string query = "SELECT ID FROM EMPLOYEES WHERE ID LIKE '3%' ORDER BY ID DESC LIMIT 1";
        sqlite3_stmt* stmt = db.fetchQuery(query);
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            e_id = sqlite3_column_int(stmt, 0) + 1 ;
            if(e_id == 4000)
                return false;
        }
        else {
            sqlite3_finalize(stmt);
            e_id = 3000 + 1;
        }
        sqlite3_finalize(stmt);

        emp = new StockClerk(e_id,e_name,e_salary);
        emp->AddEmployee(db,e_type);
    }
    return true;
}

bool Manager::RemoveEmployee(Database& db)
{
    int employeeID;
    bool first = true;
    cout << "Enter employee ID to remove: " << endl;
    do{
        if(!first)
            cout << "employee ID not found, enter again: " << endl;
        cin >> employeeID;
        first = false;
    }while(!Employee::IsEmployeeInTable(db,employeeID));

    string query = "DELETE FROM EMPLOYEES WHERE ID = " + to_string(employeeID) + ";";
    return db.executeQuery(query);
}

void Manager::showFeedback()
{
    ifstream infile("Feedback.txt");
    cout << infile.rdbuf() << endl;

}
