#ifndef TEXT_FUNCS_H
#define TEXT_FUNCS_H
#include <limits.h>

const long unsigned int SIZE_T_ERROR = ULONG_MAX;

struct string;

struct text_t;

struct text_t* t_read_from_file(const char* name);

void t_destruct(struct text_t* struct_p);

struct string* t_string_p(const struct text_t* struct_p);
struct string* t_string_p(const struct text_t* struct_p, size_t string_numb);

size_t string_size(void);
size_t t_size(const struct text_t* struct_p);
size_t t_str_count(const struct text_t* struct_p);
size_t t_line_len(const struct text_t* struct_p, size_t line_number);
size_t str_line_len(const struct string* struct_p, size_t line_number);

char* t_text_p(const struct text_t* struct_p);
char* t_line_p(const struct text_t* struct_p, size_t line_number);
char* str_line_p(const struct string* struct_p, size_t line_number);
#endif
