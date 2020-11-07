#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

int maximum(vector<int> arr, size_t size);

int minimum(vector<int> arr, size_t size);

void simpleCountingSort(vector<int> A, size_t N);

int main() {
    size_t N;
    cin >> N;
    vector<int> A(N);
    for (int i = 0; i < N; i++) {
        A[i] = pow(-1, i) * rand() / 10;
        cout << A[i] << ' ';
    }
    cout << endl << endl;
    simpleCountingSort(A, N);
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

void simpleCountingSort(vector<int> A, size_t N) {
    int max_val = maximum(A, N);
    int min_val = minimum(A, N);
    unsigned int numbers_range = abs(max_val - min_val);
    vector<int> frequency(numbers_range);
    for (int i = 0; i <= numbers_range; i++)
        frequency[i] = 0;
    for (size_t i = 0; i < N; i++)
        ++frequency[abs(A[i] - min_val)];
    size_t position = 0;
    vector<int> B(N);
    for (int i = 0; i <= numbers_range; i++)
        cout << i << '\t' << frequency[i] << endl;
    for (int i = 0; i <= numbers_range; i++)
        for (size_t j = 0; j < frequency[i]; j++) {
            B[position] = i + min_val;
            ++position;
        }
    for (int i = 0; i < N; i++)
        cout << B[i] << ' ';
}