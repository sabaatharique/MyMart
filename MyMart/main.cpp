#include <iostream>
#include <cashier.h>
#include <stockclerk.h>
#include <database.h>
#include <customer.h>
#include <manager.h>
#include <ui.h>
using namespace std;


int main()
{
//    system("color 5F");
//
    Database db;
    db.initialiseDatabase();

    Manager M;
    Cashier C;
    StockClerk SC;

    Ui* ui = new Ui();

    ui->Engine(db, M, C, SC);

//      Manager mmmm;
//      mmmm.showFeedback();
//    mmmm.AddNewEmployee(db);
//    db.displayTable("SELECT * FROM EMPLOYEES;");
//    cout << endl;
//    mmmm.RemoveEmployee(db);
    //db.displayTable("SELECT * FROM EMPLOYEES;");
//    Cashier ridita;
//    ridita.CheckoutCustomer(db);
//    Manager mmmm;
//    mmmm.showFeedback();


//
//    int n;
//    cin >> n;
//    system("cls");
//    if(n==2)
//    {
//        StockClerk Mishkat;
//        cout << "Press 1 to show all products." << endl;
//        cout << "Press 2 to show expired products." << endl;
//        cout << "Press 3 to show out of stock products." << endl;
//        int op;
//        cout << "Enter no : " << endl;
//        cin >> op;
//        system("cls");
//        while(op != -1)
//        {
//            if(op == 1)
//                Mishkat.ShowAllProducts(db);
//            else if(op == 2)
//                Mishkat.ShowExpiredProducts(db);
//            else if(op == 3)
//                Mishkat.ShowOutOfStockProducts(db);
//            cout << "Enter no : " << endl;
//            cin >> op;
//        }
//    }
//    else if(n == 3) {
//        Cashier saba;
//        saba.CheckoutCustomer(db);
//    }
//    //system("cls");
//
//    db.displayTable("SELECT * FROM PRODUCTS;");
//    cout << endl;
//
//    db.displayTable("SELECT * FROM CUSTOMERS;");
//    cout << endl;
//
//    db.displayTable("SELECT * FROM EMPLOYEES;");
//    cout << endl;
//
//    cout << Manager::GetProfit() << endl;
//    StockClerk Mishkat;
//    Mishkat.ShowExpiredProducts(db);
//    Mishkat.ShowAllProducts(db);
//
//    cout << "Profit: " << Manager::GetProfit() << endl;
//
//    Customer Ridita;
////    Ridita.GetCustomerByID(db,10000001);
////    Ridita.DisplayDetails();
//
//    Cashier saba;
//    saba.OpenCustomerAccount(db);
//    ShoppingCart cart = saba.ProcessCart(db);
//    saba.MakeReceipt(cart,&Ridita);
//    saba.GiveFeedback();

//    db.displayTable("SELECT * FROM PRODUCTS;");
//    cout << endl;
//
    db.closeDatabase();

    //delete ui;
	return 0;
}
