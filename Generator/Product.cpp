#include "Product.h"

Product::Product(const std::string& PRODUCT_ID, const std::string& PROCESS_NAME, const int counts)
: PRODUCT_ID(PRODUCT_ID), PROCESS_NAME(PROCESS_NAME), counts(counts) {}

std::string Product::getProductId() const {
    return PRODUCT_ID;
}

std::string Product::getProcessName() const {
    return PROCESS_NAME;
}

int Product::getCounts() const {
    return counts;
}

void Product::exportToCSV(const std::string &filename, const std::vector <Product> &Products) {
    std::ofstream file(filename);

    file << "PRODUCT_ID,PROCESS_NAME,COUNTS\n";

    for(const auto& Product:Products) {
        file << Product.getProductId() << ","
             << Product.getProcessName() << ","
             << Product.getCounts() << "\n";
    }

    file.close();
}
