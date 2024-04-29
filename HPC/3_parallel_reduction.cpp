#include <bits/stdc++.h>
#include <omp.h>
using namespace std;

void sum_reduction(vector<int> &arr) {
    int sum = arr[0] ;
    #pragma omp parallel for reduction(+:sum)
    for( int i=1; i<arr.size(); i++ ) {
        sum += arr[i] ;
    }
    cout << "Sum : " << sum << endl ;
}

void min_reduction( vector<int> &arr ) {
    int min_value = arr[0] ;
    #pragma omp parallel for reduction(min:min_value)
    for( int i=1; i<arr.size(); i++ ) {
        if( arr[i] < min_value )  {
            min_value = arr[i] ;
        }
    }
    cout << "Min : " << min_value << endl ;
}

void max_reduction( vector<int> &arr ) {
    int max_value = arr[0] ;
    #pragma omp parallel for reduction(max:max_value)
    for( int i=1; i<arr.size(); i++ ) {
        if( arr[i] > max_value )  {
            max_value = arr[i] ;
        }
    }
    cout << "Max : " << max_value << endl ;
}

void average_reduction( vector<int> &arr ) {
    double average = 0 ;
    #pragma omp parallel for reduction(+:average)
    for( int i=0; i<arr.size(); i++ ) {
        average += arr[i] ;
    }
    average /= arr.size() ;
    cout << "Average : " << average << endl ;
}

vector<int> genrateRandomArray(int size) {
    vector<int> arr(size) ;
    for( int i = 0; i<size; i++ ) {
        arr[i] = i % 1000 + 1;
    }
    return arr ;
}

int main()
{
    vector<int> arr = genrateRandomArray(100) ;

    double start = omp_get_wtime() ;
    min_reduction(arr) ;
    max_reduction(arr) ;
    sum_reduction(arr) ;
    average_reduction(arr) ;
    double end = omp_get_wtime() ;
    cout << "Parallel Reduction Time: " << (end-start) << endl ;

    return 0;
}