#include <bits/stdc++.h>
#include <omp.h>
using namespace std;

void SequentialBubble(vector<int> &arr) {
    int n = arr.size() ;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j< n-i-1; j++) {
            if ( arr[j] > arr[j+1] ) {
                swap(arr[j], arr[j+1]) ;
            }
        }
    } 
}

void parallelBubble(vector<int> &arr) {
    int n = arr.size() ;
    
     #pragma omp parallel for num_threads(4) 
    {for (int i = 0; i < n; i++)
    {
        bool swapped = false;
        #pragma omp for
        for (int j = 0; j< n-i-1; j++) {
            if ( arr[j] > arr[j+1] ) {
                swap(arr[j], arr[j+1]) ;
                swapped = true ;
            }
        }
        if (!swapped) break;
    } }
}

vector<int> genrateRandomArray(int size) {
    vector<int> arr(size) ;
    for( int i= 0; i<size; i++ ) {
        arr[i] = rand() % 10000 ;
    }
    return arr ;
}

int main()
{
    vector<int> arr = genrateRandomArray(50000);

    double start = omp_get_wtime() ;
    SequentialBubble(arr) ;
    double end = omp_get_wtime() ;
    cout << "\nSequential Bubble Sort : " << (end - start) << " sec" << endl ;

    start = omp_get_wtime() ;
    parallelBubble(arr) ;
    end = omp_get_wtime() ;
    cout << "\nParallel Bubble Sort : " << (end - start) << " sec" << endl ;

    return 0;
}