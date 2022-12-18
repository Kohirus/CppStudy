/**
 * @file ngx_mem_pool.hpp
 * @brief Nginx 内存池的的 C++ 实现
 * @author Leaos
 * @date 2022-12-17
 */

#ifndef _NGX_MEM_POOL_H_
#define _NGX_MEM_POOL_H_

using u_char     = unsigned char;
using ngx_uint_t = unsigned int;

struct ngx_pool_s;

/// @brief 清理数据的回调函数
typedef void (*ngx_pool_cleanup_pt)(void* data);

/// @brief 清理数据的相关信息
struct ngx_pool_cleanup_s {
    ngx_pool_cleanup_pt handler; // 清理数据的回调函数
    void*               data;    // 回调函数的函数参数
    ngx_pool_cleanup_s* next;    // 指向下一个清理数据信息结构
};

/// @brief 大块内存的头部数据信息
struct ngx_pool_large_s {
    ngx_pool_large_s* next;  // 指向下一个分配的大块内存
    void*             alloc; // 指向所分配的大块内存的起始地址
};

/// @brief 小块内存的头部数据信息
struct ngx_pool_data_t {
    u_char*     last;   // 小块内存的可用内存的起始地址
    u_char*     end;    // 小块内存的可用内存的末尾地址
    ngx_pool_s* next;   // 指向下一个小块内存
    ngx_uint_t  failed; // 当前小块内存池分配内存失败的次数
};

/// @brief 内存池头部信息和管理成员信息
struct ngx_pool_s {
    ngx_pool_data_t     d;       // 当前小块内存的使用情况
    size_t              max;     // 小块内存和大块内存的分界线
    ngx_pool_s*         current; // 指向可以提供小块内存分配的第一块内存池
    ngx_pool_large_s*   large;   // 指向大块内存池链表
    ngx_pool_cleanup_s* cleanup; // 指向预置清理操作的回调函数入口
};

// 清空内存
#define ngx_memzero(buf, n) (void)memset(buf, 0, n)
// 将数值d调整为a的临近倍数
#define ngx_align(d, a) (((d) + (a - 1)) & ~(a - 1))
// 把指针p调整到a的临近倍数
#define ngx_align_ptr(p, a) (u_char*)(((uintptr_t)(p) + ((uintptr_t)a - 1)) & ~((uintptr_t)a - 1))

const int NGX_ALIGNMENT           = sizeof(unsigned long); // 分配小块内存时平台相关的字节调整数
const int ngx_pagesize            = 4096;                  // 默认的物理页面大小
const int NGX_MAX_ALLOC_FROM_POOL = ngx_pagesize - 1;      // 小块内存池可分配的最大空间
const int NGX_DEFAULT_POOL_SIZE   = (16 * 1024);           // 16K
const int NGX_POOL_ALIGNMENT      = 16;                    // 内存池大小按照16字节大小进行对齐
// 小块内存池最小的 size 调整为 NGX_POOL_ALIGNMENT 的临近倍数
const int NGX_MIN_POOL_SIZE = ngx_align(sizeof(ngx_pool_s) + 2 * sizeof(ngx_pool_large_s), NGX_POOL_ALIGNMENT);

class ngx_mem_pool {
public:
    ngx_mem_pool(size_t size);
    ~ngx_mem_pool();

    // 从内存池申请 size 大小的内存，不考虑字节对齐
    void* ngx_palloc(size_t size);
    // 从内存池申请 size 大小的内存，考虑字节对齐
    void* ngx_pnalloc(size_t size);
    // 调用 ngx_palloc 实现内存分配，但是会将内存初始化为 0
    void* ngx_pcalloc(size_t size);
    // 释放大块内存
    void ngx_pfree(void* p);
    // 内存重置
    void ngx_reset_pool();
    // 添加清理数据的回调函数
    ngx_pool_cleanup_s* ngx_pool_cleanup_add(size_t size);

private:
    // 小块内存分配
    void* ngx_palloc_small(size_t size, ngx_uint_t align);
    // 大块内存分配
    void* ngx_palloc_large(size_t size);
    // 分配新的小块内存池
    void* ngx_palloc_block(size_t size);

private:
    ngx_pool_s* pool_; // 内存池入口指针
};

#endif // !_NGX_MEM_POOL_H_