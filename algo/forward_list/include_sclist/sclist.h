#ifndef __sclist_h
#define __sclist_h

#include <memory>
#include <initializer_list>

#include "sclist_base.h"
#include "sclist_node.h"

// single chain list
template <typename T>
struct SCList : public SCList_base {
};

// 遍历list所有结点, Function处理data
template <typename T, typename Function>
void list_for_each(SCList<T> *list, Function fn)
{
    for (auto x = list_head(list); x != NULL; x = x->next) {
        fn(*list_data<T>(x));
    }
}

// 查找list中data等于指定值的结点
template <typename T>
SCList_node<T> *list_search(SCList<T> *list, const T &val)
{
    return list_search(list_head(list), val);
}

template <typename T, typename Predicate>
SCList_node<T> *list_search_if(SCList<T> *list, Predicate pred)
{
    return list_search_if(list_head(list), pred);
}

// 删除list中值为val的所有的结点
#if 0
template <typename T>
void list_remove(SCList<T> *list, const T &val)
{
    while
}
#endif

// 销毁list
template <typename T, typename Deleter = std::default_delete<SCList_node<T>>>
void list_destroy(SCList<T> *list, Deleter del = Deleter())
{
    while (!list_is_empty(list)) {
        del(list_node<T>(list_delete_head(list)));
    }
}

// 清空list
template <typename T, typename Deleter = std::default_delete<SCList_node<T>>>
void list_clear(SCList<T> *list, Deleter del = Deleter())
{
    list_destroy(list, del);
    list_init(list);
}

#endif
