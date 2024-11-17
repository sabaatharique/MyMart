#ifndef PRODUCT_H
#define PRODUCT_H

#include <iostream>

using namespace std;

class Product
{
    public:
        Product(int n, string x, double p, double c, int s);
        virtual ~Product();

        int GetProductID();

        string GetProductName();

        double GetSellingPrice();
        void SetSellingPrice(double val);

        double GetBuyingCost();
        void SetBuyingCost(double val);

        int GetQuantityInStock();
        void SetQuantityInStock(int val);

    protected:

    private:
        int ProductID;
        string ProductName;
        double SellingPrice;
        double BuyingCost;
        int QuantityInStock;
};

#endif // PRODUCT_H
