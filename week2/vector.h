/***********************************************************************
 * Header File:
 *    STACK : Stack template class
 * Author:
 *    Anthony Virgin
 * Summary:
 *    Stack template that behaves like the stack in STL.
 ************************************************************************/
#ifndef STACK_H
#define STACK_H

#include <cassert>

 // a little helper macro to write debug code
#ifdef NDEBUG
#define Debug(statement)
#else
#define Debug(statement) statement
#endif // !NDEBUG

namespace custom
{

    /************************************************
     * Stack
     * ADT
     ***********************************************/
    template <class T>
    class stack
    {
    public:
        // constructors and destructors
        stack();
        stack(int numElements);
        stack(int numElements, const T& t);
        stack(const stack& rhs);
        ~stack() { delete[] array; }
        stack& operator = (const stack& rhs);

        // standard container interfaces
        // array treats size and max_size the same
        int  size()      const { return numElements; }
        int  capacity()  const { return numCapacity; }
        void clear() { numElements = 0; }
        bool empty()     const { return size() == 0; }
        void push(const T& t);
        void resize(int num);
        void resize(int num, const T& t);
        void pop();
        T top();
        T top(); const

        T& operator [] (int index)
        {
            return array[index];
        }
        const T& operator [] (int index) const
        {
            return array[index];
        }

        // the various iterator interfaces
        class iterator;
        class const_iterator;
        iterator begin() { return iterator(array); }
        iterator end() { return iterator(array + numElements); }
        const_iterator cbegin() const { return const_iterator(array); }
        const_iterator cend()   const { return const_iterator(array + numElements); }

    private:
        T* array;              // dynamically allocated array of T
        int numElements;               
        int numCapacity;

    };

    /**************************************************
     * VECTOR ITERATOR
     * An iterator through vector
     *************************************************/
    template <class T>
    class stack <T> ::iterator
    {
    public:
        // constructors, destructors, and assignment operator
        iterator() : p(NULL) {              }
        iterator(T* p) : p(p) {              }
        iterator(const iterator& rhs) { *this = rhs; }
        iterator& operator = (const iterator& rhs)
        {
            this->p = rhs.p;
            return *this;
        }

        // equals, not equals operator
        bool operator != (const iterator& rhs) const { return rhs.p != this->p; }
        bool operator == (const iterator& rhs) const { return rhs.p == this->p; }

        // dereference operator
        T& operator * () { return *p; }
        const T& operator * () const { return *p; }

        // prefix increment
        iterator& operator ++ ()
        {
            p++;
            return *this;
        }

        // postfix increment
        iterator operator ++ (int postfix)
        {
            iterator tmp(*this);
            p++;
            return tmp;
        }

        iterator& operator -- ()
        {
            p--;
            return *this;
        }

        iterator operator -- (int postfix)
        {
            iterator tmp(*this);
            p--;
            return tmp;
        }

    private:
        T* p;
    };

    /*******************************************
     * VECTOR :: Assignment
     *******************************************/
    template <class T>
    stack <T>& stack <T> :: operator = (const stack <T>& rhs)
    {
        clear();

        if (rhs.numElements > numCapacity)
            resize(rhs.numElements);

        assert(numCapacity >= rhs.numElements);

        numElements = rhs.numElements;
        for (int i = 0; i < rhs.numElements; i++)
            array[i] = rhs.array[i];

        return *this;
    }

    /*******************************************
     * VECTOR :: COPY CONSTRUCTOR
     *******************************************/
    template <class T>
    stack <T> ::stack(const stack <T>& rhs) :
        array(NULL), numElements(0), numCapacity(0)
    {
        if (!rhs.empty())
            *this = rhs;
    }

    /********************************************
     * Vector : DEFAULT CONSTRUCTOR
     ********************************************/
    template <class T>
    stack <T> ::stack()
    {
        numElements = 0;
        numCapacity = 0;
        array = new T[0];

    }

    /**********************************************
     * VECTOR : NON-DEFAULT CONSTRUCTOR
     **********************************************/
    template <class T>
    stack <T> ::stack(int numElements) :
        array(NULL), numElements(0), numCapacity(0)
    {
        if (numElements > 0)
        {
            resize(numElements);
            this->numElements = numElements;
        }
    }

    /******************************************
     *NON-DEFAULT constructor
     *
     ******************************************/
    template <class T>
    stack <T> ::stack(int numElements, const T& t) :
        array(NULL), numElements(0), numCapacity(0)
    {
        if (numElements > 0)
        {
            resize(numElements, t);
            this->numElements = numElements;
        }
    }

    /*********************************************
    *PUSH_BACK
    **********************************************/
    template <class T>
    void stack <T> ::push(const T& t)
    {
        if (numElements == numCapacity)
        {
            if (numCapacity == 0)
                resize(1);
            else
                resize(numCapacity * 2);
        }

        array[numElements++] = t;

    }

    /*****************************************
    *RESIZE
    ******************************************/
    template <class T>
    void stack <T> ::resize(int num)
    {
        T* arrayNew;
        arrayNew = new T[num];
        for (int i = 0; i < numElements; i++)
        {
            arrayNew[i] = array[i];
        }
        delete[] array;
        array = arrayNew;
        numCapacity = num;
    }

    template<class T>
    inline void stack<T>::pop()
    {
    }

    template<class T>
    inline T stack<T>::top()
    {
        return T();
    }

}; // namespace custom

#endif 
#pragma once
