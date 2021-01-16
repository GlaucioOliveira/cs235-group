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
        stack() : data(NULL), numElements(0), numCapacity(0) {}
        stack(int numElements);
        stack(int numElements, const T& t);
        stack(const stack& rhs);
        ~stack() { delete[] data; }
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
        //T top(); const

        T& operator [] (int index)
        {
            return data[index];
        }
        const T& operator [] (int index) const
        {
            return data[index];
        }

        // the various iterator interfaces
        class iterator;
        class const_iterator;
        iterator begin() { return iterator(data); }
        iterator end() { return iterator(data + numElements); }
        const_iterator cbegin() const { return const_iterator(data); }
        const_iterator cend()   const { return const_iterator(data + numElements); }

    private:
        T* data;              // dynamically allocated array of T
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
            data[i] = rhs.data[i];

        return *this;
    }

    /*******************************************
     * STACK :: COPY CONSTRUCTOR
     *******************************************/
    template <class T>
    stack <T> ::stack(const stack <T>& rhs) :
        data(NULL), numElements(0), numCapacity(0)
    {
        if (!rhs.empty())
            *this = rhs;
    }

    /********************************************
     * STACK : DEFAULT CONSTRUCTOR
     ********************************************/
     /* template <class T>
      stack <T> ::stack()
      {
          numElements = 0;
          numCapacity = 0;
          data(NULL);

      }*/

      /**********************************************
       * STACK : NON-DEFAULT CONSTRUCTOR
       **********************************************/
    template <class T>
    stack <T> ::stack(int numCapacity) :
        data(NULL), numElements(0), numCapacity(0)
    {
        if (numCapacity > 0)
        {
            resize(numCapacity);
            this->numCapacity = numCapacity;
        }
    }

    /******************************************
     *NON-DEFAULT constructor
     *
     ******************************************/
    template <class T>
    stack <T> ::stack(int numElements, const T& t) :
        data(NULL), numElements(0), numCapacity(0)
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

        data[numElements++] = t;

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
            arrayNew[i] = data[i];
        }
        delete[] data;
        data = arrayNew;
        numCapacity = num;
    }

    /*****************************************
    *POP
    ******************************************/
    template<class T>
    void stack<T>::pop()
    {
        if (!empty())
            numElements--;
    }

    /*****************************************
    *TOP
    ******************************************/
    template<class T>
    T stack<T>::top()
    {
        if (!empty())
            return data[size() - 1];
        else
            throw "ERROR: Unable to reference the element from an empty Stack";
        
    }

}; // namespace custom

#endif 
#pragma once

