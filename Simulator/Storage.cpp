#include "Storage.h"

std::unordered_map<std::string, int> Storage::inventory;
Position Storage::position(0, 0); // 초기 위치는 (0, 0)으로 설정

Storage::Storage() {
    setName("Storage");
}

void Storage::addInventory(const std::string& component, int quantity) {
    inventory[component] += quantity;
}

int Storage::getInventoryQuantity(const std::string& component) const {
    auto it = inventory.find(component);
    if (it != inventory.end()) {
        return it->second;
    }
    return 0;
}

void Storage::handle(void* message) {
    // handle 함수 구현
}

void Storage::initialize() {
    addInventory("a", 987654321);
    addInventory("b", 987654321);
    addInventory("c", 987654321);
    addInventory("aa", 0);
    addInventory("bb", 0);
    addInventory("cc", 0);
    addInventory("dd", 0);
    addInventory("aaa", 0);
    addInventory("p1", 0);
    addInventory("p2", 0);

    position = Position(0,0);
}

Position Storage::getPosition() {
    return position;
}