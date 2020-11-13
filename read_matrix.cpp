#include<iostream>
#include"read_matrix.h"

int main(void) {
    collection_of_matrices matrices = get_matrices();
    for(short i = 0; i < matrices.size(); i++) {
        for(short j = 0; j < MATRIX_ROW_SIZE; j++) {
            for(short k = 0; k < MATRIX_COLUMN_SIZE; k++)
                cout << matrices[i][j][k] << " ";
            cout << endl;
        }
        cout << endl;
    }
    return 0;
}