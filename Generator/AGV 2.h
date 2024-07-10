#include <string>
#include <vector>
#include <fstream>

class AGV {
private:
    std::string AGV_ID;
    int x;
    int y;


public:
    AGV(const std::string& AGV_ID, int x, int y);

    std::string getAgvID() const;
    int getX() const;
    int getY() const;

    static void exportToCSV(const std::string& filename, const std::vector<AGV>& AGV);
};
