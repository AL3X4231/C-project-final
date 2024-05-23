#ifndef COLUMN_H
#define COLUMN_H

#define MAX_STRING_LENGTH 100

// Enumération pour les types de données
typedef enum {
    NULLVAL = 1,
    UINT,
    INT,
    CHAR,
    FLOAT,
    DOUBLE,
    STRING,
    STRUCTURE,
} ENUM_TYPE;

// Union pour stocker différents types de données
typedef union {
    unsigned int uint_value;
    signed int int_value;
    char char_value;
    float float_value;
    double double_value;
    char* string_value;
    void* struct_value;
} COL_TYPE;

// Structure pour représenter une colonne
typedef struct {
    char *title;
    unsigned int size;       // taille logique
    unsigned int max_size;   // taille physique
    ENUM_TYPE column_type;
    COL_TYPE **data;         // tableau de pointeurs vers les données stockées
    unsigned long long *index;
    int valid_index;         // index valid (0 : no index, -1 : invalid index, 1 : valid index)
    int sort_dir;            // direction de tri (0 : ASC, 1 : DESC)
} COLUMN;

COLUMN *create_column(ENUM_TYPE type, char *title);
int insert_value(COLUMN *col, void *value);
void delete_column(COLUMN **col);
void print_col(COLUMN *col);
unsigned int count_occurrences(COLUMN *col, void *value);
void *get_value_at_position(COLUMN *col, unsigned int position);
unsigned int count_values_greater_than(COLUMN *col, void *value);
unsigned int count_values_less_than(COLUMN *col, void *value);
unsigned int count_values_equal_to(COLUMN *col, void *value);
void sort(COLUMN *col, int sort_dir);
int insertion_sort_index(COLUMN *col, int sort_dir);
int compare_values(COLUMN *col, int index1, int index2, int sort_dir);
void print_sorted_column(COLUMN *col);
void erase_index(COLUMN *col);
int check_index(COLUMN *col);
void update_index(COLUMN *col);
int search_value_in_column(COLUMN *col);
void get_search_value(void *value, int column_type);

#endif // COLUMN_H
