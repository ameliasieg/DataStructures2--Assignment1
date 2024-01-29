#include <iostream>
#include <string>

#include "tvector.h"

using namespace std;

template <typename T> 
void PrintList(const TVector<T>& v, string label)
{
   cout << label << " size is: " << v.GetSize() << "\n" << label << " = "; 
   v.Print(cout);
   cout << "\n\n";
}

// MAIN STARTS HERE
int main()
{
   TVector<int> v1;	// Integer list

   // BEGINNING OF OUTPUT CODE
   cout << "Beginning output code... " << endl;
   
   for (int i = 0; i < 10; i++)
	   v1.InsertBack(i*3);

   PrintList(v1, "v1");

   for (int i = 0; i < 8; i++)
      v1.Insert( v1.GetIterator(), (i+1) * 50 );

   PrintList(v1, "v1");

   v1.RemoveBack();
   PrintList(v1, "v1");

   v1.RemoveBack();
   PrintList(v1, "v1");

   v1.Remove(v1.GetIterator());
   PrintList(v1, "v1");

   v1.Remove(v1.GetIterator());
   PrintList(v1, "v1");
   
   // Try an iterator, and some middle inserts/deletes
   cout << "Testing some inserts with an iterator\n\n";

   TVectorIterator<int> itr = v1.GetIterator();
   itr = v1.Insert(itr, 999);
   itr.Next();
   itr.Next();				// Advance two spots
   itr = v1.Insert(itr, 888);
   itr.Next();				
   itr.Next();				
   itr.Next();				// Advance three spots
   itr = v1.Insert(itr, 777);

   PrintList(v1, "v1");

   cout << "Testing some removes (with iterator)\n\n";

   itr.Next();   
   itr.Next();   			// Advance two spots
   itr = v1.Remove(itr);		// Delete current item
   PrintList(v1, "v1");

   for (int i = 0; i < 5; i++)
      itr.Previous();			// Back 5 spots

   itr = v1.Remove(itr);		// Delete current item
   PrintList(v1, "v1");
   
   // Building another list

   cout << "Building a new list\n";
   TVector<int> v2;
   for (int i = 0; i < 10; i++)
      v2.InsertBack(i * 3 + 1);

   PrintList(v2, "v2");

   // Testing + overload:
   cout << "Testing operator+ overload\n";
   TVector<int> v3 = v1 + TVector<int>(100, 7);

   TVector<int> v4;
   v4 = v2 + v1;

   PrintList(v3, "v3");
   PrintList(v4, "v4");

   cout << "Testing a call to the 2-param delete\n";
   TVectorIterator<int> itr1 = v4.GetIterator();
   TVectorIterator<int> itr2 = v4.GetIterator();

   itr1.Next();
   itr1.Next();
   cout << "itr1 is attached to: " << itr1.GetData() << '\n';
   
   for (int i = 0; i < 8; i++)
      itr2.Next();
   
   cout << "itr2 is attached to: " << itr2.GetData() << '\n';
   
   cout << "Calling:  v4.Remove(itr1, itr2);\n";
   v4.Remove(itr1, itr2);   
   PrintList(v4, "v4");

   // TESTING UNUSED FUNCTIONS - GetFirst, GetLast, and GetIteratorEnd
   PrintList(v1, "v1");
   cout << "Testing GetFirst: ";
   int test100 = v1.GetFirst();
   cout << test100 << endl;   
   
   cout << "Testing GetLast: ";
   int test200 = v1.GetLast();
   cout << test200 << endl;   
   
   cout << "Testing GetIteratorEnd: ";
   auto itr300 = v1.GetIteratorEnd();
   cout << itr300.GetData() << endl;   
   
}