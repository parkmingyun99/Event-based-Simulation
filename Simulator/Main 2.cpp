#include <iostream>
#include <vector>
#include "EoModel.h"
#include "Event.h"
#include "SimEngine.h"
#include "Generator.h"
#include "Transducer.h"
#include "Machine.h"
#include "AGV.h"
#include "Storage.h"

int main() {

    // // Generator 객체 생성
    Generator generator;

    // // Transducer 객체 생성
    Transducer transducer;

    // Machine 객체 생성
    Machine machine;

    // AGV 객체 생성
    AGV agv;

    // Storage 객체 생성
    Storage storage;

    // SimEngine 인스턴스 가져오기
    SimEngine& engine = SimEngine::getInstance();

    engine.addModel(&generator);
    engine.addModel(&transducer);
    engine.addModel(&machine);
    engine.addModel(&agv);
    engine.addModel(&storage);

    engine.setEndTime(3600);
    engine.run();

    return 0;
}
