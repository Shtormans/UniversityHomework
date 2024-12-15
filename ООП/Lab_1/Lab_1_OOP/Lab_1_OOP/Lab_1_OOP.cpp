#include <iostream>
#include <vector>

#include "Car.h"
#include "Bike.h"

int main()
{
    std::vector<Vehicle*> vehicles;

    vehicles.emplace_back(new Car("Toyota", 4));
    vehicles.emplace_back(new Bike("Mountain"));

    for (const auto& vehicle : vehicles) {
        vehicle->showDetails();
    }

    return 0;
}