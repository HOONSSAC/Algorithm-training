#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 배열 출력
void printArr(int arr[], int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

// 배열 내 두 원소의 위치를 바꾸는 함수
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// 피봇을 기준으로 배열을 두 부분으로 나누는 함수
int partition(int arr[], int left, int right) {
    int pivotindex = left + rand() % (right - left + 1); // 랜덤한 pivot 선택
    int pivot = arr[pivotindex];
    swap(&arr[pivotindex], &arr[left]); // pivot을 배열의 시작점으로 이동
    int i = left + 1;
    for(int j = left + 1; j <= right; j++) {
        if(arr[j] < pivot) {
            swap(&arr[j], &arr[i]);
            i++;
        }
    }
    swap(&arr[left], &arr[i - 1]); // pivot을 최종 위치로 이동
    return i - 1; // pivot의 최종 위치 반환
}

// 선택 알고리즘
int Selection(int arr[], int left, int right, int k) {
    if (left == right) {
        return arr[left]; // 배열에 원소가 하나만 있을 경우
    }
    int p = partition(arr, left, right); // 피봇을 기준으로 배열을 나눔
    int S = (p - 1) - left + 1; // 피봇의 위치를 기준으로 왼쪽 배열의 크기
    if (k <= S) {
        return Selection(arr, left, p - 1, k); // 왼쪽 배열에서 k번째로 작은 원소를 찾음
    }
    else if (k == S + 1) {
        return arr[p]; // 피봇이 k번째로 작은 원소인 경우
    }
    else {
        return Selection(arr, p + 1, right, k - S - 1); // 오른쪽 배열에서 k번째로 작은 원소를 찾음
    }
}