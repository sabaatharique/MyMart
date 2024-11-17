#include "stockclerk.h"

StockClerk::StockClerk(int n, string x, double s = 0) : Employee(n, x, s)
{

}

StockClerk::~StockClerk()
{

}



bool StockClerk::CheckExpiry(PerishableProducts* p, Date today)
{
    return *p > today;
}

void StockClerk::CheckStock(Product* p)
{

}

void StockClerk::RestockProduct(Product* p)
{

}


