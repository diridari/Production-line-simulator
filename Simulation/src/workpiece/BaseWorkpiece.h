//
// Created by basti on 03.11.2020.
//

#ifndef PRODUCTION_LINE_SIMULATOR_BASEWORKPIECE_H
#define PRODUCTION_LINE_SIMULATOR_BASEWORKPIECE_H
#include <stdint.h>
#include <string>
#include <iostream>
#define WORKPIECE_MAX_INCREASE 10000
#define MAXPOSITION 1000000
using namespace std;
class BaseWorkpiece {
private:
    uint32_t position;
    const string workpieceName;
public:
    BaseWorkpiece();
    explicit BaseWorkpiece(string name);
    explicit BaseWorkpiece(uint32_t position_, string name = "Baseworkpiece");
    uint32_t getPosition() const;
    uint8_t setPosition(uint32_t pos);
    string getName() const;

    /**
     * increase or decrease position by the paramter
     * @param increasePosition add position (max by WORKPIECE_MAX_INCREASE)
     * @return 1 == success
     */
    uint8_t moveBy(int32_t increasePosition);

};
std::ostream &operator<<(std::ostream &strm, BaseWorkpiece a);
#endif //PRODUCTION_LINE_SIMULATOR_BASEWORKPIECE_H
