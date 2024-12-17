#include "shoppingcart.h"

ShoppingCart::ShoppingCart() : TotalBill(0.0) {}

ShoppingCart::~ShoppingCart() {}

map<Product*, double> ShoppingCart::GetCart()
{
    return Cart;
}

void ShoppingCart::AddToCart(Database& db, Product* p, double quantity)
{
    Cart[p] += quantity;

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

