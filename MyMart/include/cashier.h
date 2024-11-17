#ifndef CASHIER_H
#define CASHIER_H

#include <employee.h>
#include <product.h>
#include <iostream>

using namespace std;



class Cashier : public Employee
{
    public:
        Cashier(int n, string x, double s);
        ~Cashier();

        void GetEmployeeType();

        int ProcessPayment();

    protected:

    private:
};

#endif // CASHIER_H
