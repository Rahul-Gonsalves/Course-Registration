// RQueue: 

#include "rqueue.h"
using namespace std;
using std::cout;
using std::endl;
using std::domain_error;
#include <vector>

RQueue::RQueue(prifn_t priFn)
{
  _heap = nullptr;
  _size = 0;
  priority = priFn;
}

RQueue::~RQueue()
{
  clear();
}

RQueue::RQueue(const RQueue& rhs) 
{
  if(rhs._size == 0) {
    _size = 0;
    priority = rhs.priority;
    _heap = nullptr;
    return;
  }
  _heap = deepCopy(rhs._heap);
  _size = rhs._size;
  priority = rhs.priority;
}

RQueue& RQueue::operator=(const RQueue& rhs)
{
  if(this == &rhs) {
    return *this;
  }
  
  clear();
  _heap = deepCopy(rhs._heap);
  _size = rhs._size;
  priority = rhs.priority;
  return *this;
}

Node* RQueue::deepCopy(Node* copy) //if there is a need to deep copy
{
  if(copy == nullptr) {
    return nullptr;
  }
  Node* newNode = new Node(copy->_student);
  newNode->_left = deepCopy(copy->_left);
  newNode->_right = deepCopy(copy->_right);
  return newNode;
}

void RQueue::insertStudent(const Student& input) {
  if(_size == 0) { //if the heap is empty, create a new minheap with the input student
    _heap = new Node(input);
    _size++;
    return;
  }

  // Create a new heap with the input student
  RQueue newHeap = RQueue(priority);
  newHeap._heap = new Node(input);
  newHeap._size = 1;

  // Merge the current heap into the new heap
  newHeap.mergeWithQueue(*this);
  delete _heap; // delete the current heap

  // Update the current heap to be the new merged heap
  _heap = newHeap._heap;
  _size = newHeap._size;

  newHeap._heap = nullptr;
  newHeap._size = 0;
  
}

Student RQueue::getNextStudent() {
  if (_heap == nullptr || _size == 0) {
    throw std::domain_error("Queue is empty.");
  }

  // Pop off the root student
  Student student = _heap->_student;

  // Remove the root and reheapify
  Node* oldHeap = _heap;
  _heap = mergeHelp(_heap->_left, _heap->_right);
  delete oldHeap;
  _size--;

  return student;
}

void RQueue::mergeWithQueue(RQueue& rhs) { 
  //check priority function
  if (priority != rhs.priority) {
    throw domain_error("Priority functions do not match.");
  }

  _size += rhs._size; // update the size
  _heap = mergeHelp(_heap, rhs._heap); // merge the two heaps
  

  rhs._size = 0; 
  rhs._heap = nullptr;
}

Node* RQueue::mergeHelp(Node* p1, Node* p2) {
  //If p1 is nullptr, return p2
  if(p2 == nullptr) {
    return p1;
  }
  else if (p1 == nullptr) {
    return p2;
  }

  //If p1 does not have higher priority than p2, swap p1 and p2
  if (priority(p2->_student) < priority(p1->_student)) {
    Node *temp = p1;
    p1 = p2;
    p2 = temp;
  }

  //Swap the left and right subtrees of p1
  Node *temp = p1->_left;
  //Recursively merge p2 with the subtree of p1
  p1->_left = mergeHelp(p1->_right, p2);
  p1->_right = temp;

  return p1;
}

void RQueue::clear() {
  if(_heap == nullptr) {
    return;
  }
  while(_heap != nullptr) {
    getNextStudent();
  }
  _size = 0;
  _heap = nullptr;
}

int RQueue::numStudents() const
{
  return _size;
}

void RQueue::printStudentQueue() const {
  //preorder traversal
  cout << "Contents of the student queue:" << endl;
  printHelp(_heap);
  
}
void RQueue::printHelp(Node* pos) const {
  
  if (pos != nullptr) {
    cout << "[" <<priority(pos->_student) << "] " << pos->_student << endl;
    printHelp(pos->_left);
    printHelp(pos->_right);
  }
  else {
    return;
  }
}

prifn_t RQueue::getPriorityFn() const {

  return priority;

}

void RQueue::setPriorityFn(prifn_t priFn) {
  //if the new function is the same as the current, do nothing
  if(priFn == priority) { return; } 

    // put all students into a vector
    std::vector<Student> students;
    while (_heap != nullptr) {
      students.push_back(getNextStudent());
    }

    priority = priFn;

    // Rebuild the heap
    for (const auto& student : students) {
        insertStudent(student);
    }
}


// for debugging
void RQueue::dump() const
{
  if (_size == 0) {
    cout << "Empty skew heap.\n" ;
  } else {
    dump(_heap);
    cout << endl;
  }
}

// for debugging
void RQueue::dump(Node *pos) const {
  if ( pos != nullptr ) {
    cout << "(";
    dump(pos->_left);
    cout << priority(pos->_student) << ":" << pos->_student.getName();
    dump(pos->_right);
    cout << ")";
  }
}

// overloaded insertion operator for Student class
ostream& operator<<(ostream& sout, const Student& student) {
  sout << "Student: " << student.getName() << ", priority: " << student.getPriority()
       << ", year: " << student.getYear() << ", major: " << student.getMajorStr() 
       << ", group: " << student.getGroupStr();
  return sout;
}

// overloaded insertion operator for Node class
ostream& operator<<(ostream& sout, const Node& node) {
  sout << node.getStudent();
  return sout;
}