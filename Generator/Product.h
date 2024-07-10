#include <string>
#include <vector>
#include <fstream>

class Product {
private:
    //PRODUCT_ID (parts_ID의 의미로 간주)
    std::string PRODUCT_ID;
    //PRODUCT의 공정 이름
    std::string PROCESS_NAME;
    int counts;

public:
    Product(const std::string& PRODUCT_ID, const std::string& PROCESS_NAME, const int counts);

    std::string getProductId() const;
    std::string getProcessName() const;
    int getCounts() const;

    static void exportToCSV(const std::string& filename, const std::vector<Product>& Products);
};
