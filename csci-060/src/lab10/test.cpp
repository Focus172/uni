// Week 10 - Assignment
// Templates are powerful features of C++ which allows you to write generic
// programs. Using templates you can write a single function / class to work
// with different data types. While “calling the function / creating the class
// object” you can specify the data type you want to use. Complete the two
// functions “parkVehicle” and “remove” in the template class garage. Create car
// garage and bus garage objects to test your functions.

#include <iostream>
#include <ostream>
#include <vector>

using namespace std;

class Car {
public:
  Car(int lp) { _lp = lp; }
  int plate() { return _lp; }
  int size() { return _size; }

private:
  int _lp;
  int _size = 1;
};
class Bus {
public:
  Bus(int lp, int size = 2) {
    _lp = lp;
    _size = size;
  }
  int plate() { return _lp; }
  int size() { return _size; }

private:
  int _lp;
  int _size;
};

template <class VehicleType> class Garage {
public:
  Garage(int spots) {
    _spots = spots;
    for (int i = 0; i < spots; i++) {
      _storage.push_back(VehicleType(-1));
    }
  }

  // parks vehicle in the garage and returns the spot
  // if multiple (consecutive) spots needed then returns the first spot
  // if no spots available then returns -1
  int parkVehicle(VehicleType v) {
    int size = v.size();
    for (int i = 0; i < _spots; i++) {
      if (check_rec(i, size)) {
        for (int index = i; index < i + size; index++) {
          _storage[index] = v;
        }
        return i;
      }
    }
    return -1;
  }

  bool check_rec(int index, int size) {
    if (size == 0) {
      return true;
    }

    if (index >= _spots) {
      return false;
    }

    if (_storage[index].plate() == -1) {
      return check_rec(index + 1, size - 1);
    } else {
      return false;
    }
  }

  // removes vehicle from the garage and returns the first spot number
  // if vehicle is not present then returns -1
  int remove(VehicleType v) {
    int index = -1;
    for (int i = 0; i <= _storage.size(); i++) {
      if (_storage[i].plate() == v.plate()) {
        if (index == -1) {
          index = i;
        }
        _storage[i] = VehicleType(-1);
      }
    }

    return index;
  }

  void display() {
    int count = _storage.size();
    cout << "[";
    for (int i = 0; i < _spots; i++) {
      cout << _storage[i].plate();
      if (i + 1 != _spots)
        cout << ", ";
    }
    cout << "]" << endl;
  }

private:
  int _spots;
  vector<VehicleType> _storage;
};

int main() {
  Garage<Bus> g(10);
  g.display();
  Bus b1(101, 2);
  g.parkVehicle(b1);
  g.display();
  Bus b2(102, 3);
  g.parkVehicle(b2);
  g.display();
  g.parkVehicle(b1);
  g.remove(b2);
  g.display();
  return 0;
}
