#ifndef SHOPPINGCART_H
#define SHOPPINGCART_H

#include <iostream>
#include <vector>
#include <string>
#include <perishableproducts.h>

class ShoppingCart
{
    public:
        ShoppingCart();
        ~ShoppingCart();

        const vector<pair<Product*, double>>& GetCart();
        void AddToCart(Database& db, Product* p, double quantity);

        double GetTotalBill();

    protected:

    private:
        vector<pair<Product*, double>> Cart;
        double TotalBill;
};

#endif // SHOPPINGCART_H
