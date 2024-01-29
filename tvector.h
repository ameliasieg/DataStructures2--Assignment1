#include <iostream>
#include <utility>

template <typename T>   class TVectorIterator; // Forward declaration

// Declaration of class TVector
template <typename T>
class TVector
{
   friend class TVectorIterator<T>;

   public:
   
   TVector();				         // Empty Vector
   TVector(T val, int num);		// Vector with num copies of val - two parameter

   ~TVector();					                      // Destructor
   TVector(const TVector<T>& v);		            // Copy constructor
   TVector<T>& operator=(const TVector<T>& v);  // Copy assignment operator

   TVector(TVector<T> && v);			         // Move constructor
   TVector<T>& operator=(TVector<T> && v);	// Move assignment operator

   bool IsEmpty() const;		// Checks to see whether container is empty
   void Clear();			      // Clear out Vector, reset to empty
   int GetSize() const;			// Return the size of the Vector

   void InsertBack(const T& d);		// Insert data d as last element
   void RemoveBack();			      // Remove last element of Vector

   T& GetFirst() const;			// Return first element of Vector
   T& GetLast() const;			// Return last element of Vector

   TVectorIterator<T> GetIterator() const;      // Return iterator to first item
   TVectorIterator<T> GetIteratorEnd() const;   // Return iterator to last item

   void SetCapacity(unsigned int c);	// Reset the capacity of the Vector to c. Adjust size if c is smaller.

   // Insert data element d just before item at pos position
   // Return iterator to the new data item
   TVectorIterator<T> Insert(TVectorIterator<T> pos, const T& d);

   // Remove data item at position pos. Return iterator to the item 
   // That comes after the one being deleted
   TVectorIterator<T> Remove(TVectorIterator<T> pos);

   // Remove data item in range [pos1, pos2), i.e. remove all items from pos1 up through but not including pos2
   // Return iterator to the item that comes after the deleted items
   TVectorIterator<T> Remove(TVectorIterator<T> pos1, TVectorIterator<T> pos2);

   // Prrint Vector contents in order, separated by given delimiter
   void Print(std::ostream& os, char delim = ' ') const;

   private:

   T* array;			      // Pointer to dynamic array of items
   unsigned int capacity;	// Tracker for allocation of array
   unsigned int size;		// Number of items in the array
   static T dummy;		   // Dummy object, for empty Vector data returns assuming type T has default construction
   static const unsigned int SPARECAPACITY = 10;

};

template <typename T>
T TVector<T>::dummy;	// Initialization of static member

// Stand-alone function for concatenating two TVector objects
template <typename T>
TVector<T> operator+(const TVector<T>& t1, const TVector<T>& t2);

// Declaration of class TVectorIterator
template <typename T>
class TVectorIterator // Iterator Class - FRIEND
{
   friend class TVector<T>;

   public:

   TVectorIterator();			      // Default constructor
   bool HasNext() const;		      // Next item available?
   bool HasPrevious() const;		   // Previous item available?
   TVectorIterator<T> Next();		   // Advance to next item
   TVectorIterator<T> Previous();	// Move to previous item
   T& GetData() const;			      // Return data element of current node

   private:

   unsigned int index;		// Index of current item in Vector
   T* ptr;				      // Pointer to the data item
   unsigned int vsize;	   // Size of associated Vector

};

#include "tvector.hpp"		// Bring in definition file here