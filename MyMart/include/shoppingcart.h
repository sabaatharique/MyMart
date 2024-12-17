#ifndef SHOPPINGCART_H
#define SHOPPINGCART_H

#include <iostream>
#include <map>
#include <string>
#include <perishableproducts.h>

class ShoppingCart
{
    public:
        ShoppingCart();
        ~ShoppingCart();

        map<Product*, double> GetCart();
        void AddToCart(Database& db, Product *p, double quantity);

        double GetTotalBill();

    protected:

    private:
        map<Product*, double> Cart;
        double TotalBill;
};

#endif // SHOPPINGCART_H
