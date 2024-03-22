#include <stdio.h>
#include <time.h>
#include "setting.h"


// 랜덤으로 pivot을 선택하는 함수
int PartitionRandomPivot(int arr[], int left, int right) {
    
    srand(time(NULL)); // 랜덤으로 pivot을 선택하기 위해 seed값을 설정한다.

    int randNum = rand() % (right - left + 1) + left; // pivot을 랜덤으로 선택한다.

    // pivot을 배열의 가장 왼쪽 요소와 바꾼다. 
    SWAP(arr[randNum], arr[left]);

    int pivot = arr[left]; // pivot을 가장 왼쪽 요소로 설정한다.
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
void QuickSortRandomPivot(int arr[], int left, int right) {

    // 시작점이 끝점보다 작으면 아직 정렬이 되지 않은 요소들이 남아있으므로 계속 반복하고
    // 요소가 하나 남아있으면 정렬이 완료된 것이므로 종료한다.
    if (left < right) {
        int pivot = PartitionRandomPivot(arr, left, right); // pivot의 위치를 저장한다.
        QuickSortRandomPivot(arr, left, pivot - 1); // pivot을 기준으로 왼쪽 배열을 정렬한다.
        QuickSortRandomPivot(arr, pivot + 1, right); // pivot을 기준으로 오른쪽 배열을 정렬한다.
    }

    // 요소가 하나 남았으면 더 이상 정렬할 필요가 없다.
    else {
        return;
    }
}