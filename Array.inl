#include "Array.h"
#include <stdexcept>
#include <iostream>

inline void debug(std::string debug_msg) {
    #ifdef _DEBUG
	std::cout << "Debug: " << debug_msg << "\n";
    #endif
}

template <class value_type> size_t Array<value_type>::minsize = 10;
template <class value_type> size_t Array<value_type>::maxsize = 10000;

// Конструкторы и деструкторы

template <class value_type> Array<value_type>::Array( size_t allocsize ) : m_elements( 0 ), m_allocsize( allocsize ), m_size( 0 ) {
	allocate ( allocsize );
}

template <class value_type> Array<value_type>::Array( const Array& array ) : m_elements( 0 ), m_allocsize( 0 ), m_size( 0 ) {
	*this = array;
}

template <class value_type> Array<value_type>::Array( const std::initializer_list<value_type>& list ) : Array(list.size()) {
	int i = 0;
	for (auto& element : list) {
		m_elements[i] = element;
		++i;
	}
	m_size = list.size();
}

template <class value_type> Array<value_type>::Array(Iterator first, Iterator last) : m_elements( 0 ), m_allocsize( 0 ), m_size( 0 ) {
	if (first > last)
		throw (std::logic_error( "invalid iterators order" ));
	Array created;
	for ( Iterator it = first; it != last; ++it )
		created.push_back( *it );
	*this = created;
}

template <class value_type> Array<value_type>::~Array() { free(); }



// Перегрузки операторов

template <class value_type> value_type& Array<value_type>::operator[]( size_t index ) {
	if (0 <= index && index < size() )
		return m_elements[ index ];
	else throw ( std::out_of_range( "out of range" ));
}

template <class value_type> Array<value_type>& Array<value_type>::operator=( const Array& array ) {
	if ( this != &array ) {
		free();
		m_allocsize = array.m_allocsize;
		m_size      = array.m_size;
		m_elements  = new value_type [ m_allocsize ];
		for ( unsigned i = 0; i < m_size; ++i ) {
			m_elements[ i ] = array.m_elements[ i ];
		}
	}
	return *this;
}



// Методы доступа

template <class value_type> size_t Array<value_type>::size()     const { return m_size; }
template <class value_type> size_t Array<value_type>::capacity() const { return m_allocsize; }



// Функциональные методы

template <class value_type> void Array<value_type>::pop_back() {
	if (m_size) --m_size;
	else throw (std::logic_error("empty array deleting"));
}

template <class value_type> void Array<value_type>::push_back( value_type new_element ) {
	if (size() >= capacity())
		resize(std::min(capacity() + 10, maxsize));
	m_elements[size()] = new_element;
	++m_size;
}

template <class value_type> void Array<value_type>::print() const {
	for (unsigned i = 0; i < size(); ++i) {
		std::cout << m_elements[i] << " ";
	}
	std::cout << "\n";
}



// Приватные методы для работы с динамической памятью

template <class value_type> void Array<value_type>::allocate( size_t allocsize ) {
	if (allocsize > maxsize)
		throw(std::invalid_argument( "array too long" ));
	if (allocsize < minsize) allocsize = minsize;
	m_allocsize = allocsize;
	m_elements  = new value_type [ m_allocsize ];
}

template <class value_type> void Array<value_type>::free() {
	if (m_elements) {
		delete[] m_elements;
		m_elements = 0;
	}
}

template <class value_type> void Array<value_type>::resize( size_t reallocsize ) {
	debug("array reallocation");
	if (reallocsize > maxsize)
		throw(std::invalid_argument( "array too long" ));
	if (reallocsize == m_allocsize) return;
	if (reallocsize == 0) {
		free();
		m_elements = 0;
	} else {
		value_type* new_elements = new value_type [ reallocsize ];
		m_allocsize = reallocsize;
		if (m_size > reallocsize )
			m_size = reallocsize;
		for ( unsigned i = 0; i < m_size; ++i )
			new_elements [ i ] = m_elements [ i ];
		free();
		m_elements = new_elements;
	}
}