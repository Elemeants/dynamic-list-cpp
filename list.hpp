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
//    map(std::function<Tresult(T&)>)
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

#define loop_node(iterator_name) for(; iterator_name->next != NULL; iterator_name = iterator_name->next)
#define while_node(iterator_name) while(iterator_name->next != NULL)
#define loop_index_node(iter, lenght) for (unsigned int index = 0; iter != NULL && index < lenght; index++)

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
  unsigned int lenght;
  struct Node<T> *start_node;
  struct Node<T> *get_start_node() {
    return this->start_node;
  }
  struct Node<T> *get_last_node() {
    Node<T> *iterator_node = this->get_start_node();
    loop_node(iterator_node);
    return iterator_node;
  }
public:
  // Constructor with specifict list size
  List(unsigned int _size_nodes) : lenght(0), start_node(NULL)
  {
    for (int i = 0; i < _size_nodes; i++) this->push(T());
  }

  // Constructor with zero values
  List(): lenght(0), start_node(NULL) { }
  // Destructor of the structure
  ~List() { this->clear(); }

  T operator[](unsigned int);
  int length() const;
  List<T> *clear();
  List<T> *push(T);
  List<T> *push_front(T);
  T pop();
  T pop_back();
  void forEach(void (*function)(int, T&));
  List<T> filter(bool (*function)(T));
  template <typename Tresult>
  List<Tresult> map(Tresult (*function)(T));
  T find(bool (*function)(T));
};

// Operator overloading to get/set values of the list
template <typename T>
T List<T>::operator[](unsigned int index) {
  if (this->lenght > index) {
    Node<T> *iter = this->get_start_node();
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
  return this->lenght;
}

// Deletes all the values
template <typename T>
List<T> * List<T>::clear() {
  while (this->start_node != NULL) {
    Node<T> *iter = this->start_node;
    this->start_node = iter->next;
    delete iter;
  }
  this->lenght = 0;
  return this;
}

// Adds a value into the front of the list
template <typename T>
List<T> *List<T>::push_front(T data) {
  Node<T> *n_data = new Node<T>(data);
  if (this->start_node == NULL) {
    this->start_node = n_data;
  }
  else {
    n_data->next = this->start_node;
    this->start_node = n_data;
  }
  this->lenght++;
  return this;
}

// Adds a value into the last of the list
template <typename T>
List<T> *List<T>::push(T data)
{
  Node<T> *new_node = new Node<T>(data);
  if (this->start_node == NULL) {
    this->start_node = new_node;
  }
  else {
    this->get_last_node()->next = new_node;
  }
  this->lenght++;
  return this;
}

// Deletes the last value
template <typename T>
T List<T>::pop_back() {
  Node<T> *iterator = this->get_start_node();
  Node<T> *aux_node = this->get_start_node();
  while (iterator->next != NULL) {
    aux_node = iterator;
    iterator = iterator->next;
  }
  this->lenght--;
  aux_node->next = NULL;
  T data = iterator->data;
  delete iterator;
  return data;
}

// Deletes the firsh value
template <typename T>
T List<T>::pop()
{
  Node<T> *iter = this->get_start_node();
  this->start_node = iter->next;
  T data = iter->data;
  this->lenght--;
  delete iter;
  return data;
}

// Executes a function to every value
template <typename T>
void List<T>::forEach(void (*function)(int, T&))
{
  Node<T> *iter = this->get_start_node();
  loop_index_node(iter, this->lenght)
  {
    function(index, iter->data);
    iter = iter->next;
  }
}

// Maps the actual List into other List
template <typename T>
template <typename Tresult>
List<Tresult> List<T>::map(Tresult (*function)(T))
{
  List<Tresult> output = List<Tresult>();
  Node<T> *iter = this->get_start_node();
  loop_index_node(iter, this->lenght)
  {
    const T iterator_data = iter->data;
    Tresult data = function(iterator_data);
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
  Node<T> *iter = this->get_start_node();
  loop_index_node(iter, this->lenght)
  {
    const T iterator_data = iter->data;
    if (function(iterator_data))
    {
      output.push(iterator_data);
    }
    iter = iter->next;
  }
  return output;
}

template <typename T>
T List<T>::find(bool (*function)(T))
{
  Node<T>* iterator = this->get_start_node();
  loop_index_node(iterator, this->lenght)
  {
    const T iterator_data = iterator->data;
    if (function(iterator_data)) { return iterator_data; }
    iterator = iterator->next;
  }
  return T();
}

#endif