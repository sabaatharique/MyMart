#include "stockclerk.h"

StockClerk::StockClerk(int n, string x, double s = 0) : Employee(n, x, s) {}

StockClerk::~StockClerk() {}

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

void StockClerk::ShowAllProducts(Database& db)
{
    db.displayTable("SELECT * FROM PRODUCTS;");
    cout << endl;

    int productID;
    char choice;
    cout << "Enter product ID to update: " << endl;
    while(-1) {
        cin >> productID;

        Product *product = new Product();
        if(!product->GetProductByID(db, productID)){
            cout << "Could not find product with ID: " << productID << endl;
            delete product;
            continue;
        }


    }
}


