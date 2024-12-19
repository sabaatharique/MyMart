#include "stockclerk.h"

StockClerk::StockClerk(int n, string x, double s) : Employee(n, x, s) {}

StockClerk::~StockClerk() {}

void StockClerk::GetEmployeeType()
{
    cout << "Employee: StockClerk" << endl;
}

bool StockClerk::CheckExpiry(PerishableProducts* p, Date today)
{
    return *p < today;
}

void StockClerk::UpdateStockByID(Database& db, int ID)
{

}

void StockClerk::ShowExpiredProducts(Database& db)
{

}

void StockClerk::ShowOutOfStockProducts(Database& db)
{

}

bool StockClerk::IsProductInTable(Database& db, int ID)
{
    string query = "SELECT * FROM (SELECT * FROM PRODUCTS WHERE IN_STOCK = 0 OR EXPIRY_DATE < DATE('now')) WHERE ID = " + to_string(ID) + ";";
    sqlite3_stmt* stmt;


    int exitCode = sqlite3_prepare_v2(db.getDatabase(), query.c_str(),-1, &stmt, NULL);

    if (exitCode != SQLITE_OK) {
        cerr << "Could not prepare statement: " << sqlite3_errmsg(db.getDatabase()) << endl;
        return false;
    }

    int exists = 0;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        exists = sqlite3_column_int(stmt, 0);
    }

    if (exists) {
        sqlite3_finalize(stmt);
        return true;
    }
    sqlite3_finalize(stmt);
    return false;
}


void StockClerk::ShowAllProducts(Database& db)
{
    db.displayTable("SELECT * FROM PRODUCTS WHERE IN_STOCK = 0 OR EXPIRY_DATE < DATE('now');");
    cout << endl;

    int productID;
    cout << "Enter product ID to update: " << endl;
    while(true) {
        cin >> productID;

        if(IsProductInTable(db, productID)) cout << "YAYY" << endl;
        else cout << "NAY" << endl;
    }
}


