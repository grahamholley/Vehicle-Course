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
#include <algorithm>
using std::remove_if;
using std::find;
#include <numeric>
using std::accumulate;
using std::ostringstream;

#include "course.h"
#include "vehicle.h"

//from https://www.geeksforgeeks.org/remove-spaces-from-a-given-string/
string removeSpaces(string str)
{
  str.erase(remove(str.begin(), str.end(), ' '), str.end());
  return str;
}


//get a multiline string of the course and make it into a vector for easier manipulation(course constructor)
//add border and generate a new string course and load to the class
Course::Course(string track)
// assign values to the private members like start, finish, and  path
{
  string course_line;
  // each line
  istringstream ss_track(track);
  //stream track into string variable

  while(getline(ss_track, course_line))
  {
    course += course_line;
    course += '\n';
  }

  vector<string> vector_lines;
  split(course, vector_lines, '\n');
  string new_line;
  // after we get a vector of lines , we can do what ever to wrap it .
  vector<string> vector_lines_not_empty;
  for (auto line: vector_lines){
    if(line.size() != 0 )
      // if line not empty, add the line without spaces back to the new vector_lines_not_empty
    {
      new_line = removeSpaces(line);
      vector_lines_not_empty.push_back('+'+new_line+'+'+'\n');
    }
  }
//generate barrier of "+"
  int barrier_length = vector_lines_not_empty[0].size();
  string barrier =  "";
  for (int i = 0; i< barrier_length-1; i++){
    barrier += "+";
  }
  barrier += '\n';
  vector_lines_not_empty.insert(vector_lines_not_empty.begin(), barrier);
  vector_lines_not_empty.push_back(barrier);
  course = std::accumulate(vector_lines_not_empty.begin(), vector_lines_not_empty.end(), std::string(""));
  // add "++++" border to the course

  for (long unsigned int i=0;i<vector_lines_not_empty.size();i++){
    for (long unsigned int j=0;j<vector_lines_not_empty[0].size();j++){
      //load pairs of start,finish, and path
      if (vector_lines_not_empty[i][j] == 'S')
      {
        start_location = {i,j};
      }
      else if(vector_lines_not_empty[i][j] == 'F'){
        finish_location = {i,j};
      }
      else if(vector_lines_not_empty[i][j] == '*'){
        course_path.push_back({i,j});
      }
    }
  }
}

// output the track
ostream &operator <<(ostream & out, Course const & c)
{
  vector<string> string_vec;

  split(c.course, string_vec, '\n');
  //  get lines for the multi-line course c.course
  ostringstream out_tmp;
  pair<int,int> loc_pair;
  char vehicle_char;

  for (long unsigned int i=0;i<string_vec.size();i++){
    for (long unsigned int j=0;j<string_vec[0].size();j++){
      for(auto v: c.vehicle_ref_vector){
        loc_pair = {i,j};
        if(v->MoveWhere() ==  loc_pair)
        {
          out_tmp<<*v;
          vehicle_char = out_tmp.str()[out_tmp.str().size()-1];
          string_vec[i][j] = vehicle_char;
        }
      }
    }
    string_vec[i].push_back('\n');
  }
  string str = std::accumulate(string_vec.begin(), string_vec.end(), std::string(""));
  out<<str;
  return out;
}

// use split function from lecture
// split string based on sep, ref return of vector<string>
void split(string const &s, vector<string> &elems, char sep) {
  istringstream iss(s);
  string item;
  while (getline(iss, item, sep)) elems.push_back(item);
}

void Course::AddVehicleToStart(Vehicle* v_ref)
{
  //replace 'S' char with vehicle char
  v_ref->SetWhere(start_location);
  vehicle_ref_vector.push_back(v_ref);
}
set<Vehicle>  Course::VehiclesAtFinish(){
  //return vehicles who are at 'F' char
  set<Vehicle> whoisfinished;
  for(auto &v:vehicle_ref_vector){
    if(v->MoveWhere() == finish_location){
      whoisfinished.insert(*v);
    }
  }
  return whoisfinished;
}

Course::Course(Course const& course_input){
  //copy constructor for course
  course = course_input.course;
  start_location = course_input.start_location;
  finish_location = course_input.finish_location;
  course_path = course_input.course_path;
  // no vehicles, only path and other stuff.
}

Course &Course::operator=(Course &course_input){
  // no more vehicles in the original course.
  course = course_input.course;
  start_location = course_input.start_location;
  finish_location = course_input.finish_location;
  course_path = course_input.course_path;
  vehicle_ref_vector = course_input.vehicle_ref_vector;
  course_input.vehicle_ref_vector.clear();
  //remove cars
  return *this;
}

int Course::ReturnOffTrackVehiclesToStart(){
  // if vehicle isn't where '*' used to be or at start/finish, return to start
  int cars_not_track = 0;
  vector<pair<int,int> > the_whole_path = course_path;
  the_whole_path.push_back(start_location);
  the_whole_path.push_back(finish_location);
  bool car_not_on_the_track=false;
  for(auto &v: vehicle_ref_vector){
    car_not_on_the_track=(find(the_whole_path.begin(),the_whole_path.end(),v->MoveWhere())==the_whole_path.end());
    if (car_not_on_the_track){
      cars_not_track ++;
      v->SetWhere(start_location);
    }
  }
  return cars_not_track;
}