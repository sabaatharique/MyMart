#include "perishableproducts.h"

PerishableProducts::PerishableProducts(): Product() {}

PerishableProducts::PerishableProducts(int n, string x, double p, double c, double s, const char* e): Product(n, x, p, c, s)
{
    Date d;
    d.ToDate(e);
    ExpiryDate = d;
}


PerishableProducts::~PerishableProducts() {}

Date PerishableProducts::GetExpiryDate() { return ExpiryDate; }

void PerishableProducts::SetExpiryDate(Date val) { ExpiryDate = val; }

bool PerishableProducts::operator<(Date today)
{
    if (ExpiryDate.GetYear() < today.GetYear())
        return true;
    if (ExpiryDate.GetYear() > today.GetYear())
        return false;

    int ExpiryDate_month = static_cast<int>(ExpiryDate.GetMonth());
    int today_month = static_cast<int>(today.GetMonth());

    if (ExpiryDate_month < today_month)
        return true;
    if (ExpiryDate_month > today_month)
        return false;

    if (ExpiryDate.GetDay() < today.GetDay())
        return true;
    if (ExpiryDate.GetDay() >= today.GetDay())
        return false;
}

bool PerishableProducts::GetProductByID(Database& db, int ID)
{
    if (!Product::GetProductByID(db, ID)) {
        return false;
    }

    string query = "SELECT * FROM PRODUCTS WHERE ID = " + to_string(ID) + ";";
    sqlite3_stmt* stmt;


    int exitCode = sqlite3_prepare_v2(db.getDatabase(), query.c_str(),-1, &stmt, NULL);

    if (exitCode != SQLITE_OK) {
        cerr << "Could not prepare statement: " << sqlite3_errmsg(db.getDatabase()) << endl;
        return false;
    }

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        const char* name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        double sPrice = sqlite3_column_double(stmt, 2);
        double bCost = sqlite3_column_double(stmt, 3);
        double quantity = sqlite3_column_double(stmt, 4);
        const char* expDate = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5));

        // converting string to date struct
        Date date;
        date.ToDate(expDate);

        this->ExpiryDate = date;
    }
    else {
        sqlite3_finalize(stmt);
        cout << "No expiry date found for ID: " + to_string(ID) << endl;
        return false;
    }

    sqlite3_finalize(stmt);
    return true;
}

void PerishableProducts::DisplayDetails()
{
    Product::DisplayDetails();
    cout << "Expiry date: " << ExpiryDate.ToString() << endl;
}


bool PerishableProducts::AddProduct(Database& db)
{
    string query = "INSERT INTO PRODUCTS VALUES(" + to_string(GetProductID()) + ", '" + GetProductName() + "', " + to_string(GetSellingPrice()) + ", " + to_string(GetBuyingCost()) + ", " + to_string(GetQuantityInStock()) + ", '" + ExpiryDate.ToString() + "');";
    return db.executeQuery(query);
}



