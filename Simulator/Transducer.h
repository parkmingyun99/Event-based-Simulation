#ifndef TRANSDUCER_H
#define TRANSDUCER_H

#include "EoModel.h"

class Transducer : public EoModel {
private:
    static int totalSpendTime;

public:
    Transducer();
    void handle(void* message) override;
    void initialize() override;
};

#endif // TRANSDUCER_H