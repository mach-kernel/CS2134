/* 
 CS2134 Exam II: Functors
 
 David Stancu
 Polytechnic Institute of NYU
 dstancu@nyu.edu
 */

#include <iostream>
#include <vector>
#include <iterator>

using namespace std;

struct Worker
{
    string name;
    int type;
    Worker (const string& name, const int& type) : name(name), type(type) {}
};

/*
 "A class! You want me to use a class to compare?!"
 
 Yes I do! This is called a function-object (or a functor), it is very neat
 because it can save state past instantiation!
 
 You can do neat things like: wType(4) which will always compare against 4! 
 Awesome!
 
class wType
{
private:
    int type;
public:
    wType(const int& type) : type(type) {}
    bool operator()(const Worker& w)
    {
        return w.type == type;
    }
};
*/

/*
 
 wPromote carries out our operation. It does *not* save state, it only performs
 an action (in this case a simple increment). Nothing crazy happens here!
 
class wPromote
{
public:
    void operator()(Worker& w) { w.type++; }
};


 exec_if carries out an action (for this example, wPromote) 
 within a container if the predicate object (for this example, wType) returns 
 true. 
 
template <class pred, class op>
void exec_if(pred& p, op& o, vector<Worker>::iterator begin, vector<Worker>::iterator end)
{
    while (begin != end)
    {
        if (p(*begin)) o(*begin);
        ++begin;
    }
};
*/

int main(void)
{
    // Let's make a vector filled with workers
    vector<Worker> workers;
    workers.push_back(Worker("Jim", 1));
    workers.push_back(Worker("Steve", 1));
    workers.push_back(Worker("Bob", 2));
    workers.push_back(Worker("Don", 3));
    workers.push_back(Worker("Dan", 3));
    workers.push_back(Worker("David", 1337));
    
    // Your company's HR department wants you to give them a list of all type 3 workers, how would you do it?
    
    vector<Worker> workerst3;
    for (Worker w : workers)
        if (w.type == 3) workerst3.push_back(w);
    
    for (Worker w : workerst3) cout << w.name << endl;
    cout << endl;
    
    /*
     Sure, you can totally do that! But now, HR is getting rather needy. They want you 
     to promote all type 3 workers to type 4 work. 
     
     "Sweet, let's make another for loop!"
     No no no! You're smarter than that! HR is probably going to want to promote
     a lot of their employees. Are you going to write 10 different for loops for 
     10 different categories? No way!
     
     "So what can we do?"
     Go read and uncomment the wType class!
     */
    
    // Sweet, we can now easily compare. Let's do it!
    wType t3(3);
    
    for (Worker &w : workers) if (t3(w)) w.type++;
    for (Worker w : workers) cout << w.name << ": " << w.type << endl;
    cout << endl;
    
    /*
     Your company's HR department continues to be impressed by Don and Dan. 
     They are up for another promotion, and they are planning to give promotions to 
     others as well. 
     
     We've got a neat tool for comparisons, but can't we automate the actual
     promotion-giving process without having to write a ton of for loops? 
     
     Absolutely! Go uncomment wPromote and exec_if!
     */
    
    // No more looping. Let's see how elegant this is!
    
    wType t4(4);
    wPromote wp;
    exec_if(t4, wp, workers.begin(), workers.end());
    
    for (Worker w : workers) cout << w.name << ": " << w.type << endl;
    cout << endl;
    
    /*
     Don and Dan are now working type 5 jobs. Nicely done. But you have questions:
     
     1: "This was MORE lines than the loop! What gives?"
     This is correct, exec_if and wPromote had to be written, as well as instantiated
     within our program. But now, you can apply any predicate and operator to your
     vector of workers while reusing the same code!
     
     2: "Can I use this with any container type?"
     Certainly. Just template it. 
     
     */
    
    return 0;
}

