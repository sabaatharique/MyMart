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
        StockClerk(int n, string x, double s);
        ~StockClerk();

        bool CheckExpiry(PerishableProducts *p, Date today);

        void CheckStock(Product *p);

        void RestockProduct(Product *p);

    protected:

    private:
};

#endif // STOCKCLERK_H
