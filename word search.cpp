#include <iostream>
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <random>
#include <stdlib.h>
#include <time.h>

using namespace std;

int array_size;

void transpose(int (&array1[][]),int array2[][array_size]) {
    for(int i = 0; i < array_size; i++){
        for(int j = 0; j < array_size; j++){
            array2[i][j] = array1[j][i];
        }
    }
}

int main() {

    srand(time(NULL));
    cout << time(NULL) << '\n';


    cout << "Enter the size of the array note the number you input will be the number for the rows and columns: ";
    cin >> array_size;
    int array[array_size][array_size];
    int transposed_array[array_size][array_size];


    for (int i = 0; i < array_size; i++){
        for(int j = 0; j < array_size; j++){
            array[i][j] = rand() % 4000 + i + j;
            //cout << array[i][j];
        }
    }

    for(int i = 0; i < array_size; i++){
        cout << "Row " << i + 1 << ' ';
        for(int j = 0; j < array_size; j++){

            cout << setw(4) << array[i][j] << ' ';
        }
        cout << '\n';
    }

    transpose(array,transposed_array);
    return 0;

}
