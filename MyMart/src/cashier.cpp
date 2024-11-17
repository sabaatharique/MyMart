#include "cashier.h"

Cashier::Cashier(int n, string x, double s = 0) : Employee(n, x, s)
{

}

Cashier::~Cashier()
{

}

void Cashier::GetEmployeeType()
{
    cout << "Employee: Cashier" << endl;
}

int Cashier::ProcessPayment()
{

}




