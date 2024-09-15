#ifndef TEXT_FUNCS_H
#define TEXT_FUNCS_H

struct text_t {
    size_t size;
    size_t str_count;
    char* text_p;
    char** index_array_p;
};

struct text_t read_text_from_file(const char* name);
struct text_t parse_text(struct text_t original);
#endif
