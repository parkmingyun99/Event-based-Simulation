#include "AGV.h"
#include "Cell.h"
#include "Machine.h"
#include "Map.h"
#include "Part.h"
#include "Process_rule.h"
#include "Product.h"
#include "Scenario_settings.h"

#include <OpenXLSX.hpp>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <sys/stat.h>
#include <random>

using namespace OpenXLSX;

/*
        Map(공장의 크기)는 다음과 같이 설정될 수 있음. 1칸이 나타내는 크기 = 1m x 1m.
        1. 소규모 공장 : 50 x 50
                AGV: 5~10대
                Cell: 10~20개
        2. 중규모 공장 : 100 x 100
                AGV: 10~20개
                Cell: 20~50개
        3. 대규모 공장 : 250 x 250
                AGV: 20~50개
                Cell: 50~125개
       

        PART: (Cell/4)개
*/

int getRandomNumber(int min, int max) {
    return std::rand() % (max - min + 1) + min;
}



enum FactorySize {
    SMALL,
    MEDIUM,
    LARGE,
};

const int cellType = 4; 
// cell 종류는 4개로 static 하게 설정하였음. 자동차 생산을 기준으로 보편적으로 4단계의 과정을 거치기 때문임.
// 4개의 셀 종류는 각각 프레스 공정, 차체 공정, 도장 공정, 조립 공정을 의미함. 

int main() {
    // Seed the random number generator
    std::srand(static_cast<unsigned int>(std::time(0)));
    // Randomly select a factory size
    FactorySize size = static_cast<FactorySize>(std::rand() % 4);
    

    int rows = 0;
    int cols = 0;
    int num_agvs = 0;
    int num_cells = 0;
    int numPartType = 0;

    size=LARGE;
    
    switch (size) {
    case SMALL:
        rows = 50;
        cols = 50;
        num_agvs = getRandomNumber(5, 10);
        num_cells = getRandomNumber(10, 20);
        break;
    case MEDIUM:
        rows = 100;
        cols = 100;
        num_agvs = getRandomNumber(10, 20);
        num_cells = getRandomNumber(20, 40);
        break;
    case LARGE:
        rows = 250;
        cols = 250;
        num_agvs = getRandomNumber(20, 50);
        num_cells = getRandomNumber(50, 100);
        break;
    }

    

    // part 종류는 cell / 4 개로 정의함.
    numPartType = num_cells / 4;

    // Map 정의
    Map map(rows + 1, cols + 1);

    // AGV 정의
    std::vector<AGV> agvs;
    for (int i = 0; i < num_agvs; i++) {
        int agv_x, agv_y;

        // map에 empty space가 아니면, 위치(x, y)를 다시 설정함.
        do {
            agv_x = getRandomNumber(1, rows);
            agv_y = getRandomNumber(1, cols);
        } while (map.Get(agv_x, agv_y) != 0);
        // Create the AGV object and add it to the vector

        // doyoung : edit AGV String
        // agvs.emplace_back("AGV_" + std::to_string(i + 1), agv_x, agv_y);
        agvs.emplace_back(std::to_string(i + 1), agv_x, agv_y);

        // agvs.emplace_back("AGV_" + std::to_string(i + 1));
        // Set the value on the map to indicate the presence of an AGV
        map.Set(agv_x, agv_y, 1); // x, y, value
    }

    // Cell 정의
    std::vector<Cell> cells;
    std::vector<int> cell_type_counts(cellType + 1, 0);
    for (int i = 0; i < num_cells; i++) {
        int cell_x, cell_y;
        int cell_id = i + 1;
        int cell_type = getRandomNumber(1, cellType);

        // 빈 위치를 찾을 때까지 반복해서 무작위 좌표 생성
        do {
            cell_x = getRandomNumber(1, rows);
            cell_y = getRandomNumber(1, cols);
        } while (map.Get(cell_x, cell_y) != 0); // 이미 agv 또는 cell이 있다면, 다시 랜덤 위치 생성하기.

        // constraint 1. 실제 공장과 유사해야 함. 즉, part 1을 만드는 cell 이라면 해당 cell의 응집도가 높아야 함.
        // 차후 수정 예정.
        int cell_type_count = ++cell_type_counts[cell_type];

        // Cell 생성 후 맵에 위치 표시
        cells.emplace_back(cell_type, cell_type_count, cell_x, cell_y);
        map.Set(cell_x, cell_y, 2);
    }

    qsort(cells.data(), cells.size(), sizeof(Cell), Cell::compareCells);

    // Part 정의
    std::vector<Part> parts;
    for (int i = 0; i < numPartType; i++) {
        std::vector<int> processTime;
        std::vector<int> processLine;

        processTime.emplace_back(0); // generator's process time.

        // Cell type 만큼 랜덤 프로세스 타임 생성. 대략 30~300 이유 없음.
        for (int j = 0; j < cellType; j++) {
            int tmp = getRandomNumber(30, 300);
            std::cout << tmp << "\n";
            processTime.emplace_back(tmp);
        }

        processTime.emplace_back(0); // transducer's process time.

        // processLine 정의
        for (int j = 0; j < cellType; j++) {
            int tmp = getRandomNumber(0, cellType);
            if (tmp != 0) {
                processLine.emplace_back(tmp);
            }
            else
                j--; // doyoung : bug fix
        }

        parts.emplace_back(i + 1, processTime, processLine);
    }

    // doyoung : temporary output begin
    std::ofstream outFile("./Scenario/test.txt");
    if (!outFile) {
        std::cerr << "File could not be opened for writing." << std::endl;
        return 1;
    }
    int product_cnt = getRandomNumber(10, 100);
    for (int i = 0; i < product_cnt; i++) {
        int tmp = getRandomNumber(1, cellType);
        outFile << tmp << std::endl;
    }
    outFile.close();
    // doyoung : temporary output end

    // Scenario 정의
    mkdir("./Scenario", 0777); // Scenario 디렉토리 생성


    XLDocument doc;
    doc.create("../FacilityLayout/excel_files/import/Information.xlsx");
    doc.workbook().addWorksheet("Facility"); // Add this line
    auto wks = doc.workbook().worksheet("Facility");
    wks.cell("A1").value() = "name";
    wks.cell("B1").value() = "w[mm]";
    wks.cell("C1").value() = "h[mm]";
    wks.cell("A2").value() = "Facility";
    wks.cell("B2").value() = rows * 10; // convert to mm
    wks.cell("C2").value() = cols * 10; // convert to mm
    doc.save();
    doc.close();


    XLDocument doc2;
    // Save Departments to Information.xlsx using OpenXLSX
    doc2.open("../FacilityLayout/excel_files/import/Information.xlsx");
    doc2.workbook().addWorksheet("Departments");
    auto wks_dept = doc2.workbook().worksheet("Departments");
    wks_dept.cell("A1").value() = "name";
    wks_dept.cell("B1").value() = "w[mm]";
    wks_dept.cell("C1").value() = "h[mm]";
    wks_dept.cell("D1").value() = "group";

    XLDocument doc3;
    doc3.create("../FacilityLayout/excel_files/import/Transportflow.xlsx");
    doc3.workbook().addWorksheet("Flow matrix");
    doc3.workbook().addWorksheet("Mean matrix");
    auto wks_flow = doc3.workbook().worksheet("Flow matrix");
    auto wks_mean = doc3.workbook().worksheet("Mean matrix");

    // Assign names and groups to cells
    int cell_counter = 1;
    for (int i = 1; i <= cellType; ++i) {
        for (int j = 1; j <= cell_type_counts[i]; ++j) {
            std::string cell_name = "cell" + std::to_string(i) + "_" + std::to_string(j);
            wks_dept.cell(cell_counter + 1, 1).value() = cell_name;
            wks_dept.cell(cell_counter + 1, 2).value() = 100; // w[mm]
            wks_dept.cell(cell_counter + 1, 3).value() = 100; // h[mm]
            wks_dept.cell(cell_counter + 1, 4).value() = i; // group

            // Update Flow matrix
            wks_flow.cell(cell_counter + 1, 1).value() = cell_name;
            wks_flow.cell(1, cell_counter + 1).value() = cell_name;

            // Update Mean matrix
            wks_mean.cell(cell_counter + 1, 1).value() = cell_name;
            wks_mean.cell(1, cell_counter + 1).value() = cell_name;

            ++cell_counter;
        }
    }

    std::srand(static_cast<unsigned int>(std::time(0))); // Seed the random number generator

    for (int row = 2; row <= cell_counter; ++row) {
        for (int col = 2; col <= cell_counter; ++col) {
            int randomValue = getRandomNumber(1, 100);
            if (randomValue <= 90) { // 90% 확률로 0을 저장
                wks_flow.cell(row, col).value() = 0;
            } else { // 10% 확률로 1을 저장하고 conveyor를 저장
                wks_flow.cell(row, col).value() = 1;
                wks_mean.cell(row, col).value() = "conveyor";
            }
        }
    }


    doc2.save();
    doc2.close();

    doc3.save();
    doc3.close();
        

    AGV::exportToCSV("./Scenario/AGV.csv", agvs);
    // Cell::exportToCSV("./Scenario/CELL.csv", cells);
    Part::exportToCSV("./Scenario/PART.csv", parts);

    return 0;
}

