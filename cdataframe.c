#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cdataframe.h"

#define ASC 0
#define DESC 1


COLUMN *create_column(ENUM_TYPE type, char *title) {
    COLUMN *col = malloc(sizeof(COLUMN));
    if (col == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    col->title = strdup(title); // Duplicate the title string
    col->size = 0;
    col->max_size = 0;
    col->column_type = type;
    col->data = NULL;
    col->index = NULL;
    return col;
}

int insert_value(COLUMN *col, void *value) {
    if (col == NULL) {
        printf("Column does not exist.\n");
        return 0;
    }

    // Check if the data array needs reallocation
    if (col->size == col->max_size) {
        col->max_size += 256;
        col->data = realloc(col->data, col->max_size * sizeof(COL_TYPE*));
        if (col->data == NULL) {
            printf("Memory reallocation failed.\n");
            exit(1);
        }
    }

    // Allocate memory for the value and insert it into the column
    col->data[col->size] = malloc(sizeof(COL_TYPE));
    if (col->data[col->size] == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    memcpy(col->data[col->size], value, sizeof(COL_TYPE));
    col->size++;
    return 1;
}

void delete_column(COLUMN **col) {
    if (*col == NULL) {
        printf("Column does not exist.\n");
        return;
    }
    // Free memory allocated for title
    free((*col)->title);
    // Free memory allocated for each data element
    for (unsigned int i = 0; i < (*col)->size; i++) {
        free((*col)->data[i]);
    }
    // Free memory allocated for the data array and index array
    free((*col)->data);
    free((*col)->index);
    // Free memory allocated for the column structure
    free(*col);
    *col = NULL;
}

void print_col(COLUMN *col) {
    if (col == NULL) {
        printf("Column does not exist.\n");
        return;
    }
    printf("Column Title: %s\n", col->title);
    printf("Column Values:\n");
    for (unsigned int i = 0; i < col->size; i++) {
        printf("[%u] ", i);
        switch (col->column_type) {
            case UINT:
                printf("%u\n", col->data[i]->uint_value);
                break;
            case INT:
                printf("%d\n", col->data[i]->int_value);
                break;
            case CHAR:
                printf("%c\n", col->data[i]->char_value);
                break;
            case FLOAT:
                printf("%f\n", col->data[i]->float_value);
                break;
            case DOUBLE:
                printf("%lf\n", col->data[i]->double_value);
                break;
            case STRING:
                printf("%s\n", col->data[i]->string_value);
                break;
            case STRUCTURE:
                // Logic for displaying structured data
                break;
            default:
                printf("Unsupported data type.\n");
        }
    }
}

unsigned int count_occurrences(COLUMN *col, void *value) {
    if (col == NULL) {
        printf("Column does not exist.\n");
        return 0;
    }

    unsigned int count = 0;
    for (unsigned int i = 0; i < col->size; i++) {
        switch (col->column_type) {
            case UINT:
                if (col->data[i]->uint_value == *((unsigned int *)value)) {
                    count++;
                }
            break;
            case INT:
                if (col->data[i]->int_value == *((int *)value)) {
                    count++;
                }
            break;
            case CHAR:
                if (col->data[i]->char_value == *((char *)value)) {
                    count++;
                }
            break;
            // Add cases for other data types as needed
            default:
                printf("Unsupported data type.\n");
        }
    }
    return count;
}

void *get_value_at_position(COLUMN *col, unsigned int position) {
    if (col == NULL) {
        printf("Column does not exist.\n");
        return NULL;
    }

    if (position >= col->size) {
        printf("Position out of bounds.\n");
        return NULL;
    }

    return col->data[position];
}

unsigned int count_values_greater_than(COLUMN *col, void *value) {
    if (col == NULL) {
        printf("Column does not exist.\n");
        return 0;
    }

    unsigned int count = 0;
    for (unsigned int i = 0; i < col->size; i++) {
        switch (col->column_type) {
            case UINT:
                if (col->data[i]->uint_value > *((unsigned int *)value)) {
                    count++;
                }
            break;
            case INT:
                if (col->data[i]->int_value > *((int *)value)) {
                    count++;
                }
            break;
            case FLOAT:
                if (col->data[i]->float_value > *((float *)value)) {
                    count++;
                }
            break;
            // Add cases for other data types as needed...
            default:
                printf("Unsupported data type.\n");
        }
    }
    return count;
}

unsigned int count_values_less_than(COLUMN *col, void *value) {
    if (col == NULL) {
        printf("Column does not exist.\n");
        return 0;
    }

    unsigned int count = 0;
    for (unsigned int i = 0; i < col->size; i++) {
        switch (col->column_type) {
            case UINT:
                if (col->data[i]->uint_value < *((unsigned int *)value)) {
                    count++;
                }
            break;
            case INT:
                if (col->data[i]->int_value < *((int *)value)) {
                    count++;
                }
            break;
            case FLOAT:
                if (col->data[i]->float_value < *((float *)value)) {
                    count++;
                }
            break;
            // Add cases for other data types as needed
            default:
                printf("Unsupported data type.\n");
        }
    }
    return count;
}

unsigned int count_values_equal_to(COLUMN *col, void *value) {
    if (col == NULL) {
        printf("Column does not exist.\n");
        return 0;
    }

    unsigned int count = 0;
    for (unsigned int i = 0; i < col->size; i++) {
        switch (col->column_type) {
            case UINT:
                if (col->data[i]->uint_value == *((unsigned int *)value)) {
                    count++;
                }
            break;
            case INT:
                if (col->data[i]->int_value == *((int *)value)) {
                    count++;
                }
            break;
            case FLOAT:
                if (col->data[i]->float_value == *((float *)value)) {
                    count++;
                }
            break;
            // Add cases for other data types as needed...
            default:
                printf("Unsupported data type.\n");
        }
    }
    return count;
}


DATAFRAME *create_empty_dataframe() {
    DATAFRAME *df = malloc(sizeof(DATAFRAME));
    if (df == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    df->num_columns = 0;
    df->num_rows = 0;
    df->columns = malloc(MAX_COLUMNS * sizeof(COLUMN *));
    if (df->columns == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    return df;
}

void fill_dataframe_user(DATAFRAME *df) {
    printf("Enter the number of columns: ");
    scanf("%d", &df->num_columns);
    printf("Enter the number of rows: ");
    scanf("%d", &df->num_rows);

    for (int i = 0; i < df->num_columns; i++) {
        printf("Enter title for column %d: ", i + 1);
        char title[MAX_STRING_LENGTH]; // Assuming maximum string length
        scanf("%s", title);
        ENUM_TYPE type;
        printf("Enter type for column %d (NULLVAL, UINT, INT, CHAR, FLOAT, DOUBLE, STRING, STRUCTURE): ", i + 1);
        scanf("%d", (int *)&type);
        df->columns[i] = create_column(type, title);
    }

    for (int i = 0; i < df->num_columns; i++) {
        printf("Enter data for column '%s':\n", df->columns[i]->title);
        for (int j = 0; j < df->num_rows; j++) {
            switch (df->columns[i]->column_type) {
                case UINT: {
                    printf("Enter unsigned integer value for row %d: ", j + 1);
                    unsigned int value;
                    scanf("%u", &value);
                    insert_value(df->columns[i], &value);
                    break;
                }
                case INT: {
                    printf("Enter integer value for row %d: ", j + 1);
                    int value;
                    scanf("%d", &value);
                    insert_value(df->columns[i], &value);
                    break;
                }
                case CHAR: {
                    printf("Enter character value for row %d: ", j + 1);
                    char value;
                    scanf(" %c", &value);
                    insert_value(df->columns[i], &value);
                    break;
                }
                case FLOAT: {
                    printf("Enter float value for row %d: ", j + 1);
                    float value;
                    scanf("%f", &value);
                    insert_value(df->columns[i], &value);
                    break;
                }
                case DOUBLE: {
                    printf("Enter double value for row %d: ", j + 1);
                    double value;
                    scanf("%lf", &value);
                    insert_value(df->columns[i], &value);
                    break;
                }
                case STRING: {
                    printf("Enter string value for row %d: ", j + 1);
                    char value[MAX_STRING_LENGTH]; // Assuming maximum string length
                    scanf("%s", value);
                    insert_value(df->columns[i],&value);
                    break;
                }
                case STRUCTURE:
                    int structure_values[] = {15, 16, 17, 10, 5, 100, 4, 55, 30, 18};
                    if (j < sizeof(structure_values) / sizeof(structure_values[0])) {
                        int value = structure_values[j];
                        insert_value(df->columns[i], &value);
                    } else {
                        printf("Error: Row index exceeds predefined STRUCTURE size.\n");
                    }
                    break;
                default:
                    printf("Unsupported data type.\n");
                    break;
            }
        }
    }
}


void hard_fill_dataframe(DATAFRAME *df, int num_rows, int num_columns) {
    // Vérifier si le nombre de colonnes est supérieur au maximum autorisé
    if (num_columns > MAX_COLUMNS) {
        printf("Number of columns exceeds maximum allowed.\n");
        return;
    }

    // Remplir la dataframe avec des zéros
    df->num_rows = num_rows;
    df->num_columns = num_columns;

    for (int i = 0; i < num_columns; i++) {
        // Créer une nouvelle colonne avec des zéros
        char title[MAX_STRING_LENGTH];
        sprintf(title, "Column%d", i + 1);
        COLUMN *col = create_column(INT, title);

        // Remplir la colonne avec des zéros
        for (int j = 0; j < num_rows; j++) {
            int zero = 0;
            insert_value(col, &zero);
        }

        // Ajouter la colonne à la dataframe
        df->columns[i] = col;
    }
}

void display_dataframe(DATAFRAME *df) {
    int dprow, dpcol;

    printf("Modify the number of rows display : ");
    scanf("%d",&dprow);
    printf("\nModify the number of col display : ");
    scanf("%d",&dpcol);

    printf("Number of columns: %u\n", df->num_columns);
    printf("Number of rows: %u\n", df->num_rows);
    printf("Dataframe:\n");


    display_col_name(df);

    printf("\n");
    // Iterate over each row
    for (unsigned int i = 0; i < df->num_rows && i<dprow; i++) {
        printf("Row %u: ", i + 1);

        // Iterate over each column in the row
        for (unsigned int j = 0; j < df->num_columns && j <dpcol; j++) {
            // Access the value at row i and column j
            if (df->columns[j]->data != NULL && i < df->columns[j]->size) {
                switch (df->columns[j]->column_type) {
                    case UINT:
                        printf("%u ", *(unsigned int *)df->columns[j]->data[i]);
                    break;
                    case INT:
                        printf("%d ", *(int *)df->columns[j]->data[i]);
                    break;
                    case CHAR:
                        printf("%c ", *(char *)df->columns[j]->data[i]);
                    break;
                    case FLOAT:
                        printf("%f ", *(float *)df->columns[j]->data[i]);
                    break;
                    case DOUBLE:
                        printf("%lf ", *(double *)df->columns[j]->data[i]);
                    break;
                    case STRING:
                        printf("%s ", (char *)df->columns[j]->data[i]);
                    break;
                    case STRUCTURE:
                        printf("%d ", *(int *)df->columns[j]->data[i]);
                            break;
                    default:
                        printf("Unsupported data type\n");
                    break;
                }
            } else {
                printf("NULL ");
            }
        }
        printf("\n");
    }
}

void add_row_to_dataframe(DATAFRAME *df) {
    // Increment the number of rows in the dataframe
    df->num_rows++;

    // Allocate memory for the new row
    for (unsigned int i = 0; i < df->num_columns; i++) {
        switch (df->columns[i]->column_type) {
            case UINT: {
                unsigned int *value = malloc(sizeof(unsigned int));
                if (value == NULL) {
                    printf("Memory allocation failed.\n");
                    exit(1);
                }
                printf("Enter value for column '%s' in the new row: ", df->columns[i]->title);
                scanf("%u", value);
                // Insert the new value into the column
                insert_value(df->columns[i], value);
                break;
            }
            case INT: {
                int *value = malloc(sizeof(int));
                if (value == NULL) {
                    printf("Memory allocation failed.\n");
                    exit(1);
                }
                printf("Enter value for column '%s' in the new row: ", df->columns[i]->title);
                scanf("%d", value);
                insert_value(df->columns[i], value);
                break;
            }
            case CHAR: {
                char *value = malloc(sizeof(char));
                if (value == NULL) {
                    printf("Memory allocation failed.\n");
                    exit(1);
                }
                printf("Enter value for column '%s' in the new row: ", df->columns[i]->title);
                scanf(" %c", value);
                insert_value(df->columns[i], value);
                break;
            }
            case FLOAT: {
                float *value = malloc(sizeof(float));
                if (value == NULL) {
                    printf("Memory allocation failed.\n");
                    exit(1);
                }
                printf("Enter value for column '%s' in the new row: ", df->columns[i]->title);
                scanf("%f", value);
                insert_value(df->columns[i], value);
                break;
            }
            case DOUBLE: {
                double *value = malloc(sizeof(double));
                if (value == NULL) {
                    printf("Memory allocation failed.\n");
                    exit(1);
                }
                printf("Enter value for column '%s' in the new row: ", df->columns[i]->title);
                scanf("%lf", value);
                insert_value(df->columns[i], value);
                break;
            }
            case STRING: {
                char *value = malloc(MAX_STRING_LENGTH * sizeof(char));
                if (value == NULL) {
                    printf("Memory allocation failed.\n");
                    exit(1);
                }
                printf("Enter value for column '%s' in the new row: ", df->columns[i]->title);
                scanf("%s", value);
                insert_value(df->columns[i], value);
                break;
            }
            case STRUCTURE:{
                int structure_values[] = {15, 16, 17, 10, 5, 100, 4, 55, 30, 18};
                if (i < sizeof(structure_values) / sizeof(structure_values[0])) {
                    int value = structure_values[df->num_rows];
                    insert_value(df->columns[i], &value);
                } else {
                    printf("Error: Row index exceeds predefined STRUCTURE size.\n");
                }
                break;
            }
            default:
                printf("Unsupported data type.\n");
                break;
        }
    }
}

void add_column_and_fill(DATAFRAME *df) {
    // Vérifier si le nombre de colonnes est supérieur au maximum autorisé
    if (df->num_columns >= MAX_COLUMNS) {
        printf("Maximum number of columns reached.\n");
        return;
    }

    // Demander le titre et le type de la nouvelle colonne
    char title[MAX_STRING_LENGTH];
    printf("Enter title for the new column: ");
    scanf("%s", title);

    ENUM_TYPE type;
    printf("Enter type for the new column (NULLVAL, UINT, INT, CHAR, FLOAT, DOUBLE, STRING, STRUCTURE): ");
    scanf("%d", (int *)&type);
    COLUMN *new_column = create_column(type, title);

    // Ajouter la colonne à la dataframe
    df->columns[df->num_columns] = new_column;


    // Incrémenter le nombre de colonnes dans la dataframe
    df->num_columns++;

    // Demander à l'utilisateur de remplir les valeurs pour la nouvelle colonne
    printf("Enter values for column '%s':\n", title);
    for (unsigned int i = 0; i < df->num_rows; i++) {
        switch (type) {
            case UINT: {
                unsigned int value;
                printf("Enter unsigned integer value for row %u: ", i + 1);
                scanf("%u", &value);
                insert_value(df->columns[df->num_columns - 1], &value);
                break;
            }
            case INT: {
                int value;
                printf("Enter integer value for row %u: ", i + 1);
                scanf("%d", &value);
                insert_value(df->columns[df->num_columns - 1], &value);
                break;
            }
            case CHAR: {
                char value;
                printf("Enter character value for row %u: ", i + 1);
                scanf(" %c", &value);
                insert_value(df->columns[df->num_columns - 1], &value);
                break;
            }
            case FLOAT: {
                float value;
                printf("Enter float value for row %u: ", i + 1);
                scanf("%f", &value);
                insert_value(df->columns[df->num_columns - 1], &value);
                break;
            }
            case DOUBLE: {
                double value;
                printf("Enter double value for row %u: ", i + 1);
                scanf("%lf", &value);
                insert_value(df->columns[df->num_columns - 1], &value);
                break;
            }
            case STRING: {
                char value[MAX_STRING_LENGTH];
                printf("Enter string value for row %u: ", i + 1);
                scanf("%s", value);
                insert_value(df->columns[df->num_columns - 1], value);
                break;
            }
            case STRUCTURE:
                int structure_values[] = {15, 16, 17, 10, 5, 100, 4, 55, 30, 18};
                    if (i < sizeof(structure_values) / sizeof(structure_values[0])) {
                        int value = structure_values[i];
                        insert_value(df->columns[i], &value);
                    } else {
                        printf("Error: Row index exceeds predefined STRUCTURE size.\n");
                    }
                break;

            default:
                printf("Unsupported data type.\n");
                break;
        }
    }
}

void delete_row(DATAFRAME *df) {
    // Check if the row index is valid
    int row_index;
    printf("Type the index of the row you want to delete : ");
    scanf("%d",&row_index);
    if (row_index >= df->num_rows) {
        printf("Invalid row index.\n");
        return;
    }

    // Shift data in each column up to remove the row
    for (unsigned int i = 0; i < df->num_columns; i++) {
        for (unsigned int j = row_index; j < df->num_rows - 1; j++) {
            COL_TYPE *current = df->columns[i]->data[j];
            COL_TYPE *next = df->columns[i]->data[j + 1];
            // Move the data of the next row to the current row
            memcpy(current, next, sizeof(COL_TYPE));
        }
        // Decrement the size of the column
        df->columns[i]->size--;
    }

    // Decrement the number of rows in the dataframe
    df->num_rows--;
}

void rename_column(DATAFRAME *df) {
    // Check if the column index is valid

    int column_index;
    char new_title[MAX_STRING_LENGTH];
    printf("Type the index of the column you want to modify the title : ");
    scanf("%d",&column_index);
    printf("Type the new title : ");
    scanf("%s",&new_title);
    if (column_index >= df->num_columns) {
        printf("Invalid column index.\n");
        return;
    }

    // Free the memory allocated for the current column title
    free(df->columns[column_index]->title);

    // Allocate memory for the new title and copy it
    df->columns[column_index]->title = malloc(strlen(new_title) + 1);
    if (df->columns[column_index]->title == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }
    strcpy(df->columns[column_index]->title, new_title);
}


void delete_column_df(DATAFRAME *df) {
    // Check if the column index is valid
    int column_index;
    printf("Type the index of the column you want to delete : ");
    scanf("%d",&column_index);

    if (column_index >= df->num_columns) {
        printf("Invalid column index.\n");
        return;
    }

    // Free the memory allocated for the column data
    for (unsigned int i = 0; i < df->columns[column_index]->size; i++) {
        free(df->columns[column_index]->data[i]);
    }

    // Shift columns to the left to fill the gap of the deleted column
    for (unsigned int i = column_index; i < df->num_columns - 1; i++) {
        // Move the next column to the current column
        df->columns[i] = df->columns[i + 1];
    }

    // Decrement the number of columns in the dataframe
    df->num_columns--;
}


void display_col_name(DATAFRAME *df) {
    printf("\nColumns: ");
    for (unsigned int i = 0; i < df->num_columns; i++) {
        printf("%s ", df->columns[i]->title);
    }
}

void print_value_at_cell(DATAFRAME *df,int row,int column) {
    // Check if the row and column numbers are valid
    if (row >= df->num_rows || column >= df->num_columns) {
        printf("Invalid row or column number.\n");
        return;
    }

    // Get the pointer to the value at the specified cell
    void *value_ptr = get_value_at_position(df->columns[column], row);

    // Print the value at the specified cell based on its type
    switch (df->columns[column]->column_type) {
        case UINT:
            printf("%u ", *(unsigned int *)value_ptr);
        break;
        case INT:
            printf("%d ", *(int *)value_ptr);
        break;
        case CHAR:
            printf("%c ", *(char *)value_ptr);
        break;
        case FLOAT:
            printf("%f ", *(float *)value_ptr);
        break;
        case DOUBLE:
            printf("%lf ", *(double *)value_ptr);
        break;
        case STRING:
            printf("%s ", (char *)value_ptr);
        break;
        case STRUCTURE:
            printf("%d ", *(int *)value_ptr);
                break;
        default:
            printf("Unsupported data type.\n");
        break;
    }
}


void set_value_at_cell(DATAFRAME *df, int row, int column, void *new_value) {
    // Check if the row and column numbers are valid
    if (row >= df->num_rows || column >= df->num_columns) {
        printf("Invalid row or column number.\n");
        return;
    }

    // Free the memory of the existing value if it exists
    free(df->columns[column]->data[row]);

    // Set the new value at the specified cell
    df->columns[column]->data[row] = malloc(sizeof(COL_TYPE));
    if (df->columns[column]->data[row] == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    memcpy(df->columns[column]->data[row], new_value, sizeof(COL_TYPE));
}

int is_value_in_dataframe(DATAFRAME *df, void *value) {
    // Iterate over each column


    for (unsigned int i = 0; i < df->num_columns; i++) {
        COLUMN *col = df->columns[i];

        // Iterate over each value in the column
        for (unsigned int j = 0; j < col->size; j++) {
            // Compare the value with the current cell value
            switch (col->column_type) {
                case UINT: {
                    unsigned int *cell_value = (unsigned int *)col->data[j];
                    if (*cell_value == *((unsigned int *)value)) {
                        return 1; // Value found
                    }
                    break;
                }
                case INT: {
                    int *cell_value = (int *)col->data[j];
                    if (*cell_value == *((int *)value)) {
                        return 1; // Value found
                    }
                    break;
                }
                case CHAR: {
                    char *cell_value = (char *)col->data[j];
                    if (*cell_value == *((char *)value)) {
                        return 1; // Value found
                    }
                    break;
                }
                case FLOAT: {
                    float *cell_value = (float *)col->data[j];
                    if (*cell_value == *((float *)value)) {
                        return 1; // Value found
                    }
                    break;
                }
                case DOUBLE: {
                    double *cell_value = (double *)col->data[j];
                    if (*cell_value == *((double *)value)) {
                        return 1; // Value found
                    }
                    break;
                }
                case STRING: {
                    char *cell_value = (char *)col->data[j];
                    if (strcmp(cell_value, (char *)value) == 0) {
                        return 1; // Value found
                    }
                    break;
                }
                case STRUCTURE:
                    int *cell_value = (int *)col->data[j];
                        if (*cell_value == *((int *)value)) {
                            return 1;
                        } // Value found
                    break;
                default:
                    printf("Unsupported data type.\n");
                    break;
            }
        }
    }
    return 0; // Value not found
}

// Display the number of cells equal to x
int count_cells_equal_to_x(DATAFRAME *df, int x) {
    int count = 0;
    // Iterate over each column
    for (unsigned int i = 0; i < df->num_columns; i++) {
        COLUMN *col = df->columns[i];
        // Check if the column type is INT
        if (col->column_type == INT || col->column_type == STRUCTURE) {
            // Iterate over each value in the column
            for (unsigned int j = 0; j < col->size; j++) {
                int *cell_value = (int *)col->data[j];
                // If the value in the cell is equal to x, increment count
                if (*cell_value == x) {
                    count++;
                }
            }
        }
    }
    return count;
}

// Display the number of cells containing a value greater than x
int count_cells_greater_than_x(DATAFRAME *df, int x) {
    int count = 0;
    // Iterate over each column
    for (unsigned int i = 0; i < df->num_columns; i++) {
        COLUMN *col = df->columns[i];
        // Check if the column type is INT
        if (col->column_type == INT || col->column_type == STRUCTURE) {
            // Iterate over each value in the column
            for (unsigned int j = 0; j < col->size; j++) {
                int *cell_value = (int *)col->data[j];
                // If the value in the cell is greater than x, increment count
                if (*cell_value > x) {
                    count++;
                }
            }
        }
    }
    return count;
}

// Display the number of cells containing a value less than x
int count_cells_less_than_x(DATAFRAME *df, int x) {
    int count = 0;
    // Iterate over each column
    for (unsigned int i = 0; i < df->num_columns; i++) {
        COLUMN *col = df->columns[i];
        // Check if the column type is INT
        if (col->column_type == INT || col->column_type == STRUCTURE) {
            // Iterate over each value in the column
            for (unsigned int j = 0; j < col->size; j++) {
                int *cell_value = (int *)col->data[j];
                // If the value in the cell is less than x, increment count
                if (*cell_value < x) {
                    count++;
                }
            }
        }
    }
    return count;
}


void sort(COLUMN *col, int sort_dir) {
    // Check if the column is valid and if it has data
    int modif=1;
    if (col == NULL || col->data == NULL) {
        printf("Invalid column or no data available.\n");
        return;
    }

    // Check if the column has enough data to sort
    if (col->size < 2) {
        printf("Not enough data to sort.\n");
        return;
    }

    // Allocate memory for the index array
    col->index = malloc(col->size * sizeof(unsigned long long));
    if (col->index == NULL) {
        printf("Memory allocation failed for index array.\n");
        exit(1);
    }

    // Initialize the index array with sequential indices
    for (unsigned int i = 0; i < col->size; i++) {
        col->index[i] = i;
    }

    // Sort the index array based on the values in the column using insertion sort
    while (modif == 1) {
        modif=insertion_sort_index(col, sort_dir);
    }
    // Update the valid_index flag to indicate that the index is valid
    col->valid_index = 1;

    // Set the sort direction
    col->sort_dir = sort_dir;
}

int insertion_sort_index(COLUMN *col, int sort_dir) {
    if (col == NULL || col->data == NULL || col->size < 2) {
        printf("Invalid column or not enough data to sort.\n");
        return 0;
    }

    // Allocate memory for the index array
    col->index = malloc(col->size * sizeof(unsigned long long));
    if (col->index == NULL) {
        printf("Memory allocation failed for index array.\n");
        exit(1);
    }

    // Initialize the index array with sequential indices
    for (unsigned int i = 0; i < col->size; i++) {
        col->index[i] = i;
    }

    // Bubble sort the index array based on the values in the column
    for (unsigned int i = 0; i < col->size - 1; i++) {
        for (unsigned int j = 0; j < col->size - i - 1; j++) {
            if (compare_values(col, j, j + 1, sort_dir)) {
                // Swap indices if necessary
                unsigned long long temp = col->index[j];
                col->index[j] = col->index[j + 1];
                col->index[j + 1] = temp;
            }
        }
    }

    // Update the valid_index flag to indicate that the index is valid
    col->valid_index = 1;

    // Set the sort direction
    col->sort_dir = sort_dir;
    return 0;
}

int compare_values(COLUMN *col, int index1, int index2, int sort_dir) {
    // Compare values in the column based on the sort direction
    switch (col->column_type) {
        case UINT:
            if (sort_dir == ASC) {
                return col->data[col->index[index1]]->uint_value > col->data[col->index[index2]]->uint_value;
            } else {
                return col->data[col->index[index1]]->uint_value < col->data[col->index[index2]]->uint_value;
            }
        case INT:
            if (sort_dir == ASC) {
                printf("comparing value %d and %d",col->data[col->index[index1]]->int_value,col->data[col->index[index2]]->int_value);
                return col->data[col->index[index1]]->int_value > col->data[col->index[index2]]->int_value;
            } else {
                return col->data[col->index[index1]]->int_value < col->data[col->index[index2]]->int_value;
            }
        case CHAR:
            if (sort_dir == ASC) {
                return col->data[col->index[index1]]->char_value > col->data[col->index[index2]]->char_value;
            } else {
                return col->data[col->index[index1]]->char_value < col->data[col->index[index2]]->char_value;
            }
        case FLOAT:
            if (sort_dir == ASC) {
                return col->data[col->index[index1]]->float_value > col->data[col->index[index2]]->float_value;
            } else {
                return col->data[col->index[index1]]->float_value < col->data[col->index[index2]]->float_value;
            }
        case DOUBLE:
            if (sort_dir == ASC) {
                return col->data[col->index[index1]]->double_value > col->data[col->index[index2]]->double_value;
            } else {
                return col->data[col->index[index1]]->double_value < col->data[col->index[index2]]->double_value;
            }
        case STRING:
            if (sort_dir == ASC) {
                return strcmp(col->data[col->index[index1]]->string_value, col->data[col->index[index2]]->string_value) > 0;
            } else {
                return strcmp(col->data[col->index[index1]]->string_value, col->data[col->index[index2]]->string_value) < 0;
            }
        case STRUCTURE:
            if (sort_dir == ASC) {
                return col->data[col->index[index1]]->struct_value > col->data[col->index[index2]]->struct_value;
            } else {
                return col->data[col->index[index1]]->struct_value < col->data[col->index[index2]]->struct_value;
            }
        default:
            printf("Unsupported data type for sorting.\n");
            return 0;
    }
}


void print_sorted_column(COLUMN *col) {
    if (col == NULL || col->title == NULL || col->data == NULL || col->index == NULL) {
        printf("Invalid column.\n");
        return;
    }

    printf("Column '%s' (Sorted):\n", col->title);
    for (unsigned int i = 0; i < col->size; i++) {
        unsigned int index = col->index[i];
        if (index != -1) {
            COL_TYPE *value = col->data[index];
            printf("\n[%u] ",i);
            switch (col->column_type) {
                case UINT:
                    printf("%u ", value->uint_value);
                break;
                case INT:
                    printf("%d ", value->int_value);
                break;
                case CHAR:
                    printf("%c ", value->char_value);
                break;
                case FLOAT:
                    printf("%f ", value->float_value);
                break;
                case DOUBLE:
                    printf("%lf ", value->double_value);
                break;
                case STRING:
                    printf("%s ", value->string_value);
                break;
                case STRUCTURE:
                    printf("%d ", value->int_value);
                break;
                default:
                    printf("Unsupported data type.\n");
            }
        }
    }
    printf("\n");
}

void erase_index(COLUMN *col) {
    // Check if the column is valid
    if (col == NULL) {
        printf("Invalid column.\n");
        return;
    }

    // Free the memory allocated to the index array
    free(col->index);

    // Set the index pointer to NULL and update the valid_index attribute
    col->index = NULL;
    col->valid_index = 0;
}

int check_index(COLUMN *col) {
    // Check if the column is valid
    if (col == NULL) {
        printf("Invalid column.\n");
        return 0;
    }

    // Check the state of the valid_index attribute
    if (col->valid_index == 0) {
        // Index does not exist
        return 0;
    } else if (col->valid_index == -1) {
        // Index exists but is invalid
        return -1;
    } else {
        // Index is correct
        return 1;
    }
}

void update_index(COLUMN *col) {
    // Check if the column is valid
    if (col == NULL) {
        printf("Invalid column.\n");
        return;
    }

    // Sort the column to update the index
    sort(col, col->sort_dir);
}

int search_value_in_column(COLUMN *col) {
    void *val = NULL;
    val = malloc(sizeof(col->column_type));

    // Check if memory allocation was successful
    if (val == NULL) {
        printf("Memory allocation failed.\n");
        return 0;
    }

    if (col == NULL || col->data == NULL || col->index == NULL) {
        printf("Invalid column or no data available.\n");
        return 0;
    }
    get_search_value(val,col->column_type);

    // Perform binary search to find the value
    int left = 0, right = col->size - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        unsigned long long index = col->index[mid];
        void *value = get_value_at_position(col, index);
        if (value == NULL) {
            printf("Error accessing value.\n");
            return 0;
        }

        // Compare the value with the search value
        switch (col->column_type) {
            case UINT:
                if (*((unsigned int *)value) == *((unsigned int *)val)) return 1;
                else if (*((unsigned int *)value) < *((unsigned int *)val)) left = mid + 1;
                else right = mid - 1;
                break;
            case INT:
                if (*((int *)value) == *((int *)val)) return 1;
                else if (*((int *)value) < *((int *)val)) left = mid + 1;
                else right = mid - 1;
                break;
            case CHAR:
                if (*((char *)value) == *((char *)val)) return 1;
                else if (*((char *)value) < *((char *)val)) left = mid + 1;
                else right = mid - 1;
                break;
            case FLOAT:
                if (*((float *)value) == *((float *)val)) return 1;
                else if (*((float *)value) < *((float *)val)) left = mid + 1;
                else right = mid - 1;
                break;
            case DOUBLE:
                if (*((double *)value) == *((double *)val)) return 1;
                else if (*((double *)value) < *((double *)val)) left = mid + 1;
                else right = mid - 1;
                break;
            case STRING:
                if (strcmp((char *)value, (char *)val) == 0) return 1;
                else if (strcmp((char *)value, (char *)val) < 0) left = mid + 1;
                else right = mid - 1;
                break;
            case STRUCTURE:
                if (*((int *)value) == *((int *)val)) return 1;
                else if (*((int *)value) < *((int *)val)) left = mid + 1;
                else right = mid - 1;
                break;
            default:
                printf("Unsupported data type for search.\n");
                return 0;
        }
    }
    free(val);
    // Value not found
    return 0;
}

void search_value_in_dataframe_with_user_input(DATAFRAME *df) {
    // Check if the dataframe is valid
    if (df == NULL || df->num_columns == 0) {
        printf("Invalid dataframe or no columns available.\n");
        return;
    }

    // Ask the user to select the search value type
    int column_type;
    printf("Select the type of value to search (2: UINT, 3: INT, 4: CHAR, 5: FLOAT, 6: DOUBLE, 7: STRING): ");
    scanf("%d", &column_type);

    // Allocate memory for the search value
    void *value;
    switch (column_type) {
        case UINT:
            value = malloc(sizeof(unsigned int));
            break;
        case INT:
            value = malloc(sizeof(int));
            break;
        case CHAR:
            value = malloc(sizeof(char));
            break;
        case FLOAT:
            value = malloc(sizeof(float));
            break;
        case DOUBLE:
            value = malloc(sizeof(double));
            break;
        case STRING:
            value = malloc(MAX_STRING_LENGTH * sizeof(char)); // Assuming MAX_STRING_LENGTH is defined
            break;
        case STRUCTURE:
            value = malloc(sizeof(int));
            break;
        default:
            printf("Invalid value type selected.\n");
        return;
    }

    // Get the search value from the user
    get_search_value(value, column_type);

    // Perform the search operation
    if (is_value_in_dataframe(df, value)) {
        printf("Value found in the dataframe.\n");
    } else {
        printf("Value not found in the dataframe.\n");
    }

    // Free allocated memory for search value
    free(value);
}

void get_search_value(void *value, int column_type) {
    switch (column_type) {
        case UINT:
            printf("Enter the unsigned integer value to search/set: ");
        scanf("%u", (unsigned int *)value);
        break;
        case INT:
            printf("Enter the integer value to search/set: ");
        scanf("%d", (int *)value);
        break;
        case CHAR:
            printf("Enter the character value to search/set: ");
        scanf(" %c", (char *)value); // Note the space before %c to consume any leading whitespace
        break;
        case FLOAT:
            printf("Enter the float value to search/set: ");
        scanf("%f", (float *)value);
        break;
        case DOUBLE:
            printf("Enter the double value to search/set: ");
        scanf("%lf", (double *)value);
        break;
        case STRING:
            printf("Enter the string value to search/set: ");
        scanf("%s", (char *)value); // Note: This assumes a single word without spaces
        break;
        case STRUCTURE:
            printf("Enter the integer value to search/set: ");
            scanf("%d", (int *)value);
        break;
        default:
            printf("Unsupported data type for search.\n");
    }
}

void set_value_in_dataframe_with_user_input(DATAFRAME *df) {
    // Check if the dataframe is valid
    //if (df == NULL || df->num_columns == 0) {
      //  printf("Invalid dataframe or no columns available.\n");
       // return;
    //}

    // Ask the user to select the search value type
    int column_type,row,columns;
    printf("Select the type of the new val columns (2: UINT, 3: INT, 4: CHAR, 5: FLOAT, 6: DOUBLE, 7: STRING): ");
    scanf("%d", &column_type);

    // Allocate memory for the search value
    void *value;
    switch (column_type) {
        case UINT:
            value = malloc(sizeof(unsigned int));
        break;
        case INT:
            value = malloc(sizeof(int));
        break;
        case CHAR:
            value = malloc(sizeof(char));
        break;
        case FLOAT:
            value = malloc(sizeof(float));
        break;
        case DOUBLE:
            value = malloc(sizeof(double));
        break;
        case STRING:
            value = malloc(MAX_STRING_LENGTH * sizeof(char)); // Assuming MAX_STRING_LENGTH is defined
        break;
        case STRUCTURE:
            value = malloc(sizeof(int));
        break;
        default:
            printf("Invalid value type selected.\n");
        return;
    }

    printf("type col");
    scanf("%d",&columns);
    printf("type row");
    scanf("%d",&row);
    // Get the search value from the user
    get_search_value(value, column_type);

    // Perform the search operation
    set_value_at_cell(df, row , columns , value);

    printf("value set");
    // Free allocated memory for search value
    free(value);
}