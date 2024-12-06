#ifndef PERISHABLEPRODUCTS_H
#define PERISHABLEPRODUCTS_H

#include <product.h>
#include <iostream>

using namespace std;

enum Months {
    january,
    february,
    march,
    april,
    may,
    june,
    july,
    august,
    september,
    october,
    november,
    december
};

struct Date {
    int day;
    Months month;
    int year;
};

class PerishableProducts : public Product
{
    public:
        PerishableProducts();
        PerishableProducts(int n, string x, double p, double c, int s, Date e);
        ~PerishableProducts();

        Date GetExpiryDate();
        void SetExpiryDate(Date val);

        bool operator>(Date today);

        PerishableProducts GetProductByID(Database &db, int ID);
        void DisplayDetails();
        bool AddProduct(Database & db);

    protected:

    private:
        Date ExpiryDate;
};

#endif // PERISHABLEPRODUCTS_H
