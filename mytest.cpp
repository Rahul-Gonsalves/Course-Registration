#include "rqueue.h"
using namespace std;

int priorityFn1(const Student &tudent);
int priorityFn2(const Student &student);

int priorityFn1(const Student&student) {
  //priority value is determined based on some criteria
  //priority value falls in the range [0-6]
  //the smaller value means the higher priority
  int priority = student.getYear() + student.getMajor() + student.getGroup();
  return priority;
}

int priorityFn2(const Student&student) {
  //priority is determined by an officer in registrar office
  //priority value falls in the range [0-6]
  //the smaller value means the higher priority
  return student.getPriority();
}

class Tester {
    public:
        bool testBasicInsert1(RQueue& queue);
        bool testBasicInsert2(RQueue& queue);
        bool testBasicMerge(RQueue& queue1, RQueue& queue2);
        bool testBasicChangePriority(RQueue& queue);
        bool testBasicRemove(RQueue& queue);
};

bool Tester::testBasicInsert1(RQueue& queue) {
    bool allInserted = true;
    // Create some test students and insert them into the queue
    //Student(string name, int priority, int year, int major, int group)
    Student student1("Sam",1,1,1,1);
    Student student2("Liz",5,1,2,0);
    Student student3("Nick",2,0,0,0);
    Student student4("Eva",4,3,2,1);

    queue.insertStudent(student3);
    queue.insertStudent(student1);
    queue.insertStudent(student2);
    queue.insertStudent(student4);

    return allInserted;
}
bool Tester::testBasicInsert2(RQueue& queue) {
    bool allInserted = true;
    // Create some test students and insert them into the queue
    //Student(string name, int priority, int year, int major, int group)
    Student student5("John",6,3,2,1);
    Student student6("Mia",3,0,0,0);

    queue.insertStudent(student5);
    queue.insertStudent(student6);

    return allInserted;
}
bool Tester::testBasicMerge(RQueue& queue1, RQueue& queue2) {
    queue1.mergeWithQueue(queue2);
    return true;
}
bool Tester::testBasicChangePriority(RQueue& queue) {
    queue.setPriorityFn(priorityFn2);
    return true;
}
bool Tester::testBasicRemove(RQueue& queue) {
    // Remove and print students in priority order
    cout << "Final queue1 in priority order:" << endl;
    while (queue.numStudents() > 0) {
        Student student = queue.getNextStudent();
        cout << "[" << priorityFn1(student) << "] " << student << endl;
    }
    return true;
}

int main() {
    Tester tester;

    RQueue queue1(priorityFn1);
    RQueue queue2(priorityFn1);

    // Test basic insertions
    cout << "Testing basic insertions" << endl;
    if(tester.testBasicInsert1(queue1)) {
        cout << "All insertions passed" << endl;
    }
    else {
        cout << "Insertions failed" << endl;
    }

    cout << "Testing basic insertions" << endl;
    if(tester.testBasicInsert2(queue2)) {
        cout << "All insertions passed" << endl;
    }
    else {
        cout << "Insertions failed" << endl;
    }

    cout << "Testing basic merge" << endl;
    if(tester.testBasicMerge(queue1, queue2)) {
        cout << "Merge passed" << endl;
    }
    else {
        cout << "Merge failed" << endl;
    }

    cout << "Testing basic change priority" << endl;
    if(tester.testBasicChangePriority(queue1)) {
        cout << "Change priority passed" << endl;
    }
    else {
        cout << "Change priority failed" << endl;
    }

    cout << "Changing back" << endl;
    queue1.setPriorityFn(priorityFn1);

    // Remove and print students in priority order
    cout << "Testing basic remove" << endl;
    if(tester.testBasicRemove(queue1)) {
        cout << "Remove passed" << endl;
    }
    else {
        cout << "Remove failed" << endl;
    }

    return 0;
}