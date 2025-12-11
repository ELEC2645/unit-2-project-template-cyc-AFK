#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//Clear the input buffer
static void clear_input_buffer(void) {
    while (getchar() != '\n');
}

/**
 * Get a positive integer input
 * @param prompt The string prompting the user for input
 * @return A valid positive integer
 */
static int get_positive_integer(const char* prompt) {
    int num;
    int input_count;
    do {
        printf("%s", prompt);
        input_count = scanf_s("%d", &num);
        clear_input_buffer(); 
        // Check if the input is a valid integer
        if (input_count != 1) {
            printf("Invalid input! Please enter an integer.\n");
        }
        // Check if the input is a positive number
        else if (num <= 0) {
            printf("Invalid input! Please enter a positive integer.\n");
        }
    } while (input_count != 1 || num <= 0);
    return num;
}
/**
 * Enter elements into the matrix
 * @param matrix Pointer to the input matrix
 * @param rows The number of rows in the matrix
 * @param cols The number of columns in the matrix
 * Enter matrix elements row by row. Each row must have the specified number of elements; otherwise, re-enter that row.
 */
static void input_matrix(float** matrix, int rows, int cols, const char* matrix_name) {
    printf("\nPlease enter the elements of %s (%d rows & %d columns) (%d numbers per row, separated by spaces):\n", matrix_name, rows, cols, cols);
    for (int i = 0; i < rows; i++) {
        printf("Line %d", i + 1);
        int input_count;
        do {
            input_count = 0;
            for (int j = 0; j < cols; j++) {
                if (scanf_s("%f", &matrix[i][j]) == 1) {
                    input_count++;
                }
            }
            clear_input_buffer();
            if (input_count != cols) {
                printf("Input error! This line requires %d numbers. Please re-enter line %d:\n", cols, i + 1);
            }
        } while (input_count != cols);
    }
}
/**
 * Print matrix contents
 * Print the matrix in row and column format, keeping two decimal places for each element
 */
static void print_matrix(float** matrix, int rows, int cols, const char* matrix_name) {
    printf("\n%s(%d rows * %d columns)\n", matrix_name, rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%.2f\t", matrix[i][j]);
        }
        printf("\n");
    }
}
/**
 * Matrix Addition
 * Perform the addition of two matrices of the same shape, store the result in a new matrix, and print it.
 */
void matrix_addition(void) {
    printf("\n===== matrix addition =====\n");
    // Get the number of rows and columns of matrix A
    int rows1 = get_positive_integer("Please enter the number of rows of matrix A:");
    int cols1 = get_positive_integer("Please enter the number of columns of matrix A:");

    // Get the number of rows and columns of matrix B and check whether it is the same shape as matrix A
    int rows2, cols2;
    do {
        rows2 = get_positive_integer("Please enter the number of rows of matrix B:");
        cols2 = get_positive_integer("Please enter the number of columns of matrix B:");
        if (rows1 != rows2 || cols1 != cols2) {
            printf("Error! please enter matrix rows1 = rows2 cols1 = cols2\n");
        }
    } while (rows1 != rows2 || cols1 != cols2);

    // Allocate memory for three matrices
    float** A = (float**)malloc(rows1 * sizeof(float*));
    float** B = (float**)malloc(rows1 * sizeof(float*));
    float** C = (float**)malloc(rows1 * sizeof(float*));
    for (int i = 0; i < rows1; i++) {
        A[i] = (float*)malloc(cols1 * sizeof(float));
        B[i] = (float*)malloc(cols1 * sizeof(float));
        C[i] = (float*)malloc(cols1 * sizeof(float));
    }

    input_matrix(A, rows1, cols1, "Matrix A");
    input_matrix(B, rows2, cols2, "Matrix B");

    // Perform matrix addition
    for (int i = 0; i < rows1; i++) {
        for (int j = 0; j < cols1; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }

    print_matrix(A, rows1, cols1, "Matrix A");
    print_matrix(B, rows2, cols2, "Matrix B");
    print_matrix(C, rows1, cols1, "Matrix C = A + B");

    // Release dynamically allocated memory to avoid memory leaks
    for (int i = 0; i < rows1; i++) {
        free(A[i]);
        free(B[i]);
        free(C[i]);
    }
    free(A);
    free(B);
    free(C);
}

/**
 * Matrix multiplication
 * Implement multiplication of two matrices
 * The results are stored in a new matrix and printed.
 */
void matrix_multiplication(void) {
    printf("\n===== Matrix Multiplication =====\n");
    // Get the number of rows and columns of matrix A
    int rows1 = get_positive_integer("Please enter the number of rows of matrix A:");
    int cols1 = get_positive_integer("Please enter the number of columns of matrix A:");

    // Obtain the number of rows and columns of matrix B, and verify the feasibility of multiplication (the number of columns of A must equal the number of rows of B)
    int rows2, cols2;
    do {
        rows2 = get_positive_integer("Please enter the number of rows of matrix B:");
        cols2 = get_positive_integer("Please enter the number of columns of matrix B:");
        if (cols1 != rows2) {
            printf("Error! please enter matrix cols1 = rows2\n");
        }
    } while (cols1 != rows2);

    // Allocate memory for three matrices
    float** A = (float**)malloc(rows1 * sizeof(float*));
    float** B = (float**)malloc(rows2 * sizeof(float*));
    float** C = (float**)malloc(rows1 * sizeof(float*));
    for (int i = 0; i < rows1; i++) A[i] = (float*)malloc(cols1 * sizeof(float));
    for (int i = 0; i < rows2; i++) B[i] = (float*)malloc(cols2 * sizeof(float));
    for (int i = 0; i < rows1; i++) C[i] = (float*)malloc(cols2 * sizeof(float));

    input_matrix(A, rows1, cols1, "Matrix A");
    input_matrix(B, rows2, cols2, "Matrix B");

    // Perform matrix multiplication
    for (int i = 0; i < rows1; i++) { 
        for (int j = 0; j < cols2; j++) { 
            C[i][j] = 0.0; 
            for (int k = 0; k < cols1; k++) { 
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    print_matrix(A, rows1, cols1, "Matrix A");
    print_matrix(B, rows2, cols2, "Matrix B");
    print_matrix(C, rows1, cols2, "Matrix C = A + B");

    // Release dynamically allocated memory to avoid memory leaks
    for (int i = 0; i < rows1; i++) free(A[i]);
    for (int i = 0; i < rows2; i++) free(B[i]);
    for (int i = 0; i < rows1; i++) free(C[i]);
    free(A);
    free(B);
    free(C);
}

/**
 * Matrix Transpose Operation
 * Transpose the rows and columns of the matrix, store the result in a new matrix, and print it.
 */
void matrix_transpose(void) {
    printf("\n===== Matrix Transpose =====\n");
    // Get the number of rows and columns of the original matrix
    int rows = get_positive_integer("Please enter the number of rows of the original matrix:");
    int cols = get_positive_integer("Please enter the number of columns of the original matrix:");

    // Allocate memory for the original matrix and the transposed matrix
    // The number of rows in a transposed matrix equals the number of columns in the original matrix, and the number of columns equals the number of rows in the original matrix.
    float** mat = (float**)malloc(rows * sizeof(float*));
    float** trans_mat = (float**)malloc(cols * sizeof(float*));
    for (int i = 0; i < rows; i++) mat[i] = (float*)malloc(cols * sizeof(float));
    for (int i = 0; i < cols; i++) trans_mat[i] = (float*)malloc(rows * sizeof(float));

    input_matrix(mat, rows, cols, "original matrix");

    // Perform matrix transpose
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            trans_mat[j][i] = mat[i][j];
        }
    }

    print_matrix(mat, rows, cols, "original matrix");
    print_matrix(trans_mat, cols, rows, "Transpose matrix");

    // Release dynamically allocated memory to avoid memory leaks
    for (int i = 0; i < rows; i++) free(mat[i]);
    for (int i = 0; i < cols; i++) free(trans_mat[i]);
    free(mat);
    free(trans_mat);
}

/**
 * Calculate the determinant of a matrix
 * Only supports 2x2 and 3x3 matrices. Use the corresponding formula to calculate the determinant and print the result.
 */
void matrix_determinant(void) {
    printf("\n===== matrix determinant =====\n");
    int n;
    do {
        n = get_positive_integer("Please enter the order of the matrix (2 or 3):");
        if (n != 2 && n != 3) {
            printf("Error! only include n=2 and n=3\n");
        }
    } while (n != 2 && n != 3);

    float** mat = (float**)malloc(n * sizeof(float*));
    for (int i = 0; i < n; i++) {
        mat[i] = (float*)malloc(n * sizeof(float));
    }

    char matrix_name[20];
    sprintf_s(matrix_name, sizeof(matrix_name), "%d-order matrix", n); 
    input_matrix(mat, n, n, matrix_name);

    // Calculate the determinant
    float det = 0.0;
    if (n == 2) {
        det = mat[0][0] * mat[1][1] - mat[0][1] * mat[1][0];
    }
    else if (n == 3) {
        det = mat[0][0] * (mat[1][1] * mat[2][2] - mat[1][2] * mat[2][1])
            - mat[0][1] * (mat[1][0] * mat[2][2] - mat[1][2] * mat[2][0])
            + mat[0][2] * (mat[1][0] * mat[2][1] - mat[1][1] * mat[2][0]);
    }

    print_matrix(mat, n, n, matrix_name);
    printf("\nThe determinant of this %d * %d matrix is: %.2f\n", n, det);

    // Release dynamically allocated memory to avoid memory leaks
    for (int i = 0; i < n; i++) free(mat[i]);
    free(mat);
}