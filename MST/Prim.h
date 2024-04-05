#include "setting.h"

// 최소 가중치 간선을 찾는 함수
int minKey(int key[], int mstSet[], int n) {
    int min = INT_MAX, min_index = -1; // min_index를 -1로 초기화
    for (int v = 0; v < n; v++)
        if (mstSet[v] == 0 && key[v] < min)
            min = key[v], min_index = v;
    return min_index;
}

// 프림 알고리즘
void Prim(int n, int graph[n][n]) {
    int parent[n]; // 최소 스패닝 트리를 저장할 배열
    int key[n]; // 최소 가중치를 저장할 배열
    int mstSet[n]; // MST 집합에 포함된 노드를 표시하는 배열

    // 초기화
    for (int i = 0; i < n; i++)
        key[i] = INT_MAX, mstSet[i] = 0;

    key[0] = 0; // 첫 번째 정점을 시작점으로 선택
    parent[0] = -1; // 첫 번째 정점은 MST의 루트이므로 부모가 없음

    for (int count = 0; count < n - 1; count++) {
        int u = minKey(key, mstSet, n);
        mstSet[u] = 1;

        for (int v = 0; v < n; v++)
            if (graph[u][v] && mstSet[v] == 0 && graph[u][v] < key[v])
                parent[v] = u, key[v] = graph[u][v];
    }

    // 최소 스패닝 트리 출력
    printf("Edge \tWeight\n");
    for (int i = 1; i < n; i++)
        printf("%d - %d \t%d \n", parent[i], i, graph[i][parent[i]]);
}

void PrimMST(int n, int m){

    int graph[n][n]; // 인접 행렬 초기화

    memset(graph, 0, sizeof(graph)); // graph 배열을 0으로 초기화

    printf("Random Matrix Generation !!\n");

    for (int i = 0; i < m; i++) { // m개의 간선 생성을 위한 반복문
        int a, b, weight;
        do {
            a = rand() % n;
            b = rand() % n;
            weight = rand() % 20 + 1; // 가중치도 여기서 생성
        } while (a == b || graph[a][b]); // a와 b가 같지 않고, 해당 간선이 이미 존재하지 않을 때까지 반복
        
        // 새로운 간선을 배열에 추가
        graph[a][b] = weight;
        graph[b][a] = weight; // 무방향 그래프이므로 양쪽에 가중치 추가
        printf("%d. random edge : (%d,%d), weight: %d\n", i+1, a, b, weight);
    }

    // 인접 행렬 출력
    printf("\nGenerated Adjacency Matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%3d ", graph[i][j]); // 각 값 출력
        }
        printf("\n"); // 행이 끝나면 새로운 줄로
    }

    // 프림 알고리즘 실행
    printf("\nPrim's Algorithm: Minimum Spanning Tree\n");
    Prim(n, graph);
}
