#ifndef TEXT_FUNCS_H
#define TEXT_FUNCS_H

struct string {
    char* index;
    size_t len;
};

struct text_t;

struct text_t* t_read_from_file(const char* name);
void t_destruct(struct text_t* struct_p);
size_t t_size(struct text_t* struct_p);
size_t t_str_count(struct text_t* struct_p);
char* t_text_p(struct text_t* struct_p);
struct string* t_str_arr_p(struct text_t* struct_p);
#endif
