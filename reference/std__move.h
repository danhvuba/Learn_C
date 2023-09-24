#include <iostream>
#include <vector>
using namespace std;

// std::move()
template <class T>
swap(T& a, T& b) {
    T tmp(a);   // we've made a second copy of a
    a = b;      // we've made a second copy of b (and discarded a copy of a)
    b = tmp;    // we've made a second copy of tmp (and discarded a copy of b)
}

// faster
template <class T>
swap(T& a, T& b) {
    T tmp(std::move(a));
    a = std::move(b);   
    b = std::move(tmp);
}

// Think of what happens when T is, say, vector<int> of size n.
// In the first version you read and write 3*n elements, 
// in the second version you basically read and write just the 3 pointers to the vectors' buffers, plus the 3 buffers' sizes. 
// Of course, class T needs to know how to do the moving; 
// your class should have a move-assignment operator and a move-constructor for class T for this to work.