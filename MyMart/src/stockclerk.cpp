#include "stockclerk.h"

StockClerk::StockClerk(int n, string x, double s) : Employee(n, x, s) {}
StockClerk::StockClerk() {}
StockClerk::~StockClerk() {}

void StockClerk::GetEmployeeType()
{
    cout << "Employee: StockClerk" << endl;
}

bool StockClerk::CheckExpiry(PerishableProducts* p, Date today)
{
    return *p < today;
}

void StockClerk::UpdateStockByID(Database& db, int ID, float amount)
{
    string query = "UPDATE PRODUCTS SET IN_STOCK = " + to_string(amount) + " WHERE ID = " + to_string(ID) + ";";

    if(db.executeQuery(query))
        cout << "Product stock updated." << endl;
    else
        cout << "Could not update product with ID " << ID << endl;
}

void StockClerk::ShowExpiredProducts(Database& db)
{

}

void StockClerk::ShowOutOfStockProducts(Database& db)
{

}

bool StockClerk::IsProductInTable(Database& db, int ID)
{
    sqlite3_stmt* stmt = db.searchFromTable(db,ID,"(SELECT * FROM PRODUCTS WHERE IN_STOCK = 0 OR EXPIRY_DATE < DATE('now'))");

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

        if (productID == -1)
            break;

        if(IsProductInTable(db, productID)) {
            float amount;
            cout << "Enter new stock amount: " << endl;
            string pID = to_string(productID);
            cin >> amount;
        // first digit 1 indicates regular product, 21 indicates perishable but bought in kg and 22 indicates perishable but bought in unit
            if(pID[0] == '1' || pID[1] == '2') {
                while(1){
                    if(floor(amount) != amount || amount <= 0)
                    {
                        cout << "Input invalid, try again." << endl;
                        cin >> amount;
                    }
                    else
                        break;
                }
            }
            UpdateStockByID(db,productID,amount);
        }
        else
            cout << "Product does not need restocking." << endl;
    }
}


