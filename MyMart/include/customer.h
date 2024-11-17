#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <product.h>
#include <iostream>
#include <vector>

using namespace std;

class Customer
{
    public:
        Customer(string x, int n);
        virtual ~Customer();

        string GetCustomerName();

        int GetCustomerID();

        vector<Product*> GetShoppingCart();
        void AddToShoppingCart(Product *p);

        double CheckOut();

        double GetTotalAmountSpent();
        void SetTotalAmountSpent(double val);

    protected:

    private:
        string CustomerName;
        int CustomerID;
        vector<Product*> ShoppingCart;
        double TotalAmountSpent;
};

#endif // CUSTOMER_H
