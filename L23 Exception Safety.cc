// EXCEPTION SAFETY

// EX1
class A {...};
class B {...};
class C {
	A a;
	B b;
public:
	void f() {
		a.method1(); // m1 gives strong  
		b.method2(); // m2 gives strong
	}
};

// 1. can f() give a no throw? 
//   no, since m1 and m2 are both not no throw

// 2. can f() give a strong?
//   no, if m1 completes and m2 throws, the program state 
//   is now different if m1 made any chages

// 3. can f() give a basic?
//   you do not have enough information to decid

// *************************************************************************
// FIRST APPROACH
// TRY TO GIVE A STRONG 
//   if we could undo the effect of m1 t
//   then we could give a strong
//   BUT, often things CANNOT be undone
//   ** can almost NEVER be undone if they are non-local side-effects  
// ASSUMPTION
//   let's assume m1 and m2 only have 
//   local side-effects -> (only modify its own objects)
// SOLUTION
//   instead of undo things
//   let's do things to COPIES of a and b
//   -> if we succeed, SWAP the originals 
//   -> if causing an exception, NO PROBLEM, the original not changed

// EX2
class C {
	A a;
	B b;
public:
	void f() {
		A atemp = a; // copy 
		B btemp = b; // copy 

		atemp.method1();
		btemp.method2();

		a = atemp; // THIS IS A PROBLEM
		b = btemp; // because, if the assignent to b throws an exception, a is chagned, b is not strong 
	}
}; // this still does not give a strong

// *************************************************************************
// SECOND APPROACH
// NEW SOLUTION
// 1. place a and b in a struct 
// 2. use ptr to that structure
// ** pointer assignment never throws an exception
//      because it is just copying a number
//      which is literally just copying bytes from one place to another

// EX3
struct cImpl {
	A a;
	B b;
};

class C { 
	unique_ptr<cImpl> pImpl; 
public:
	void f() {
		unique_ptr<cImpl> temp{new cImpl{*pImpl}};
		// ctor: unique_ptr<cImpl> temp{new cImpl};
		// copy assign the actual cImpl object: *temp = *pImpl;
		// copy constructs the unique_ptr temp with the raw pointer returned by new
		//   the raw pointer returned by new points to a 
		//   cImpl object that was copy constructed using the object *pImpl 

		temp->a.method1; // if m1 throw, we have a copy 
		temp->b.method2; 

		std::swap(pImpl, temp); 
		// swaps pointers of the object
		//   changes made to temp are not in pImpl
		//   std::swap for smart ptr will swap the heap ptrs inside the object ?????????????????
	}
};





// EXCEPTION SAFETY IN THE STL 

// VECTOR
#include <vector>
// use RAII to store a heap allocated array
vector<myClass> v;
// when v goes out of scope, the elements of the array are destoryed first
//   (dtor for each myClass object will run)
//   then the array is deleted
vector<myClass*> v1;
// when v1 goes out of scope, the elements of the array are not destoryed 
//   delete is not called
// ** if the myClass objects are to be deallocated, must delete manually:
for (auto &p : v1) {
	delete p;
}

// USE SMART POINTER
vector<shared_ptr<myClass>> v3; // shared_ptr vs unique_ptr
// dtor for v3 will destory element objects 
//   dtor for shared_ptr will decrease ref count
//   deallocate if ref count is 0 

vector<T>::emplace_back; // gives a strong
// what if size == capacity
//   create larger heap array
//   copy from old array to new array -> THIS IS EXPENSIVE -> we should use move operation instead of copying
//   update old array to new
//   deallocate old array -> NO THROW (delete never throws)

// BUT, what if exception occurs during the move 
//   old array is changed -> no strong 
//   emplace_back will use the move operations if they are no throw
//   otherwise, copy is used

class myClass {
	...
	myClss (myClass&& other) noexcept {
		...
	}
}; // make methods noexcept if they have the no throw guarantee
