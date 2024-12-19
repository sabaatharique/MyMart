#ifndef PERISHABLEPRODUCTS_H
#define PERISHABLEPRODUCTS_H

#include <product.h>
#include <Date.h>
#include <iostream>

using namespace std;

class PerishableProducts : public Product
{
    public:
        PerishableProducts();
        PerishableProducts(int n, string x, double p, double c, double s, const char* e);
        ~PerishableProducts();

        Date GetExpiryDate();
        void SetExpiryDate(Date val);

        bool operator>(Date today);

        bool GetProductByID(Database &db, int ID) override;
        void DisplayDetails()override;
        bool AddProduct(Database &db) override;

    protected:

    private:
        Date ExpiryDate;
};

#endif // PERISHABLEPRODUCTS_H
