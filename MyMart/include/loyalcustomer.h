#ifndef LOYALCUSTOMER_H
#define LOYALCUSTOMER_H

#include <customer.h>


class LoyalCustomer : public Customer
{
    public:
        LoyalCustomer(string x, int n);
        LoyalCustomer();
        virtual ~LoyalCustomer();

    protected:

    private:
        double DiscountPercentage;

};

#endif // LOYALCUSTOMER_H
