#ifndef TEXT_FUNCS_H
#define TEXT_FUNCS_H

struct string;

struct text_t;
//TODO - поменять имена переменных, сделать функцию сортировки
struct text_t* text_t_read_from_file(const char* name);

void t_destruct(struct text_t* struct_p);

struct string* text_t_string_p(const struct text_t* struct_p,
                          size_t string_numb);

size_t string_size(void);
size_t text_t_size(const struct text_t* struct_p);
size_t text_t_str_count(const struct text_t* struct_p);
size_t text_t_line_len(const struct text_t* struct_p,
                  size_t line_number);
size_t string_line_len(const struct string* struct_p,
                    size_t line_number);

char* text_t_text_p(const struct text_t* struct_p);
char* text_t_line_p(const struct text_t* struct_p,
               size_t line_number);
char* string_line_p(const struct string* struct_p,
                 size_t line_number);
#endif
