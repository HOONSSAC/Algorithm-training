#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ITEMS 1000 // 아이템의 개수
#define CAPACITY 20 // 한 개의 bin의 volume
#define TRIALS 100 // 시행 횟수

// 아이템을 랜덤하게 생성하는 함수
void generate_items(int *items, int size) {
    for (int i = 0; i < size; i++) {
        items[i] = rand() % 10 + 1;
    }
}

// First Fit 알고리즘
int first_fit(int *items, int size) {
    int *bins = (int *)malloc(size * sizeof(int)); // bin의 남은 공간을 저장할 배열
    int bin_count = 0; // bin의 개수

    for (int i = 0; i < size; i++) {
        int j;
        // 현재 아이템을 담을 수 있는 bin을 찾음
        for (j = 0; j < bin_count; j++) {
            // 담을 수 있으면 담고 반복문 종료
            if (bins[j] >= items[i]) {
                bins[j] -= items[i];
                break;
            }
        }
        // 담을 수 있는 bin이 없으면 새로운 bin을 추가
        if (j == bin_count) {
            bins[bin_count] = CAPACITY - items[i];
            bin_count++;
        }
    }
    free(bins); // 동적 메모리 해제
    return bin_count; // bin의 개수 반환
}

// Next Fit 알고리즘
int next_fit(int *items, int size) {
    int bin_count = 1; // bin의 개수
    int current_capacity = CAPACITY; // 현재 bin의 남은 공간

    for (int i = 0; i < size; i++) {
        // 현재 bin에 담을 수 있으면 담고, 아니면 새로운 bin을 추가
        if (current_capacity >= items[i]) {
            current_capacity -= items[i];
        } else {
            bin_count++;
            current_capacity = CAPACITY - items[i];
        }
    }
    return bin_count; // bin의 개수 반환
}

// Best Fit 알고리즘
int best_fit(int *items, int size) {
    int *bins = (int *)malloc(size * sizeof(int)); //  bin의 남은 공간을 저장할 배열
    int bin_count = 0; // bin의 개수

    for (int i = 0; i < size; i++) {
        int min_space = CAPACITY + 1; // 가장 작은 공간
        int best_bin = -1; // 가장 작은 공간을 가진 bin의 인덱스

        // 가장 작은 공간을 가진 bin을 찾음
        for (int j = 0; j < bin_count; j++) {
            if (bins[j] >= items[i] && bins[j] - items[i] < min_space) {
                min_space = bins[j] - items[i];
                best_bin = j;
            }
        }
        // 가장 작은 공간을 가진 bin에 담을 수 있으면 담고, 아니면 새로운 bin을 추가
        if (best_bin == -1) {
            bins[bin_count] = CAPACITY - items[i];
            bin_count++;
        } else {
            bins[best_bin] -= items[i];
        }
    }
    free(bins); // 동적 메모리 해제
    return bin_count; // bin의 개수 반환
}

// Worst Fit 알고리즘
int worst_fit(int *items, int size) {
    int *bins = (int *)malloc(size * sizeof(int)); // bin의 남은 공간을 저장할 배열
    int bin_count = 0; // bin의 개수

    for (int i = 0; i < size; i++) {
        int max_space = -1; // 가장 큰 공간
        int worst_bin = -1; // 가장 큰 공간을 가진 bin의 인덱스

        for (int j = 0; j < bin_count; j++) {
            // 가장 큰 공간을 가진 bin을 찾음
            if (bins[j] >= items[i] && bins[j] - items[i] > max_space) {
                max_space = bins[j] - items[i];
                worst_bin = j;
            }
        }
        // 가장 큰 공간을 가진 bin에 담을 수 있으면 담고, 아니면 새로운 bin을 추가
        if (worst_bin == -1) {
            bins[bin_count] = CAPACITY - items[i];
            bin_count++;
        } else {
            bins[worst_bin] -= items[i];
        }
    }
    free(bins); // 동적 메모리 해제
    return bin_count; // bin의 개수 반환
}

int main() {
    srand(time(NULL));

    int *items = (int *)malloc(ITEMS * sizeof(int)); // 아이템의 크기를 저장할 배열
    int total_first_fit = 0, total_next_fit = 0, total_best_fit = 0, total_worst_fit = 0;

    // TRIALS만큼 시행
    for (int i = 0; i < TRIALS; i++) {
        generate_items(items, ITEMS); // 아이템 생성

        total_first_fit += first_fit(items, ITEMS); // First Fit
        total_next_fit += next_fit(items, ITEMS); // Next Fit
        total_best_fit += best_fit(items, ITEMS); // Best Fit
        total_worst_fit += worst_fit(items, ITEMS); // Worst Fit
    }

    // 평균값 출력
    printf("First fit의 평균 bin 사용량: %.2f\n", (double)total_first_fit / TRIALS);
    printf("Next fit의 평균 bin 사용량: %.2f\n", (double)total_next_fit / TRIALS);
    printf("Best fit의 평균 bin 사용량: %.2f\n", (double)total_best_fit / TRIALS);
    printf("Worst fit의 평균 bin 사용량: %.2f\n", (double)total_worst_fit / TRIALS);

    free(items); // 동적 메모리 해제

    return 0;
}
