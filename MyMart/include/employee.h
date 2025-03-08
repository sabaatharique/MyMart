#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <iostream>
#include <database.h>

using namespace std;

class Employee
{
    public:
        Employee(int n, string x, double s);
        Employee();
        virtual ~Employee();

        virtual void GetEmployeeType() = 0;

        int GetEmployeeID();

        string GetEmployeeName();

        double GetSalary();
        void SetSalary(double val);
        virtual bool AddEmployee(Database &db,int choice);
        static bool IsEmployeeInTable(Database& db, int ID);

    protected:

    private:
        int EmployeeID;
        string EmployeeName;
        double Salary;
};

#endif // EMPLOYEE_H
