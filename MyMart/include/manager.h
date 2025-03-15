#ifndef MANAGER_H
#define MANAGER_H

#include <employee.h>
#include <product.h>
#include <perishableproducts.h>
#include <cashier.h>
#include <stockclerk.h>
#include <cmath>
#include <fstream>
#include <iostream>
#include <curses.h>


class Manager : public Employee
{
    public:
        Manager();
        Manager(int n, string x, double s = 0);
        ~Manager();
        string GetEmployeeType() override;

        static double GetProfit();
        static void SetProfit(const double p);
        static double GetTotalBalance();
        static void SetTotalBalance(const double b);

        bool IsEmployeeIdValid(Database& db, string& id, int login_type);

        bool IsEmployeePassValid(Database& db, string &id, string &password, int login_type);

        bool AddNewProducts(Database& db);

        bool DeleteProduct(Database& db, int start_line);

        bool AddNewEmployee(Database& db);

        bool RemoveEmployee(Database& db, int start_line);

        bool SetSalary(Database& db, int start_line);

        bool showFeedback();
    protected:

    private:
        static double profit;
        static double totalBalance;


};

#endif // MANAGER_H
