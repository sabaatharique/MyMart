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

    int productID;
    double quantity;
    cout << "Scan product ID, enter -1 to end process." << endl;

    while(1){
        cout << "Enter ID to scan: " << endl;
        cin >> productID;
        if(productID < 0)
            break;

        // odd ID numbers indicate regular product, even indicates perishable
        if (productID % 2) {
            Product *product = new Product();
            if(!product->GetProductByID(db, productID)){
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
            if(!perishableProduct->GetProductByID(db, productID)){
                cout << "Could not add product to cart." << endl;
                delete perishableProduct;
                continue;
            }

            perishableProduct->DisplayDetails();

            // check if expired
            Date today;
            today.GetTodaysDate();
            cout << today.ToString() << endl;
            if (*perishableProduct < today){
                cout << "Product expired, please refer to stock clerk." << endl;
                continue;
            }
            if (perishableProduct->GetQuantityInStock() == 0){
                cout << "Product out of stock, please refer to stock clerk." << endl;
                delete perishableProduct;
                continue;
            }

            // loop until valid input given
            cout << "Enter kilograms of item purchased: " << endl;
            while(1)
            {
                cin >> quantity;

                if(quantity <= 0)
                    cout << "Input invalid, try again." << endl;
                else if (quantity > perishableProduct->GetQuantityInStock())
                    cout << "Not enough product in stock." << endl;
                else
                    break;
            }

            cart.AddToCart(db, perishableProduct, quantity);
            cout << quantity << "kg of " << perishableProduct->GetProductName() << " added to cart." << endl;
        }
    }
    return cart;
}

double Cashier::MakeReceipt(ShoppingCart& shoppingCart)
{
    unordered_map<int, pair<Product*, double>> cart = shoppingCart.GetCart();
    double totalBill = shoppingCart.GetTotalBill();

    cout << string(25, '-') << " RECEIPT " << string(25, '-') << endl;
    cout << "No.  Product Name     Qty     Price     Subtotal" << endl;
    cout << string(59, '-') << endl;

    int i = 1;
    for (auto &prod : cart) {
        Product* product = prod.second.first; // Get the product pointer
        double quantity = prod.second.second; // Get the quantity

        if (product == nullptr) {
            cout << i + 1 << ". Invalid product in cart!" << endl;
            continue;
        }

        // Print base class details
        cout << i + 1 << ".   "
             << product->GetProductName() << "   "
             << quantity << "   "
             << product->GetSellingPrice() << "   "
             << quantity * product->GetSellingPrice() << endl;
    }

    cout << string(59, '-') << endl;
    cout << "Total Bill: " << totalBill << endl;
    cout << string(59, '-') << endl;

    return totalBill;
}









