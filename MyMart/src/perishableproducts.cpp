#include "perishableproducts.h"

PerishableProducts::PerishableProducts(int n, string x, double p, double c, int s, Date e) : Product(n, x, p, c, s), ExpiryDate(e)
{

}

PerishableProducts::~PerishableProducts()
{
    //dtor
}

Date PerishableProducts::GetExpiryDate() { return ExpiryDate; }

void PerishableProducts::SetExpiryDate(Date val) { ExpiryDate = val; }

bool PerishableProducts::operator>(Date today)
{
    if (ExpiryDate.year > today.year)
        return true;
    if (ExpiryDate.year < today.year)
        return false;

    if (ExpiryDate.month > today.month)
        return true;
    if (ExpiryDate.month < today.month)
        return false;

    if (ExpiryDate.day >= today.day)
        return true;
    if (ExpiryDate.day < today.day)
        return false;
}

