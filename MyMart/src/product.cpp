#include "product.h"

Product::Product(int n, string x, double p, double c, int s) : ProductID(n), ProductName(x), SellingPrice(p), BuyingCost(c), QuantityInStock(s) {}

Product::~Product() {}

int Product::GetProductID() { return ProductID; }

string Product::GetProductName() { return ProductName; }

double Product::GetSellingPrice() { return SellingPrice; }

void Product::SetSellingPrice(double val) { SellingPrice = val; }

double Product::GetBuyingCost() { return BuyingCost; }

void Product::SetBuyingCost(double val) { BuyingCost = val; }

int Product::GetQuantityInStock() { return QuantityInStock; }

void Product::SetQuantityInStock(int val) { QuantityInStock = val; }

