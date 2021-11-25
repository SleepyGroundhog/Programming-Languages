#include "Array.h"
#include <stdexcept>

template <class T> size_t Array<T>::maxsize = 100;

template <class T> Array<T>::Array( size_t allocsize ) : m_allocsize( allocsize ), m_size( 0 ) {
	if ( allocsize < 0 || allocsize > maxsize )
		throw(std::invalid_argument( "invalid array size" ));
	if ( alloctsize == 0 ) m_elements = 0;
	else m_elements = new T[m_allocsize];
}

template <class T> Array<T>::Array( const Array& array ) : m_allocsize( 0 ), m_size( 0 ) {
	m_elements = 0;
	*this = array;
}

template <class T> Array<T>& Array<T>::operator=( const Array& array ) {
	if ( this != *array ) {
		if ( m_elements ) delete[] m_elements;
		m_allocsize = array.m_allocsize;
		m_size      = array.m_size;
		m_elements  = new T[m_allocsize];
		for ( int i = 0; i < m_size; ++i ) {
			m_elements[i] = array.m_elements[i];
		}
	}
	return *this;
}


template <class T> Array<T>::~Array() {
	if ( m_elements ) delete[] m_elements;
}

template <class T> size_t Array<T>::size() const {
	return m_size;
}

template <class T> size_t Array<T>::capacity() const {
	return m_allocsize;
}

template <class T> void Array<T>::pop_back() {
	if ( !m_size )
		--m_size;
}

template <class T> void Array<T>::push_back( T new_element ) {
	
}

template <class T> void Array<T>::reallocate( size_t new_allocsize) {
	if ( allocsize < 0 || allocsize > maxsize )
		throw( std::invalid_argument( "invalid array size" ));
	else if ( alloctsize == 0 ) new_elements = 0;
	else new_elements = new T[new_allocsize];
	if ( new_elements ) {
		for ( int i = 0; i < m_size; ++i ) {
			new_elements[i] = m_elements[i];
		}
		m_allocsize = new_allocsize;
	}
	free();
	m_elements = new_elements;
}

template <class T> void Array<T>::free() {
	if ( m_elements ) {
		delete[] m_elements;
		m_elements = 0;
	}
}