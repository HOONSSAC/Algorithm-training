#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

#define VERTEX_COUNT 10
#define EDGE_COUNT 11

#define INF INT_MAX

// 최소 거리를 가진 정점을 찾는 함수
int getMinDistanceVertex(int distance[], bool visited[], int n) {
    int min = INF, minIndex = -1; // 최소 거리와 인덱스를 -1로 초기화
    for (int v = 0; v < n; v++) {
        // 방문하지 않은 정점 중 최소 거리를 가진 정점을 찾음
        if (!visited[v] && distance[v] <= min) {
            min = distance[v], minIndex = v; // 최소 거리와 인덱스 갱신
        }
    }
    return minIndex; // 최소 거리를 가진 정점의 인덱스 반환
}

// 최단 경로를 역추적하여 출력하는 함수
void printPath(int prev[], int j) {
    // 기저 사례 : j가 -1이면 경로의 시작점에 도달한 것임
    if (prev[j] == -1) return;

    printPath(prev, prev[j]); // 재귀적으로 이전 정점을 출력
    printf(" -> %d", j + 1); // 현재 정점 출력
}

void dijkstra(int **graph, int src, int n) {
    int distance[n]; // 최단 거리를 저장할 배열
    bool visited[n]; // 방문한 정점을 표시할 배열
    int prev[n]; // 각 정점의 이전 정점을 저장할 배열

    // 초기화
    for (int i = 0; i < n; i++) {
        distance[i] = INF;
        visited[i] = false;
        prev[i] = -1; // 이전 정점이 없음을 나타내기 위해 -1로 초기화
    }

    distance[src] = 0; // 시작 정점의 거리는 0

    for (int count = 0; count < n - 1; count++) {
        int u = getMinDistanceVertex(distance, visited, n);
        visited[u] = true;

        for (int v = 0; v < n; v++) {
            if (!visited[v] && graph[u][v] && distance[u] != INF && distance[u] + graph[u][v] < distance[v]) {
                distance[v] = distance[u] + graph[u][v];
                prev[v] = u; // v 정점에 도달하기 직전에 방문한 정점을 u로 설정
            }
        }
    }

    // 결과 출력
    printf("\nVertex\tDistance\tPath\n");
    for (int i = 0; i < n; i++) {
        printf("%d \t\t %d\t\t\t", i + 1, distance[i]);
        if (distance[i] == INF) {
            printf("No path\n");
        } else {
            printf("1"); // 시작 정점 출력
            printPath(prev, i); // 해당 정점까지의 최단 경로 출력
            printf("\n");
        }
    }
}

int main(void){
    srand(time(NULL));

    int n = VERTEX_COUNT; // 정점의 수
    int m = EDGE_COUNT; // 간선의 수

    // 동적 할당으로 인접 행렬 초기화
    int **adjacencyMatrix = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        adjacencyMatrix[i] = (int *)malloc(n * sizeof(int));
        memset(adjacencyMatrix[i], 0, n * sizeof(int));
    }

    // 무작위 간선 생성
    printf("Random Graph Generation !!\n");
    for(int i = 0; i < m; i++) {
        int a, b, weight;
        do {
            a = rand() % n;
            b = rand() % n;
            weight = rand() % 20 + 1;
        } while (a == b || adjacencyMatrix[a][b] != 0); // 중복 간선 방지
        
        adjacencyMatrix[a][b] = weight;
        adjacencyMatrix[b][a] = weight; // 무방향 그래프의 경우 양방향에 가중치 추가
        printf("%d. random edge : (%d,%d), weight: %d\n", i+1, a+1, b+1, weight);
    }

    dijkstra(adjacencyMatrix, 0, n); // 1번 정점에서 시작하여 모든 정점까지의 최단 경로 찾기

    // 동적 할당된 메모리 해제
    for (int i = 0; i < n; i++) {
        free(adjacencyMatrix[i]);
    }
    free(adjacencyMatrix);

    return 0;
}
