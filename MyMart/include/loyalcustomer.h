#ifndef LOYALCUSTOMER_H
#define LOYALCUSTOMER_H

#include <customer.h>


class LoyalCustomer : public Customer
{
    public:
        LoyalCustomer(string x, int n);
        LoyalCustomer();
        ~LoyalCustomer();

        double CalculateDiscount();

    protected:

    private:

};

#endif // LOYALCUSTOMER_H
