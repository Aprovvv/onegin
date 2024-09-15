#ifndef SORT_FUNCS_H
#define SORT_FUNCS_H
void swap(void* p1, void* p2, size_t size);
void my_sort(int* data, size_t size, int (*compar)(int a, int b));
int compar_int(int a, int b);
#endif
