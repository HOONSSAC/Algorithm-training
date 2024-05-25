#include <stdio.h>

#define MAX_ITEMS 4 // 물건의 개수
#define MAX_WEIGHT 10 // 가방의 최대 무게

// max 함수 정의
int max(int a, int b) {
    return (a > b) ? a : b; // a와 b 중 큰 값을 반환
}

// 0/1 Knapsack DP 함수 정의
int knapsack(int W, int wt[], int val[], int n, int chosenItems[]) {
    int i, w;
    // DP를 위한 테이블 초기화
    // K[i][w]는 i개의 물건을 넣었을 때 무게 w까지 담을 수 있는 최대 가치
    int K[MAX_ITEMS + 1][MAX_WEIGHT + 1];

    // 테이블을 bottom-up 방식으로 채움
    for (i = 0; i <= n; i++) {
        for (w = 0; w <= W; w++) {
            if (i == 0 || w == 0) // 물건이 없거나 가방의 무게가 0인 경우
                K[i][w] = 0; // 0으로 초기화
            else if (wt[i - 1] <= w) // 만약 물건을 넣을 수 있는 경우
                // 물건을 넣었을 때와 넣지 않았을 때 중 큰 값 선택
                K[i][w] = max(val[i - 1] + K[i - 1][w - wt[i - 1]], K[i - 1][w]);
            else // 물건을 넣을 수 없는 경우
                K[i][w] = K[i - 1][w]; // 이전 상태를 그대로 가져옴
        }
    }

    // 최대 가치를 만드는 물건 찾기
    int res = K[n][W];
    w = W; // 가방의 무게
    for (i = n; i > 0 && res > 0; i--) { // 물건의 개수만큼 반복
        if (res == K[i - 1][w]) // 이전 상태와 같은 경우
            continue; // 다음 물건으로 넘어감
        else {
            // 이 물건은 가방에 들어감
            chosenItems[i - 1] = 1; // 선택된 물건 표시
            res = res - val[i - 1]; // 가치 갱신
            w = w - wt[i - 1]; // 무게 갱신
        }
    }

    return K[n][W]; // 최대 가치 반환
}

int main() {
    int val[MAX_ITEMS] = {100000, 400000, 300000, 500000}; // 물건의 가치
    int wt[MAX_ITEMS] = {5, 4, 6, 3}; // 물건의 무게
    int W = MAX_WEIGHT; // 가방의 최대 무게
    int n = MAX_ITEMS; // 물건의 개수
    int chosenItems[MAX_ITEMS] = {0}; // 선택된 물건들

    printf("가방에 담을 수 있는 물건의 최대 가치는 %d원입니다.\n", knapsack(W, wt, val, n, chosenItems));
    printf("가방에 담은 물건: ");
    for (int i = 0; i < n; i++) {
        if (chosenItems[i]) {
            printf("물건%d ", i + 1); // 물건 번호 출력
        }
    }
    printf("\n");
    return 0;
}
