#ifndef CASHIER_H
#define CASHIER_H

#include <employee.h>
#include <shoppingcart.h>
#include <loyalcustomer.h>
#include <cmath>
#include <string>
#include <iostream>

using namespace std;

class Cashier : public Employee
{
    public:
        Cashier(int n, string x, double s = 0);
        Cashier();
        ~Cashier();

        void GetEmployeeType();

        ShoppingCart ProcessCart(Database& db);

        void MakeReceipt(ShoppingCart& cart, Customer *customer);

        void CheckoutCustomer(Database& db);

        Customer* OpenCustomerAccount(Database& db);

    protected:

    private:
};

#endif // CASHIER_H
