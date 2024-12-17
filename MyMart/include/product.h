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

        int GetProductID() const;
        void SetProductID(int n);

        string GetProductName() const;
        void SetProductName(string x);

        double GetSellingPrice() const;
        void SetSellingPrice(double p);

        double GetBuyingCost() const;
        void SetBuyingCost(int c);

        double GetQuantityInStock() const;
        void SetQuantityInStock(double s);

        bool GetProductByID(Database &db, int ID);
        void DisplayDetails();
        bool AddProduct(Database &db);
        bool DeleteProduct(Database& db);

    protected:

    private:
        int ProductID;
        string ProductName;
        double SellingPrice;
        double BuyingCost;
        double QuantityInStock;
};

#endif // PRODUCT_H
