#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>
#include <iomanip>


using namespace std;
unsigned int microsecond = 1000000;

string begin(){
    string fileName;
    cout << "Welcome to the Matrix." << endl;
    usleep(1.5 * microsecond);
    cout << "No not that one." << endl;
    usleep(1.5 * microsecond);
    cout << "Well, who knows I guess." << endl;
    usleep(1.5 * microsecond);
    cout << "Enter the name of your data file grade-keeper I am not afraid: ";
    cin >> fileName;
    return fileName;
}

int menu(){
    int entry;
    cout << endl;
    cout << "1) Print your Matrices" << endl;
    cout << "2) Add your Matrices" << endl;
    cout << "3) Multiply your Matrices" << endl;
    cout << "4) Subtract your Matrices" << endl;
    cout << "5) Change an element in Matrix A" << endl;
    cout << "6) Find the max element of Matrix A" << endl;
    cout << "7) Transpose Matrix A" << endl;
    cout << "8) Exit" << endl;
    cout << "Choice: ";
    cin >> entry;
    cout << endl;
    return entry;
}

int first(string fileName){
    ifstream textFile (fileName);
    int entry;
    if (textFile.is_open()){
        textFile >> entry;
        textFile.close();
    }
    return 2*(entry*entry)+1;
}

int readin(string fileName, int *array){
    ifstream textFile (fileName);
    int entry;
    if (textFile.is_open()){
        int ind = 0;
        while (textFile >> entry){
            array[ind] = entry;
            ind++;
        }
        textFile.close();
    }
    return 0;
}

int process(int *raw, int **ma, int **mb){
    for (int s = 0; s < raw[0]; s++){
        ma[s] = new int[raw[0]];
        mb[s] = new int[raw[0]];
    }
    int dim = raw[0]*raw[0];
    int length = 2*(dim)+1;
    int k = 1;
    for (int i = 0; i < raw[0]; i++){
        for (int j = 0; j < raw[0]; j++, k++){
            //cout << "For A: " << raw[k] << " For B: " << raw[k+dim] << endl;
            ma[i][j] = raw[k];
            mb[i][j] = raw[k+dim];
        }
    }
    return 0;
}

int display(int **matrix, int len){
    cout << left;
    for (int i = 0; i < len; i++){
        for (int j = 0; j < len; j++){
            cout << setw(5) << matrix[i][j];
        }
        cout << endl;
    }
    cout << endl;
    return 0;
}

int add(int **ma, int **mb, int len){
    int **result = new int*[len];
    for (int s = 0; s < len; s++){
        result[s] = new int[len];
    }
    for (int i = 0; i < len; i++){
        for (int j = 0; j < len; j++){
            result[i][j] = ma[i][j] + mb [i][j];
        }
    }
    cout << "Matrix A + Matrix B = " << endl;
    display(result, len);
    return 0;
}

int multiply(int **ma, int **mb, int len){
    int **result = new int*[len];
    for (int i = 0; i < len; i++){
        result[i] = new int[len];
    }
    int s = 0;
    while (s < len){
        for (int r = 0; r < len; r++){
            int temp = 0;
            for (int p = 0, q = 0; p < len; p++, q++){
                temp += ma[s][p]*mb[q][r];
            }
            result[s][r] = temp;
        }
        s++;
    }
    cout << "Matrix A * Matrix B = " << endl;
    display(result, len);
    return 0;
}

int sub(int **ma, int **mb, int len){
    int **result = new int*[len];
    for (int s = 0; s < len; s++){
        result[s] = new int[len];
    }
    for (int i = 0; i < len; i++){
        for (int j = 0; j < len; j++){
            result[i][j] = ma[i][j] - mb [i][j];
        }
    }
    cout << "Matrix A - Matrix B = " << endl;
    display(result, len);
    return 0;
}

int change(int **mtx, int len, int x, int y, int val){
    if ((x < 1 || x > len) && (y < 1 || y > len)){
        return 3;
    }
    if (x < 1 || x > len){
        return 1;
    }
    if (y < 1 || y > len){
        return 2;
    }
    mtx[x-1][y-1] = val;
    cout << "Matrix A updated:" << endl;
    display(mtx, len);
    return 0;
}

int max(int **mtx, int len){
    int max = mtx[0][0];
    for (int i = 0; i < len; i++){
        for (int j = 0; j < len; j++){
            if (max < mtx[i][j]){
                max = mtx[i][j];
            }
        }
    }
    return max;
}

int t_pose(int **mtx, int len){
    int **result = new int*[len];
    for (int s = 0; s < len; s++){
        result[s] = new int[len];
    }
    for (int i = 0; i < len; i++){
        for (int j = 0; j < len; j++){
            result[i][j] = mtx[j][i];
        }
    }
    cout << "Transpose of Matrix A: " << endl;
    display(result, len);
    return 0;
}

int run(int **matrixA, int **matrixB, int len){
    int flag = 1;
    while (flag == 1){
        int choice = menu();
        //cout << choice << endl;
        switch(choice){
            case 1:
                cout << "Matrix A: " << endl;
                display(matrixA, len);
                cout << "Matrix B: " << endl;
                display(matrixB, len);
                break;
            case 2:
                add(matrixA, matrixB, len);
                break;
            case 3:
                multiply(matrixA, matrixB, len);
                break;
            case 4:
                sub(matrixA, matrixB, len);
                break;
            case 5:
                int x, y, val, temp_e;
                cout << "Enter the row number: ";
                cin >> x;
                cout << endl;
                cout << "Enter the column number: ";
                cin >> y;
                cout << endl;
                cout << "Enter the updated value that you want: ";
                cin >> val;
                cout << endl;
                temp_e = change(matrixA, len, x, y, val);
                if (temp_e == 1){
                    cout << "Bad row number." << endl;
                }else if(temp_e ==2){
                    cout << "Bad column number." << endl;
                }else if(temp_e == 3){
                    cout << "Bad row and column number." << endl;
                    usleep(1.5 * microsecond);
                    cout << "Get it together dude." << endl;
                }
                break;
            case 6:
                cout << "Max of Matrix A: " << max(matrixA, len) << endl;
                break;
            case 7:
                cout << "You know I had to do it to 'em." << endl;
                usleep(1.5 * microsecond);
                cout << endl;
                t_pose(matrixA, len);
                break;
            case 8:
                cout << "I hope your rambles have been sweet, and your reveries spacious." << endl;
                flag = 0;
                break;
            default:
                cout << "Invalid response." << endl;
                usleep(2 * microsecond);
                cout << "Get out." << endl;
                usleep(1 * microsecond);
                flag = 0;
        }
    }
    return 0;
}


int main(){
    string fileName = begin();
    int raw_data[first(fileName)];
    readin(fileName, raw_data);
    int** matrixA = new int*[raw_data[0]];
    int** matrixB = new int*[raw_data[0]];
    process(raw_data, matrixA, matrixB);
    run(matrixA, matrixB, raw_data[0]);
    return 0;
}