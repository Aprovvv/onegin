#ifndef SORT_FUNCS_H
#define SORT_FUNCS_H
typedef int(*cf)(const void* a, const void* b);

void swap(void* p1, void* p2, size_t size);
void my_sort(void* data, size_t nmemb, size_t size, cf compare);
#endif
