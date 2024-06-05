#ifndef __STRUCTURES_H__
#define __STRUCTURES_H__

#define MAX_LEN 101

typedef struct
{
    char branch[MAX_LEN];
    short int domestic;
    short int translate;
    short year;
} technical_t;

typedef struct
{
    short int novel;
    short int play;
    short int poetry;
} fiction_t;

typedef struct
{
    short int story;
    short int poetry;
} children_t;

typedef union
{
    technical_t technical;
    fiction_t fiction;
    children_t children;  
} type_t;

typedef struct
{
    char author[MAX_LEN];
    char name[MAX_LEN];
    char publish_house[MAX_LEN];
    short size_book;
    char is_type[MAX_LEN];
    type_t type;
} books_t;

typedef struct
{
    short size_book;
    short id;
} keys_t;

typedef struct
{
    books_t *books;
    keys_t *keys;
    short size;
} table_t;

#endif
