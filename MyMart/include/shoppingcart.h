#ifndef SHOPPINGCART_H
#define SHOPPINGCART_H

#include <iostream>
#include <unordered_map>
#include <string>
#include <perishableproducts.h>

class ShoppingCart
{
    public:
        ShoppingCart();
        ~ShoppingCart();

        const unordered_map<int, pair<Product*, double>>& GetCart();
        void AddToCart(Database& db, Product* p, double quantity);

        double GetTotalBill();

    protected:

    private:
        unordered_map<int, pair<Product*, double>> Cart;
        double TotalBill;
};

#endif // SHOPPINGCART_H
