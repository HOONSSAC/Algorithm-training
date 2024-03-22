#include <stdio.h>
#include "setting.h"

// 중앙값을 찾는 함수
int medianOfThree(int arr[], int left, int right) {
    int mid = left + (right - left) / 2;

    // 중앙값을 찾아서 가장 왼쪽, 중앙, 가장 오른쪽 요소를 정렬한다.
    // 가장 왼쪽 요소가 중앙값보다 크다면 두 요소를 바꾼다.
    if (arr[mid] < arr[left]) {
        SWAP(arr[left], arr[mid]);
    } // 가장 오른쪽 요소가 중앙값보다 작다면 두 요소를 바꾼다.
    if (arr[right] < arr[left]) {
        SWAP(arr[left], arr[right]);
    } // 중앙값이 가장 오른쪽 요소보다 작다면 두 요소를 바꾼다.
    if (arr[mid] < arr[right]) {
        SWAP(arr[mid], arr[right]);
    }

    // 중앙값을 가장 오른쪽 바로 앞에 위치하도록 한다.
    SWAP(arr[mid], arr[right - 1]);
    return right - 1; // 중앙값의 인덱스를 반환한다.
}


// 랜덤으로 pivot을 선택하는 함수
int PartitionMedian(int arr[], int left, int right) {
    
    int pivotIndex = medianOfThree(arr, left, right); // pivot의 위치를 저장한다.
    int pivot = arr[pivotIndex]; // pivot 값을 저장한다.

    SWAP(arr[pivotIndex], arr[left]); // pivot을 배열의 가장 왼쪽 요소와 바꾼다.

    int i = left; // 왼쪽부터 시작하는 인덱스

    // pivot을 기준으로 왼쪽에는 pivot보다 작은 요소들을, 오른쪽에는 pivot보다 큰 요소들을 정렬한다.
    for(int j = left + 1; j <= right; j++) {
        if(arr[j] < pivot) {
            i++;
            SWAP(arr[i], arr[j]);
        }
    }


    // pivot을 최종 위치로 이동시킨다.
    SWAP(arr[i], arr[left]);

    // pivot의 최종 위치를 반환한다.
    return i;
}

// QuickSort의 재귀함수이며, 배열과 시작점과 끝점을 인자로 받는다.
void QuickSortMedianPivot(int arr[], int left, int right) {

    int pivot; // pivot의 위치를 저장하는 변수

    // 시작점이 끝점보다 작으면 아직 정렬이 되지 않은 요소들이 남아있으므로 계속 반복하고
    // 요소가 하나 남아있으면 정렬이 완료된 것이므로 종료한다.
    if (left < right) {
        pivot = PartitionMedian(arr, left, right); // pivot의 위치를 저장한다.
        QuickSortMedianPivot(arr, left, pivot - 1); // pivot을 기준으로 왼쪽 배열을 정렬한다.
        QuickSortMedianPivot(arr, pivot + 1, right); // pivot을 기준으로 오른쪽 배열을 정렬한다.
    }

    // 요소가 하나 남았으면 더 이상 정렬할 필요가 없다.
    else {
        return;
    }
}