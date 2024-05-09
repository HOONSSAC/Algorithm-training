#include <stdio.h>
#include <limits.h>
#include <windows.h>

#define INF INT_MAX // 무한대 값으로 INT_MAX 사용
#define N 10 // 정점의 개수

void printMatrix(int matrix[N][N]); // 행렬 출력 함수
void floyd(int graph[N][N]); // 플로이드-워셜 알고리즘 함수
void dijkstra(int graph[N][N], int start); // 다익스트라 알고리즘 함수

int main() {
    int graph[N][N] = {
        {0, 15, 12, INF, INF, INF, INF, INF, INF, INF},
        {15, 0, INF, INF, INF, 21, INF, 7, INF, INF},
        {12, INF, 0, 4, 10, INF, INF, INF, INF, INF},
        {INF, INF, 4, 0, 3, INF, 13, INF, INF, INF},
        {INF, INF, 10, 3, 0, INF, INF, 10, INF, INF},
        {INF, 21, INF, INF, INF, 0, INF, INF, 25, INF},
        {INF, INF, INF, 13, INF, INF, 0, INF, INF, 15},
        {INF, 7, INF, INF, 10, INF, INF, 0, 19, 9},
        {INF, INF, INF, INF, INF, 25, INF, 19, 0, 5},
        {INF, INF, INF, INF, INF, INF, 15, 9, 5, 0}
    };

    // 시간 측정을 위한 변수
    LARGE_INTEGER frequency;
    LARGE_INTEGER start, end;
    double interval; // 시간 측정 결과

    QueryPerformanceFrequency(&frequency); // CPU 주파수 측정
    QueryPerformanceCounter(&start); // 시간 측정 시작

    floyd(graph); // 플로이드-워셜 알고리즘 실행

    QueryPerformanceCounter(&end); // 시간 측정 종료
    interval = (double) (end.QuadPart - start.QuadPart) / frequency.QuadPart; // 시간 측정 결과 계산
    printf("Time taken by Floyd's algorithm: %f\n", interval); // 시간 측정 결과 출력

    // 다익스트라 알고리즘 실행
    for (int i = 0; i < N; i++) {
        QueryPerformanceCounter(&start); // 시간 측정 시작
        dijkstra(graph, i); // 다익스트라 알고리즘 실행
        QueryPerformanceCounter(&end); // 시간 측정 종료
        interval = (double) (end.QuadPart - start.QuadPart) / frequency.QuadPart; // 시간 측정 결과 계산
        printf("Time taken by Dijkstra's algorithm with start point %d: %f\n", i+1, interval); // 시간 측정 결과 출력
    }

    return 0;
}

// 행렬 출력 함수
void printMatrix(int matrix[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (matrix[i][j] == INF)
                printf("%4s", "INF");
            else
                printf("%4d", matrix[i][j]);
        }
        printf("\n");
    }
}

// 플로이드-워셜 알고리즘 함수
void floyd(int graph[N][N]) {
    int dist[N][N], i, j, k; // 최단 경로를 저장할 2차원 배열 dist

    // dist 배열 초기화
    for (i = 0; i < N; i++)
        for (j = 0; j < N; j++)
            dist[i][j] = graph[i][j];

    // 플로이드-워셜 알고리즘
    for (k = 0; k < N; k++) {
        for (i = 0; i < N; i++) {
            for (j = 0; j < N; j++) {
                // i에서 j로 가는 경로보다 i에서 k를 거쳐 j로 가는 경로가 더 짧을 경우
                if (dist[i][k] != INF && dist[k][j] != INF && dist[i][k] + dist[k][j] < dist[i][j])
                    dist[i][j] = dist[i][k] + dist[k][j]; // 더 작은 값으로 갱신
            }
        }
    }

    printMatrix(dist); // 최단 경로 출력
}

// 다익스트라 알고리즘 함수
void dijkstra(int graph[N][N], int start) {
    int dist[N]; // 최단 거리를 저장할 배열
    int visited[N] = {0}; // 방문한 정점을 표시할 배열

    // dist 배열 초기화
    for (int i = 0; i < N; i++)
        dist[i] = INF;

    dist[start] = 0; // 시작 정점의 최단 거리는 0

    for (int count = 0; count < N-1; count++) {
        int min = INF, min_index; // 최단 거리와 그 정점을 저장할 변수

        // 방문하지 않은 정점 중 최단 거리를 가진 정점을 찾음
        for (int v = 0; v < N; v++)
            if (visited[v] == 0 && dist[v] <= min)
                min = dist[v], min_index = v; // 최단 거리와 그 정점을 저장

        visited[min_index] = 1; // 최단 거리를 가진 정점을 방문 표시

        // 최단 거리를 가진 정점을 경유지로 하여 나머지 정점들의 최단 거리를 계산
        for (int v = 0; v < N; v++)
          if (!visited[v] && graph[min_index][v] && dist[min_index] != INF &&
            dist[min_index] + graph[min_index][v] < dist[v] && dist[min_index] + graph[min_index][v] > 0) // 오버플로우 방지 조건 추가
              dist[v] = dist[min_index] + graph[min_index][v]; // 더 작은 값으로 갱신
    }

    // 최단 거리 출력
    for (int i = 0; i < N; i++)
        printf("%d ", dist[i]);
    printf("\n");
}