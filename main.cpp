#include <iostream>
#include <vector>
#include <fstream>
#include <ctime>
#include <cstring>
#include <cstdlib>
#include <limits>

using namespace std;

int maximum(vector<int> arr, size_t size);

int minimum(vector<int> arr, size_t size);

vector<int> simpleCountingSort(vector<int> A, size_t N);

bool is_digit(string s);


int main(int argc, char *argv[]) {
    unsigned int start_time = clock();
    try {
        bool is_t = false;
        if (argc > 4 || argc < 3)
            throw "INCORRECT_ARGUMENTS";
        ifstream fin(argv[1]);
        if (!fin.is_open())
            throw "IN_NOT_OPENED";
        ofstream fout(argv[2]);
        if (!fout.is_open())
            throw "OUT_NOT_OPENED";
        fout.clear();
        if (argc == 4)
            is_t = strcmp(argv[3], "-t") == 0;

        size_t amount_of_strings = 0;
        size_t max_string_len = 0;
        size_t min_string_len = numeric_limits<size_t>::max();;
        size_t N = 0;
        vector<int> A;
        string numbers_buffer;

        while (!fin.eof()) {
            fin >> numbers_buffer;
            max_string_len = max(numbers_buffer.length(), max_string_len);
            min_string_len = min(numbers_buffer.length(), min_string_len);
            amount_of_strings++;
            if (is_digit(numbers_buffer)) {
                A.push_back(stoi(numbers_buffer));
                N++;
            }
        }

        if (!is_t) {
            vector<int> B = simpleCountingSort(A, N);
            for (int i = 0; i < N; i++)
                fout << B[i] << ' ';
        } else
            for (int i = 0; i < N; i++)
                fout << A[i] << ' ';

        fin.close();
        fout.close();

        unsigned int end_time = clock();
        cout << "Work time = " << start_time - end_time << " ms" << endl;
        cout << "Amount of strings = " << amount_of_strings << endl;
        cout << "Mid string length = " << (max_string_len + min_string_len) / 2
             << endl;
        return 0;
    }

    catch (string &errors) {
        cout << errors;
        return -1;
    }
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
    if (s[0] != '-' && (s[0] < '0' || s[0] > '9'))
        return false;
    for (int i = 1; i < s.size(); i++)
        if (s[i] < '0' || s[i] > '9')
            return false;
    return true;
}