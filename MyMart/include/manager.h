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
#include <ntdef.h>
#include <bcrypt.h>
#include <curses.h>

#pragma comment(lib, "bcrypt.lib")  // Link bcrypt library

#define HASH_ALGORITHM BCRYPT_SHA256_ALGORITHM  // Use SHA-256
#define HASH_SIZE 32   // 32-byte hash output


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

        string hashPassword(const string &password);

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
