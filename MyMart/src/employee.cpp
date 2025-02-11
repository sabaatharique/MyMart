#include "employee.h"

Employee::Employee(int n, string x, double s = 0) : EmployeeID(n), EmployeeName(x), Salary(s) {}

Employee::Employee() {}

Employee::~Employee() {}

int Employee::GetEmployeeID() { return EmployeeID; }

string Employee::GetEmployeeName() { return EmployeeName; }

double Employee::GetSalary() { return Salary; }

void Employee::SetSalary(double val) { Salary = val; }
