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
    sqlite3_stmt* stmt = db.searchFromTable(db,ID,"PRODUCTS");

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        Product::GetProductByID(db, ID);
        const char* expDate = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5));

        // converting string to date struct
        Date date;
        date.ToDate(expDate);

        this->ExpiryDate = date;
    }
    else {
        sqlite3_finalize(stmt);
        //cout << "No expiry date found for ID: " + to_string(ID) << endl;
        return false;
    }

    sqlite3_finalize(stmt);
    return true;
}

int PerishableProducts::DisplayDetails(int start_line)
{
    int next_line = Product::DisplayDetails(start_line);

    mvwprintw(stdscr, next_line, 2, "Expiry date: ");
    mvwprintw(stdscr, next_line, 2 + 13, ExpiryDate.ToString().c_str());

    return next_line + 1;
}


bool PerishableProducts::AddProduct(Database& db)
{
    string query = "INSERT OR IGNORE INTO PRODUCTS VALUES(" + to_string(GetProductID()) + ", '" + GetProductName() + "', " + to_string(GetSellingPrice()) + ", " + to_string(GetBuyingCost()) + ", " + to_string(GetQuantityInStock()) + ", '" + ExpiryDate.ToString() + "');";
    return db.executeQuery(query);
}



