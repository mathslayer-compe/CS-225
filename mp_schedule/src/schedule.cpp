/**
 * @file schedule.cpp
 * Exam scheduling using graph coloring
 */

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <map>
#include <unordered_map>

#include "schedule.h"
#include "utils.h"
#include <algorithm>
using namespace std;

/**
 * Takes a filename and reads in all the text from the file
 * Newline characters are also just characters in ASCII
 * 
 * @param filename The name of the file that will fill the string
 */
std::string file_to_string(const std::string& filename){
  std::ifstream text(filename);

  std::stringstream strStream;
  if (text.is_open()) {
    strStream << text.rdbuf();
  }
  return strStream.str();
}

/**
 * Given a filename to a CSV-formatted text file, create a 2D vector of strings where each row
 * in the text file is a row in the V2D and each comma-separated value is stripped of whitespace
 * and stored as its own string. 
 * 
 * Your V2D should match the exact structure of the input file -- so the first row, first column
 * in the original file should be the first row, first column of the V2D.
 *  
 * @param filename The filename of a CSV-formatted text file. 
 */
V2D file_to_V2D(const std::string & filename){
    // Your code here!
    //open
    //get line
    //create string vector for words
    //remove the commas
    //add words into string vector
    //add vector to v2d that needs to be returned
    //nested for loop
    //trim each word
    V2D stud;
    std::ifstream file;
    file.open(filename);
    
    while(!(file.eof())){
      std::vector<std::string> words;
      std::string read;
      std::getline(file, read, '\n');
      SplitString(read, ',', words);
      stud.push_back(words);
    }
    for (unsigned i = 0; i <stud.size(); i++){
      for (unsigned j = 0; j <stud[i].size(); j++) {
        stud[i][j] = Trim(stud[i][j]);
      }
    }
    return stud;
    
}

bool compare(string input, vector<string> word){
  for(unsigned int i=0; i<word.size(); i++){
    if(input==word[i]){
      return true;
    }
  }
  return false;
}
vector<string> student_class(string input, V2D stu){
  vector<string> clas;
  for(unsigned int i=0; i<stu.size(); i++){
    if(stu[i][0]==input){
      for(unsigned int j=1; j<stu[i].size(); j++){
        clas.push_back(stu[i][j]);
      }
    }
  }
  return clas;
}
/**
 * Given a course roster and a list of students and their courses, 
 * perform data correction and return a course roster of valid students (and only non-empty courses).
 * 
 * A 'valid student' is a student who is both in the course roster and the student's own listing contains the course
 * A course which has no students (or all students have been removed for not being valid) should be removed
 * 
 * @param cv A 2D vector of strings where each row is a course ID followed by the students in the course
 * @param student A 2D vector of strings where each row is a student ID followed by the courses they are taking
 */
V2D clean(V2D & cv, V2D & student){
    // YOUR CODE HERE
    V2D stud;
    for(unsigned int i=0; i<cv.size(); i++){
      vector<string> course;
      course.push_back(cv[i][0]);
      string letter=cv[i][0];
      for(unsigned int j=1; j<cv[i].size(); j++){
        vector<string> clas= student_class(cv[i][j], student);
        if(compare(letter,clas)){
          course.push_back(cv[i][j]);
        }
      }
      if(course.size()>1) {
        stud.push_back(course);
      }

    }
    return stud;

}
vector<vector<int>> Graph(V2D section){
  vector<vector<int>> graph_matrix(section.size(),vector<int>(section.size(),0));
  unsigned row_ct=0;
  while(row_ct<section.size()){
    for (unsigned i=0; i<section.size(); i++){
      if(row_ct==i){
        continue;
      }
      else{
        vector<string> node(2*section.size());
        sort(section[row_ct].begin(),section[row_ct].end());
        sort(section[i].begin(), section[i].end());
        set_intersection(section[row_ct].begin(),section[row_ct].end(),section[i].begin(),section[i].end(),node.begin());
        if(node[0]!="" && node.size()>1){
          graph_matrix[row_ct][i]=1;
        }
      }
    }
    row_ct++;
  }
  return graph_matrix;
}

bool bound(int col_num, int vertex,vector<int> &color,vector<vector<int>> &graph){
  bool safe=true;
  unsigned graph_ct=0;
  while(graph_ct<graph.size()){
    if(graph[vertex][graph_ct]){
      if(col_num==color[graph_ct]){
        safe=false;
      }
    }
    graph_ct++;
  }
  return safe;
}
bool color_alg(int lim, int vertex, vector<int> &color, vector<vector<int>> &graph){
  int size=int(graph.size());
  bool safe;
  if(vertex==size){
    return true;
  }
  for (int j=1; j<=lim; j++){
    if(bound(j,vertex, color, graph)==false){
      continue;
    }
    else{
      color[vertex]=j;
      if(color_alg(lim, vertex+1, color, graph)){
        safe=true;
      }
      else{
        color[vertex]=0;
        safe=false;
      }
    }
  }
  return safe;
}
/**
 * Given a collection of courses and a list of available times, create a valid scheduling (if possible).
 * 
 * A 'valid schedule' should assign each course to a timeslot in such a way that there are no conflicts for exams
 * In other words, two courses who share a student should not share an exam time.
 * Your solution should try to minimize the total number of timeslots but should not exceed the timeslots given.
 * 
 * The output V2D should have one row for each timeslot, even if that timeslot is not used.
 * 
 * As the problem is NP-complete, your first scheduling might not result in a valid match. Your solution should 
 * continue to attempt different schedulings until 1) a valid scheduling is found or 2) you have exhausted all possible
 * starting positions. If no match is possible, return a V2D with one row with the string '-1' as the only value. 
 * 
 * @param courses A 2D vector of strings where each row is a course ID followed by the students in the course
 * @param timeslots A vector of strings giving the total number of unique timeslots
 */
V2D schedule(V2D courses, std::vector<std::string> timeslots){
  // Your code here!
  V2D sched;
  V2D sub;
  vector<vector<int>> graph=Graph(courses);
  vector<int> color(graph.size(), 0);
  

  if(!color_alg(timeslots.size(),0,color,graph)){
    V2D wrong(1,vector<string>(1,"-1"));
    sched=wrong;
  }
  else{
    unsigned cor=0;
    unsigned sked=0;
   while(cor<courses.size()){
      vector<string> clas;
      clas.push_back(courses[cor][0]);
      clas.push_back(timeslots[color[cor]-1]);
      sub.push_back(clas);
      cor++;
    }
    while(timeslots.size()>sked){
      vector<string> slot;
      slot.push_back(timeslots[sked]);
      for (unsigned i=0; i<sub.size(); i++){
        vector<string>::iterator it;
        it=find(sub[i].begin(),sub[i].end(), timeslots[sked]);
        if(it!=sub[i].end()){
          slot.push_back(sub[i][0]);
        }
      }
      sked++;
      if(slot.size()>1){
        sched.push_back(slot);
      }
    }
  }
  return sched;
}