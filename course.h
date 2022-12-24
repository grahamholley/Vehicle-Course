#pragma once
#include <iostream>
#include <set>
#include <map>
#include <vector>
#include "vehicle.h"
using std::string;
using std::set;
using std::ostream;
using std::map; // map for recording the traces of each vehicles.
using std::vector;
#include <utility>
using std::pair;


class Course
{
  //private member declarations
 private:
  string course = "";
  pair<int,int> start_location;
  pair<int, int> finish_location;
  vector< pair<int,int> > course_path;
  vector<Vehicle*> vehicle_ref_vector;

 public:
  //public member function declarations
  Course() = default;
  Course(string);
  ~Course(){};
  Course(Course const&);
  Course &operator=(Course &);
  void AddVehicleToStart(Vehicle*);
  set<Vehicle> VehiclesAtFinish();
  int ReturnOffTrackVehiclesToStart();
  friend ostream &operator <<(ostream &, Course const &);
};
//declare split function from lecture
void split(string const &, vector<string> &, char);