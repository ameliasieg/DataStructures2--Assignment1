#include <iostream>
using namespace std;

///////////////////////// TVECTOR FUNCTIONS ///////////////////////////

// Empty Vector
template <typename T>
TVector<T>::TVector()
{
    capacity = SPARECAPACITY;
    size = 0;
    array = new T[capacity];
}

// Two Parameter Constructor
template <typename T>
TVector<T>::TVector(T val, int num)
{
    capacity = num + SPARECAPACITY;
    size = num;
    array = new T[capacity];
   
    for(int i = 0; i < num; i++)
    {
        array[i] = val;
    }
}

// Destructor
template <typename T>
TVector<T>::~TVector()
{
    delete [] array;
    array = nullptr;
}

// Copy Constructor (deep copy)
template <typename T>
TVector<T>::TVector(const TVector<T>& v)	
{
   // Member-by-member deep copy
   capacity = v.capacity;
   size = v.size;
   array = new T[capacity];
   
   for (int i = 0; i < size; i++)
   {
        array[i] = v.array[i];
   }
}

// Copy Assignment operator=
template <typename T>
TVector<T>& TVector<T>::operator=(const TVector<T>& v)
{   
   if (this != &v) // If not self-assignment
   {
      // Delete whole array
      delete[] array;

      // Member-by-member assignment
      capacity = v.capacity; 
      size = v.size;
      
      // Dynamically allocate new space again because we deleted old space 
      array = new T[capacity];
      
      for (int i = 0; i < size; i++)
          array[i] = v.array[i];
       
   }

   return *this; // Return calling object
}

// Move Constructor
template <typename T>
TVector<T>::TVector(TVector<T> && v)
{
   capacity = v.capacity;
   size = v.size;
   array = v.array;

   v.array = nullptr; 
   v.capacity = 0;
   v.size = 0;
}

// Move Assignment
template <typename T>
TVector<T>& TVector<T>::operator=(TVector<T> && v)
{
   // Member-by-member swap (exchange pointer instead of pointee)
   std::swap(capacity, v.capacity);	// Swap trackers between calling object and parameter
   std::swap(size, v.size);
   std::swap(array, v.array); // Trade pointers between calling object and parameter

   return *this;
}

template <typename T>
bool TVector<T>::IsEmpty() const
{
    if (size == 0) // If empty...
        return true;

    else
        return false;

}

template <typename T>
void TVector<T>::Clear()
{
    // Go through the array and make everything empty with the dummy
    for(int i = 0; i < size; i++)
    {
        array[i] = dummy;
    }

    size = 0;
}

// Return the size of the vector
template <typename T>
int TVector<T>::GetSize() const
{
    return size;
}

template <typename T>
void TVector<T>::InsertBack(const T& d)
{
    if(size == capacity)
    {
        SetCapacity(2 * capacity + 1);
    }

    array[size] = d;
    size++;
}

template <typename T>
void TVector<T>::RemoveBack()
{
    array[size - 1] = dummy;
    size--;
}

template <typename T>
T& TVector<T>::GetFirst() const ////////////////////////////////////////////////////////////////////////////////////////////// NOT USED

{
    return array[0];
}

template <typename T>
T& TVector<T>::GetLast() const ////////////////////////////////////////////////////////////////////////////////////////////// NOT USED
{
    return array[size - 1];
}

template <typename T>
TVectorIterator<T> TVector<T>::GetIterator() const
{
    TVectorIterator<T> myIterator;
    
    if (size == 0)
    {
        return myIterator;
    }

    myIterator.ptr = &array[0]; // or just array - from recitation
    myIterator.vsize = size;
    myIterator.index = 0;
}

template <typename T>
TVectorIterator<T> TVector<T>::GetIteratorEnd() const /////////////////////////////////////////////////////////////////////////// NOT USED
{
    TVectorIterator<T> myIterator;
    myIterator.index = size - 1;
    myIterator.vsize = size;
    myIterator.ptr = &array[size - 1];
    return myIterator;
}

template <typename T>
void TVector<T>::SetCapacity(unsigned int c)
{
    T* newArray = new T[c];
   
    for(int i = 0; i < c; i++)
    {
        newArray[i] = array[i];
    }
    
    delete[] array;
    array = newArray;

    if(c < size)
    {
        size = c;
    }

    capacity = c;
}

template <typename T>
TVectorIterator<T> TVector<T>::Insert(TVectorIterator<T> pos, const T& d)
{
    if(size == capacity)
    {
        SetCapacity(capacity + SPARECAPACITY);
    }

    for (int i = 0; i < size - pos.index; i++)
    {
        array[size - i] = array[size - (i + 1)];
    }
    
    array[pos.index] = d;
    pos.vsize++;
    size++;
    return pos;
}

template <typename T>
TVectorIterator<T> TVector<T>::Remove(TVectorIterator<T> pos)
{
    if(size == 0 || pos.index < 0 || pos.index >= size)
    {
        TVectorIterator<T> myIterator;
        return myIterator;
    }

    TVectorIterator<T> myIterator = pos;
    
    for (int i = pos.index; i < size - 1; i++) // This is a move left operation
    {
        array[i] = array[i + 1];
    }
    
    size--;
    myIterator.vsize = size;
    return myIterator; 

}

template <typename T>
TVectorIterator<T> TVector<T>::Remove(TVectorIterator<T> pos1, TVectorIterator<T> pos2) // Removes within a range
{
    // If the initial vector was empty, there's nothing to delete - so just leave it empty and return a default iterator
    if (size == 0)
    {
        return GetIterator();
    }

    // If the first iterator is after the second iterator (error situation), don't delete anything, and just return the first iterator (pos1)
    if (pos2.index < pos1.index)
    {
        return pos1;
    }

    int outsideItr = 0;
    int newSize = 0;

    // Do DMA stuff
    int* newArray = new int[capacity];
    
    for(int i = 0; i < size; i++)
    {
        if(i < pos1.index || i >= pos2.index)
        {
            newArray[outsideItr] = array[i]; // newArray has the contents that we want
            outsideItr++;
            newSize++;
        }
    }

    delete [] array; // Deleting the old array
    array = newArray; // Points array to same memory as newArray
    size = newSize; /// Adjust the size

    TVectorIterator<T> itr;
    
    for(int i = 0; i < pos1.index; i++)
    {
        itr.Next();
    }
    
    return itr; // Because of the return type being an iterator
}

template <typename T>
void TVector<T>::Print(std::ostream& os, char delim) const
{
    if (size == 0)
    {
        os << "Nothing to print, size is 0" << "\n";
    }

    else
        os << array[0];

    for (int i = 1; i < size; i++)
    {
        os << delim << array[i];
    }
}

/////////////////////// TVECTORITERATOR FUNCTIONS //////////////////////////

// VectorIterator Default Constructor
template <typename T>
TVectorIterator<T>::TVectorIterator() 
{
    index = 0; 
    vsize = 0;
    ptr = nullptr;
}

template <typename T>
bool TVectorIterator<T>::HasNext() const
{
    return (vsize != index);
}

template <typename T>
bool TVectorIterator<T>::HasPrevious() const
{
    return (index > 0);
}

template <typename T>
TVectorIterator<T> TVectorIterator<T>::Next()
{
    if (ptr != nullptr && HasNext())
    {
        ptr++;
        index++;
    }

    return *this; // Returns the calling object
}

template <typename T>
TVectorIterator<T> TVectorIterator<T>::Previous()
{
    if (ptr != nullptr && HasPrevious())
    {
        ptr--;
        index--;
    }

    return *this; // Returns the calling object
}

template <typename T>
T& TVectorIterator<T>::GetData() const
{
    if (ptr != nullptr)
    {
        return *ptr;
    }
    
    return TVector<T>::dummy;
}

template <typename T>
TVector<T> operator+(const TVector<T>& t1, const TVector<T>& t2) // Adds stuff to the end of the vector
{
    TVector<T> vector(t1);

    for(auto itr = t2.GetIterator(); itr.HasNext(); itr.Next()) // Moves through t2
    {
        vector.InsertBack(itr.GetData()); // Adds stuff to the back
    }

    return vector;
}
