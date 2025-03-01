#ifndef MANAGER_H
#define MANAGER_H

#include <employee.h>
#include <shoppingcart.h>
#include <cmath>
#include <iostream>


class Manager : public Employee
{
    public:
        Manager();
        Manager(int n, string x, double s = 0);
        ~Manager();
        void GetEmployeeType();

        bool AddNewProducts(Database& db);

        bool DeleteProduct(Database& db);


    protected:

    private:



};

#endif // MANAGER_H
