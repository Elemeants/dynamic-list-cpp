// ---------------------------------------------------------------------------
// Dinamic array library - v1.1
//
// AUTHOR:
// Created by Daniel Polanco - Jdanypa@gmail.com
//    Github: https://github.com/Elemeants/dynamic-list-cpp/
//
// CONSTRUCTOR:
//    List<Type>(Size)
//        - Type: Define the kind of var of the List
//        - Size: Specifies the initial size of the list
//                if is empty the default size is 0
//
// METHODS:
//    length() : Returns the length
//    clear()  : Deletes all the values from the List
//    push(T)  : Adds a value to the front
//    push_back(T) : Adds a value to the back
//    pop()    : Deletes the last value
//    pop_front()  : Deletes the first value
//    forEach(std::function<void(int, T&)>)
//             : Executes a function to every value
//    map(std::function<Result(T&)>)
//             : Maps the actual List into other List
//    filter(std::function<bool(T&)> function)
//            : Returns a list with the values filtered
//
// Examples:
//    Create a new List of kind T:
//      [1]-. List<int> integerList = List<int>();
//      [2]-. List<int> integerList = List<int>(40);
//
//    Push values into a List:
//      [1]-. integerList.push(20);
//       -> [ ] <- [1], [2], [3]
//           0      1    2    3
//         Is inserted in the start of the list
//      [2]-. integerList.push_back(20);
//          [1], [2], [3] -> [ ] <-
//           0    1    2      3
//         Is inserted in the end of the list
//
//    Pop values from List:
//      [1]-. integerList.push_back(20) -> T;
//          [1], [2], [3] -> [ ] <-
//           0    1    2      3
//         The last value is deleted and is returned
//      [2]-. integerList.pop_front() -> T;
//       -> [ ] <- [1], [2], [3]
//           0      1    2    3
//         The first value is deleted and is returned
//
//     Get/Set a value from the List:
//       [GET]-. int value = integerList[3];
//          [1], [2], [3] -> [4] <-
//           0    1    2      3
//          So 'value' is going to be '4'
//       [SET]-. integerList[3] = 3;
//          [1], [2], [3] -> [4 -> 3] <-
//           0    1    2        3
//          The value of the index 3 is changed to 3
//
//      Clean the List:
//        [1] integerList.clean();
//          [1], [2], [3], [4]  -> [0]
//           0    1    2    3   ->  0
//          Deletes all the values and returns a empty List
//
//
//
// HISTORY:
// 05/07/2019 v1.1 - Fix bug and new repo on Github
// 31/01/2019 v1.0 - First version
// ---------------------------------------------------------------------------
#ifndef LIST_H
#define LIST_H

template <typename T>
struct Node {
    T data;
    Node *next;
    Node()
    : data(T()), next(NULL) { }
    Node(T _data)
    : data(_data), next(NULL) { }
    ~Node() { }
};

template <typename T>
struct List
{
private:
  size_t _len;
  struct Node<T> *arr_data;
  struct Node<T> *GetIter() {
    return this->arr_data;
  }
public:
  // Constructor with specifict list size
  List(unsigned int _size_nodes)
  {
    this->_len = 0;
    if (this->arr_data) {
      delete this->arr_data;
      this->arr_data = NULL;
    }
    for (int i = 0; i < _size_nodes; i++) this->push(T());
  }

  // Constructor with zero values
  List()
  {
    this->_len = 0;
    this->arr_data = NULL;
  }

  // Destructor of the structure
  ~List()
  {
    this->_len = 0;
    this->clear();
  }

  T operator[](unsigned int);
  int length() const;
  List<T> *clear();
  List<T> *push(T);
  List<T> *push_front(T);
  T pop();
  T pop_back();
  void forEach(void (*function)(int, T&));
  List<T> filter(bool (*function)(T));
  template <typename Result>
  List<Result> map(Result (*function)(T));
};


// Operator overloading to get/set values of the list
template <typename T>
T List<T>::operator[](unsigned int index){
  if (this->_len > index) {
    Node<T> *iter = this->GetIter();
    for (int i = 0; iter->next != NULL && i <= index; i++) {
      iter = iter->next;
    }
    return iter->data;
  }
  return T();
}

// Get the length of the list
template <typename T>
int List<T>::length() const {
  return this->_len;
}

// Deletes all the values
template <typename T>
List<T> * List<T>::clear() {
  while (this->arr_data != NULL) {
    Node<T> *iter = this->arr_data;
    this->arr_data = iter->next;
    delete iter;
  }
  this->_len = 0;
  return this;
}

// Adds a value into the front of the list
template <typename T>
List<T> *List<T>::push_front(T data) {
  Node<T> *new_node = new Node<T>(data);
  if (this->arr_data == NULL) {
    this->arr_data = new_node;
  }
  else {
    new_node->next = this->arr_data;
    this->arr_data = new_node;
  }
  this->_len++;
  return this;
}

// Adds a value into the last of the list
template <typename T>
List<T> *List<T>::push(T data)
{
  Node<T> *new_node = new Node<T>(data);
  Node<T> *iter = this->GetIter();
  if (this->arr_data == NULL) {
    this->arr_data = new_node;
  }
  else {
    while (iter->next != NULL) {
      iter = iter->next;
    }
    iter->next = new_node;
  }
  this->_len++;
  return this;
}

// Deletes the last value
template <typename T>
T List<T>::pop_back() {
  Node<T> *iter = this->GetIter();
  Node<T> *aux_node = this->GetIter();
  while (iter->next != NULL) {
    aux_node = iter;
    iter = iter->next;
  }
  this->_len--;
  aux_node->next = NULL;
  T data = iter->data;
  delete iter;
  return data;
}

// Deletes the firsh value
template <typename T>
T List<T>::pop()
{
  Node<T> *iter = this->GetIter();
  this->arr_data = iter->next;
  T data = iter->data;
  this->_len--;
  delete iter;
  return data;
}

// Executes a function to every value
template <typename T>
void List<T>::forEach(void (*function)(int, T&))
{
  Node<T> *iter = this->GetIter();
  for (int index = 0; iter != NULL && index < this->_len; index++)
  {
    function(index, iter->data);
    iter = iter->next;
  }
}

// Maps the actual List into other List
template <typename T>
template <typename Result>
List<Result> List<T>::map(Result (*function)(T))
{
  List<Result> output = List<Result>();
  Node<T> *iter = this->GetIter();
  for (int index = 0; iter != NULL && index < this->_len; index++)
  {
    Result data = function(iter->data);
    output.push(data);
    iter = iter->next;
  }
  return output;
}

// Returns a list with the values filtered
template <typename T>
List<T> List<T>::filter(bool (*function)(T))
{
  List<T> output = List<T>();
  Node<T> *iter = this->GetIter();
  for (int index = 0; iter != NULL && index < this->_len; index++)
  {
    const T indexVal = iter->data;
    if (function(indexVal))
    {
      output.push(indexVal);
    }
    iter = iter->next;
  }
  return output;
}

#endif