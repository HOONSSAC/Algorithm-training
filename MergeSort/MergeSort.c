#include <stdio.h>
#include <time.h>
#include <string.h>
#define MAX 12 // 배열의 길이

// 배열을 순서대로 출력하는 함수
void printArr(int list[]) {
    for (int i = 0; i < MAX; i++) {
        printf("%d | ", list[i]);
    }
    printf("\n");
}

// 기존의 배열에 정렬된 배열을 덮어씌우는 함수
void inputArr(int list1[], int list2[], int start, int end) {
    int k = 0; // mergeSortArr의 시작 인덱스를 맞추기 위한 변수
    for (int i = start; i <= end; i++){
        list1[i] = list2[k++];
    }
}

// conquer 함수
void merge(int list[], int first, int mid, int last) {
    int mergeSortArr[1000]; // 정렬된 배열을 저장하는 변수
    int i = first; // 왼쪽 배열의 첫번째 인덱스
    int j = mid + 1; // 오른쪽 배열의 첫번째 인덱스
    int k = 0; // 정렬된 배열의 인덱스

    // 두 배열의 인덱스가 각각 마지막 인덱스가 될 때까지 반복한다.
    while (i <= mid && j <= last) {
        
        // 만약 왼쪽 요소가 오른쪽 요소보다 작다면
        if (list[i] <= list[j]) {
            // 새로운(정렬된) 배열에 현재의 왼쪽 요소를 저장한다.
            mergeSortArr[k] = list[i];
            i++; // 왼쪽 배열의 요소를 하나 저장했기 때문에 인덱스를 업데이트 해준다.
            k++; // 새로운(정렬된) 배열의 인덱스를 업데이트 해준다.
        }
        // 만약 왼쪽 요소보다 오른쪽 요소가 작다면
        else {
            // 새로운 배열에 현재의 오른쪽 요소를 저장한다.
            mergeSortArr[k] = list[j];
            j++; // 오른쪽 배열의 요소를 하나 저장했기 때문에 인덱스를 업데이트 해준다.
            k++; // 새로운 배열의 인덱스를 업데이트 해준다.
        }
    }

    // 왼쪽 배열의 요소가 남아있다면 순서대로 새로운 배열에 저장한다.
    while (i <= mid) {
        mergeSortArr[k++] = list[i++];
    }

    // 오른쪽 배열의 요소가 남아있다면 순서대로 새로운 배열에 저장한다.
    while (j <= last) {
        mergeSortArr[k++] = list[j++];
    }

    // 정렬된 mergeSortArr배열을 원래의 배열 list에 복사하는 함수를 호출한다.
    inputArr(list, mergeSortArr, first, last);
}

// divide 함수
// 배열과 배열의 첫번째 인덱스, 마지막 인덱스를 파라미터로 받는다.
void mergeSort(int list[], int first, int last) {
    
    // 첫번째 인덱스가 마지막 인덱스보다 작다면 재귀 함수를 실행한다.
    // 같거나 크면 재귀 함수를 호출하지 않는다.
    if (first < last) {
        // mid 에는 현재 배열의 중간지점 인덱스 값을 저장한다.
        int mid = (first + last) / 2;

        // 중간 인덱스를 기준으로 분할한 배열의 왼쪽을 가지고
        // 함수를 재귀 호출한다.
        // 최초 실행 시 배열의 첫번째 요소만 남을 때까지 분할한다.
        mergeSort(list, first, mid);

        // 중간 인덱스를 기준으로 분할한 배열의 오른쪽을 가지고
        // 함수를 재귀 호출한다.
        mergeSort(list, mid + 1, last);

        // 분할된 왼쪽 배열과 오른쪽 배열을 merge 함수를 통해 정렬시킨다.
        merge(list, first, mid, last);
    } else {
        // 재귀함수 조건에 만족하지 못한다면, 함수를 종료한다.
        return;
    }
}

int main(int args, char* argv[]) {
    
    // 배열 생성 및 정의
    int arr[] = {6, 3, 11, 9, 12, 2, 8, 15, 18, 10, 7, 14};
	
    // 기존 배열 출력
    printArr(arr);

    clock_t start, end; // 시간 측정을 위한 변수
    start = clock(); // 시간 측정 시작

    for(int i = 0; i < 10000000; i++) {
        int testArr[MAX]; // 정렬된 배열을 저장할 배열
        memcpy(testArr, arr, sizeof(arr)); // 원본 배열을 복사

        // mergeSort 함수 호출
        // 생성한 배열, 첫번째 인덱스와 마지막 인덱스를 파라미터로 보낸다.
        mergeSort(testArr, 0, MAX - 1);     

        memcpy(arr, testArr, sizeof(arr)); // 다시 원본 배열로 복사
    }

    end = clock(); // 시간 측정 종료

    // 정렬된 함수를 출력한다.
    printArr(arr);
    printf("Time: %f\n", (double)(end - start) / CLOCKS_PER_SEC); // 시간 출력

    return 0;
}
