// Generator.cpp
#include "Generator.h"
#include "Product.h"
#include "Machine.h"
#include <iostream>

double arrivalRate=3.0;

Generator::Generator() {
    setName("Generator");
    numTotalProduct1=100; // 만들어야 할 p1 갯수
    numTotalProduct2=50; // 만들어야 할 p2 갯수
    numGenProduct=0; // 현재 만든 갯수 
    
}

void Generator::handle(void* message) {
    // 더 이상 제품을 만들 필요가 없는 경우
    if (numGenProduct >= numTotalProduct1 && numGenProduct >= numTotalProduct2) {
        std::cout << "All products produced." << std::endl;
        return;
    }

    // 모든 머신에 대해 반복하여 가장 빨리 사용 가능한 머신을 찾습니다.
    for (auto& machine : machines) {
        // 사용중인 머신인가? 사용중 아니라면 사용중으로 변경함.
        if(!machine.getIsUse()) continue;
        machine.setIsUse(false); // 사용중으로 변경함.
        // char* material = const_cast<char*>("a"); // a라는 부품을 머신으로 보냄. 실제론 적절한 부품을 보내야 함.
        // void* ptr=static_cast<void*>(material);
        void* machinePtr=reinterpret_cast<void*>(&machine); 
        schedule(machine.getProcessTime(),"Machine", machinePtr); // 부품 하나를 머신으로 던짊.
    }

     schedule(10,"Generator",nullptr);
    
}



void Generator::initialize() {

    // 1. Two Product Generate
    products={
        Product("p1","m1-m2,m2-m1"),
        Product("p2","m1-m1-m1,m2-m2")
    };
    
    // 2. Two Machine Generate
    machines={
        // parameter : machineID, processTime, machine_locationX, machine_locationY
        Machine(getCurrentTime(),"m1",10, 5,5), 
        Machine(getCurrentTime(),"m2",20, 7,7)
    };
    // 3. Add input-output rules for machines
    // m1의 머신 규칙
    machines[0].addInputOutputRule("a", "aa");
    machines[0].addInputOutputRule("aa", "aaa");
    machines[0].addInputOutputRule("aaa", "p2");
    machines[0].addInputOutputRule("c", "dd");
    machines[0].addInputOutputRule("cc", "p1");
    // m2의 머신 규칙
    machines[1].addInputOutputRule("b", "bb");
    machines[1].addInputOutputRule("bb", "p2");
    machines[1].addInputOutputRule("c", "cc");
    machines[1].addInputOutputRule("dd", "p1");

    // 4. 100*100 Matrix Generate
    std::vector<int> row(101, 0); // Create a row with 101 zeros
    my2DArray.assign(101, row); // Initialize my2DArray with 101x101 size

    // Set the machines' positions in my2DArray to 1
    my2DArray[5][5] = 1; // Machine m1 at position (5, 5)
    my2DArray[7][7] = 1; // Machine m2 at position (7, 7)

    std::cout << "Initializing Generator." << std::endl;

    schedule(0,"Generator",nullptr);
}