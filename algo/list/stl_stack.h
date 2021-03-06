#ifndef __stl_stack_h
#define __stl_stack_h

#include "sclist.h"
#include <stddef.h>
#include <assert.h>

namespace stl {

template <typename T>
class stack {
protected:
    typedef SCList<T> list_type;
    typedef SCList_link link_type;
	typedef SCList_node<T> node_type;

private:
    list_type list_;
    int size_ = 0;

public:
    typedef T value_type;
    typedef size_t size_type;

    // construct an empty stack
    stack()
    {
        list_init(list_);
    }

    // destroy stack
    ~stack()
    {
        using sclist::free_node;
        list_destroy(list_, [](link_type x) { free_node(list_link_cast<T>(x)); });
    }

    // number of elements
    size_type size() const 
    {
        return size_;
    }

    // is stack empty?
    bool empty() const 
    {
        return list_is_empty(list_);
    }

    // push element into the stack
    void push(const T& elem) 
    {
        using sclist::new_node;
        list_insert_front(list_, new_node(elem));
        size_++;
    }

    // pop element out of the stack
    void pop() 
    {
        assert(!empty());

        using sclist::free_node;
        free_node(list_link_cast<T>(list_delete_front(list_)));
        size_--;
    }

    // return value of next element
    T& top() 
    {
        assert(!empty());

        return list_link_cast<T>(list_head(list_))->value;
    }
};

}   // namespace stl

#endif /* __stl_stack_h */
