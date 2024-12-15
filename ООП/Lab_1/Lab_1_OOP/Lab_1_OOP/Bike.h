#pragma once

#include <iostream>
#include "Vehicle.h"

class Bike : public Vehicle {
private:
    std::string type;

public:
    Bike(const std::string& type) : type(type) {}

    void showDetails() const override {
        std::cout << "Bike: " << type << std::endl;
    }
};
