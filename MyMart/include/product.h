#ifndef PRODUCT_H
#define PRODUCT_H

#include <iostream>
#include <database.h>

using namespace std;

class Product
{
    public:
        Product();
        Product(int n, string x, double p, double c, int s);
        virtual ~Product();

        Product GetProductByID(Database &db, int ID);
        void DisplayDetails();
        bool AddProduct(Database &db);

    protected:

    private:
        int ProductID;
        string ProductName;
        double SellingPrice;
        double BuyingCost;
        int QuantityInStock;
};

#endif // PRODUCT_H
