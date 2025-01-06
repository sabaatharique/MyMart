#include "cashier.h"

Cashier::Cashier(int n, string x, double s) : Employee(n, x, s) {}

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

double Cashier::MakeReceipt(ShoppingCart& shoppingCart)
{
    unordered_map<int, pair<Product*, double>> cart = shoppingCart.GetCart();
    double totalBill = shoppingCart.GetTotalBill();

    cout << string(30, '-') << " RECEIPT " << string(30, '-') << endl;
    cout << setw(7) << "No.";
    cout << setw(27) << "Product Name";
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
    cout << setw(59) << "Total: " << totalBill << endl;
    cout << string(69, '-') << endl;

    return totalBill;
}









