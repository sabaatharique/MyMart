#include <iostream>
#include <cashier.h>
#include <stockclerk.h>
#include <database.h>
#include<customer.h>
using namespace std;

int main()
{
    system("color 5F");

    /*cout << "\n\n";
    cout << " " << string(118, '~') << " " << endl;
    cout << string(55, ' ') << "MY MART" << endl;
    cout << " " << string(118, '~') << " " << endl;

    cout << string(55, ' ') << "Login as :\n" << endl;
    cout << string(54, ' ') << "1.Manager" << endl;
    cout << string(54, ' ') << "2.Stockclerk" << endl;
    cout << string(54, ' ') << "3.Cashier" << endl;

    cout << string(50, ' ') << string(20, '_') << "\n" << string(49, ' ') << "  Enter Username :\n" << string(50, ' ') << string(20, '-') << endl;
    cout << string(50,' ');
    string name;
    cin >> name;
    cout << string(50, ' ') << string(20, '_') << "\n" << string(49, ' ') << "  Enter Password :\n" << string(50, ' ') << string(20, '-') << endl;
    string password;
    cout << string(50,' ');
    cin >> password;*/


    Database db;
    db.initialiseDatabase();
    cout << endl;

    int n;
    cin >> n;
    system("cls");
    if(n==2)
    {
        StockClerk Mishkat;
        cout << "Press 1 to show all products." << endl;
        cout << "Press 2 to show expired products." << endl;
        cout << "Press 3 to show out of stock products." << endl;
        int op;
        cout << "Enter no : " << endl;
        cin >> op;
        system("cls");
        while(op != -1)
        {
            if(op == 1)
                Mishkat.ShowAllProducts(db);
            else if(op == 2)
                Mishkat.ShowExpiredProducts(db);
            else if(op == 3)
                Mishkat.ShowOutOfStockProducts(db);
            cout << "Enter no : " << endl;
            cin >> op;
        }
    }
    else if(n == 3) {
        Cashier saba;
        saba.CheckoutCustomer(db);
    }
    //system("cls");

    db.displayTable("SELECT * FROM PRODUCTS;");
    cout << endl;

    db.displayTable("SELECT * FROM CUSTOMERS;");
    cout << endl;

    db.displayTable("SELECT * FROM EMPLOYEES;");
    cout << endl;
//
//    StockClerk Mishkat;
//    Mishkat.ShowAllProducts(db);
//
//    Cashier saba;
//    ShoppingCart cart = saba.ProcessCart(db);
//    saba.MakeReceipt(cart);
//
//    Customer Ridita;
//    Ridita.GetCustomerByID(db,220041101);
//    Ridita.DisplayDetails();
//
//    db.displayTable("SELECT * FROM PRODUCTS;");
//    cout << endl;

    db.closeDatabase();

	return 0;
}
