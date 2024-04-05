#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// 간선 구조체 선언
typedef struct {
    int node[2];
    int distance;
} Edge;

// 부모 노드를 찾는 함수
int getParent(int parent[], int x){
    if(parent[x] == x)
        return x;
    return parent[x] = getParent(parent, parent[x]);
}

// 두 부모 노드를 합치는 함수
void unionParent(int parent[], int a, int b){
    a = getParent(parent, a);
    b = getParent(parent, b);
    if(a < b) parent[b] = a;
    else parent[a] = b;
}

// 같은 부모를 가지는지 확인
int findParent(int parent[], int a, int b){
    a = getParent(parent, a);
    b = getParent(parent, b);
    if(a == b)
        return 1;
    return 0;
}

// 간선 비교 함수
int compare(const void* a, const void* b){
    Edge* edgeA = (Edge*)a;
    Edge* edgeB = (Edge*)b;
    if(edgeA->distance > edgeB->distance) return 1;
    else if(edgeA->distance < edgeB->distance) return -1;
    else return 0;
}

int main(void){
    srand(time(NULL));

    int n = 10; // 정점의 수
    int m = 11; // 간선의 수
    Edge edges[m]; // 간선 정보를 저장할 배열

    int exists[11][11]; // 이미 존재하는 간선을 확인하기 위한 배열, 정점의 수 + 1로 크기 설정
    memset(exists, 0, sizeof(exists)); // exists 배열을 0으로 초기화

    printf("Random Matrix Generation !!\n");

    for(int i = 0; i < m; i++) { // m개의 간선 생성을 위한 반복문
        int a, b, weight;
        do {
            a = rand() % n + 1;
            b = rand() % n + 1;
            weight = rand() % 20 + 1; // 가중치도 여기서 생성
        } while (a == b || exists[a][b]); // a와 b가 같지 않고, 해당 간선이 이미 존재하지 않을 때까지 반복
        
        // 새로운 간선을 배열에 추가
        edges[i].node[0] = a;
        edges[i].node[1] = b;
        edges[i].distance = weight;

        exists[a][b] = exists[b][a] = 1; // 간선이 존재함을 표시
        printf("%d. random edge : (%d,%d), (%d,%d), weight: %d\n", i+1, a, b, b, a, weight);
    }

    // 간선의 비용을 기준으로 오름차순 정렬
    qsort(edges, m, sizeof(Edge), compare);

    int parent[n+1]; // 인덱스를 1부터 사용하기 위해 n+1 크기로 선언
    for(int i = 1; i <= n; i++){
        parent[i] = i;
    }

    int sum = 0;

    int adjacencyMatrix[n][n]; // 인접 행렬 초기화
    memset(adjacencyMatrix, 0, sizeof(adjacencyMatrix));

    for(int i = 0; i < m; i++){
        if(!findParent(parent, edges[i].node[0], edges[i].node[1])){
            sum += edges[i].distance;
            unionParent(parent, edges[i].node[0], edges[i].node[1]);
            // 인접 행렬에 간선의 가중치를 추가합니다. 양방향으로 표시
            adjacencyMatrix[edges[i].node[0] - 1][edges[i].node[1] - 1] = edges[i].distance;
            adjacencyMatrix[edges[i].node[1] - 1][edges[i].node[0] - 1] = edges[i].distance;
        }
    }

    printf("\nNumber of Vertices: %d\n", n);
    printf("Number of Edges: %d\n\n", m);

    printf("Adjacency Matrix of Direct Graph\n");
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            printf("%3d ", adjacencyMatrix[i][j]);
        }
        printf("\n");
    }

    return 0;
}

