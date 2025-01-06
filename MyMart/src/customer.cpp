#include "customer.h"

Customer::Customer(string x, int n) : CustomerName(x), CustomerID(n), TotalAmountSpent(0) {}

Customer::~Customer() {}

string Customer::GetCustomerName()
{
    return CustomerName;
    }

int Customer::GetCustomerID()
{
    return CustomerID;
}

double Customer::GetTotalAmountSpent()
{
    return TotalAmountSpent;
}

void Customer::SetTotalAmountSpent(double val)
{
    TotalAmountSpent = val;
}

bool Customer::GetCustomerByID(Database& db, int ID)
{
    sqlite3_stmt* stmt = db.searchFromTable(db,ID,"CUSTOMERS");

    if (sqlite3_step(stmt) == SQLITE_ROW) {


    }
    else {
        sqlite3_finalize(stmt);
        cout << "No customer found with ID: " + to_string(ID) << endl;
        return false;
    }
    sqlite3_finalize(stmt);
    return true;
}

bool Customer::AddCustomer(Database& db)
{
    string query = "INSERT INTO CUSTOMERS VALUES(" + to_string(CustomerID) + ", '" + CustomerName + "', 'REGULAR', " + to_string(TotalAmountSpent) + ");";

    if(db.executeQuery(query))
        cout << "Customer added." << endl;
    else
        cout << "Could not add customer with ID " << CustomerID << endl;
}
