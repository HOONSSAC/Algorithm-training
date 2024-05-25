#include <stdio.h>

#define MAX_ITEMS 4
#define MAX_WEIGHT 10

// max 함수 정의
int max(int a, int b) {
    return (a > b) ? a : b;
}

// 0/1 Knapsack DP 함수 정의
int knapsack(int W, int wt[], int val[], int n, int chosenItems[]) {
    int i, w;
    // DP를 위한 테이블 초기화
    int K[MAX_ITEMS + 1][MAX_WEIGHT + 1];

    // 테이블을 bottom-up 방식으로 채움
    for (i = 0; i <= n; i++) {
        for (w = 0; w <= W; w++) {
            if (i == 0 || w == 0)
                K[i][w] = 0;
            else if (wt[i - 1] <= w)
                K[i][w] = max(val[i - 1] + K[i - 1][w - wt[i - 1]], K[i - 1][w]);
            else
                K[i][w] = K[i - 1][w];
        }
    }

    // 최대 가치를 만드는 물건 찾기
    int res = K[n][W];
    w = W;
    for (i = n; i > 0 && res > 0; i--) {
        if (res == K[i - 1][w])
            continue;
        else {
            // 이 물건은 가방에 들어감
            chosenItems[i - 1] = 1;
            res = res - val[i - 1];
            w = w - wt[i - 1];
        }
    }

    return K[n][W];
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
