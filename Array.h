#pragma once
#include <iostream>
#include <string>

// The class implements a dynamic array with an immutable length.
// The memory for the array is allocated in the heap.
//

// Template may be removed, for that enough edit "T" in the "using value_type = T" to the any required type;
// The minimum set of operations that the type "T" have to support:
// T& operator=(const T&), std::istream& operator>>(std::istream&, T&), std::ostream& operator<<(std::ostream&, const T&).
//

template <class T> class Array {
public:

    // Type aliases
    //

    using size_t   = unsigned int; // any size, lenght, index or number variable
    using value_t  = T;            // data type that is stored in the array
    using Iterator = value_t*;     // iterators that is using pointers to array elements


    // Constructors and destructor
    // When passing negative numbers to constructors, they will be implicitly converted to
    // unsigned it, so std:range_error that array too long will be called.
    //

    Array(size_t size) : m_size(size)
    {
        if (size > maxsize()) {
            throw std::range_error("array too long");
        }
        m_data = new value_t[size];
    }

    Array(size_t size, value_t default_value) : Array(size) {
        for (auto& element : *this) {
            element = default_value;
        }
    }

    Array(const Iterator begin, const Iterator end) : Array(end - begin) {
        if (begin >= end) {
            throw invalid_iterators("invalid iterators");
        }
        size_t index = 0;
        for (Iterator it = begin; it != end; ++it) {
            m_data[index++] = *it;
        }
    }

    Array(const Array& array) : Array(array.cbegin(), array.cend()) {}

    ~Array() { delete[] m_data; }

    
    // Operators overloading
    //

    // Assigment operator with checking arrays size for equality
    Array& operator=(const Array& array) {
        if (this != &array) {
            if (size() != array.size()) {
                throw different_sizes("array sizes are different");
            }
            for (size_t n = 0; n < size(); ++n) {
                m_data[n] = array[n];
            }
        }
        return *this;
    }

    // No-constant indexation operator overloading
    value_t& operator[](size_t index) {
        if (index < m_size) {
            return m_data[index];
        } else {
            throw std::out_of_range("array out of range");
        }
    }

    // Constant indexation operator overloading
    const value_t& operator[](size_t index) const {
        if (index < m_size) {
            return m_data[index];
        }
        else {
            throw std::out_of_range("array out of range");
        }
    }


    // Getters and iterators getters.
    // All end iterators is pointed to element after last, so appealing to them will 
    // be create error of accessing to invalid memory.
    //

    size_t size() const { return m_size; }
    static size_t maxsize() { return MAX_SIZE; }
    Iterator       begin() { return m_data; }
    Iterator       end()   { return m_data + m_size; } 
    const Iterator begin()  const { return m_data; }
    const Iterator end()    const { return m_data + m_size; }
    const Iterator cbegin() const { return m_data; }
    const Iterator cend()   const { return m_data + m_size; }
    

    // Input and output functions and operators
    //

    // Sequential output of elements with a configurable separator and end character
    std::ostream& print(std::ostream& outputstream, const char* sep = " ", const char* end = "") const {
        for (int i = 0; i < size(); ++i) {
            outputstream << m_data[i];
            if (i != size() - 1) {
                outputstream << sep;
            }
        }
        outputstream << end;
        return outputstream;
    }

    // Sequential input of elements
    friend std::istream& operator>>(std::istream& inputstream, Array& array) {
        for (auto& element : array) {
            inputstream >> element;
        }
        return inputstream;
    }

    // Sequential output of elements separated by a space
    friend std::ostream& operator<<(std::ostream& outputstream, const Array& array) {
        for (auto& element : array) {
            outputstream << element << " ";
        }
        return outputstream;
    }


    // Exceptions classes
    //

    // Exception: trying to work with two arrays of different lengths
    class different_sizes : public std::logic_error {
    public: different_sizes(const char* msg) : logic_error(msg) {}
    };

    // Exception: function get invalid iterators
    class invalid_iterators : public std::invalid_argument {
    public: invalid_iterators(const char* msg) : invalid_argument(msg) {}
    };

private:
    const static size_t MAX_SIZE = 1000000000; // max array size
    const size_t        m_size;                // real array size
    value_t*            m_data;                // array elements

};