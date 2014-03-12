/* 
 CS2134 Exam II: std::sort and fun with functors and comparator functions
 
 David Stancu
 Polytechnic Institute of NYU
 dstancu@nyu.edu
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Student
{
    string name;
    int age; 
    Student (const string& name, const int& age) : name(name), age(age) {}
};

/*
 This function gets called by std::sort whenever it is comparing elements.
 
 "Why comparison via the < operator"?
 Data sets are most commonly sorted in ascending order, 
 so it makes more sense to identify whether or not the
 "current step" is less than the next item.
 
 "What happens when you use the > operator?"
 It will sort the data set in reverse.
 
 "Does operator < have to be overloaded for this to work?"
 Absolutely. 
 */

bool comp(const Student& lhs, const Student& rhs) 
{
    return lhs.age < rhs.age;
}

// Default constructors are automagically generated. 
// Not called "reverse" because of conflict with std::reverse
struct rever
{
    bool operator()(const Student& lhs, const Student& rhs)
    {
        return lhs.age > rhs.age;
    }
};
 
int main(void) 
{
    // STL's sorting functions are fantastic for vectors and such, but what about non-elementary types?
    vector<Student> classroom;
    classroom.push_back(Student("David", 19));
    classroom.push_back(Student("Tim", 20));
    classroom.push_back(Student("Rose", 90)); // it's never too late to get an education
    classroom.push_back(Student("Steve", 22));
    
    // How would I go about sorting these students by age? std::sort? Can I?
    sort(classroom.begin(), classroom.end());
    //sort(classroom.begin(), classroom.end(), comp);
    
    /*
     The above line does NOT compile, but why? Surely it's syntacticly correct?!
     std::sort(RAI begin, RAI end);
     std::sort(RAI begin, RAI end, class comp);
     
     The second overload is very important. If you have a user-defined class,
     you will need to write your own comparator function. Let's do that, shall we?
     (Uncomment the second sort call, comment the first, and look at comp)
     */
    
    // Let's see if our sorting function works!
    for (Student s : classroom) cout << s.age << endl; 
    cout << endl;
    
    /* 
     At the university that these students attend, they give priority to students 
     who are older. Can we sort this vector in reverse? Can we do it differently?
     
     Yes! Let's use a comparison object!
     */
    
    rever rev;
    sort(classroom.begin(), classroom.end(), rev);
    
    // What happened here? Neat right?!
    for (Student s : classroom) cout << s.age << endl; 
    cout << endl;
    
    /*
     "As it pertains to design: why would you use an object as a comparator?"
     
     There are a couple of cases:
     
     1: You've got classes which inherit from one another that have similar 
     parameters, so you can make a templated comparator that compares any 
     class member of your choice
     
     2: Functors can save state, and sorting doesn't always have to be done
     in an ascending or descending fashion. Say you're an avid tennis player
     and you want to go to different courts on different days of the week. 
     You could write a functor class that compares "tennisCourt" objects with 
     a private distance member which is compared in operator(). It can return
     true for all objects within your azimuth and false for objects which are not.
     (Pssst, look at Sellie's train stop homework!)
     
     */
    
    return 0;
}

