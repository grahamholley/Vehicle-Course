#include <iostream>
#include <vector>
#include <sstream>
using std::istringstream;
using std::vector;
using std::string;
using std::getline;
using std::ostream;
#include <iterator>
using std::cout;
using std::endl;
#include<utility>
using std::pair;
#include <algorithm>
using std::remove_if;
#include <numeric>
#include <stdexcept>
using std::accumulate;
using std::ostream;
#include<set>
using std::set;

#include "vehicle.h"


Vehicle::Vehicle(char ch)
{
  //vehicle constructor
  vehicle_char = ch;
}

// output the track
ostream &operator <<(ostream & out, Vehicle const & v)
{
  out << v.vehicle_char;
  return out;
}

//< comparison operator returns bool
bool operator<(const Vehicle&i1, const Vehicle&i2) {
  return i1.vehicle_char< i2.vehicle_char;
}

pair<int,int> Vehicle::MoveWhere(){
  return loc;
}

//== comparison operator returns bool
bool operator==(const Vehicle&i1, const Vehicle&i2) {
  return i1.vehicle_char ==  i2.vehicle_char;
}

void Vehicle::SetWhere(pair<int,int> where){
  loc = where;
}

//set direction for vehicle
void Vehicle::SetBearing(char c){
  if (c == 'N' || c==  'S' || c=='E'||c=='W')orientation = c;
  else throw std::invalid_argument("I cant understand");
}

//move the vehicle by one char based on its orientation
void Vehicle::MoveForward(int i){
  if(orientation=='W')loc.second-=i;
  else if (orientation=='E')loc.second+=i;
  else if (orientation=='N') loc.first-=i;
  else if (orientation=='S') loc.first+=i;
}

//assign new orientation direction based on direction to the right
void Vehicle::TurnRight(){
  if(orientation=='W')orientation = 'N';
  else if (orientation=='E')orientation='S';
  else if (orientation=='N') orientation='E';
  else if (orientation=='S') orientation='W';
}

//assign new orientation direction based on direction to the left
void Vehicle::TurnLeft(){
  if(orientation=='W')orientation = 'S';
  else if (orientation=='E')orientation='N';
  else if (orientation=='N') orientation='W';
  else if (orientation=='S') orientation='E';
}