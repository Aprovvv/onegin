#ifndef TEXT_FUNCS_H
#define TEXT_FUNCS_H

struct string {
    char* index;
    size_t len;
};

struct text_t;

struct text_t* read_text_from_file(const char* name);
void destruct(struct text_t* struct_p);
size_t text_t_size(struct text_t* struct_p);
size_t text_t_str_count(struct text_t* struct_p);
char* text_t_text_p(struct text_t* struct_p);
struct string* text_t_str_arr_p(struct text_t* struct_p);
#endif
