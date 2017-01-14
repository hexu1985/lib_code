#ifndef __sp_counted_base_h
#define __sp_counted_base_h

#include <atomic>

// shared pointer counted base
class sp_counted_base {
private:
    std::atomic<long> use_count_;

    sp_counted_base(const sp_counted_base &) = delete;
    sp_counted_base &operator =(const sp_counted_base &) = delete;

public:
    sp_counted_base(): use_count_(1) {}

    virtual ~sp_counted_base() {}

    // 当引用计数递减至0, 释放所持有的对象
    virtual void dispose() = 0;

    // 当引用计数递减至0, 释放计数器本身
    virtual void destroy() { delete this; }

    // 增加持有者, 增加引用计数
    void add_ref_copy()
    {
        ++use_count_;
    }

    // 持有者释放控制, 减少引用计数
    void release() 
    {
        if(--use_count_ == 0) {
            dispose();
            destroy();
        }
    }

    // 获取持有对象的指针
    virtual void *get_pointer() = 0;

    // 获取指向deleter的指针
    virtual void *get_deleter() = 0;

    // 获取当前引用计数
    long use_count() const { return use_count_; }
};

#endif