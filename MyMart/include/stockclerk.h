#ifndef STOCKCLERK_H
#define STOCKCLERK_H

#include <employee.h>
#include <product.h>
#include <perishableproducts.h>
#include <iostream>

using namespace std;

class StockClerk : public Employee
{
    public:
        StockClerk(int n, string x, double s = 0);
        ~StockClerk();

        void GetEmployeeType();

        bool CheckExpiry(PerishableProducts *p, Date today);

        void UpdateExpiryDate();
        void UpdateStockByID(Database &db, int ID);
        void ShowExpiredProducts(Database &db);
        void ShowOutOfStockProducts(Database &db);
        void ShowAllProducts(Database &db);
        bool IsProductInTable(Database &db, int ID);

    protected:

    private:
};

#endif // STOCKCLERK_H
