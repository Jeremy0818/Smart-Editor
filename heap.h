// - - - - - - - - - - - - - - - - - - - -
//   Name : Jeremy Choo, Siyuan Liu
//   ID : 1602380, 1589879
//   CMPUT 275, Winter 2019
//
//   project: Text Editor
// - - - - - - - - - - - - - - - - - - - -
#ifndef _HEAP_H_
#define _HEAP_H_

#include <vector>
#include <algorithm>
#include <utility>


using namespace std;
// Only assumes the key type K is totally ordered and comparable via <

template <class T, class K>
class BinaryHeap {
public:
  // constructor not required because the only "initialization"
  // is through the constructor of the variable "heap" which is called by default

  // return the minimum element in the heap
  pair<T, K> max() const;

  // insert an item with the given key
  // if the item is already in the heap, will still insert a new copy with this key
  void insert(const T& item, const K& key);

  // pop the minimum item from the heap
  void popMax();

  // update the node in the tree
  void update(int index);

  // find function for heap
  int find(const T& val) const;

  // returns the number of items held in the heap
  int size() const;

private:
  // the array holding the heap
  std::vector< pair<T, K> > heap;

  //  will fix the heap property at index i and interate with its parent
  void fixHeapUp(int i);

  // will fix the heap property at index i and iterate with the child
  // that received i's item (if appropriate)
  void fixHeapDown(int i);
};

template <class T, class K>
pair<T, K> BinaryHeap<T, K>::max() const {
  // the underlying vector throws an exception if the heap is empty
  return heap.at(0);
}

template <class T, class K>
void BinaryHeap<T, K>::insert(const T& item, const K& key) {
  pair<T, K> node(item, key);

  // add the new item to the end of the heap
  heap.push_back(node);

  // fix the heap property
  fixHeapUp(heap.size()-1);
}

template <class T, class K>
void BinaryHeap<T, K>::popMax() {
  // move the last item of the last layer to the top
  // if the heap has size 1, this just pops it
  heap[0] = heap.back();
  heap.pop_back();

  // if there is anything left in the heap, fix the heap property
  if (heap.size() > 0) {
    fixHeapDown(0);
  }
}

template <class T, class K>
int BinaryHeap<T, K>::size() const {
  return heap.size();
}

template <class T, class K>
void BinaryHeap<T, K>::fixHeapUp(int i) {
  while (i > 0) {
    int pi = (i-1)>>1; // parent index

    // if i's key is smaller than its parent's key, swap it and go up
    if (heap[i].second > heap[pi].second) {
      std::swap(heap[i], heap[pi]);
      i = pi;
    }
    else {
      // otherwise, no more fixing needs to be done
      return;
    }
  }
}

template <class T, class K>
void BinaryHeap<T, K>::fixHeapDown(int i) {
  while (true) {
    // calculate indices of the two children
    int lchild = (i<<1)+1, rchild = (i<<1)+2;

    // if no children, no problem
    if (lchild >= heap.size()) {
      return;
    }

    int max_child;
    // identify the child with the minimum key, being careful
    // to handle the case where there is no right child
    if (rchild >= heap.size() || heap[lchild].second > heap[rchild].second) {
      max_child = lchild;
    }
    else {
      max_child = rchild;
    }

    // if there is a violation of the heap property for i, swap its node
    // with the node held by the minimum-key child and repeat with this child
    if (heap[max_child].second > heap[i].second) {
      std::swap(heap[i], heap[max_child]);
      i = max_child;
    }
    else {
      return;
    }
  }
}

template <class T, class K>
void BinaryHeap<T, K>::update(int index) {
  /*
  This function will update the frequency of the word by adding one and fix the heap
  so that it still satisfy the heap property.
  Argument:
    index: the index of the word in the vector heap to be updated
  */
  heap[index].second += 1;
  int pi = (index - 1) >> 1; // parent index
  if (pi <= 0)
    return;
  if (heap[pi] < heap[index])
    fixHeapUp(index);
  else
    fixHeapDown(index);
}

template <class T, class K>
int BinaryHeap<T, K>::find(const T& val) const {
  /*
  This function will find the index of the word in the heap.
  Argument:
    val: the value of the string
  return:
    index: the index of the word in the vector heap
  */
  int index = 0;
  for (auto it = heap.begin() ; it != heap.end() ; it++) {
    if (it->first == val)
      break;
    index++;
  }
  return index;
}

#endif
