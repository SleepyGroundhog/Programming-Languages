#include "Array.h"
#include <stdexcept>
#include <iostream>

template <class T> size_t Array<T>::minsize = 10;
template <class T> size_t Array<T>::maxsize = 10000;

// Конструкторы и деструктор класса Array

template <class T> Array<T>::Array( size_t allocsize )
	: m_elements(0), m_allocsize(0), m_size(0) {
	allocate ( allocsize );
}

template <class T> Array<T>::Array( const Array& array )
	: Array() {
	*this = array;
}

template <class T> Array<T>::Array( const std::initializer_list<T>& uniform_list )
	: Array(uniform_list.size()) {
	int i = 0;
	for (auto& element : uniform_list) {
		m_elements[i] = element;
		++i;
	}
	m_size = uniform_list.size();
}

template <class T> Array<T>::Array(Iterator first, Iterator last)
	: Array() {
	if (first > last)
		throw (std::logic_error( "invalid iterators order" ));
	Array created;
	for ( Iterator it = first; it != last; ++it )
		created.push_back( *it );
	*this = created;
}

template <class T> Array<T>::~Array() { free(); }



// Перегрузки операторов

template <class T> T& Array<T>::operator[]( size_t index ) {
	if (0 <= index && index < size() )
		return m_elements[ index ];
	else throw ( std::out_of_range( "out of range" ));
}

template <class T> Array<T>& Array<T>::operator=( const Array& array ) {
	if ( this != &array ) {
		free();
		m_allocsize = array.m_allocsize;
		m_size      = array.m_size;
		m_elements  = new T [ m_allocsize ];
		for ( unsigned i = 0; i < m_size; ++i ) {
			m_elements[ i ] = array.m_elements[ i ];
		}
	}
	return *this;
}



// Итераторы

template <class T> T* Array<T>::begin() const { return m_elements; }
template <class T> T* Array<T>::end()   const { return (m_elements + m_size); }


// Функциональные методы

template <class T> size_t Array<T>::size()     const { return m_size; }

template <class T> size_t Array<T>::capacity() const { return m_allocsize; }

template <class T> void Array<T>::pop_back() {
	if (m_size) --m_size;
	else throw (std::logic_error("empty array deleting"));
}

template <class T> void Array<T>::push_back( T new_element ) {
	if (size() >= capacity())
		resize(std::min(capacity() + 10, maxsize));
	++m_size;
	m_elements[size() - 1] = new_element;
}

template <class T> void Array<T>::print(bool newline) const {
	if (size() == 0) {
		std::cout << "array is empty";
		if (newline) std::cout << "\n";
		return;
	}
	for ( auto element : *this )
		std::cout << element << " ";
	if (newline) std::cout << "\n";
}

template <class T> void Array<T>::clear() { resize(10); m_size = 0; }

template <class T> void Array<T>::resize(size_t reallocsize) {
	if (reallocsize > maxsize)
		throw(std::invalid_argument("array too long"));
	if (reallocsize == m_allocsize) return;
	if (reallocsize == 0) {
		free();
		m_elements = 0;
	}
	else {
		T* new_elements = new T[reallocsize];
		m_allocsize = reallocsize;
		if (m_size > reallocsize)
			m_size = reallocsize;
		for (unsigned i = 0; i < m_size; ++i)
			new_elements[i] = m_elements[i];
		free();
		m_elements = new_elements;
	}
}



// Приватные методы для работы с динамической памятью

template <class T> void Array<T>::allocate( size_t allocsize ) {
	if (allocsize > maxsize)
		throw(std::invalid_argument( "array too long" ));
	if (allocsize < minsize) allocsize = minsize;
	m_allocsize = allocsize;
	m_elements  = new T [ m_allocsize ];
}

template <class T> void Array<T>::free() {
	if (m_elements) {
		delete[] m_elements;
		m_elements = 0;
	}
}

