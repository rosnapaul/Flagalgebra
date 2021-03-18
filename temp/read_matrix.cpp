#include<iostream>
#include"read_matrix.h"

int main(void) {
    int i,j,k; // Variables Needed For Loop
    collection_of_matrices matrices = get_matrices(); // `matrices` Contains All 262 Matrices.

    for(i = 0; i < matrices.size(); i++) { // matrices.size() gives 261
        for(j = 0; j < MATRIX_ROW_SIZE; j++) { // MATRIX_ROW_SIZE is set as 6
            for(k = 0; k < MATRIX_COLUMN_SIZE; k++) // MATRIX_COLUMN_SIZE is set as 5
                cout << matrices[i][j][k] << " ";
            cout << endl;
        }
        cout << endl;
    }
    return 0;
}