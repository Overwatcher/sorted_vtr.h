#pragma once
#include <stdlib.h>
#include <iostream>
#include <errno.h>
#include <stdexcept>
#include <string.h>
//These cmp functions are here just for testing. For other types implement your own cmp
int cmp(const char* s1, const char *s2);
int cmp(const int s1, const int s2);
//newalloc
template <class T>
T* newalloc(T* old, long oldsize, long newsize);
//!!! sorted_vtr<T>::Change(...) !!! hasn't been implemented yet
template <class T> class sorted_vtr {
	private:
		long size;
		long *index;
		long allocated;
		long first_empty;
		char *bitmask;
		T* array;
		long _GetFirstEmpty();
		long _Insert(const T&, const long);
	public:
		sorted_vtr() {
			size = 0;
			array = nullptr;
			index = nullptr;
			allocated = 0;
			first_empty = 0;
			bitmask = nullptr;
		};
		~sorted_vtr() {
			delete (array);
			delete (index);
			delete (bitmask);
		}
		long Insert(const T&);
		long InsertUnique(const T&);
		long Remove(const T&);
		int Change(const T& was, const T& will);
		T& operator[](long i);		
		//Operation including BinSearch should be atomic, because a returned index can change;
		//Also BinSearch will ALWAYS return an index (retval). You should check if (cmp(vtr[retval], search) == 0).
		//If not, than there is no 'search' element in vtr;
		//If there are any other elements == search, they ALL go AFTER retval;
		long BinSearch(const T &t);
		long GetSize() {return size; }
};
template <class T>
long sorted_vtr<T>::_GetFirstEmpty() {
	long block = first_empty / 8;
	char position = first_empty % 8;
	while (1) {
		if (!(bitmask[block] & (1<<position))) {
		       	return block*8 + position;
		}
		position = (position + 1) % 8;
		if (position == 0) block ++;
	}	
}
template <class T>
long sorted_vtr<T>::_Insert(const T &t, const long pos) {	
	size++;
	long wasallocated = allocated;
	long i = pos;
	char need_alloc = 0;
	if (allocated == 0)  {
		need_alloc = 2;
		allocated = 70000;
	}
	void * bufpointer;
	if (size >= allocated) {
		need_alloc = 1;
		allocated = 2*allocated;
	}
	if (need_alloc > 0) {
		if (need_alloc == 1) index = newalloc<long>(index, wasallocated, allocated);
		else index = new long[allocated];
		if (need_alloc == 1) array = newalloc<T>(array, wasallocated, allocated);
		else array = new T[allocated];
		if (need_alloc == 1) bitmask = newalloc<char>(bitmask, wasallocated, allocated);
		else bitmask = new char[allocated];
	}
	array[first_empty] = t;
	bitmask[first_empty/8] = bitmask[first_empty/8] + (1<<(first_empty % 8));
	if (cmp (array[index[i]], t) < 0) {
		i++;
	}
	if (size != 1) {
		long new_i = first_empty;
		long temp;
		for (; i < size; i++) {
			temp = index[i];
			index[i] = new_i;
			new_i = temp;
		}
	}
	first_empty = _GetFirstEmpty();
	return pos;
};
template <class T>
long sorted_vtr<T>::Insert(const T &t) {
	long pos = BinSearch(t);
	return _Insert(t, pos);
}
template <class T>
long sorted_vtr<T>::InsertUnique(const T &t) {
	long pos = BinSearch(t);
	if (size != 0 && cmp(array[index[pos]], t) == 0) return pos;
	return _Insert(t, pos);
	
}
template <class T>
T& sorted_vtr<T> :: operator[](long i) {
	if (size <= i) {
		throw std::out_of_range("out of range");
	};
	return array[index[i]];
};
template <class T>
long sorted_vtr<T> :: Remove(const T& t) {
	long find = BinSearch(t);
	long deleted = 0;
	while (cmp(array[index[find+deleted]], t) == 0 && find+deleted < size) {
		long block = index[find+deleted] / 8;
		char pos = index[find+deleted] % 8;
		bitmask[block] = bitmask[block] & (255 - 1<<pos);
		deleted ++;
	}
	if (deleted == 0) return 0;
	if (first_empty > find) first_empty = index[find];
	for (long i = find + deleted; i < size; i++) {
		index[i - deleted] = index[i];
	}
	size = size - deleted;
	return deleted;
	
}
template <class T>
long sorted_vtr<T> :: BinSearch(const T &t) {
	long begin = 0;
	long end = size - 1;
	long i;
	long result;
	while (end - begin > 0) {
		i = (begin + end)/2;
		if (result = cmp(array[index[i]], t) < 0) {
			begin = i + 1;
			continue;
		}
		end = i;	
	}
	return begin;
}
template <class T>
T* newalloc(T* old, long oldsize, long newsize) {
	T* retval = new T[newsize];
	for (long i = 0; i < oldsize; i++) {
		retval[i] = old[i];
	}
	delete old;
	return retval;
}
int cmp(const char* s1, const char* s2) {
	return strcmp(s1, s2);
}
int cmp(const int s1, const int s2) {
	if (s1 < s2) return -1;
	if (s1 == s2) return 0;
	return 1;
}
