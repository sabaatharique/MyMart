#ifndef PRODUCT_H
#define PRODUCT_H

#include <iostream>
#include <database.h>

using namespace std;

enum Table {
    Expired,
    OutOfStock,
    All
};

class Product
{
    public:
        Product();
        Product(int n, string x, double p, double c, double s);
        virtual ~Product();

        int GetProductID() const;
        void SetProductID(int n);

        string GetProductName() const;
        void SetProductName(string x);

        double GetSellingPrice() const;
        void SetSellingPrice(double p);

        double GetBuyingCost() const;
        void SetBuyingCost(double c);

        double GetQuantityInStock() const;
        void SetQuantityInStock(double s);

        virtual bool GetProductByID(Database &db, int ID);
        virtual void DisplayDetails();
        virtual bool AddProduct(Database &db);
        static bool IsProductInTable(Database& db, int ID, Table tbl);

    protected:

    private:
        int ProductID;
        string ProductName;
        double SellingPrice;
        double BuyingCost;
        double QuantityInStock;
};

#endif // PRODUCT_H
