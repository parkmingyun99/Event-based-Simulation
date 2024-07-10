#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>
#include <vector>
#include <fstream>

class Product {
private:
    std::string productName;
    std::string route;

public:
    Product(const std::string& productName);
    Product(const std::string& productName, const std::string& route);
    virtual ~Product();
    
    std::string getProductName() const;
    std::string getRoute() const;

};

#endif // PRODUCT_H