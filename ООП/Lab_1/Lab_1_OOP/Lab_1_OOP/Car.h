#pragma once

#include <iostream>
#include "Vehicle.h"

class Car : public Vehicle {
private:
    std::string brand;
    int numberOfDoors;

public:
    Car(const std::string& brand, int doors)
        : brand(brand), numberOfDoors(doors) {}

    void showDetails() const override {
        std::cout << "Car: " << brand
            << ", Doors: " << numberOfDoors << std::endl;
    }
};

