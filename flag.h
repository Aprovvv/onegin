/**@file */
#ifndef FLAG_H
#define FLAG_H
/**
 * Функция, которая парсит флаг.
 * \param all_flags {Массив структур, содержащий все возмодные флаги}
 * \param flag_count {размер массива}
 * \param argv {аргумент, который надо проанализировать}
 * \returns 0, если ошибка, код флага по ASCII, если все ок
 */
int analyze_flag(const struct flag_struct all_flags[], int flag_count, const char* argv);

struct flag_struct
{
    char short_flag;
    const char* long_flag;
};
#endif
