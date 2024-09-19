#include <iostream>
#include <string>
using namespace std;

class Vehicle {
protected:
    string make;
    string model;
    int year;
public:
    Vehicle(string mk, string mdl, int yr) : make(mk), model(mdl), year(yr) {}

    virtual void displayInfo() const {
        cout << "Make: " << make << ", Model: " << model << ", Year: " << year << endl;
    }
    string getMake() const { return make; }
    string getModel() const { return model; }
    int getYear() const { return year; }
};

class Engine {
protected:
    int horsepower;
    double displacement;
public:
    Engine(int hp, double disp) : horsepower(hp), displacement(disp) {}
    int getHorsepower() const { return horsepower; }
    double getDisplacement() const { return displacement; }
};

class Car : public virtual Vehicle, public Engine {
private:
    int numberOfDoors;
public:
    Car(string mk, string mdl, int yr, int hp, double disp, int doors)
        : Vehicle(mk, mdl, yr), Engine(hp, disp), numberOfDoors(doors) {}

    void displayInfo() const override {
        Vehicle::displayInfo();
        cout << "Horsepower: " << horsepower << ", Displacement: " << displacement << "L" << endl;
        cout << "Doors: " << numberOfDoors << endl;
    }
    int getNumberOfDoors() const { return numberOfDoors; }
};

class Truck : public virtual Vehicle, public Engine {
private:
    double loadCapacity;
public:
    Truck(string mk, string mdl, int yr, int hp, double disp, double loadCap)
        : Vehicle(mk, mdl, yr), Engine(hp, disp), loadCapacity(loadCap) {}

    void displayInfo() const override {
        Vehicle::displayInfo();
        cout << "Horsepower: " << horsepower << ", Displacement: " << displacement << "L" << endl;
        cout << "Load capacity: " << loadCapacity << " tons" << endl;
    }

    double getLoadCapacity() const { return loadCapacity; }
    double calcFuelConsumption(double speed, double cargoWeight) const {
        double base = (horsepower / 10.0) + (displacement * 0.1);
        double cargoEffect = cargoWeight / loadCapacity;
        double speedEffect = speed / 100.0;
        return base * (1 + cargoEffect) * speedEffect;
    }
};

class ElectricVehicle : public virtual Vehicle {
protected:
    double batteryCapacity;
    int range;
public:
    ElectricVehicle(string mk, string mdl, int yr, double batteryCap, int rng)
        : Vehicle(mk, mdl, yr), batteryCapacity(batteryCap), range(rng) {}

    void displayInfo() const override {
        Vehicle::displayInfo();
        cout << "Battery capacity: " << batteryCapacity << " kWh, Range: " << range << " km" << endl;
    }
    double getBatteryCapacity() const { return batteryCapacity; }
    int getRange() const { return range; }
};

class ElectricCar : public ElectricVehicle, public Car {
public:
    ElectricCar(string mk, string mdl, int yr, int hp, double disp, int doors, double batteryCap, int rng)
        : Vehicle(mk, mdl, yr),
        Car(mk, mdl, yr, hp, disp, doors),
        ElectricVehicle(mk, mdl, yr, batteryCap, rng) {}

    void displayInfo() const override {
        ElectricVehicle::displayInfo();
        cout << "Horsepower: " << getHorsepower() << ", Displacement: " << getDisplacement() << "L" << endl;
        cout << "Doors: " << getNumberOfDoors() << endl;
    }
};

int main() {
    Car car("Toyota", "Camry", 2020, 203, 2.5, 4);
    Truck truck("Ford", "F-150", 2019, 450, 3.5, 1.5);
    ElectricVehicle ev("Tesla", "Model S", 2021, 100, 600);
    ElectricCar ecar("Tesla", "Model 3", 2022, 258, 0.0, 4, 75, 500);

    car.displayInfo();
    cout << endl;
    truck.displayInfo();
    cout << "Fuel consumption at 80 km/h with 1.2 tons of cargo: "
        << truck.calcFuelConsumption(80, 1.2) << " liters/100 km" << endl;
    cout << endl;
    ev.displayInfo();
    cout << endl;
    ecar.displayInfo();
    cout << endl;
    const Car constCar("Honda", "Civic", 2018, 158, 2.0, 4);
    cout << "Const car make: " << constCar.getMake() << ", model: " << constCar.getModel() << endl;

}