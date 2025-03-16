#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <product.h>
#include <iostream>
#include <vector>

using namespace std;

class Customer
{
    public:
        Customer(string x, int n);
        Customer();
        virtual ~Customer();

        string GetCustomerName();
        void SetCustomerName(string name);

        int GetCustomerID();
        void SetCustomerID(int ID);

        double GetTotalAmountSpent();
        void SetTotalAmountSpent(double val);

        bool AddCustomer(Database &db);

        bool GenerateNewID(Database &db);

        virtual bool GetCustomerByID(Database &db, int ID);

        bool UpdateTotalAmountSpent(Database &db);

        bool UpdateCustomerStatus(Database &db);

        int DisplayDetails(int start_line);

    protected:

    private:
        int CustomerID;
        string CustomerName;
        double TotalAmountSpent;
};

#endif // CUSTOMER_H
