#include <stdio.h>
#include "cdataframe.h"
#include <stdlib.h>
#define ASC 0
#define DESC 1


int main() {
    int sortdir;
    int choice, result;
    int columns,row,value;
    DATAFRAME *df = create_empty_dataframe();
    do {
        printf("\nMenu:\n");
        printf("1. Fill the CDataframe\n");
        printf("2. Display the CDataframe\n");
        printf("3. Perform usual operations\n");
        printf("4. Analyze and statistics\n");
        printf("5. Sort\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                do {
                    printf("\nMenu:Fill the CDataframe\n");
                    printf("1. Filling in the CDataframe with user input\n");
                    printf("2. Hard filling of the CDataframe\n");
                    printf("3. Exit\n");
                    printf("Enter your choice: ");
                    scanf("%d", &choice);

                    switch(choice) {

                        case 1:
                            fill_dataframe_user(df);
                            break;
                        case 2:
                            hard_fill_dataframe(df,5,5);
                            printf("Dataframe 5x5 hard fill with 0 created");
                                    break;
                        case 3:
                            printf("Exiting...\n");
                                    break;
                        break;
                        default:
                            printf("Invalid choice. Please try again.\n");
                    }

                } while(choice != 3);


                            break;
            case 2:
                display_dataframe(df);
                break;


            case 3:
                do {
                    printf("\nMenu: Perform usual operations\n");
                    printf("1. Add a row of values to the CDataframe\n");
                    printf("2. Delete a row of values from the CDataframe\n");
                    printf("3. Add a column to the CDataframe\n");
                    printf("4. Delete a column from the CDataframe\n");
                    printf("5. Rename the title of a column in the CDataframe\n");
                    printf("6. Check the existence of a value (search) in the CDataframe\n");
                    printf("7. Access the value in a CDataframe cell using its row and column number\n");
                    printf("8. Replace the value in a CDataframe cell using its row and column number\n");
                    printf("9. Exit\n");
                    printf("Enter your choice: ");
                    scanf("%d", &choice);

                    switch(choice) {
                        case 1:
                            add_row_to_dataframe(df);
                                        break;
                        case 2:
                            delete_row(df);

                                        break;
                        case 3:
                            add_column_and_fill(df);
                                    break;
                        case 4:
                            delete_column_df(df);
                            printf("Exiting...\n");
                            break;
                        case 5:
                            rename_column(df);
                            break;
                        case 6:
                            search_value_in_dataframe_with_user_input(df);
                            break;

                        case 7:

                            printf("type col");
                            scanf("%d",&columns);
                            printf("type row");
                            scanf("%d",&row);
                            print_value_at_cell(df,row,columns);
                            break;

                        case 8:

                            set_value_in_dataframe_with_user_input(df) ;
                            break;

                        case 9:
                            printf("Exiting...\n");
                            break;
                        default:
                            printf("Invalid choice. Please try again.\n");
                    }

                } while(choice != 9);

                        break;
            case 4:
                do {
                    printf("\nMenu: Analysis and statistics\n");
                    printf("1. Display the number of cells equal to x (x given as parameter)\n");
                    printf("2. Display the number of cells containing a value greater than x (x given as a parameter)\n");
                    printf("3.  Display the number of cells containing a value less than x(x given as parameter)\n");
                    printf("4. Exit\n");
                    printf("Enter your choice: ");
                    scanf("%d", &choice);

                    switch(choice) {
                        case 1:
                            printf("type value : ");
                            scanf("%d",&value);
                            result = count_cells_equal_to_x(df,value);
                            printf("Number of value equal to %d is %d",value,result);


                                        break;
                        case 2:
                            printf("type value : ");
                            scanf("%d",&value);
                            count_cells_greater_than_x(df,value);
                                        break;
                        case 3:
                            printf("type value : ");
                            scanf("%d",&value);
                            count_cells_less_than_x(df,value);
                                    break;
                        case 4:
                            printf("Exiting...\n");
                        break;
                        break;
                        default:
                            printf("Invalid choice. Please try again.\n");
                    }

                } while(choice != 4);

                        break;
            case 5:
                do {
                    printf("\nMenu: Sort\n");
                    printf("1. Sort a columns\n");
                    printf("2. Display a sorted columns basing on index\n");
                    printf("3. Erase a columns index\n");
                    printf("4. Update a columns index\n");
                    printf("5. Dichotomous search of a value in a columns\n");
                    printf("6. Exit\n");
                    printf("Enter your choice: ");
                    scanf("%d", &choice);

                    switch(choice) {
                        case 1:

                            printf("type columns index : ");
                            scanf("%d",&value);
                            printf("type 0 for ASC; 1 for DESC: ");
                            scanf("%d",&sortdir);
                            sort(df->columns[value],sortdir);
                            break;
                        case 2:
                            printf("type columns index : ");
                            scanf("%d",&value);
                            print_sorted_column(df->columns[value]);
                            break;
                        case 3:
                            printf("type columns index : ");
                            scanf("%d",&value);
                            erase_index(df->columns[value]);
                            break;
                        case 4:
                            printf("type columns index : ");
                            scanf("%d",&value);
                            update_index(df->columns[value]);
                            break;
                        case 5:
                            printf("type columns index : ");
                            scanf("%d",&value);
                            result = search_value_in_column(df->columns[value]);
                            if (result == 1) {
                                printf("Value found\n");
                            }
                            break;
                        case 6:
                            printf("Exiting...\n");
                            break;
                        default:
                            printf("Invalid choice. Please try again.\n");
                    }

                } while(choice != 6);
                choice=0;
                break;
            case 6:
                printf("Exiting...\n");
            break;
            default:
                printf("Invalid choice. Please try again.\n");
        }

    } while(choice != 6);

    return 0;
}
