#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>

using namespace std;

int maximum(vector<int> arr, size_t size);

int minimum(vector<int> arr, size_t size);

vector<int> simpleCountingSort(vector<int> A, size_t N);

bool is_digit(string s);


int main(int argc, char *argv[]) {
    bool is_t = false;
    if (argc > 4 || argc < 3) {
        cout << "Incorrect amount of arguments\n";
        return -1;
    }
    ifstream fin(argv[1]);
    ofstream fout(argv[2]);
    if (argc == 4)
        is_t = argv[3] == "-t";
    size_t N = 0;
    vector<int> A(N);
    string numbers_buffer;
    while (!fin.eof()) {
        fin >> numbers_buffer;
        if (is_digit(numbers_buffer)) {
            A.push_back(stoi(numbers_buffer));
            N++;
        }
    }
    if (is_t) {
        vector<int> B = simpleCountingSort(A, N);
        for (int i = 0; i < N; i++)
            fout << B[i] << ' ';
    }
    else
        for (int i = 0; i < N; i++)
            fout << A[i] << ' ';
    return 0;
}


int maximum(vector<int> arr, size_t size) {
    int max;
    max = arr[0];
    for (int i = 0; i < size; i++)
        if (arr[i] > max)
            max = arr[i];
    return max;
}


int minimum(vector<int> arr, size_t size) {
    int min;
    min = arr[0];
    for (int i = 0; i < size; i++)
        if (arr[i] < min)
            min = arr[i];
    return min;
}


vector<int> simpleCountingSort(vector<int> A, size_t N) {
    int max_val = maximum(A, N);
    int min_val = minimum(A, N);
    unsigned int numbers_range = abs(max_val - min_val) + 1;
    vector<int> frequency(numbers_range);
    for (int i = 0; i < numbers_range; i++)
        frequency[i] = 0;
    for (size_t i = 0; i < N; i++)
        ++frequency[abs(A[i] - min_val)];
    size_t position = 0;
    vector<int> B(N);
    for (int i = 0; i < numbers_range; i++)
        for (size_t j = 0; j < frequency[i]; j++) {
            B[position] = i + min_val;
            ++position;
        }
    return B;
}


bool is_digit(string s) {
    for (int i = 0; i < s.size(); i++)
        if ((s[i] == '-' && i != 0) || (s[i] > '0' && s[i] < '9'))
            return false;
    return true;
}