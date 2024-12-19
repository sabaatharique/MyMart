#include <iostream>
#include <cashier.h>
#include <database.h>

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

    Cashier saba(220041130, "Saba Atharique");
    ShoppingCart cart = saba.ProcessCart(db);
    cout << "RECEIPT" <<endl;
    saba.MakeReceipt(cart);

    //db.displayTable("SELECT * FROM PRODUCTS;");
    //cout << endl;

    db.closeDatabase();

	return 0;
}
