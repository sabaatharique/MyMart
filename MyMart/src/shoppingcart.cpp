#include "shoppingcart.h"

ShoppingCart::ShoppingCart() : TotalBill(0.0) {}

ShoppingCart::~ShoppingCart() {}

const vector<pair<Product*, double>>& ShoppingCart::GetCart()
{
    return Cart;
}

void ShoppingCart::AddToCart(Database& db, Product* p, double quantity)
{
    pair<Product*, double> product(p, quantity);
    Cart.push_back(product);

    p->SetQuantityInStock(p->GetQuantityInStock() - quantity);

    string sql = "UPDATE PRODUCTS "
                 "SET IN_STOCK = " + to_string(p->GetQuantityInStock()) + " "
                 "WHERE ID = " + to_string(p->GetProductID()) + ";";
    db.executeQuery(sql);

    TotalBill += quantity * p->GetSellingPrice();
}

double ShoppingCart::GetTotalBill()
{
    return TotalBill;
}

