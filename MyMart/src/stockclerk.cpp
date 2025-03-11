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

void StockClerk::UpdateStockByID(Database& db, int ID, float amount)
{
    string query = "UPDATE PRODUCTS SET IN_STOCK = " + to_string(amount) + " WHERE ID = " + to_string(ID) + ";";

    if(db.executeQuery(query))
        cout << "Product stock updated." << endl;
    else
        cout << "Could not update product with ID " << ID << endl;
}

double StockClerk::GetExpiredStockAmount(Database& db, int ID)
{
    double loss;
    string query = "SELECT IN_STOCK*BUYING_COST FROM PRODUCTS WHERE ID = " + to_string(ID) + ";";
    sqlite3_stmt* stmt = db.fetchQuery(query);
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        loss = sqlite3_column_int(stmt, 0);
    }
    sqlite3_finalize(stmt);
    return loss;
}


void StockClerk::UpdateExpiryDateByID(Database& db, PerishableProducts &Exp, int ID)
{
    string expDate = "'" + Exp.GetExpiryDate().ToString() + "'";
    string query = "UPDATE PRODUCTS SET EXPIRY_DATE = " + expDate + " WHERE ID = " + to_string(ID) + ";";

    if(db.executeQuery(query))
        cout << "Product expiry date updated." << endl;
    else
        cout << "Could not update product with ID " << ID << endl;
}

void StockClerk::ShowExpiredProducts(Database& db)
{
    db.displayTable("SELECT * FROM PRODUCTS WHERE EXPIRY_DATE < DATE('now');");
    cout << endl;

    int productID;
    cout << "Enter product ID to update: " << endl;
    while(true) {
        cin >> productID;

        if (productID == -1)
            break;

        if(Product::IsProductInTable(db, productID, Expired)) {
            float amount;
            cout << "Enter new stock amount: " << endl;
            string pID = to_string(productID);
            cin >> amount;
        // first digit 1 indicates regular product, 21 indicates perishable but bought in kg and 22 indicates perishable but bought in unit
            if(pID[1] == '2') {
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
            double cur_profit = Manager::GetProfit();
            double loss = GetExpiredStockAmount(db,productID);
            Manager::SetProfit(cur_profit-loss);
            UpdateStockByID(db, productID, amount);

            bool notfirst = false;
            Date dt, today;
            today.GetTodaysDate();
            PerishableProducts Exp;
            do{
                string date;
                if(notfirst) cout << "Invalid Expiry Date! ";
                cout << "Enter new expiry date : " << endl;
                cin >> date;
                dt.ToDate(date.c_str());
                Exp.SetExpiryDate(dt);
            } while(notfirst = CheckExpiry(&Exp, today));

            UpdateExpiryDateByID(db, Exp, productID);
        }
        else
            cout << "Product could not be found." << endl;
    }
}

void StockClerk::ShowOutOfStockProducts(Database& db)
{
    db.displayTable("SELECT * FROM PRODUCTS WHERE IN_STOCK = 0;");
    cout << endl;

    int productID;
    cout << "Enter product ID to update: " << endl;
    while(true) {
        cin >> productID;

        if (productID == -1)
            break;

        if(Product::IsProductInTable(db, productID,OutOfStock)) {
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

void StockClerk::ShowAllProducts(Database& db)
{
    db.displayTable("SELECT * FROM PRODUCTS;");
    cout << endl;
}


