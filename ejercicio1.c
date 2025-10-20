// ejercicio1.c
#include <stdio.h>
#include <stdlib.h>

void print_matrix(int *mat_ptr, int rows, int cols) {
    int *p = mat_ptr;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            printf("%d ", *(p + i*cols + j));
        }
        printf("\n");
    }
}

void flatten_matrix_to_array(int *mat_ptr, int rows, int cols, int *out_arr) {
    int *src = mat_ptr;
    int *dst = out_arr;
    int total = rows * cols;
    for (int k = 0; k < total; ++k) {
        *(dst + k) = *(src + k);   // aritmética de punteros, sin indexado []
    }
}

void array_to_matrix(int *arr, int rows, int cols, int *mat_ptr) {
    int *src = arr;
    int *dst = mat_ptr;
    int total = rows * cols;
    for (int k = 0; k < total; ++k) {
        *(dst + k) = *(src + k);
    }
}

void bubble_sort_ptr(int *arr, int n) {
    // Bubble sort usando solo aritmética de punteros y swap con temp
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - 1 - i; ++j) {
            int *a = arr + j;
            int *b = arr + j + 1;
            if (*a > *b) {
                int tmp = *a;
                *a = *b;
                *b = tmp;
            }
        }
    }
}

int main(void) {
    // Tres matrices de ejemplo (documenta estas en el reporte)
    int A[2][3] = {{9, 1, 5}, {3, 7, 2}};      // 2x3
    int B[3][3] = {{10, 2, 8}, {4, 6, 1}, {3, 9, 5}}; // 3x3
    int C[4][2] = {{12, 4}, {7, 0}, {3, 11}, {5, 2}}; // 4x2

    // Proceso para cada matriz: flatten, sort, rebuild, imprimir
    struct {
        int *ptr;
        int rows;
        int cols;
        const char *name;
    } cases[3] = {
        {(int*)A, 2, 3, "A (2x3)"},
        {(int*)B, 3, 3, "B (3x3)"},
        {(int*)C, 4, 2, "C (4x2)"}
    };

    for (int t = 0; t < 3; ++t) {
        int rows = cases[t].rows;
        int cols = cases[t].cols;
        int total = rows * cols;
        int *temp_arr = malloc(sizeof(int) * total);
        if (!temp_arr) {
            fprintf(stderr, "Malloc failed\n");
            return 1;
        }

        printf("Matriz original %s:\n", cases[t].name);
        print_matrix(cases[t].ptr, rows, cols);
        // Flatten
        flatten_matrix_to_array(cases[t].ptr, rows, cols, temp_arr);
        // Ordenar
        bubble_sort_ptr(temp_arr, total);
        // Reconstruir
        array_to_matrix(temp_arr, rows, cols, cases[t].ptr);
        printf("Matriz ordenada reconstruida %s:\n", cases[t].name);
        print_matrix(cases[t].ptr, rows, cols);
        printf("----\n");

        free(temp_arr);
    }

    return 0;
}
