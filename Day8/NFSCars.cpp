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
    virtual void StartVehicle()
    {
        cout << endl << "Starting your car";
    }
    virtual void Accelerate()
    {
        cout << endl << "Your car is reaching to its top speed.";
    }
    virtual void StopVehicle()
    {
        cout << endl << "Stopping your car";
    }
    virtual void CarDetails()
    {
        cout << endl << "It is a NFS car.";
    }
    virtual ~NFSCar()
    {
        cout << "Your car was destroyed...";
    }
};

class Lamborghini : public NFSCar
{
public:
    void StartVehicle()
    {
        cout << endl << "Starting my car - Lamborghini";
    }
    void Accelerate()
    {
        cout << endl << "Lamborghini reaching top speed of: " << GetTopSpeed() << "Kmph.";
    }
    void CarDetails()
    {
        cout << endl << "Car Name: Lamborghini Aventador SVJ\n" << "Car Engine: " << GetEngine() << endl << "Car Doors: " << GetDoors() << endl << "Car Capacity: " << GetCapacity();
    }
    void StopVehicle()
    {
        cout << endl << "Stopping vehicle of type - Lamborghini";
    }
    ~Lamborghini()
    {
        cout << endl << "Your Lamborghini car was destroyed in an accident.";
    }
};

class Mercedes : public NFSCar
{
public:
    void StartVehicle()
    {
        cout << endl << "Starting my car - Mercedes";
    }
    void Accelerate()
    {
        cout << endl << "Mercedes reaching top speed of: " << GetTopSpeed() << "Kmph.";
    }
    void CarDetails()
    {
        cout << endl << "Car Name: Mercedes-AMG One\n" << "Car Engine: " << GetEngine() << endl << "Car Doors: " << GetDoors() << endl << "Car Capacity: " << GetCapacity();
    }
    void StopVehicle()
    {
        cout << endl << "Stopping vehicle of type - Mercedes";
    }
    ~Mercedes()
    {
        cout << endl << "Your Mercedes car was destroyed in an accident.";
    }
};

class BMW : public NFSCar
{
public:
    void StartVehicle()
    {
        cout << endl << "Starting my car - BMW";
    }
    void Accelerate()
    {
        cout << endl << "BMW reaching top speed of: " << GetTopSpeed() << "Kmph.";
    }
    void CarDetails()
    {
        cout << endl << "Name: BMW M8 Competition\n" << "Car Engine: " << GetEngine() << endl << "Car Doors: " << GetDoors() << endl << "Car Capacity: " << GetCapacity();
    }
    void StopVehicle()
    {
        cout << endl << "Stopping vehicle of type - BMW";
    }
    ~BMW()
    {
        cout << endl << "Your BMW car was destroyed in an accident.";
    }
};

int main()
{
    NFSCar *lamborghini = new Lamborghini();
    NFSCar *bmw = new BMW();
    NFSCar *mercedes = new Mercedes();

    lamborghini->SetEngine(6498);
    lamborghini->SetDoors(2);
    lamborghini->SetCapacity(2);
    lamborghini->SetTopSpeed(352);
    lamborghini->StartVehicle();
    lamborghini->Accelerate();
    lamborghini->CarDetails();
    lamborghini->StopVehicle();
    cout << endl;
    bmw->SetEngine(4395);
    bmw->SetDoors(2);
    bmw->SetCapacity(4);
    bmw->SetTopSpeed(250);
    bmw->StartVehicle();
    bmw->Accelerate();
    bmw->CarDetails();
    bmw->StopVehicle();
    cout << endl;
    mercedes->SetEngine(1599);
    mercedes->SetDoors(2);
    mercedes->SetCapacity(2);
    mercedes->SetTopSpeed(352);
    mercedes->StartVehicle();
    mercedes->Accelerate();
    mercedes->CarDetails();
    mercedes->StopVehicle();
    cout << endl;
    delete lamborghini;
    cout << endl;
    delete bmw;
    cout << endl;
    delete mercedes;
    cout << endl;
    return 0;
}