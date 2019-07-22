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

template <typename T>
struct List
{
private:
  unsigned int lenght;
  T *data;

public:
  // Constructor with specifict list size
  List(unsigned int _size_nodes) : lenght(0)
  {
    this->data = new T[_size_nodes];
  }

  // Constructor with zero values
  List() : lenght(0), data(NULL) {}
  // Destructor of the structure
  ~List() { this->clear(); }

  T operator[](unsigned int);
  int length() const;
  List<T> *clear();
  List<T> *push(T);
  List<T> *push_front(T);
  T pop();
  T pop_back();
  void forEach(void (*function)(int, T &));
  List<T> filter(bool (*function)(T));
  template <typename Tresult>
  List<Tresult> map(Tresult (*function)(T));
  T find(bool (*function)(T));
  T first();
  T last();
};

// Operator overloading to get/set values of the list
template <typename T>
T List<T>::operator[](unsigned int index)
{
  if (this->lenght > index && index >= 0)
  {
    return this->data[index];
  }
  return T();
}

// Get the length of the list
template <typename T>
int List<T>::length() const
{
  return this->lenght;
}

// Deletes all the values
template <typename T>
List<T> *List<T>::clear()
{
  delete[] this->data;
  this->lenght = 0;
  return this;
}

// Adds a value into the front of the list
template <typename T>
List<T> *List<T>::push_front(T data)
{
  T *new_data_pos = new T[this->lenght + 1]();
  T *old_data_pos = this->data;
  new_data_pos[0] = data;
  for (int i = 0; i < this->lenght; i++)
  {
    new_data_pos[i + 1] = old_data_pos[i];
  }
  delete[] old_data_pos;
  this->data = new_data_pos;
  this->lenght++;
  return this;
}

// Adds a value into the last of the list
template <typename T>
List<T> *List<T>::push(T data)
{
  T *new_data_pos = new T[this->lenght + 1]();
  T *old_data_pos = this->data;
  for (int i = 0; i < this->lenght; i++)
  {
    new_data_pos[i] = old_data_pos[i];
  }
  new_data_pos[this->lenght] = data;
  delete[] old_data_pos;
  this->data = new_data_pos;
  this->lenght++;
  return this;
}

// Deletes the last value
template <typename T>
T List<T>::pop_back()
{
  T *new_data_pos = new T[this->lenght - 1]();
  T *old_data_pos = this->data;
  for (int i = 0; i < (this->lenght - 1); i++)
  {
    new_data_pos[i] = old_data_pos[i];
  }
  T data_pop = old_data_pos[this->lenght - 1];
  delete[] old_data_pos;
  this->data = new_data_pos;
  this->lenght--;
  return data_pop;
}

// Deletes the firsh value
template <typename T>
T List<T>::pop()
{
  T *new_data_pos = new T[this->lenght - 1]();
  T *old_data_pos = this->data;
  for (int i = 0; i < (this->lenght - 1); i++)
  {
    new_data_pos[i] = old_data_pos[i + 1];
  }
  T data_pop = old_data_pos[0];
  delete[] old_data_pos;
  this->data = new_data_pos;
  this->lenght--;
  return data_pop;
}

// Executes a function to every value
template <typename T>
void List<T>::forEach(void (*function)(int, T &))
{
  for (int index = 0; index < this->lenght; index++)
  {
    T val = this->data[index];
    function(index, val);
  }
}

// Maps the actual List into other List
template <typename T>
template <typename Tresult>
List<Tresult> List<T>::map(Tresult (*function)(T))
{
  List<Tresult> output;
  for (int index = 0; index < this->lenght; index++)
  {
    const T val = this->data[index];
    Tresult data = function(val);
    output.push(data);
  }
  return output;
}

// Returns a list with the values filtered
template <typename T>
List<T> List<T>::filter(bool (*function)(T))
{
  List<T> output;
  for (int index = 0; index < this->lenght; index++)
  {
    const T val = this->data[index];
    if (function(val))
    {
      output.push(val);
    }
  }
  return output;
}

template <typename T>
T List<T>::find(bool (*function)(T))
{
  for (int index = 0; index < this->lenght; index++)
  {
    const T val = this->data[index];
    if (function(val))
    {
      return val;
    }
  }
  return T();
}

template <typename T>
T List<T>::first() {
  return (*this)[0];
}

template <typename T>
T List<T>::last() { return (*this)[this->lenght - 1]; }

#endif