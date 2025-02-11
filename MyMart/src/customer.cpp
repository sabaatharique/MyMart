#include "customer.h"

Customer::Customer(string x, int n) : CustomerName(x), CustomerID(n), TotalAmountSpent(0) {}

Customer::Customer() {}

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
        int id = sqlite3_column_int(stmt, 0);
        const char* name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        double total_spent = sqlite3_column_double(stmt, 3);

        this->CustomerID = id;
        this->CustomerName = name;
        this->TotalAmountSpent = total_spent;
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

bool Customer::UpdateTotalAmountSpent(Database& db)
{
    string query = "UPDATE CUSTOMERS SET TOTAL_SPENT = " + to_string(TotalAmountSpent) + " WHERE ID = " + to_string(CustomerID) + ";";
    if(!db.executeQuery(query))
        cout << "Could not update customers spending." << endl;
    else
        cout << "Updated customers total spending." << endl;
}

bool Customer::UpdateCustomerStatus(Database& db)
{
    string query = "UPDATE CUSTOMERS SET TYPE = 'LOYAL' WHERE ID = " + to_string(CustomerID) + ";";
    if(!db.executeQuery(query))
        cout << "Could not update customer status." << endl;
    else
        cout << "Updated customer status." << endl;
}

void Customer::DisplayDetails()
{
    cout << "Customer ID: " << CustomerID << endl;
    cout << "Customer name: " << CustomerName << endl;
    cout << "Total Amount Spent: " << TotalAmountSpent << endl;
}
