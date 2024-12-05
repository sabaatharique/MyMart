#include "customer.h"

Customer::Customer(string x, int n) : CustomerName(x), CustomerID(n), TotalAmountSpent(0) {}

Customer::~Customer() {}

string Customer::GetCustomerName()
{
    return CustomerName;
    }

int Customer::GetCustomerID()
{
    return CustomerID;
}

vector<Product*> Customer::GetShoppingCart()
{
    return ShoppingCart;
}

void Customer::AddToShoppingCart(Product *p){
    ShoppingCart.push_back(p);
};

double Customer::CheckOut()
{
    double total = 0.0;
    for (auto i : ShoppingCart) {
        total += i->GetSellingPrice();
    }
    return total;
}

double Customer::GetTotalAmountSpent()
{
    return TotalAmountSpent;
}

void Customer::SetTotalAmountSpent(double val)
{
    TotalAmountSpent = val;
}
