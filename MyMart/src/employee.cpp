#include "employee.h"

Employee::Employee(int n, string x, string t, double s = 0) : EmployeeID(n), EmployeeName(x), EmployeeType(t), Salary(s) {}

Employee::Employee() {}

Employee::~Employee() {}

int Employee::GetEmployeeID() { return EmployeeID; }

string Employee::GetEmployeeName() { return EmployeeName; }

double Employee::GetSalary() { return Salary; }

void Employee::SetSalary(double val) { Salary = val; }

bool Employee::AddEmployee(Database& db, int choice)
{
    if(choice == '1')
    {
        string query = "INSERT OR IGNORE INTO EMPLOYEES VALUES(" + to_string(EmployeeID) + ", '" + EmployeeName + "', 'CASHIER'," + to_string(Salary) + ", NULL, NULL);";
        return db.executeQuery(query);
    }
    else if(choice == '2')
    {
        string query = "INSERT OR IGNORE INTO EMPLOYEES VALUES(" + to_string(EmployeeID) + ", '" + EmployeeName + "', 'STOCK CLERK'," + to_string(Salary) + ", NULL, NULL);";
        return db.executeQuery(query);
    }
}

bool Employee::IsEmployeeInTable(Database& db, int ID)
{
    string query = "(SELECT * FROM EMPLOYEES)";
    sqlite3_stmt* stmt = db.searchFromTable(db, ID, query);

    int exists = 0;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        exists = sqlite3_column_int(stmt, 0);
    }

    if (exists) {
        sqlite3_finalize(stmt);
        return true;
    }
    sqlite3_finalize(stmt);
    return false;
}

bool Employee::GetEmployeeByID(Database& db, int ID)
{
    sqlite3_stmt* stmt = db.searchFromTable(db, ID, "EMPLOYEES");

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        const char* name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        double salary = sqlite3_column_double(stmt, 3);

        this->EmployeeID = id;
        this->EmployeeName = name;
        this->Salary = salary;

    }
    else {
        sqlite3_finalize(stmt);
        cerr << "No Employee found with ID: " << ID << endl;
        return false;
    }
    sqlite3_finalize(stmt);
    return true;

}

