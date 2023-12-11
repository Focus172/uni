// Week 10 - Assignment
// Templates are powerful features of C++ which allows you to write generic
// programs. Using templates you can write a single function / class to work
// with different data types. While “calling the function / creating the class
// object” you can specify the data type you want to use. Complete the two
// functions “parkVehicle” and “remove” in the template class garage. Create car
// garage and bus garage objects to test your functions.

use std::fmt::Display;

#[derive(Debug, Clone, Copy)]
struct Garage<V, const SIZE: usize = 10>
where
    V: Vehicle + Copy + PartialEq,
{
    storage: [Option<V>; SIZE],
}

impl<V: Vehicle + Copy + PartialEq> Display for Garage<V> {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        let thing = self.storage.map(|a| a.map(|v| v.plate()).unwrap_or(0));
        write!(f, "{:?}", thing)
    }
}

impl<V: Vehicle + Copy + PartialEq, const SIZE: usize> Garage<V, SIZE> {
    pub fn new() -> Self {
        Self {
            storage: [None; SIZE],
        }
    }

    // parks vehicle in the garage and returns the spot
    // if multiple (consecutive) spots needed then returns the first spot
    // if no spots available then returns -1
    fn park_vehicle(&mut self, v: V) -> Option<usize> {
        self.storage
            .windows(v.size())
            .enumerate()
            .find(|(_, slc)| slc.iter().all(|s| s.is_none()))
            .map(|(i, _)| i)
            .map(|i| {
                for ind in i..i + v.size() {
                    self.storage[ind] = Some(v);
                }
                i
            })
    }
    // removes vehicle from the garage and returns the first spot number
    // if vehicle is not present then returns -1
    fn remove(&mut self, v: V) -> Option<usize> {
        self.storage
            .windows(v.size())
            .enumerate()
            .find(|(_, slc)| slc.iter().all(|s| s.is_some_and(|vh| vh == v)))
            .map(|(i, _)| i)
            .map(|i| {
                for ind in i..i + v.size() {
                    self.storage[ind] = None;
                }
                i
            })
        // int index = -1;
        // for (int i = 0; i <= _storage.size(); i++) {
        //   if (_storage[i].plate() == v.plate()) {
        //     if (index == -1) {
        //       index = i;
        //     }
        //     _storage[i] = VehicleType(-1);
        //   }
        // }
        //
        // return index;
    }
}

trait Vehicle {
    fn register(plate: usize) -> Self;
    fn plate(&self) -> usize;
    fn size(&self) -> usize;
}

#[derive(Debug, Clone, Copy, PartialEq, Eq, PartialOrd, Ord)]
struct Car {
    plate: usize,
    size: usize,
}

impl Vehicle for Car {
    fn register(plate: usize) -> Self {
        Self { plate, size: 1 }
    }

    fn plate(&self) -> usize {
        self.plate
    }

    fn size(&self) -> usize {
        self.size
    }
}

#[derive(Debug, Clone, Copy, PartialEq, Eq, PartialOrd, Ord)]
struct Bus {
    plate: usize,
    size: usize,
}
impl Vehicle for Bus {
    fn register(plate: usize) -> Self {
        Self { plate, size: 2 }
    }

    fn plate(&self) -> usize {
        self.plate
    }

    fn size(&self) -> usize {
        self.size
    }
}
impl Bus {
    pub fn new(plate: usize, size: usize) -> Self {
        Self { plate, size }
    }
}

pub fn main() {
    let mut g = Garage::<_, 10>::new();
    println!("{}", &g);
    let b1 = Bus::new(101, 2);
    g.park_vehicle(b1);
    println!("{}", &g);
    let b2 = Bus::new(102, 3);
    g.park_vehicle(b2);
    println!("{}", &g);
    g.park_vehicle(b1);
    g.remove(b2);
    println!("{}", &g);
    g.remove(b1);
    println!("{}", &g);
    g.park_vehicle(b2);
    println!("{}", &g);
    g.park_vehicle(b2);
    println!("{}", &g);
}
