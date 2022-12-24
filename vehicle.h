#pragma once
#include <iostream>
#include <utility>
using std::pair;
using std::ostream;


class Vehicle
{
  //private member declarations
 private:
  char vehicle_char;
  char orientation;
  pair<int, int> loc;

  //public member function declarations
 public:
  Vehicle() = default;
  Vehicle(char);
  ~Vehicle(){}; // jus keep it there.

  void SetBearing(char);
  void MoveForward(int i =1);
  pair<int,int> MoveWhere();
  void SetWhere(pair<int,int>);
  void TurnLeft();
  void TurnRight();
  friend bool operator<(const Vehicle&, const Vehicle&);
  friend bool operator==(const Vehicle&, const Vehicle&);
  friend ostream &operator <<(ostream &, Vehicle const &);
};