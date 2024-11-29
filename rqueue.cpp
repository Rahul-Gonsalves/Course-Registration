// RQueue: 

#include "rqueue.h"
using namespace std;
using std::cout;
using std::endl;
using std::domain_error;

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

  clear();
  if(rhs._size == 0) {
    _size = 0;
    priority = rhs.priority;
    return;
  }
  _heap = new Node (*rhs._heap); //deep copy
  _size = rhs._size;
  priority = rhs.priority;
}

RQueue& RQueue::operator=(const RQueue& rhs)
{
  if(this == &rhs) {
    return *this;
  }
  
  clear();
  _heap = new Node (*rhs._heap); //deep copy
  _size = rhs._size;
  priority = rhs.priority;
  return *this;
  

}

void RQueue::insertStudent(const Student& input) {
  if(_size == 0) { //if the heap is empty, create a new minheap with the input student
    _heap = new Node(input);
    _size++;
    return;
  }

  //create a new minheap to merge to the current heap
  RQueue newQueue(priority);
  newQueue._heap = new Node(input);
  newQueue._size = 1;

  mergeWithQueue(newQueue);
}

Student RQueue::getNextStudent() {
  if (_size == 0) {
    throw domain_error("Queue is empty.");
  }
  int size = _size - 1;
  Student student = _heap->_student; // get the student with the highest priority
  
  Node* left = _heap->_left; 
  Node* right = _heap->_right; 
  delete _heap; // delete the root node
  
  mergeHelp(left, right); // merge the left and right subtrees
  _heap = left; // set the heap to the merged heap

  _size = size; // decrement the size
  return student;
}


void RQueue::mergeWithQueue(RQueue& rhs) { 
  //check priority function
  if (priority != rhs.priority) {
    throw domain_error("Priority functions do not match.");
  }

  if (_heap == nullptr) { // if the heap is empty, set the heap to the rhs heap

    if(rhs._heap == nullptr) { return; } // if the rhs heap is empty, return
    _heap = new Node(*rhs._heap); 
    //rhs.clear();
    rhs._heap = nullptr;
  } 
  else if (rhs._heap == nullptr) { return; } // if the rhs heap is empty, return
  else { // if both heaps are not empty
    _size += rhs._size; // add the size of the rhs heap to the size of the current heap

    // if the rhs heap has a higher priority (lower number), swap the heaps
    if (priority(_heap->_student) > priority(rhs._heap->_student)) { 
      //swap the heaps
      Node *temp = _heap;
      _heap = rhs._heap;
      rhs._heap = temp;
    }
    //now recursively merge rhs and the left subtree of the heap, replacing the left subtree of p1 with the result of the recursive merge.
    mergeHelp(_heap, rhs._heap); // call helper function to merge the two heaps
    
  }
}

void RQueue::mergeHelp(Node* &p1, Node* &p2) {
  //If p1 is nullptr, return p2
  if (p1 == nullptr) {
    if(p2 == nullptr) { return; } // if the rhs heap is empty, return
    p1 = new Node(*p2);
    p2 = nullptr;
    return;
  }
  //If p2 is nullptr, return p1
  else if (p2 == nullptr) {
    return;
  }

  //If p1 does not have higher priority than p2, swap p1 and p2
  if (priority(p2->_student) < priority(p1->_student)) {
    Node *temp = p1;
    p1 = p2;
    p2 = temp;
  }

  //Swap the left and right subtrees of p1
  Node *temp = p1->_left;
  p1->_left = p1->_right;
  p1->_right = temp;

  //Recursively merge p2 with the left subtree of p1
  mergeHelp(p1->_left, p2);
}

void RQueue::clear() {
  if (_size == 0) { // if the heap is empty, return
    return;
  }
  clearHelp(_heap); // call helper funct to delete all nodes
  _heap = nullptr;
  _size = 0;
}

void RQueue::clearHelp(Node *pos) {
  if(pos == nullptr) {
    return;
  }
  clearHelp(pos->_left);
  clearHelp(pos->_right);
  delete pos;
  pos = nullptr;
}

int RQueue::numStudents() const
{
  return _size;
}

void RQueue::printStudentQueue() const {
  //preorder traversal
  printHelp(_heap);
  
}
void RQueue::printHelp(Node* pos) const {
  if (pos != nullptr) {
    cout << pos->_student << endl;
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

  int size = _size; //keep the size for later
  priority = priFn;
  
  //rebuild the heap
  RQueue newQueue(priority);
  while (_size > 0) {
    newQueue.insertStudent(getNextStudent());
  }
  delete _heap;

  _heap = newQueue._heap;
  _size = size; //reset the size

  newQueue._heap = nullptr;


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