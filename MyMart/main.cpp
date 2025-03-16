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

    Ui* ui = new Ui();

    ui->Engine(db);


    db.closeDatabase();

    delete ui;
	return 0;
}
