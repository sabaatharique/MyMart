#include "product.h"

Product::Product() : ProductID(0) {}

Product::Product(int n, string x, double p, double c, int s) : ProductID(n), ProductName(x), SellingPrice(p), BuyingCost(c), QuantityInStock(s) {}

Product::~Product() {}

Product Product::GetProductByID(Database& db, int ID)
{
    string query = "SELECT * FROM PRODUCTS WHERE ID = " + to_string(ID) + ";";
    sqlite3_stmt* stmt;


    int exitCode = sqlite3_prepare_v2(db.getDatabase(), query.c_str(),-1, &stmt, NULL);

    if (exitCode != SQLITE_OK) {
        cerr << "Could not prepare statement: " << sqlite3_errmsg(db.getDatabase()) << endl;
        return Product();
    }

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        const char* name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        double sPrice = sqlite3_column_double(stmt, 2);
        double bCost = sqlite3_column_int(stmt, 3);
        int quantity = sqlite3_column_int(stmt, 4);

        Product prod(id, name, sPrice, bCost, quantity);
        return prod;
    }
    else {
        sqlite3_finalize(stmt);
        cout << "No product found with ID: " + to_string(ID) << endl;
        return Product();
    }
    sqlite3_finalize(stmt);
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
    string query = "INSERT INTO PRODUCTS VALUES(" + to_string(ProductID) + ", '" + ProductName + "', " + to_string(SellingPrice) + ", " + to_string(BuyingCost) + ", " + to_string(QuantityInStock) + ");";
    return db.executeQuery(query);
}




