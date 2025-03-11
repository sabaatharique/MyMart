#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <iostream>
#include <database.h>

using namespace std;

class Employee
{
    public:
        Employee(int n, string x, string t, double s);
        Employee();
        virtual ~Employee();

        virtual string GetEmployeeType() = 0;

        int GetEmployeeID();

        string GetEmployeeName();

        double GetSalary();
        void SetSalary(double val);
        virtual bool AddEmployee(Database &db,int choice);
        static bool IsEmployeeInTable(Database& db, int ID);

    protected:
        string EmployeeType;
    private:
        int EmployeeID;
        string EmployeeName;
        double Salary;
};

#endif // EMPLOYEE_H
