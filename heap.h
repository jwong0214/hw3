#ifndef HEAP_H
#define HEAP_H
#include <functional>
#include <stdexcept>
#include <vector>

template <typename T, typename PComparator = std::less<T> >
class Heap
{
public:
  /**
   * @brief Construct a new Heap object
   * 
   * @param m ary-ness of heap tree (default to 2)
   * @param c binary predicate function/functor that takes two items
   *          as an argument and returns a bool if the first argument has
   *          priority over the second.
   */
  Heap(int m=2, PComparator c = PComparator());

  /**
  * @brief Destroy the Heap object
  * 
  */
  ~Heap();

  /**
   * @brief Push an item to the heap
   * 
   * @param item item to heap
   */
  void push(const T& item);

  /**
   * @brief Returns the top (priority) item
   * 
   * @return T const& top priority item
   * @throw std::underflow_error if the heap is empty
   */
  T const & top() const;

  /**
   * @brief Remove the top priority item
   * 
   * @throw std::underflow_error if the heap is empty
   */
  void pop();

  /// returns true if the heap is empty

  /**
   * @brief Returns true if the heap is empty
   * 
   */
  bool empty() const;

    /**
   * @brief Returns size of the heap
   * 
   */
  size_t size() const;

private:
  /// Add whatever helper functions and data members you need below
  void trickleUp(size_t index);
  void heapify(size_t index);

  std::vector<T> data_;
  PComparator comp_;
  int m_;
};

// Add implementation of member functions here
template <typename T, typename PComparator>
Heap<T,PComparator>::Heap(int m, PComparator c)
  : data_(), comp_(c), m_(m)
{
  if(m_ < 2) {
    throw std::invalid_argument("Heap m must be greater than or equal to 2.");
  }
}

template <typename T, typename PComparator>
Heap<T,PComparator>::~Heap()
{
}

template <typename T, typename PComparator>
bool Heap<T,PComparator>::empty() const
{
  return data_.empty();
}

template <typename T, typename PComparator>
size_t Heap<T,PComparator>::size() const
{
  return data_.size();
}

template <typename T, typename PComparator>
void Heap<T,PComparator>::push(const T& item)
{
  data_.push_back(item);
  trickleUp(data_.size() - 1);
}

// We will start top() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
T const & Heap<T,PComparator>::top() const
{
  // Here we use exceptions to handle the case of trying
  // to access the top element of an empty heap
  if(empty()){
    // ================================
    // throw the appropriate exception
    // ================================
    throw std::underflow_error("Called on an empty heap.");
  }
  // If we get here we know the heap has at least 1 item
  // Add code to return the top element
  return data_.front();
}


// We will start pop() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
void Heap<T,PComparator>::pop()
{
  if(empty()){
    // ================================
    // throw the appropriate exception
    // ================================
    throw std::underflow_error("Called on an empty heap.");
  }
  data_.front() = data_.back();
  data_.pop_back();
  if(!empty()) {
    heapify(0);
  }
}

template <typename T, typename PComparator>
void Heap<T,PComparator>::trickleUp(size_t index)
{
  if(index == 0) return;

  size_t parent = (index - 1) / m_;
  if(comp_(data_[index], data_[parent])) {
    std::swap(data_[index], data_[parent]);
    trickleUp(parent);
  }
}

template <typename T, typename PComparator>
void Heap<T,PComparator>::heapify(size_t index)
{
  size_t best = index;
  size_t childStart = m_ * index + 1;

  for(size_t k = 0; k < (size_t)m_; ++k)
  {
    size_t child = childStart + k;
    if(child < data_.size() && comp_(data_[child], data_[best])) {
      best = child;
    }
  }

  if(best != index) {
    std::swap(data_[index], data_[best]);
    heapify(best);
  }
}

#endif

