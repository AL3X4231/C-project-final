#ifndef CDATAFRAME_H
#define CDATAFRAME_H

#include "column.h"

#define MAX_STRING_LENGTH 100 // Définir la longueur maximale d'une chaîne de caractères
#define MAX_COLUMNS 100 // Définir le nombre maximum de colonnes dans la dataframe

// Structure pour représenter une dataframe
typedef struct {
    unsigned int num_columns; // nombre de colonnes
    unsigned int num_rows;    // nombre de lignes
    COLUMN **columns; // tableau de pointeurs vers les colonnes
} DATAFRAME;

DATAFRAME *create_empty_dataframe();
void fill_dataframe_user(DATAFRAME *df);
void hard_fill_dataframe(DATAFRAME *df, int num_rows, int num_columns);
void display_dataframe(DATAFRAME *df);
void add_row_to_dataframe(DATAFRAME *df);
void add_column_and_fill(DATAFRAME *df);
void delete_row(DATAFRAME *df);
void delete_column_df(DATAFRAME *df);
void rename_column(DATAFRAME *df);
void display_col_name(DATAFRAME *df);
void set_value_at_cell(DATAFRAME *df, int row, int column, void *new_value);
void print_value_at_cell(DATAFRAME *df, int row, int column);
int is_value_in_dataframe(DATAFRAME *df, void *value);
int count_cells_equal_to_x(DATAFRAME *df, int x);
int count_cells_greater_than_x(DATAFRAME *df, int x);
int count_cells_less_than_x(DATAFRAME *df, int x);
void search_value_in_dataframe_with_user_input(DATAFRAME *df);
void set_value_in_dataframe_with_user_input(DATAFRAME *df);

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


#endif
=======
#endif // CDATAFRAME_H

