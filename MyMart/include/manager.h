#ifndef MANAGER_H
#define MANAGER_H

#include <employee.h>
//#include <shoppingcart.h>
#include<product.h>
#include<perishableproducts.h>
#include<cashier.h>
#include<stockclerk.h>
#include <cmath>
#include <iostream>


class Manager : public Employee
{
    public:
        Manager();
        Manager(int n, string x, double s = 0);
        ~Manager();
        void GetEmployeeType();

        static double GetProfit();
        static void SetProfit(const double p);
        static double GetTotalBalance();
        static void SetTotalBalance(const double b);
        bool AddNewProducts(Database& db);

        bool DeleteProduct(Database& db);

        bool AddNewEmployee(Database& db);

        bool RemoveEmployee(Database& db);

        void SetSalary(Database& db);
    protected:

    private:
        static double profit;
        static double totalBalance;


};

#endif // MANAGER_H
