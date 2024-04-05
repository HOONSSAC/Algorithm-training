#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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
    return edgeA->distance - edgeB->distance;
}

int main(void){
    srand(time(NULL)); // 난수 생성 시드 초기화

    int n = 10; // 정점 10개
    int m = 11; // 간선 11개

    Edge* edges = (Edge*)malloc(sizeof(Edge) * m); // 간선 배열 동적 할당

    // 랜덤 간선과 가중치 생성
    for(int i = 0; i < m; i++){
        int a = rand() % n + 1; // 1부터 n까지의 랜덤 정점
        int b = rand() % n + 1; // 1부터 n까지의 랜덤 정점
        int distance = rand() % 20 + 1; // 1부터 20까지의 랜덤 가중치
        edges[i].node[0] = a;
        edges[i].node[1] = b;
        edges[i].distance = distance;
    }

    // 간선의 비용을 기준으로 오름차순 정렬
    qsort(edges, m, sizeof(Edge), compare);

    int parent[n];
    for(int i = 0; i < n; i++){
        parent[i] = i;
    }

    int sum = 0;

    for(int i = 0; i < m; i++){
        if(!findParent(parent, edges[i].node[0] - 1, edges[i].node[1] - 1)){
            sum += edges[i].distance;
            unionParent(parent, edges[i].node[0] - 1, edges[i].node[1] - 1);
        }
    }

    printf("%d\n", sum);
    
    free(edges); // 동적 할당된 메모리 해제

    return 0;
}
