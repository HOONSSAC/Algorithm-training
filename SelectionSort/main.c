#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "selection.h"
#define MAX 100000

int main() {
    srand(time(NULL)); // 난수 생성기 초기화

    int arr1[12] = {6, 3, 11, 9, 12, 2, 8, 15, 18, 10, 7, 14}; // 임의의 배열
    int small_arr1 = 7; // arr1에서 n번째로 작은 값
    
    int arr2[MAX]; // 랜덤한 값 입력 받을 배열
    int small_arr2 = 30000; // arr2에서 n번째로 작은 값
    // arr2에 랜덤한 값 입력 받기
    for (int i = 0; i < MAX; i++) {
        arr2[i] = rand() % 200000 + 1;
    }

    int n = sizeof(arr1) / sizeof(arr1[0]); // pivot을 기준으로 배열을 나눌 때 사용할 배열의 크기
    printArr(arr1, n); // arr1 출력
    printf("arr1에서 %d번째로 작은 값: %d\n\n", small_arr1, Selection(arr1, 0, 11, small_arr1)); // arr1에서 n번째로 작은 값 출력

    clock_t start, end; // 시간 측정을 위한 변수 
    start = clock(); // 시간 측정 시작
    printf("arr2에서 %d번째로 작은 값: %d\n", small_arr2, Selection(arr2, 0, MAX - 1, small_arr2)); // arr2에서 n번째로 작은 값 출력
    end = clock(); // 시간 측정 종료
    printf("Time: %f\n", (double)(end - start) / CLOCKS_PER_SEC); // 시간 출력

    return 0;
}