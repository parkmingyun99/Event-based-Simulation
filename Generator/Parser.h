#ifndef PARSER_H
#define PARSER_H

#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <functional>

template<typename T>
std::vector<T> parseCSV(const std::string& filePath, std::function<T(std::vector<std::string>&)> createEntity) {
    std::vector<T> entities;
    std::ifstream file(filePath);
    std::string line;
    std::getline(file, line); // 헤더 스킵
    while (std::getline(file, line)) {
        std::istringstream stream(line);
        std::string field;
        std::vector<std::string> fields;
        while (getline(stream, field, ',')) {
            fields.push_back(field);
        }
        entities.push_back(createEntity(fields));
    }
    return entities;
}

#endif // PARSER_H
