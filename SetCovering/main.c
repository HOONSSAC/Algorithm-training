#include <stdio.h>
#include <stdbool.h>

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
    int max_cover = 0;
    int max_subset_index = -1;
    for (int i = 0; i < F_SIZE; i++) {
        int cover = 0;
        for (int j = 0; subsets[i][j] != 0; j++) {
            if (U[subsets[i][j]]) cover++;
        }
        if (cover > max_cover) {
            max_cover = cover;
            max_subset_index = i;
        }
    }
    return max_subset_index;
}

int main() {
    init_U();
    
    int C[F_SIZE] = {0}; // 결과 집합 커버
    int c_size = 0; // 결과 집합 커버의 크기
    
    while (!is_U_empty()) {
        int subset_index = find_max_covering_subset();
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
