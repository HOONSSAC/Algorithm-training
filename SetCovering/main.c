#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#define U_SIZE 10 
#define F_SIZE 10

// 서브셋들
int subsets[F_SIZE][U_SIZE + 1] = {
    {1, 2, 3, 8, 0}, // S1
    {1, 2, 3, 4, 8, 0}, // S2
    {1, 2, 3, 4, 0}, // S3
    {2, 3, 4, 5, 7, 8, 0}, // S4
    {4, 5, 6, 7, 0}, // S5
    {5, 6, 7, 9, 10, 0}, // S6
    {4, 5, 6, 7, 0}, // S7
    {1, 2, 4, 8, 0}, // S8
    {6, 9, 0}, // S9
    {6, 10, 0} // S10
};

bool U[U_SIZE + 1]; // 유니버스 집합

// U를 초기화하는 함수
void init_U() {
  // U를 초기화
    for (int i = 1; i <= U_SIZE; i++) { 
        U[i] = true; 
    }
}

// U가 비었는지 확인하는 함수
bool is_U_empty() {
    for (int i = 1; i <= U_SIZE; i++) {
        if (U[i]) return false; 
    }
    return true;
}

// U에서 S를 제거하는 함수
void remove_from_U(int subset[]) {
    for (int i = 0; subset[i] != 0; i++) {
        U[subset[i]] = false;
    }
}

// U의 원소들을 가장 많이 포함하는 집합을 찾는 함수
int find_max_covering_subset() {
    int max_cover = 0; // 가장 많이 포함하는 원소의 개수
    int max_subset_index = -1; // 가장 많이 포함하는 집합의 인덱스

    for (int i = 0; i < F_SIZE; i++) {
        int cover = 0;

        // 집합의 원소들 중 U에 포함된 원소의 개수를 센다
        for (int j = 0; subsets[i][j] != 0; j++) {
            if (U[subsets[i][j]]) cover++;
        }

        // 가장 많이 포함하는 집합을 찾는다
        if (cover > max_cover) {
            max_cover = cover; // 가장 많이 포함하는 원소의 개수 갱신
            max_subset_index = i; // 가장 많이 포함하는 집합의 인덱스 갱신
        }
    }
    return max_subset_index; // 가장 많이 포함하는 집합의 인덱스 반환
}

// 주어진 subsets 배열을 출력하는 함수
void print_subsets() {
    printf("F = { S1, S2, S3, S4, S5, S6, S7, S8, S9, S10 }\n\n");
    for (int i = 0; i < F_SIZE; i++) {
        printf("S%d: { ", i+1);
        for (int j = 0; subsets[i][j] != 0; j++) {
            printf("%d ", subsets[i][j]);
        }
        printf("}\n");
    }
}


int main() {
    init_U(); // U 초기화
    
    int C[F_SIZE] = {0}; // 결과 집합 커버
    int c_size = 0; // 결과 집합 커버의 크기

    // 전체 집합 U 출력
    printf("전체 집합 U: { ");
    for (int i = 1; i <= U_SIZE; i++) {
        printf("%d ", i);
    }
    printf("}\n");

    // 주어진 subsets 출력
    print_subsets();
    printf("\n");

    while (!is_U_empty()) {
        int subset_index = find_max_covering_subset(); // U를 가장 많이 포함하는 집합 찾기
        if (subset_index == -1) break; // 더 이상 포함할 집합이 없는 경우
        
        remove_from_U(subsets[subset_index]); // U에서 선택된 집합 제거
        C[c_size++] = subset_index + 1; // 결과 집합 커버에 추가
    }
    
    printf("집합 커버 C: ");
    for (int i = 0; i < c_size; i++) {
        printf("S%d ", C[i]);
    }
    printf("\n");
    
    return 0;
}
