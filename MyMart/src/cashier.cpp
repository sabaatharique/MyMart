#include "cashier.h"
#include "shoppingcart.h"
Cashier::Cashier(int n, string x, double s) : Employee(n, x, "CASHIER", s) {}
Cashier::Cashier() {}
Cashier::~Cashier() {}

string Cashier::GetEmployeeType()
{
    return EmployeeType;
}

ShoppingCart Cashier::ProcessCart(Database& db)
{
    clear();
    mvhline(0, 1, ACS_HLINE, COLS-2);
    mvprintw(0, (COLS - 6) / 2, "MyMart");
    refresh();

    ShoppingCart cart;

    //string hold1 = "", hold2 = "", hold3 = "", hold4 = "";

    char temp[200];
    string productID;
    double quantity;

    mvwprintw(stdscr, 2, 2, "Scan product ID, enter -1 to end process:");


    while(1){
        string hold1 = "", hold2 = "", hold3 = "", hold4 = "";
        hold1 = "Enter ID to scan: ";
        mvwprintw(stdscr, 3, 2, hold1.c_str());
        curs_set(1);
        echo();

        move(3, 2 + hold1.size());
        clrtoeol();
        getnstr(temp, sizeof(temp) - 1);
        productID = string(temp);
        curs_set(0);
        noecho();

        if(productID == "-1")
            break;

        // first digit 1 indicates regular product, 21 indicates perishable but bought in kg and 22 indicates perishable but bought in unit
        if (productID[0] == '1') {
            Product *product = new Product();
            if(!product->GetProductByID(db, stoi(productID))){
                mvwprintw(stdscr, 4, 2, "Could not add product to cart, press enter to continue");
                delete product;

                while(true) {
                    int ch = getch();
                    if(ch == '\n') break;
                }
                move(4, 2);
                clrtoeol();
                move(3, 2);
                clrtoeol();
                continue;
            }

            if(product->GetQuantityInStock() == 0) {
                mvwprintw(stdscr, 4, 2, "product out of stock, press enter to buy a different one");
                delete product;

                while(true) {
                    int ch = getch();
                    if(ch == '\n') break;
                }
                move(4, 2);
                clrtoeol();
                move(3, 2);
                clrtoeol();
                continue;
            }

            int next_line = product->DisplayDetails(4);

            hold2 = "Enter number of item purchased: ";
            mvwprintw(stdscr, next_line, 2, hold2.c_str());
            curs_set(1);
            echo();

            move(next_line, 2 + hold2.size());
            clrtoeol();
            getnstr(temp, sizeof(temp) - 1);
            quantity = stod(string(temp));

            while(true) {
                if(quantity > product->GetQuantityInStock()) {
                    hold2 = "Not enough product in stock, try again: ";
                    mvwprintw(stdscr, next_line, 2, hold2.c_str());
                    move(next_line, 2 + hold2.size());
                    clrtoeol();
                    getnstr(temp, sizeof(temp) - 1);
                    quantity = stod(string(temp));
                }
                else if(floor(quantity) != quantity || quantity <= 0) {
                    hold2 = "Input invalid, try again: ";
                    mvwprintw(stdscr, next_line, 2, hold2.c_str());
                    move(next_line, 2 + hold2.size());
                    clrtoeol();
                    getnstr(temp, sizeof(temp) - 1);
                    quantity = stod(string(temp));
                }
                else
                    break;
            }

            cart.AddToCart(db, product, quantity);

            hold3 += to_string(quantity);
            if(quantity < 10) {
                hold3 += " unit of ";
            }
            else {
                hold3 += " units of ";
            }
            hold3 += product->GetProductName();
            hold3 += " added to cart.";

            mvwprintw(stdscr, next_line + 1, 2, hold3.c_str());

            mvwprintw(stdscr, next_line + 2, 2, "Press enter to add more!");

            while(true) {
                int ch = getch();
                if(ch == '\n') break;
            }
            move(next_line + 2, 2);
            clrtoeol();
            move(next_line + 1, 2);
            clrtoeol();
            move(next_line, 2);
            clrtoeol();
            for(int i=0; i<5; i++) {
                move(next_line - i - 1, 2);
                clrtoeol();
            }
            move(4, 2);
            clrtoeol();
            move(3, 2);
            clrtoeol();
        }
        // even number indicates perishable product
        else {
            PerishableProducts *perishableProduct = new PerishableProducts();
            if(!perishableProduct->GetProductByID(db, stoi(productID))){
                mvwprintw(stdscr, 4, 2, "Could not add perishable product to cart, press enter to continue");
                delete perishableProduct;

                while(true) {
                    int ch = getch();
                    if(ch == '\n') break;
                }
                move(4, 2);
                clrtoeol();
                move(3, 2);
                clrtoeol();
                continue;
            }

            if(perishableProduct->GetQuantityInStock() == 0) {
                mvwprintw(stdscr, 4, 2, "product out of stock, press enter to buy a different one");
                delete perishableProduct;

                while(true) {
                    int ch = getch();
                    if(ch == '\n') break;
                }
                move(4, 2);
                clrtoeol();
                move(3, 2);
                clrtoeol();
                continue;
            }

            // check if expired
            Date today;
            today.GetTodaysDate();
            if (*perishableProduct < today){
                mvwprintw(stdscr, 4, 2, "Product expired, press enter to continue");
                delete perishableProduct;

                while(true) {
                    int ch = getch();
                    if(ch == '\n') break;
                }
                move(4, 2);
                clrtoeol();
                move(3, 2);
                clrtoeol();
                continue;
            }

            int next_line = perishableProduct->DisplayDetails(4);

            hold2 += "Enter ";
            if(productID[1] == '1') {
                hold2 += "kilograms";
            }
            else {
                hold2 += "number";
            }
            hold2 += " of item purchased: ";
            mvwprintw(stdscr, next_line, 2, hold2.c_str());
            curs_set(1);
            echo();

            move(next_line, 2 + hold2.size());
            clrtoeol();
            getnstr(temp, sizeof(temp) - 1);
            quantity = stod(string(temp));

            while(true) {
                if(quantity > perishableProduct->GetQuantityInStock()) {
                    hold2 = "Not enough product in stock, try again: ";
                    mvwprintw(stdscr, next_line, 2, hold2.c_str());
                    move(next_line, 2 + hold2.size());
                    clrtoeol();
                    getnstr(temp, sizeof(temp) - 1);
                    quantity = stod(string(temp));
                }
                else if((productID[1] == '2' && floor(quantity) != quantity) || quantity <= 0) {
                    hold2 = "Input invalid, try again: ";
                    mvwprintw(stdscr, next_line, 2, hold2.c_str());
                    move(next_line, 2 + hold2.size());
                    clrtoeol();
                    getnstr(temp, sizeof(temp) - 1);
                    quantity = stod(string(temp));
                }
                else
                    break;
            }


            cart.AddToCart(db, perishableProduct, quantity);
            //cout << quantity << ((productID[1] == '1') ? "kg of " : " ") << perishableProduct->GetProductName() << " added to cart." << endl;

            hold3 += to_string(quantity);

            if(productID[1] == '1') {
                if(quantity < 10) {
                    hold3 += " kg of ";
                }
                else {
                    hold3 += " kgs of ";
                }
            }
            else {
                if(quantity < 10) {
                    hold3 += " unit of ";
                }
                else {
                    hold3 += " units of ";
                }
            }

            hold3 += perishableProduct->GetProductName();
            hold3 += " added to cart.";

            mvwprintw(stdscr, next_line + 1, 2, hold3.c_str());

            mvwprintw(stdscr, next_line + 2, 2, "Press enter to add more!");

            while(true) {
                int ch = getch();
                if(ch == '\n') break;
            }
            move(next_line + 2, 2);
            clrtoeol();
            move(next_line + 1, 2);
            clrtoeol();
            move(next_line, 2);
            clrtoeol();
            for(int i=0; i<6; i++) {
                move(next_line - i - 1, 2);
                clrtoeol();
            }
            move(4, 2);
            clrtoeol();
            move(3, 2);
            clrtoeol();
        }
    }
    curs_set(0);
    noecho();
    return cart;
}

void Cashier::MakeReceipt(ShoppingCart& shoppingCart, Customer *customer)
{
    clear();
    mvhline(0, 1, ACS_HLINE, COLS-2);
    mvprintw(0, (COLS - 6) / 2, "MyMart");
    refresh();

    unordered_map<int, pair<Product*, double>> cart = shoppingCart.GetCart();
    double totalBill = shoppingCart.GetTotalBill();

    int row = 2; // Start row position for printing
    int col = 5; // Start column position

    mvwprintw(stdscr, row++, col, "%s RECEIPT %s", std::string(30, '-').c_str(), std::string(30, '-').c_str());
    row++; // Move down for better spacing

    mvwprintw(stdscr, row, col, "%-7s %-27s %-7s %-8s %-10s %-10s", "No.", "Product Name", "ID", "Qty", "Price", "Subtotal");
    row++;
    mvwprintw(stdscr, row++, col, "%s", std::string(69, '-').c_str());

    int i = 1;
    for (auto& prod : cart) {
        Product* product = prod.second.first;
        double quantity = prod.second.second;

        if (product == NULL) {
            mvwprintw(stdscr, row++, col, "%d. Invalid product in cart.", i++);
            continue;
        }

        mvwprintw(stdscr, row++, col, "%-7d %-27s %-7d %-8.2f %-10.2f %-10.2f",
                  i++,
                  product->GetProductName().c_str(),
                  product->GetProductID(),
                  quantity,
                  product->GetSellingPrice(),
                  quantity * product->GetSellingPrice());
    }

    mvwprintw(stdscr, row++, col, "%s", std::string(69, '-').c_str());
    mvwprintw(stdscr, row++, col, "%-50s %-19.2f", "Amount: ", totalBill);

    // Handle loyal customer discount
    LoyalCustomer* loyalCustomer = dynamic_cast<LoyalCustomer*>(customer);
    if (loyalCustomer) {
        double discountAmount = totalBill * loyalCustomer->CalculateDiscount();
        double netAmount = totalBill - discountAmount;

        mvwprintw(stdscr, row++, col, "%-50s %-18.2f%%", "Discount: ", loyalCustomer->CalculateDiscount() * 100);
        mvwprintw(stdscr, row++, col, "%-50s %-19.2f", "Net Amount: ", netAmount);

        // Update manager profit
        double cur_profit = Manager::GetProfit();
        Manager::SetProfit(cur_profit - discountAmount);
    }

    mvwprintw(stdscr, row++, col, "%s", std::string(69, '-').c_str());

    // Display prompt for user input
    row += 2; // Move down a bit for better spacing
    mvwprintw(stdscr, row++, col, "Press Enter to continue");
    wrefresh(stdscr); // Refresh the window to show output

    // Wait for the user to press Enter
    while(true) {
        int ch = getch();
        if(ch == '\n') break;
    }
}

Customer* Cashier::OpenCustomerAccount(Database& db)
{
    string hold1 = "", hold2 = "";
    char temp[200];

    mvwprintw(stdscr, 2, 2, "Open customer account: ");
    mvwprintw(stdscr, 3, 2, "1. Enter existing ID");
    mvwprintw(stdscr, 4, 2, "2. Create new customer ID");
    //cout << "Open customer account: " << endl;

    int choice;
    // loop while input is incorrect
    do {
        //cout << "1. Enter existing ID" << endl << "2. Create new customer ID" << endl;
        choice = getch();
    } while (choice != '1' && choice != '2');

    if(choice == '1') {
        attron(A_REVERSE);
        mvwprintw(stdscr, 3, 2, "1. Enter existing ID");
        attroff(A_REVERSE);
    }
    else if(choice == '2') {
        attron(A_REVERSE);
        mvwprintw(stdscr, 4, 2, "2. Create new customer ID");
        attroff(A_REVERSE);
    }

    // if customer already exists, search database
    if (choice == '1') {
        string customerID;
        hold1 = "Enter customer ID: ";
        while(1){

            mvwprintw(stdscr, 6, 2, hold1.c_str());

            curs_set(1);
            echo();
            move(6, 2 + hold1.size());
            clrtoeol();
            getnstr(temp, sizeof(temp) - 1);
            customerID = string(temp);

            if(customerID[0] == '1'){
                Customer *customer = new Customer();

                if(customer->GetCustomerByID(db, stoi(customerID))){
                    int next_line = customer->DisplayDetails(7);

                    curs_set(0);
                    noecho();

                    mvprintw(next_line + 1, 2, "Press enter to process cart!");
                    refresh();

                    while(true) {
                        int ch = getch();
                        if(ch == '\n') break;
                    }

                    return customer;
                }
                // if no customer with id found, loop
            }
            else if(customerID[0] == '2') {
                LoyalCustomer *loyalCustomer = new LoyalCustomer();

                if(loyalCustomer->GetCustomerByID(db, stoi(customerID))){
                    int next_line = loyalCustomer->DisplayDetails(7);

                    curs_set(0);
                    noecho();

                    mvprintw(next_line, 2, "Press enter to process cart!");
                    refresh();

                    while(true) {
                        int ch = getch();
                        if(ch == '\n') break;
                    }

                    return loyalCustomer;
                }
                // if no loyal customer with id found, loop
            }
            hold1 = "ID not found! please give a existing id: ";
        }

    }
    // if new customer, create account
    else if (choice == '2') {
        Customer *customer = new Customer();

        if (!customer->GenerateNewID(db))
            return NULL;


        hold2 = "Enter customer name: ";
        mvwprintw(stdscr, 6, 2, hold2.c_str());

        curs_set(1);
        echo();
        move(6, 2 + hold2.size());
        clrtoeol();
        getnstr(temp, sizeof(temp) - 1);

        string name(temp);

        customer->SetCustomerName(name);

        // see aforementioned ???
        if (!customer->AddCustomer(db))
            return NULL;

        int next_line = customer->DisplayDetails(7);
        curs_set(0);
        noecho();

        mvprintw(next_line, 2, "Press enter to process cart!");
        refresh();

        while(true) {
            int ch = getch();
            if(ch == '\n') break;
        }
        return customer;
    }

    return NULL;
}


void Cashier::CheckoutCustomer(Database& db)
{
    // find customer's account
    Customer *customer = OpenCustomerAccount(db);

    while (customer == NULL)
    {
        customer = OpenCustomerAccount(db);
    }

    // scan customer's cart
    ShoppingCart cart = ProcessCart(db);

    GiveFeedback(customer);
    // create receipt for customer
    MakeReceipt(cart, customer);

    // update customer's total spending, add current bill
    customer->SetTotalAmountSpent(customer->GetTotalAmountSpent() + cart.GetTotalBill());
    customer->UpdateTotalAmountSpent(db);

    // check if customer is eligible to become a loyalty member
    customer->UpdateCustomerStatus(db);

    delete customer;
}

void Cashier::GiveFeedback(Customer* customer)
{
    clear();
    mvhline(0, 1, ACS_HLINE, COLS-2);
    mvprintw(0, (COLS - 6) / 2, "MyMart");
    refresh();

    char temp[100];
    string feedback, hold = "";
    int id = customer->GetCustomerID();
    hold = "Enter Feedback: ";
    mvwprintw(stdscr, 1, 2, hold.c_str());
    curs_set(1);
    echo();

    move(1, 2 + hold.size());
    clrtoeol();
    getnstr(temp, sizeof(temp) - 1);
    feedback = string(temp);
    ofstream outfile("Feedback.txt", ios:: app);
    outfile  << id << ": " << feedback << '\n';

    outfile.close();

    curs_set(0);
    noecho();

    mvprintw(3, 2, "Feedback added! press enter to continue");

    while(true) {
        int ch = getch();
        if(ch == '\n') break;
    }
    move(3, 2);
    clrtoeol();
    move(1, 2);
    clrtoeol();
}
