#include "Manager.h"

using namespace std;

Manager::Manager(int n, string x, double s) : Employee(n, x, s) {}

Manager::Manager(){}

Manager::~Manager(){}

void Manager::GetEmployeeType()
{
    cout << "Employee: Manager" << endl;
}

bool Manager::AddNewProducts(Database& db)
{
    Product* prdct;
    int type,p_id;
    string p_name;
    const char* date;
    double sell_price, buying_cost,stock;

    cout << "Enter Product Type: \n1.Non-Perishable\n2.Perishable\n" << endl;
    cin >> type;
    if(type == 2)
    {
        int choice;
        cin >> choice;
        if(choice == 1)
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
        else if(choice == 2)
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
        cout << "Enter Product Name: " << endl;
        cin >> p_name;
        cout << "Enter Sell Price: " << endl;
        cin >> sell_price;
        cout << "Enter Buying Cost: " << endl;
        cin >> buying_cost;
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
        cout << "Enter Product Name: " << endl;
        cin >> p_name;
        cout << "Enter Sell Price: " << endl;
        cin >> sell_price;
        cout << "Enter Buying Cost: " << endl;
        cin >> buying_cost;
        stock = 0;
        prdct = new Product(p_id, p_name, sell_price, buying_cost, stock);
        prdct->AddProduct(db);
    }
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

