/*
 * Set ADT
 * Project5.c 
 *
 * Anika Agarwal
 * Fall 2017
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Set.h"

/*
 * Several of the required functions have been written already
 * You may use these functions as-is or you may modify them in any way. 
 * Please NOTE, you are responsible for ensuring that the functions work correctly in 
 * your project solution. Just because the function works correctly in my solution does 
 * NOT mean that the function will work correctly in yours. 
 */

/*
 * Design NOTES:
 *
 * The design provided in this starter kit assumes
 * (1) empty sets will be represented with length == 0 and elements == nullptr (i.e., address 0)
 * (2) amortized doubling is not used, and capacity is ignored/unused. Functions should assume that 
 * the amount of storage available in the elements[] array is equal to length
 */



/* done for you already */
void destroySet(Set* self) {
	free(self->elements);
}

/* done for you already */
void createEmptySet(Set* self) {
	self->len = 0;
	self->elements = 0;
}

/* done for you already */
void createSingletonSet(Set* self, int x) {
	self->elements = (int*) malloc(sizeof(int));
	self->elements[0] = x;
	self->len = 1;
}

/* done for you already */
void createCopySet(Set* self, const Set* other) {
	self->elements = (int*) malloc(other->len * sizeof(int));
	for (int k = 0; k < other->len; k += 1) {
		self->elements[k] = other->elements[k];
	}
	self->len = other->len;	
}

/* done for you already */
void assignSet(Set* self, const Set* other) {
	if (self == other) { return; }
	
	destroySet(self);
	createCopySet(self, other);
}

/* binary search --> member set log(n)*/
bool binarySearch(const Set* self, int low, int high, int x) {
    int mid = (low + high)/2;  //set midpoint for comparison
    if (low > high){    //cant search
        return false;
    }
    if (self->elements[mid] == x) { //found element
        return true;
    }
    else if (self->elements[mid] > x) {   //return against upper part of set
        return binarySearch(self, low, mid - 1, x);
    }
    else if (self->elements[mid] < x){    //return against lower part of set
        return binarySearch(self, mid + 1, high, x);
    }
}
/* return true if x is an element of self */
bool isMemberSet(const Set* self, int x) {
    // N complexity
    /*bool a = false; //0 = not in set
    for(int i = 0; i < (self->len); i++){
        if(self->elements[i] == x){
            a = true;  // 1 = in set
        }
    }
    return a;*/

    //log(N); binary search
    return binarySearch(self, 0, (self->len) - 1, x);
}

/*
 * add x as a new member to this set. 
 * If x is already a member, then self should not be changed
 * Be sure to restore the design invariant property that elements[] remains sorted
 * (yes, you can assume it is sorted when the function is called, that's what an invariant is all about)
 */
void insertSet(Set* self, int x) {
    //if x is already a member of the set, return
    if(isMemberSet(self, x) == true){
        return;
    }

    //malloc for new sorted elements
    int* insertSet = (int *) malloc((self->len + 1) * sizeof(int));

    //find where new element should be inserted
    int index;
    for(index=0; index < self->len && x > self->elements[index]; index++){}

    //insert elements
    int s=0; //self index
    int i=0; //insertSet index

   while(i< (self->len +1)){
       if(i == index){
           insertSet[i] = x;
       }
       else{
           insertSet[i] = self->elements[s];
           s++;
       }
       i++;
   }

    //replace old set with new set
    destroySet(self);
    self->len = self->len + 1;
    self->elements = insertSet;
}


/*
 * don't forget: it is OK to try to remove an element
 * that is NOT in the set.  
 * If 'x' is not in the set 'self', then
 * removeSet should do nothing (it's not an error)
 * Otherwise, ('x' IS in the set), remove x. Be sure to update self->length
 * It is not necessary (nor recommended) to call malloc -- if removing an element means the 
 * array on the heap is "too big", that's almost certainly OK, and reallocating a smaller array 
 * is almost definitely NOT worth the trouble
 */
void removeSet(Set* self, int x) {
    //if x is not in set, return
    if(isMemberSet(self, x) == false){
        return;
    }

    //find where new element should be inserted
    int index;
    for(index=0; index < self->len && x > self->elements[index]; index++){}

    //rewrite value at index
    int i=index;
    while(i < (self->len -1)){
        self->elements[i] = self->elements[i+1]; //replace each element with value after it
        i++;
    }

    self->len = self->len -1; //update length

}

/* done for you already */
void displaySet(const Set* self) {
	int k;
	
	printf("{");

	if (self->len == 0) { 
		printf("}"); 
	}
	else {
		for (k = 0; k < self->len; k += 1) {
			if (k < self->len - 1) {
				printf("%d,", self->elements[k]);
			} else {
				printf("%d}", self->elements[k]);
			}
		}
	}
}

/* return true if self and other have exactly the same elements */
bool isEqualToSet(const Set* self, const Set* other) {
    //check length
    if(self->len != other->len){
        return false;
    }

    //check each element
    for(int a =0; a< self->len; a++){
        if(self->elements[a] != other->elements[a]){
            return false;
        }
    }

    return true;
}

/* return true if every element of self is also an element of other */
bool isSubsetOf(const Set* self, const Set* other) {
    //for every element to of slef to be in other, len of self must be less than other and greater than 0
    if(self->len > other->len){
        return false;
    }
    if(self->len == 0) {
        return true;  //NOTE: for any set, x, x is a subset of itself.
    }

    //iterate through both sets
    int s=0; //index of self
    int o; //index of other

    for(o=0; o< other->len; o++){  //continue for all elements in other
        if(self->elements[s] == other->elements[o]){
            s++;
        }
        if(s == self->len){
            return true; //all elements match
        }
    }
    return false; //at least one element did not match
}

/* done for you */
bool isEmptySet(const Set* self) {
	return self->len == 0;
}

/* remove all elements from self that are not also elements of other */
void intersectFromSet(Set* self, const Set* other) {
    //create new set to hold values
    int* intersectSet = (int*) malloc (self->len * sizeof(int));

    //iterate through values
    int s=0; //self index
    int o=0; //other index
    int i=0; //intersectSet index

    while(s<self->len && o<other->len){
        if(self->elements[s] < other->elements[o]){ //if self value too small, increment to next value
            s++;
        }
        else if(self->elements[s] == other->elements[o]){ //if match, add to set
            intersectSet[i] = self->elements[s];
            i++;
            s++;
            o++;
        }
        else if(self->elements[s] > other->elements[o]){ //if other value too small, increment to next value
            o++;
        }
    }

    //return new set values
    destroySet(self);
    self->len = i;
    self->elements = intersectSet;

}

/* remove all elements from self that are also elements of other */
void subtractFromSet(Set* self, const Set* other) {
    //create new set to hold values
    int* subSet = (int*) malloc (self->len * sizeof(int));

    //find matches in arrays
    int s=0;
    int o=0;
    int i=0;

    while(s<self->len && o<other->len){
        if(self->elements[s] < other->elements[o]){
            //if values aren't exact match, add to new set
            subSet[i] = self->elements[s];
            s++;
            i++;
        }
        else if(self->elements[s] == other->elements[o]){
            s++;
            o++;
        }
        else if(self->elements[s] > other->elements[o]){
            o++;
        }
    }

    while(s < self->len){ //add all remaining elements of self
        subSet[i] = self->elements[s];
        i++;
        s++;
    }

    //return new set values
    destroySet(self);
    self->len = i;
    self->elements = subSet;
}

/* add all elements of other to self (obviously, without creating duplicate elements) */
void unionInSet(Set* self, const Set* other) {
    //create new set to hold values
    int* unionSet = (int*) malloc ((self->len + other->len) * sizeof(int));

    //find matches in arrays
    int s = 0;
    int o = 0;
    int i = 0;

    while(s<self->len && o<other->len){
        if (self->elements[s] < other->elements[o]){
            unionSet[i] = self->elements[s];
            i++;
            s++;
        }
        else if (self->elements[s] == other->elements[o]){
            unionSet[i] = self->elements[s];
            i++;
            s++;
            o++;
        }
        else if(self->elements[s] > other->elements[o]){
            unionSet[i] = other->elements[o];
            i++;
            o++;
        }
    }

    while(s<self->len){
        unionSet[i] = self->elements[s];
        s++;
        i++;
    }

    while(o<other->len){
        unionSet[i] = other->elements[o];
        o++;
        i++;
    }

    //return new set values
   // printf("%d\n", unionSet);
    destroySet(self);
    self->len = i;
    self->elements = unionSet;
}
