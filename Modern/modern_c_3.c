#include <stdio.h>

typedef str* (*allocator_cb)(char *);

typedef struct str str;
struct  str
{
    char *data;
    size_t size;
};

typedef struct str_buf str_buf;
struct str_buf
{
    char *data;
    size_t size;
    size_t capacity;
    allocator_cb allocator;
};

// handle functions str_buf
str_buf sb_make(size_t size, allocator_cb allocator);
void sb_append(str_buf *sb, str s) ;
void sb_insert(str_buf *sb, str s, size_t size);
void sb_remove(str_buf *sb, size_t capacity, size_t size);
str sb_str(str_buf) ;

// service functions str
_Bool str_valid(str);
_Bool str_match(str, str);
_Bool str_contains(str, str);
str str_sub(str src, size_t begin, size_t end);
str str_find_first(str haystack, str needle);
str str_find_last(str haystack, str needle);
str str_remove_prefix(str source, str prefix);
str str_remove_suffix(str source, str suffix);
str str_pop_1st_split_impl(str* source, str splitby);

// _Generic : choose one of several expressions at compile time based on src
#define str_pop_1st_split(src, split_by)    \
    _Generic((split_by),                      \
    const char *: str_pop_1st_split_impl(src, cstr(split_by)), \
    default: str_pop_1st_split_impl(src, split_by))

int main(void) {


    return 0;
}
