#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <iostream>

using namespace std;

class Employee
{
    public:
        Employee(int n, string x, double s);
        virtual ~Employee();

        virtual void GetEmployeeType() = 0;

        int GetEmployeeID();

        string GetEmployeeName();

        double GetSalary();
        void SetSalary(double val);

    protected:

    private:
        int EmployeeID;
        string EmployeeName;
        double Salary;
};

#endif // EMPLOYEE_H
