#include <bits/stdc++.h>
#include <omp.h>
using namespace std;

void merge( vector<int> &arr, int left, int mid, int right ) {

    int n1 = mid - left + 1 ;
    int n2 = right - mid ;
    vector<int> L(n1), R(n2) ;

    for( int i=0; i<n1; i++ ) {
        L[i] = arr[ left + i ] ;
    }

    for( int i=0; i<n2; i++ ) {
        R[i] = arr[ mid + i + 1] ;
    }

    int i=0, j=0, k=left ;

    while ( i<n1 && j<n2)
    {
        if ( L[i] <= R[j] ) {
            arr[k] = L[i] ;
            i++ ;
        }
        else {
            arr[k] = R[j] ;
            j++ ;
        }
        k++ ;
    }
    
    while( i < n1 ) {
        arr[k] = L[i] ;
        i++ ;
        k++ ;
    }

    while( j < n2 ) {
        arr[k] = R[j] ;
        j++ ;
        k++ ;
    }
}

void SequentialMergeSort(vector<int> &arr, int left, int right) {
    if( left < right ) {
        int mid = left + (right-left) / 2 ;
        SequentialMergeSort(arr, left, mid ) ;
        SequentialMergeSort(arr, mid+1, right ) ;
        merge(arr, left, mid, right) ;
    }
}

void parallelMergeSort(vector<int> &arr, int left, int right) {
    if( left < right ) {
        int mid = left + (right-left) / 2 ;
        #pragma omp parallel sections num_threads(2)
        {
            #pragma omp section 
            {
                SequentialMergeSort(arr, left, mid ) ;
            }
            #pragma omp section 
            {
                SequentialMergeSort(arr, mid+1, right ) ;
            }
            merge(arr, left, mid, right) ;
        }
    }
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
    vector<int> arr = genrateRandomArray(50000); ;
    vector<int> copyVector = arr ;
    
    double start = omp_get_wtime() ;
    SequentialMergeSort(arr, 0, arr.size() - 1) ;
    double end = omp_get_wtime() ;
    cout << "\nSequential MergeSort : " << (end - start) << " sec" << endl ;    

    start = omp_get_wtime() ;
    parallelMergeSort(arr, 0, arr.size() - 1) ;
    end = omp_get_wtime() ;
    cout << "\nParallel MergeSort : " << (end - start) << " sec" << endl ;

    return 0;
}