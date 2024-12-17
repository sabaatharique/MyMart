#include "cashier.h"

Cashier::Cashier(int n, string x, double s) : Employee(n, x, s) {}

Cashier::~Cashier() {}

void Cashier::GetEmployeeType()
{
    cout << "Employee: Cashier" << endl;
}

ShoppingCart& Cashier::ProcessCart(Database& db)
{
    ShoppingCart cart;

    int productID = 0;
    double quantity = 0;
    cout << "Scan product ID, enter -1 to end process." << endl;

    while(1){
        cout << "Enter ID to scan: " << endl;
        cin >> productID;
        if(productID == -1)
            break;

        // odd ID numbers indicate regular product, even indicates perishable
        if (productID % 2) {
            Product product;
            if(!product.GetProductByID(db, productID)){
                cout << "Could not add product to cart." << endl;
                continue;
            }

            product.DisplayDetails();

            cout << "Enter number of item purchased: " << endl;
            while(1)
            {
                cin >> quantity;

                if(floor(quantity) != quantity || quantity <= 0)
                    cout << "Input invalid, try again." << endl;
                else if (quantity > product.GetQuantityInStock())
                    cout << "Not enough product in stock." << endl;
                else
                    break;
            }

            cout << quantity << " " << product.GetProductName() << " added to cart." << endl;
            cart.AddToCart(db, &product, quantity);
        }
        // even number indicated perishable product
        else {
            PerishableProducts perishableProduct;
            if(!perishableProduct.GetProductByID(db, productID)){
                cout << "Could not add product to cart." << endl;
                continue;
            }

            perishableProduct.DisplayDetails();

            // check if expired
            Date today;
            today.GetTodaysDate();
            if (perishableProduct > today){
                cout << "Product expired, please refer to stock clerk." << endl;
                continue;
            }

            // loop until valid input given
            cout << "Enter kilograms of item purchased: " << endl;
            while(1)
            {
                cin >> quantity;

                if(quantity <= 0)
                    cout << "Input invalid, try again." << endl;
                else if (quantity > perishableProduct.GetQuantityInStock())
                    cout << "Not enough product in stock." << endl;
                else
                    break;
            }

            cart.AddToCart(db, &perishableProduct, quantity);
            cout << quantity << "kg of " << perishableProduct.GetProductName() << " added to cart." << endl;
        }
    }
    return cart;
}

double Cashier::MakeReceipt(ShoppingCart& shoppingCart)
{
    map<Product*, double> cart = shoppingCart.GetCart();
    int i = 1;
    for(auto &product : cart){
        cout << product.first->GetProductName() << endl;
    }
}






