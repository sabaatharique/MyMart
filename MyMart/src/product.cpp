#include "product.h"

Product::Product() : ProductID(0) {}

Product::Product(int n, string x, double p, double c, double s) : ProductID(n), ProductName(x), SellingPrice(p), BuyingCost(c), QuantityInStock(s) {}

Product::~Product() {}

int Product::GetProductID() const
{
    return ProductID;
}

string Product::GetProductName() const
{
    return ProductName;
}

double Product::GetSellingPrice() const
{
    return SellingPrice;
}

double Product::GetBuyingCost() const
{
    return BuyingCost;
}

double Product::GetQuantityInStock() const
{
    return QuantityInStock;
}

void Product::SetProductID(int n)
{
    ProductID = n;
}

void Product::SetProductName(string x)
{
    ProductName = x;
}

void Product::SetSellingPrice(double p)
{
    SellingPrice = p;
}

void Product::SetBuyingCost(double c)
{
    BuyingCost = c;
}

void Product::SetQuantityInStock(double s)
{
    QuantityInStock = s;
}

bool Product::GetProductByID(Database& db, int ID)
{
    sqlite3_stmt* stmt = db.searchFromTable(db, ID, "PRODUCTS");

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        const char* name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        double sPrice = sqlite3_column_double(stmt, 2);
        double bCost = sqlite3_column_double(stmt, 3);
        double quantity = sqlite3_column_double(stmt, 4);

        this->ProductID = id;
        this->ProductName = name;
        this->SellingPrice = sPrice;
        this->BuyingCost = bCost;
        this->QuantityInStock = quantity;

    }
    else {
        sqlite3_finalize(stmt);
        cout << "No product found with ID: " << ID << endl;
        return false;
    }
    sqlite3_finalize(stmt);
    return true;
}

void Product::DisplayDetails()
{
    cout << "Product ID: " << ProductID << endl;
    cout << "Product name: " << ProductName << endl;
    cout << "Selling price: " << SellingPrice << endl;
    cout << "Buying cost: " << BuyingCost << endl;
    cout << "Quantity in stock: " << QuantityInStock << endl;
}

bool Product::AddProduct(Database& db)
{
    string query = "INSERT OR IGNORE INTO PRODUCTS VALUES(" + to_string(ProductID) + ", '" + ProductName + "', " + to_string(SellingPrice) + ", " + to_string(BuyingCost) + ", " + to_string(QuantityInStock) + ", NULL);";
    return db.executeQuery(query);
}


bool Product::IsProductInTable(Database& db, int ID, Table tbl)
{
    string table;
    if(tbl == Expired)
        table = " WHERE EXPIRY_DATE < DATE('now')";
    else if(tbl == OutOfStock)
        table = " WHERE IN_STOCK = 0";
    else
        table = "";

    string query = "(SELECT * FROM PRODUCTS" + table + ")";
    sqlite3_stmt* stmt = db.searchFromTable(db, ID, query);

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

