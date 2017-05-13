#ifndef __forward_list_h
#define __forward_list_h

#include <cstddef>
#include <traits>
#include <initializer_list>

#include "sclist.h"
#include "forward_list_iterator.h"

template <typename T>
class forward_list: private SCList<T> {
public:
    typedef T value_type;
    typedef T &reference;
    typedef T *pointer;
    typedef ptrdiff_t difference_type;
    typedef size_t size_type;
    typedef forward_list_iterator<T> iterator;

    forward_list()
    {
        list_init(this);
    }

    explicit forward_list(std::initializer_list<value_type> il)
    {
        list_init(this);
        auto x = list_dummy_head(this);
        for (auto &e : il) {
            x = list_insert_next(x, new SCList_node<T>(e));
        }
    }

	explicit forward_list(size_type n, const value_type &val = value_type())
    {
        list_init(this);
        auto x = list_dummy_head(this);
        for (size_type i = 0; i < n; i++) {
            x = list_insert_next(x, new SCList_node<T>(val));
        }
    }

	template <typename InputIterator, typename = typename
		std::enable_if<!std::is_integral<InputIterator>::value>::type>
	list(InputIterator first, InputIterator last)
    {
        list_init(this);
        auto x = list_dummy_head(this);
        while (first != last) {
            x = list_insert_next(x, new SCList_node<T>(*first++));
        }
    }

    ~forward_list()
    {
        list_clear(this);
    }

    bool empty() const
    {
        return list_is_empty(this);
    }

    void push_front(const value_type &val)
    {
        list_insert_head(this, new SCList_node<T>(val));
    }

};

#endif