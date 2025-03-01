#include "customer.h"

Customer::Customer(string x, int n) : CustomerName(x), CustomerID(n), TotalAmountSpent(0) {}

Customer::Customer() : TotalAmountSpent(0) {}

Customer::~Customer() {}

string Customer::GetCustomerName()
{
    return CustomerName;
}

void Customer::SetCustomerName(string name)
{
    CustomerName = name;
}
int Customer::GetCustomerID()
{
    return CustomerID;
}

void Customer::SetCustomerID(int ID)
{
    CustomerID = ID;
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
    sqlite3_stmt* stmt = db.searchFromTable(db, ID, "CUSTOMERS");

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
        cout << "No customer found with ID: " << ID << endl;
        return false;
    }

    sqlite3_finalize(stmt);
    return true;
}

bool Customer::AddCustomer(Database& db)
{
    string query = "INSERT INTO CUSTOMERS VALUES(" + to_string(CustomerID) + ", '" + CustomerName + "', 'REGULAR', " + to_string(TotalAmountSpent) + ");";

    if(!db.executeQuery(query))
        return false;

    return true;
}

bool Customer::GenerateNewID(Database& db)
{
    string query = "SELECT COUNT(*) FROM CUSTOMERS;";

    sqlite3_stmt *stmt;
    int exitCode = sqlite3_prepare_v2(db.getDatabase(), query.c_str(),-1, &stmt, NULL);

    if (exitCode != SQLITE_OK) {
        cerr << "Could not prepare statement: " << sqlite3_errmsg(db.getDatabase()) << endl;
        return false;
    }

    exitCode = sqlite3_step(stmt)
;    if (exitCode == SQLITE_ROW) {
        int totalCustomers = sqlite3_column_int(stmt, 0);

        // maximum capacity
        if (totalCustomers > 9999998)
            return false;

        // new ID is in numerical order, 1 + total number of customers
        SetCustomerID(totalCustomers + 1 + 10000000);
    }
    else {
        cerr << "Could not execute query: " << sqlite3_errmsg(db.getDatabase()) << endl;
        return false;
    }

    sqlite3_finalize(stmt);
    return true;
}


bool Customer::UpdateTotalAmountSpent(Database& db)
{
    string query = "UPDATE CUSTOMERS SET TOTAL_SPENT = " + to_string(TotalAmountSpent) + " WHERE ID = " + to_string(CustomerID) + ";";
    if(!db.executeQuery(query))
        cout << "Could not update customer's spending." << endl;
    else
        cout << "Updated customer's total spending." << endl;
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
