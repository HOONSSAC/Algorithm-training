#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

// 최적의 행렬 곱셈 순서를 출력하는 함수
void printOptimalParens(int **s, int i, int j) {
    if (i == j) {
        printf("A%d", i);
    } else {
        printf("(");
        printOptimalParens(s, i, s[i][j]); // 왼쪽 행렬 출력
        printf(" x ");
        printOptimalParens(s, s[i][j] + 1, j); // 오른쪽 행렬 출력
        printf(")");
    }
}

// 행렬의 크기 배열 p를 사용하여 최소 곱셈 횟수를 계산하는 함수
void MatrixChainOrder(int p[], int n) {
    // 동적으로 2차원 배열 할당
    int **m = (int **)malloc(n * sizeof(int *));
    int **s = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        m[i] = (int *)malloc(n * sizeof(int));
        s[i] = (int *)malloc(n * sizeof(int));
    }

    int i, j, k, L, q;
    
    // 단일 행렬의 곱셈 횟수는 0이므로 대각선을 0으로 초기화
    for (i = 1; i < n; i++)
        m[i][i] = 0;
    
    // L은 행렬 사이의 거리
    // L = 2일 때부터 최소 곱셈 횟수 계산
    for (L = 2; L < n; L++) {
        // i는 행렬의 시작점, j는 행렬의 끝점
        for (i = 1; i < n - L + 1; i++) {
            j = i + L - 1;
            m[i][j] = INT_MAX; // 최소값을 찾기 위해 최대값으로 초기화
            for (k = i; k <= j - 1; k++) {
                q = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j]; // 곱셈 횟수 계산
                if (q < m[i][j]) { // 최소값인 경우
                    m[i][j] = q; // 최소값 저장
                    s[i][j] = k; // 최소값을 만드는 k 저장
                }
            }
        }
    }

    // 결과 출력
    printf("Chained Matrix Multiplication\n==================================\nM\t");
    for (i = 1; i < n; i++) {
        printf("%d\t", i);
    }
    printf("\n");
    for (i = 1; i < n; i++) {
        printf("%d\t", i);
        for (j = 1; j < n; j++) {
            if (j < i)
                printf("0\t");
            else
                printf("%d\t", m[i][j]);
        }
        printf("\n");
    }
    printf("\nFinal Solution : %d\n\n", m[1][n-1]);

    // 최적 순서 출력
    printf("Implicit Order for Matrix Multiplication : ");
    printOptimalParens(s, 1, n-1); // 최적의 행렬 곱셈 순서 출력
    printf("\n");

    // 동적으로 할당한 메모리 해제
    for (i = 0; i < n; i++) {
        free(m[i]);
        free(s[i]);
    }
    free(m);
    free(s);
}

int main() {
    // 행렬 입력
    // A1 : 10x20, A2 : 20x5, A3 : 5x15, A4 : 15x30
    int arr[] = {10, 20, 5, 15, 30};
    int size = sizeof(arr) / sizeof(arr[0]); // 행렬의 개수
    
    MatrixChainOrder(arr, size); // 최적의 행렬 곱셈 순서 출력
    
    return 0;
}
