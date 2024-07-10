#ifndef GENERATOR_H
#define GENERATOR_H

#include <string>
#include <vector>
#include <queue>
#include "EoModel.h"
#include "Product.h"
#include "Machine.h"
#include "Storage.h"

class Generator : public EoModel {
private:
    int numTotalProduct1;
    int numTotalProduct2;
    int numGenProduct;
    std::vector<Machine> machines;
    std::vector<Product> products;
    Storage storage;
    std::vector<std::vector<int>> my2DArray;
    std::queue<Product> productQueue;

public:
    Generator();
    void handle(void* message) override;
    void initialize() override;
};

#endif // GENERATOR_H
