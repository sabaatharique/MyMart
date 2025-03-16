#ifndef STOCKCLERK_H
#define STOCKCLERK_H

#include <employee.h>
#include <product.h>
#include <perishableproducts.h>
#include <manager.h>
#include <cmath>
#include <cstring>
#include <iostream>

using namespace std;

class StockClerk : public Employee
{
    public:
        StockClerk(int n, string x, double s = 0);
        StockClerk();
        ~StockClerk();

        string GetEmployeeType() override;

        bool CheckExpiry(PerishableProducts *p, Date today);

        bool UpdateExpiryDateByID(Database& db, int ID, string Exp);
        bool UpdateExpiryDateByID(Database& db, PerishableProducts &Exp, int ID);
        bool UpdateStockByID(Database &db, int ID, double amount);
        bool ShowExpiredProducts(Database &db);
        bool ShowOutOfStockProducts(Database &db);
        bool ShowAllProducts(Database &db);

        double GetExpiredStockAmount(Database &db, int ID);

    protected:

    private:

};

#endif // STOCKCLERK_H
