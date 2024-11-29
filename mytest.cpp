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

        bool testInsertDelete(RQueue& queue);
        bool testChangePriority(RQueue& queue);
        bool testAssignConstructor(RQueue& queue, RQueue& queue2);
        bool testCopyConstructor(RQueue& queue);
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

bool Tester::testInsertDelete(RQueue& queue) {
    Student student1("Sam",1,1,1,1);
    Student student2("Liz",5,1,2,0);
    queue.insertStudent(student1);
    queue.getNextStudent();
    queue.insertStudent(student1);
    queue.getNextStudent();
    queue.insertStudent(student1);
    queue.getNextStudent();

    queue.insertStudent(student1);
    queue.insertStudent(student2);
    queue.getNextStudent();
    queue.getNextStudent();
    try {
        queue.getNextStudent();
    } catch (domain_error &e) {
        cout << "Caught exception: " << e.what() << endl;
    }
    queue.insertStudent(student1);
    queue.insertStudent(student2);
    queue.getNextStudent();
    queue.insertStudent(student1);
    queue.getNextStudent();

    return true;
}
bool Tester::testChangePriority(RQueue& queue) {
    Student student1("Sam",1,1,1,1);
    Student student2("Liz",5,1,2,0);
    Student student3("Nick",2,0,0,0);
    Student student4("Eva",4,3,2,1);

    queue.insertStudent(student1);
    queue.insertStudent(student2);
    queue.insertStudent(student3);
    queue.insertStudent(student4);

    queue.setPriorityFn(priorityFn2);
    queue.setPriorityFn(priorityFn2);
    queue.setPriorityFn(priorityFn2);
    queue.setPriorityFn(priorityFn2);
    queue.setPriorityFn(priorityFn2);
    queue.setPriorityFn(priorityFn1);

    queue.getNextStudent();
    queue.getNextStudent();
    queue.getNextStudent();
    queue.getNextStudent();

    return true;
}
bool Tester::testAssignConstructor(RQueue& queue, RQueue& queue2) {
    queue2 = queue;
    return queue2.numStudents() == queue.numStudents();
}
bool Tester::testCopyConstructor(RQueue& queue) {
    RQueue queue2(queue);
    bool b = queue2.numStudents() == queue.numStudents();
    queue2.clear();

    return b;
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

    cout << "Queue 1 dump after inserting 4 students (Nick, Sam, Liz, Eva):" << endl;
    queue1.dump();

    cout << "Testing basic insertions" << endl;
    if(tester.testBasicInsert2(queue2)) {
        cout << "All insertions passed" << endl;
    }
    else {
        cout << "Insertions failed" << endl;
    }

    cout << "Queue 2 dump after inserting 2 students (John, Mia):" << endl;
    queue2.dump();

    // Test basic merge
    cout << "Testing basic merge" << endl;
    if(tester.testBasicMerge(queue1, queue2)) {
        cout << "Merge passed" << endl;
    }
    else {
        cout << "Merge failed" << endl;
    }

    cout << "Contents of queue1 after merging with queue2:" << endl;
    queue1.dump();

    // Change priority function
    cout << "Testing basic change priority" << endl;
    if(tester.testBasicChangePriority(queue1)) {
        cout << "Change priority passed" << endl;
        cout << "Num students before changing priority fn: " << queue1.numStudents() << endl;
    }
    else {
        cout << "Change priority failed" << endl;
    }

    cout << "Contents of queue1 after changing the priority function to priorityFn2:" << endl;
    queue1.dump();
    cout << "Num students after changing priority fn: " << queue1.numStudents() << endl;

    cout << "Changing back" << endl;
    queue1.setPriorityFn(priorityFn1);
    cout << "Contents of queue1 after changing the priority function to priorityFn1:" << endl;
    queue1.dump();
    cout << "Num students after changing priority fn: " << queue1.numStudents() << endl;


    // Remove and print students in priority order
    cout << "Testing basic remove" << endl;
    if(tester.testBasicRemove(queue1)) {
        cout << "Remove passed" << endl;
    }
    else {
        cout << "Remove failed" << endl;
    }

    cout << endl << endl << endl << "Now for some more advanced tests" << endl;
    cout << "Testing insert and delete" << endl;
    if(tester.testInsertDelete(queue1)) {
        cout << "Insert and delete passed" << endl;
    }
    else {
        cout << "Insert and delete failed" << endl;
    }

    cout << "Testing change priority" << endl;
    if(tester.testChangePriority(queue1)) {
        cout << "Change priority passed" << endl;
    }
    else {
        cout << "Change priority failed" << endl;
    }

    cout << "Testing assign constructor" << endl;
    RQueue tempQueue(priorityFn1);
    if(tester.testAssignConstructor(queue1, tempQueue)) {
        cout << "Assign constructor passed" << endl;
    }
    else {
        cout << "Assign constructor failed" << endl;
    }

    cout << "Testing copy constructor" << endl;
    if(tester.testCopyConstructor(queue1)) {
        cout << "Copy constructor passed" << endl;
    }
    else {
        cout << "Copy constructor failed" << endl;
    }
    

    return 0;
}