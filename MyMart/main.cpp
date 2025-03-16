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
    Database db;
    db.initialiseDatabase();

    Manager M;
    Cashier C;
    StockClerk SC;

    Ui* ui = new Ui();

    ui->Engine(db, M, C, SC);


    db.closeDatabase();

    delete ui;
	return 0;
}
