#ifndef TEXT_FUNCS_H
#define TEXT_FUNCS_H

struct string {
    char* index;
    size_t len;
};

struct text_t {
    size_t size;
    size_t str_count;
    char* text_p;
    struct string* string_array_p;
};

struct text_t* read_text_from_file(const char* name);
#endif
