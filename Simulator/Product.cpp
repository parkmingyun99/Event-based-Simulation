#include "Product.h"

// 생성자 구현
Product::Product(const std::string& productName, const std::string& route) 
    : productName(productName), route(route) {}

// 생성자 구현
Product::Product(const std::string& productName) 
    : productName(productName) {}

// 소멸자 구현
Product::~Product() {
}

// productName 반환
std::string Product::getProductName() const {
    return productName;
}

// route 반환
std::string Product::getRoute() const {
    return route;
}
