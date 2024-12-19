#ifndef CASHIER_H
#define CASHIER_H

#include <employee.h>
#include <shoppingcart.h>
#include <cmath>
#include <iostream>

using namespace std;



class Cashier : public Employee
{
    public:
        Cashier(int n, string x, double s = 0);
        ~Cashier();

        void GetEmployeeType();

        ShoppingCart ProcessCart(Database& db);

        double MakeReceipt(ShoppingCart &cart);

    protected:

    private:
};

#endif // CASHIER_H
