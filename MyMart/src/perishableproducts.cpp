#include "perishableproducts.h"

PerishableProducts::PerishableProducts(): Product() {}


PerishableProducts::PerishableProducts(int n, string x, double p, double c, int s, Date e) : Product(n, x, p, c, s), ExpiryDate(e){}

PerishableProducts::~PerishableProducts() {}

Date PerishableProducts::GetExpiryDate() { return ExpiryDate; }

void PerishableProducts::SetExpiryDate(Date val) { ExpiryDate = val; }

bool PerishableProducts::operator>(Date today)
{
    if (ExpiryDate.year > today.year)
        return true;
    if (ExpiryDate.year < today.year)
        return false;

    if (ExpiryDate.month > today.month)
        return true;
    if (ExpiryDate.month < today.month)
        return false;

    if (ExpiryDate.day >= today.day)
        return true;
    if (ExpiryDate.day < today.day)
        return false;
}

PerishableProducts PerishableProducts::GetProductByID(Database& db, int ID)
{
    string query = "SELECT * FROM PRODUCTS WHERE ID = " + to_string(ID) + ";";
    sqlite3* database = db.getDatabase();
    sqlite3_stmt* stmt;


    int exitCode = sqlite3_prepare_v2(database, query.c_str(),-1, &stmt, NULL);

    if (exitCode != SQLITE_OK) {
        cerr << "Could not prepare statement: " << sqlite3_errmsg(database) << endl;
        return PerishableProducts();
    }

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        const char* name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        double sPrice = sqlite3_column_double(stmt, 2);
        double bCost = sqlite3_column_int(stmt, 3);
        int quantity = sqlite3_column_int(stmt, 4);
        const char* expDate = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5));

        // converting string to date struct
        Date date;
        date.day = (expDate[0] - '0')*10 + (expDate[1] - '0');
        date.month = static_cast<Months>((expDate[3] - '0')*10 + (expDate[4] - '0'));
        date.year = (expDate[6] - '0')*10 + (expDate[7] - '0');

        PerishableProducts prod(id, name, sPrice, bCost, quantity, date);
        return prod;
    }
    else {
        sqlite3_finalize(stmt);
        cout << "No product found with ID: " + to_string(ID) << endl;
        return PerishableProducts();
    }
    sqlite3_finalize(stmt);
}

void PerishableProducts::DisplayDetails()
{
    Product::DisplayDetails();
    cout << "Expiry date: " << ExpiryDate.day << "-" << ExpiryDate.month << "-" << ExpiryDate.year << endl;
}


bool PerishableProducts::AddProduct(Database& db)
{
    return db.executeQuery(query);
}



