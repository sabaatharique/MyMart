#include "shoppingcart.h"

ShoppingCart::ShoppingCart() : TotalBill(0.0) {}

ShoppingCart::~ShoppingCart() {}

const unordered_map<int, pair<Product*, double>>& ShoppingCart::GetCart()
{
    return Cart;
}

void ShoppingCart::AddToCart(Database& db, Product* p, double quantity)
{
    p->SetQuantityInStock(p->GetQuantityInStock() - quantity);

    string sql = "UPDATE PRODUCTS "
                 "SET IN_STOCK = " + to_string(p->GetQuantityInStock()) + " "
                 "WHERE ID = " + to_string(p->GetProductID()) + ";";
    db.executeQuery(sql);

    Cart[p->GetProductID()].first = p;
    Cart[p->GetProductID()].second += quantity;

    TotalBill += quantity * p->GetSellingPrice();

    double cur_profit = Manager::GetProfit();
    double TotalGain = quantity * (p->GetSellingPrice() - p->GetBuyingCost());
    Manager::SetProfit(cur_profit+TotalGain);
}

double ShoppingCart::GetTotalBill()
{
    return TotalBill;
}

