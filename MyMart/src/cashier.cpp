#include "cashier.h"
#include "shoppingcart.h"
Cashier::Cashier(int n, string x, double s) : Employee(n, x, s) {}
Cashier::Cashier() {}
Cashier::~Cashier() {}

void Cashier::GetEmployeeType()
{
    cout << "Employee: Cashier" << endl;
}

ShoppingCart Cashier::ProcessCart(Database& db)
{
    ShoppingCart cart;

    string productID;
    double quantity;
    cout << "Scan product ID, enter -1 to end process." << endl;

    while(1){
        cout << "Enter ID to scan: " << endl;
        cin >> productID;
        if(productID == "-1")
            break;

        // first digit 1 indicates regular product, 21 indicates perishable but bought in kg and 22 indicates perishable but bought in unit
        if (productID[0] == '1') {
            Product *product = new Product();
            if(!product->GetProductByID(db, stoi(productID))){
                cout << "Could not add product to cart." << endl;
                delete product;
                continue;
            }

            product->DisplayDetails();

            if (product->GetQuantityInStock() == 0){
                cout << "Product out of stock, please refer to stock clerk." << endl;
                delete product;
                continue;
            }

            cout << "Enter number of item purchased: " << endl;
            while(1)
            {
                cin >> quantity;

                if(floor(quantity) != quantity || quantity <= 0)
                    cout << "Input invalid, try again." << endl;
                else if (quantity > product->GetQuantityInStock())
                    cout << "Not enough product in stock." << endl;
                else
                    break;
            }

            cout << quantity << " " << product->GetProductName() << " added to cart." << endl;
            cart.AddToCart(db, product, quantity);
        }
        // even number indicates perishable product
        else {
            PerishableProducts *perishableProduct = new PerishableProducts();
            if(!perishableProduct->GetProductByID(db, stoi(productID))){
                cout << "Could not add product to cart." << endl;
                delete perishableProduct;
                continue;
            }

            perishableProduct->DisplayDetails();

            // check if expired
            Date today;
            today.GetTodaysDate();
            if (*perishableProduct < today){
                cout << "Product expired, please refer to stock clerk." << endl;
                continue;
            }
            if (perishableProduct->GetQuantityInStock() == 0){
                cout << "Product out of stock, please refer to stock clerk." << endl;
                delete perishableProduct;
                continue;
            }

            // for perishable products
            cout << "Enter " << ((productID[1] == '1') ? "kilograms" : "number") << " of item purchased: " << endl;

            // loop until valid input given
            while(1)
            {
                cin >> quantity;

                if(quantity <= 0 || (productID[1] == '2' && floor(quantity) != quantity))
                    cout << "Input invalid, try again." << endl;
                else if (quantity > perishableProduct->GetQuantityInStock())
                    cout << "Not enough product in stock." << endl;
                else
                    break;
            }

            cart.AddToCart(db, perishableProduct, quantity);
            cout << quantity << ((productID[1] == '1') ? "kg of " : " ") << perishableProduct->GetProductName() << " added to cart." << endl;
        }
    }
    return cart;
}

void Cashier::MakeReceipt(ShoppingCart& shoppingCart, Customer *customer)
{
    unordered_map<int, pair<Product*, double>> cart = shoppingCart.GetCart();
    double totalBill = shoppingCart.GetTotalBill();

    cout << string(30, '-') << " RECEIPT " << string(30, '-') << endl;
    cout << setw(7) << "No.";
    cout << setw(27) << "Product name";
    cout << setw(7) << "ID";
    cout << setw(8) << "Qty";
    cout << setw(10) << "Price";
    cout << setw(10) << "Subtotal" << endl;
    cout << string(69, '-') << endl;

    int i = 1;
    for (auto &prod : cart) {
        Product* product = prod.second.first;
        double quantity = prod.second.second;

        if (product == NULL) {
            cout << i++ << ". Invalid product in cart." << endl;
            continue;
        }

            cout << setw(7) << i++;
            cout << setw(27) << product->GetProductName();
            cout << setw(7) << product->GetProductID();
            cout << setw(8) << quantity;
            cout << setw(10) << product->GetSellingPrice();
            cout << setw(10) << quantity * product->GetSellingPrice() << endl;
    }

    cout << string(69, '-') << endl;
    cout << setw(50) << "Amount: " << setw(19) << totalBill << endl;

    // add discount for loyal customers only
    LoyalCustomer* loyalCustomer = dynamic_cast<LoyalCustomer*>(customer);
    if (loyalCustomer) {
        double discountAmount = totalBill * loyalCustomer->CalculateDiscount();
        double netAmount = totalBill - discountAmount;

        cout << setw(50) << "Discount: " << setw(18) << loyalCustomer->CalculateDiscount() * 100 << "%" << endl;
        cout << setw(50) << "Net amount: " << setw(19) << netAmount << endl;

        double cur_profit = Manager::GetProfit();
        double loss = discountAmount;
        Manager::SetProfit(cur_profit-loss);
    }

    cout << string(69, '-') << endl;
}

Customer* Cashier::OpenCustomerAccount(Database& db)
{
    cout << "Open customer account: " << endl;

    bool first = true;
    int choice;
    // loop while input is incorrect
    do {
        if (!first)
            cout << "Invalid input, try again." << endl;

        cout << "1. Enter existing ID" << endl << "2. Create new customer ID" << endl;
        cin >> choice;
        first = false;
    } while (choice < 1 || choice > 2);

    // if customer already exists, search database
    if (choice == 1) {
        string customerID;
        while(1){
            cout << "Enter customer ID: " << endl;
            cin >> customerID;

            if(customerID[0] == '1'){
                Customer *customer = new Customer();

                if(customer->GetCustomerByID(db, stoi(customerID))){
                    customer->DisplayDetails();
                    return customer;
                }
                // if no customer with id found, loop
            }
            else if(customerID[0] == '2') {
                LoyalCustomer *loyalCustomer = new LoyalCustomer();

                if(loyalCustomer->GetCustomerByID(db, stoi(customerID))){
                    loyalCustomer->DisplayDetails();
                    return loyalCustomer;
                }
                // if no loyal customer with id found, loop
            }
        }

    }
    // if new customer, create account
    else if (choice == 2) {
        Customer *customer = new Customer();

        if (!customer->GenerateNewID(db)) {
            cout << "Could not create new customer ID. Try again." << endl;
            return NULL;
        }

        string name;
        cout << "Enter customer name: " << endl;
        cin.ignore();
        getline(cin, name);
        customer->SetCustomerName(name);

        // see aforementioned ???
        if (!customer->AddCustomer(db))
            cout << "Could not add customer to database." << endl;

        customer->DisplayDetails();

        return customer;
    }

    return NULL;
}


void Cashier::CheckoutCustomer(Database& db)
{
    // find customer's account
    int choice;
    Customer *customer = OpenCustomerAccount(db);

    while (customer == NULL)
    {
        cout << "Customer login failed:" << endl <<
        "1. Retry" << endl <<
        "2. Continue to checkout" << endl;
        cin >> choice;

        if(choice == 1)
            customer = OpenCustomerAccount(db);
        else if (choice == 2)
            break;
        else
            cout << "Invalid input, try again." << endl;
    }

    // scan customer's cart
    ShoppingCart cart = ProcessCart(db);

    // create receipt for customer
    MakeReceipt(cart, customer);

    // update customer's total spending, add current bill
    customer->SetTotalAmountSpent(customer->GetTotalAmountSpent() + cart.GetTotalBill());
    customer->UpdateTotalAmountSpent(db);

    // check if customer is eligible to become a loyalty member
    customer->UpdateCustomerStatus(db);

    delete customer;
}

void Cashier::GiveFeedback()
{
    string feedback;
    cout << "Enter Feedback: " << endl;
    cin.ignore();
    getline(cin, feedback);
    cout << "Customer feedback: " << feedback << endl;
}
