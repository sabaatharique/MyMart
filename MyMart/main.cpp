#include <iostream>
#include <cashier.h>
#include <stockclerk.h>
#include <database.h>

#include<customer.h>
using namespace std;

int main()
{
    Database db;
    db.initialiseDatabase();
    cout << endl;

    db.displayTable("SELECT * FROM PRODUCTS;");
    cout << endl;

    db.displayTable("SELECT * FROM CUSTOMERS;");
    cout << endl;

    db.displayTable("SELECT * FROM EMPLOYEES;");
    cout << endl;

    StockClerk Mishkat;
    Mishkat.ShowAllProducts(db);

//    Cashier saba;
//    ShoppingCart cart = saba.ProcessCart(db);
//    saba.MakeReceipt(cart);
//
//    Customer Ridita;
//    Ridita.GetCustomerByID(db,220041101);
//    Ridita.DisplayDetails();

    db.displayTable("SELECT * FROM PRODUCTS;");
    cout << endl;

    db.closeDatabase();

	return 0;
}
