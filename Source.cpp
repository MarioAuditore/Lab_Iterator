#include "Header.h"

int main() {
  Deque<int> dq;
  //------------
  DequeIterator<Deque<int>> IsEmptyCheck = dq.begin();
  cout << "Dequeue is empty? - " << dq.IteratorIsEmpty(IsEmptyCheck) << endl;
  
  //------------
  cout << "Filling the Deque"<<endl;
  dq.insertlast(5);
  dq.insertlast(10);
  dq.insertlast(15);
  dq.insertlast(20);
  dq.insertlast(2);
  dq.insertlast(5);
  dq.insertlast(-13);
  dq.insertlast(47);
  dq.insertlast(1);
  cout << "Deque: " << endl;
  dq.show();
  IsEmptyCheck = dq.begin();
  cout << "Dequeue is empty? - " << dq.IteratorIsEmpty(IsEmptyCheck) << endl;
 

  cout << "______________________________" << endl;
  DequeIterator<Deque<int>> MyIterator = dq.begin();
  cout << "MyIterator begin" << MyIterator->data << endl;
  ++MyIterator;
  cout << "operand++ x1 Myiter " << MyIterator->data<<endl;
  ++MyIterator;
  cout << "operand++ x2 Myiter " << MyIterator->data << endl;
  DequeIterator<Deque<int>> MyIterator_end = dq.end();
  cout << "end " << MyIterator_end->data << endl;

  cout << "______________________________" << endl;
  cout << "Deque before:" << endl;
  dq.show();
  cout << "Insert number -12 on position of operand++ x2 Myiter " << endl;
  cout << "Operation result" << dq.insert(MyIterator, -12)->data << endl;
  cout << "Deque after:" << endl;
  dq.show();

  cout << "______________________________" << endl;
  cout << "Erase position - 3 with the help of MyIterator++ x2 (same one) " << endl;
  cout << "Eraseure result "<<dq.erase(MyIterator)->data << endl;
  cout << "Deque after:" << endl;
  dq.show();

  cout << "______________________________" << endl;
  cout << "Erase from begin++ x5 to end (For end will use MyIterator_end):" << endl;
  MyIterator = dq.begin();
  for (int i = 0; i < 5; i++)
  {
    MyIterator++;
  }
  cout << "Mass erasure result " << dq.erase(MyIterator, MyIterator_end)->data << endl;
  cout << "Deque after:" << endl;
  dq.show();


  cout << "______________________________" << endl;
  cout << "Let's create second deque and swap it with first" << endl;
  Deque<int> dq4swap;
  
  for (int i = 0; i < 10; i++)
  {
    dq4swap.insertlast(i);
  }
  cout << "dq4swap before swap: " << endl;
  dq4swap.show();
  dq.swap(&dq4swap);

  cout << "Dq after swap:" << endl;
  dq.show();

  cout << "dq4swap after swap: " << endl;
  dq4swap.show();
  
  return 0;
}