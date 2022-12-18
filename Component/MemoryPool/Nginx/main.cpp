#include <iostream>
#include <cstring>
#include "ngx_mem_pool.hpp"
using namespace std;

struct Data {
    char* ptr;
    FILE* pfile;
};

void func1(char* p) {
    printf("Free the memory of ptr!\n");
    free(p);
}

void func2(FILE* pf) {
    printf("Close the file!\n");
    fclose(pf);
}

int main() {
    ngx_mem_pool pool(512);

    // 分配小块内存
    void* p1 = pool.ngx_palloc(128);
    if (p1 == NULL) {
        printf("Failed to ngx_palloc 128 bytes...");
        return -1;
    }

    // 分配大块内存
    Data* p2 = (Data*)pool.ngx_palloc(512);
    if (p2 == NULL) {
        printf("Failed to ngx_palloc 512 bytes...");
        return -1;
    }

    p2->ptr = (char*)malloc(12);
    strcpy(p2->ptr, "hello world");
    p2->pfile = fopen("data.txt", "w");

    ngx_pool_cleanup_s* c1 = pool.ngx_pool_cleanup_add(sizeof(char*));
    c1->handler            = (ngx_pool_cleanup_pt)func1;
    c1->data               = p2->ptr;

    ngx_pool_cleanup_s* c2 = pool.ngx_pool_cleanup_add(sizeof(FILE*));
    c2->handler            = (ngx_pool_cleanup_pt)func2;
    c2->data               = p2->pfile;

    return 0;
}