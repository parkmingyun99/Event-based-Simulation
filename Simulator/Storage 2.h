#ifndef STORAGE_H
#define STORAGE_H

#include <string>
#include <unordered_map>
#include "EoModel.h"
#include "Position.h"


class Storage : public EoModel {
private:
    static std::unordered_map<std::string, int> inventory;
    static Position position;

public:
    Storage();
    void addInventory(const std::string& component, int quantity = 1);
    int getInventoryQuantity(const std::string& component) const;
    void handle(void* message) override;
    void initialize() override;
    static Position getPosition();
};

#endif