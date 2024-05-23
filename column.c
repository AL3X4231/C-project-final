#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "column.h"

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
    col->data = NULL; // Initialize data pointer to NULL
    col->index = NULL; // Initialize index pointer to NULL
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
