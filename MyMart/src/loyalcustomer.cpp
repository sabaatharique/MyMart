#include "loyalcustomer.h"

LoyalCustomer::LoyalCustomer(string x,int  n) : Customer(x,n)
{

}

LoyalCustomer::LoyalCustomer()
{

}

LoyalCustomer::~LoyalCustomer()
{

}


double LoyalCustomer::CalculateDiscount()
{
    int TotalAmountSpent = GetTotalAmountSpent();
    if (TotalAmountSpent >= 10000 && TotalAmountSpent < 15000)
        return 0.025;
    else if (TotalAmountSpent >= 15000 && TotalAmountSpent < 25000)
        return 0.05;
    else if (TotalAmountSpent >= 25000)
        return 0.1;
}


