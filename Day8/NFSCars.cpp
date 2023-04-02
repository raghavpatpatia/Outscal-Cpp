#include <iostream>

using namespace std;

class NFSCar
{
private:
    int engine;
    int doors;
    int capacity;
    int topSpeed;
public:
    void SetEngine(int cc){engine = cc;}
    void SetDoors(int number){doors = number;}
    void SetCapacity(int seats){capacity = seats;}
    void SetTopSpeed(int speed){topSpeed = speed;}
    int GetEngine() {return engine;}
    int GetDoors() {return doors;}
    int GetCapacity() {return capacity;}
    int GetTopSpeed() {return topSpeed;}
    virtual void StartVehicle() = 0;
    virtual void Accelerate() = 0;
    virtual void StopVehicle() = 0;
    virtual void CarDetails() = 0;
    virtual void CarCrashed()
    {
        cout << endl << "Your car was destroyed in an accident..." << endl;
    }
    ~NFSCar()
    {
        CarCrashed();
    }
};

class Lamborghini : public NFSCar
{
public:
    virtual void StartVehicle()
    {
        cout << endl << "Starting my car - Lamborghini" << endl;
    }
    virtual void Accelerate()
    {
        cout << endl << "Lamborghini reaching top speed of: " << GetTopSpeed() << "Kmph." << endl;
    }
    virtual void CarDetails()
    {
        cout << endl << "Car Name: Lamborghini Aventador SVJ\n" << "Car Engine: " << GetEngine() << endl << "Car Doors: " << GetDoors() << endl << "Car Capacity: " << GetCapacity() << endl;
    }
    virtual void StopVehicle()
    {
        cout << endl << "Stopping vehicle of type - Lamborghini" << endl;
    }
};

class Mercedes : public NFSCar
{
public:
    virtual void StartVehicle()
    {
        cout << endl << "Starting my car - Mercedes" << endl;
    }
    virtual void Accelerate()
    {
        cout << endl << "Mercedes reaching top speed of: " << GetTopSpeed() << "Kmph." << endl;
    }
    virtual void CarDetails()
    {
        cout << endl << "Car Name: Mercedes-AMG One\n" << "Car Engine: " << GetEngine() << endl << "Car Doors: " << GetDoors() << endl << "Car Capacity: " << GetCapacity() << endl;
    }
    virtual void StopVehicle()
    {
        cout << endl << "Stopping vehicle of type - Mercedes" << endl;
    }
};

class BMW : public NFSCar
{
public:
    virtual void StartVehicle()
    {
        cout << endl << "Starting my car - BMW" << endl;
    }
    virtual void Accelerate()
    {
        cout << endl << "BMW reaching top speed of: " << GetTopSpeed() << "Kmph." << endl;
    }
    virtual void CarDetails()
    {
        cout << endl << "Name: BMW M8 Competition\n" << "Car Engine: " << GetEngine() << endl << "Car Doors: " << GetDoors() << endl << "Car Capacity: " << GetCapacity() << endl;
    }
    virtual void StopVehicle()
    {
        cout << endl << "Stopping vehicle of type - BMW" << endl;
    }
};

int main()
{
    NFSCar *car;
    car = new Lamborghini();
    car->SetEngine(6498);
    car->SetDoors(2);
    car->SetCapacity(2);
    car->SetTopSpeed(352);
    car->StartVehicle();
    car->Accelerate();
    car->CarDetails();
    car->StopVehicle();
    car = new BMW();
    car->SetEngine(4395);
    car->SetDoors(2);
    car->SetCapacity(4);
    car->SetTopSpeed(250);
    car->StartVehicle();
    car->Accelerate();
    car->CarDetails();
    car->StopVehicle();
    car = new Mercedes();
    car->SetEngine(1599);
    car->SetDoors(2);
    car->SetCapacity(2);
    car->SetTopSpeed(352);
    car->StartVehicle();
    car->Accelerate();
    car->CarDetails();
    car->StopVehicle();
    delete car;
    return 0;
}