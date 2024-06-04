#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_VERTICES 20
#define MIN_VERTICES 10
#define MAX_EDGES 30
#define MIN_EDGES 20

// Edge를 나타내는 구조체
typedef struct {
    int u, v; // 간선의 양 끝점
} Edge;

// Graph를 나타내는 구조체
typedef struct {
    int vertex_count; // 정점의 개수
    int edge_count; // 간선의 개수
    Edge edges[MAX_EDGES]; // 간선들
} Graph;

// 랜덤한 그래프를 생성하는 함수
Graph generate_graph() {
    Graph g;
    srand(time(NULL));

    // 정점의 개수와 간선의 개수를 랜덤하게 설정
    g.vertex_count = MIN_VERTICES + rand() % (MAX_VERTICES - MIN_VERTICES + 1);
    g.edge_count = MIN_EDGES + rand() % (MAX_EDGES - MIN_EDGES + 1);

    // 간선들을 랜덤하게 설정
    for (int i = 0; i < g.edge_count; i++) {
        g.edges[i].u = rand() % g.vertex_count;
        g.edges[i].v = rand() % g.vertex_count;
        
        // 루프 간선을 방지
        while (g.edges[i].u == g.edges[i].v) {
            g.edges[i].v = rand() % g.vertex_count; // 끝점을 다시 설정
        }
    }

    return g; // 생성된 그래프 반환
}

// 그래프를 출력하는 함수
void print_graph(Graph g) {
    printf("Graph with %d vertices and %d edges:\n", g.vertex_count, g.edge_count);
    for (int i = 0; i < g.edge_count; i++) {
        printf("(%d, %d)\n", g.edges[i].u, g.edges[i].v);
    }
    printf("\n");
}

// 가장 많은 edge를 가진 vertex를 우선 선택하는 방식
int* vertex_cover_greedy(Graph g) {
    int* cover = (int*)malloc(g.vertex_count * sizeof(int)); // vertex cover를 저장할 배열
    int cover_size = 0; // vertex cover의 크기
    int* degree = (int*)calloc(g.vertex_count, sizeof(int)); // 각 정점의 차수를 저장할 배열
    int* covered = (int*)calloc(g.edge_count, sizeof(int)); // 각 간선이 cover되었는지 여부를 저장할 배열

    // 각 정점의 차수 계산
    for (int i = 0; i < g.edge_count; i++) {
        degree[g.edges[i].u]++; // u의 차수 증가
        degree[g.edges[i].v]++; // v의 차수 증가
    }

    // 가장 많은 edge를 가진 vertex를 선택하고, 그 vertex와 연결된 edge들을 cover
    while (1) {
        int max_degree = -1; // 가장 큰 차수
        int max_vertex = -1; // 가장 많은 edge를 가진 vertex 

        // 가장 많은 edge를 가진 vertex 찾기
        for (int i = 0; i < g.vertex_count; i++) {
            // 차수가 가장 큰 vertex 선택
            if (degree[i] > max_degree) {
                max_degree = degree[i];
                max_vertex = i;
            }
        }

        if (max_degree == 0) break; // 모든 edge가 cover된 경우 종료

        cover[cover_size++] = max_vertex; // vertex cover에 추가
        degree[max_vertex] = 0; // 차수 0으로 설정

        // vertex와 연결된 edge들을 cover
        for (int i = 0; i < g.edge_count; i++) {
            // vertex와 연결된 edge들을 cover
            if (!covered[i] && (g.edges[i].u == max_vertex || g.edges[i].v == max_vertex)) {
                covered[i] = 1; // cover되었음을 표시
                degree[g.edges[i].u]--; // u의 차수 감소
                degree[g.edges[i].v]--; // v의 차수 감소
            }
        }
    }

    // 동적할당된 메모리 해제
    free(degree);
    free(covered);

    // vertex cover의 크기에 맞게 메모리 재할당
    cover = (int*)realloc(cover, cover_size * sizeof(int));
    return cover; // vertex cover 반환
}

// Maximal matching을 사용하는 방식
int* vertex_cover_matching(Graph g, int* cover_size) {
    int* cover = (int*)malloc(g.vertex_count * sizeof(int)); // vertex cover를 저장할 배열
    int* matched = (int*)calloc(g.vertex_count, sizeof(int)); // 각 정점이 matching되었는지 여부를 저장할 배열
    int* covered = (int*)calloc(g.edge_count, sizeof(int)); // 각 간선이 cover되었는지 여부를 저장할 배열
    *cover_size = 0; // vertex cover의 크기

    // 각 정점이 matching되었는지 여부를 저장할 배열
    for (int i = 0; i < g.edge_count; i++) {
        // 각 정점이 matching되었는지 여부를 저장
        if (!covered[i] && !matched[g.edges[i].u] && !matched[g.edges[i].v]) {
            matched[g.edges[i].u] = 1; // u가 matching됨
            matched[g.edges[i].v] = 1; // v가 matching됨
            covered[i] = 1; // 간선이 cover됨
            cover[(*cover_size)++] = g.edges[i].u; // vertex cover에 추가
            cover[(*cover_size)++] = g.edges[i].v;
        }
    }

    // 동적할당된 메모리 해제
    free(matched);
    free(covered);

    // vertex cover의 크기에 맞게 메모리 재할당
    cover = (int*)realloc(cover, (*cover_size) * sizeof(int));
    return cover; // vertex cover 반환
}

// vertex cover를 출력하는 함수
void print_cover(int* cover, int cover_size) {
    printf("Vertex cover의 크기 : %d, Vertex cover : ", cover_size);
    for (int i = 0; i < cover_size; i++) {
        printf("%d ", cover[i]);
    }
    printf("\n");
}

int main() {
    Graph g = generate_graph(); // 랜덤한 그래프 생성
    print_graph(g); // 생성된 그래프 출력
    printf("================================================================\n");

    // Greedy 방식으로 vertex cover 계산
    int* cover_greedy = vertex_cover_greedy(g);
    int cover_size_greedy = 0; // Greedy 방식으로 계산된 vertex cover의 크기
    while (cover_greedy[cover_size_greedy] != '\0') cover_size_greedy++;
    printf("\n가장 많은 edge를 가지는 vertex를 우선 선택하는 방식\n");
    print_cover(cover_greedy, cover_size_greedy); // Greedy 방식으로 계산된 vertex cover 출력
    free(cover_greedy); // 동적할당된 메모리 해제

    // Maximal matching 방식으로 vertex cover 계산
    int cover_size_matching; // Maximal matching 방식으로 계산된 vertex cover의 크기
    int* cover_matching = vertex_cover_matching(g, &cover_size_matching); // Maximal matching 방식으로 vertex cover 계산
    printf("\nMaximal matching 방식\n");
    print_cover(cover_matching, cover_size_matching); // Maximal matching 방식으로 계산된 vertex cover 출력
    free(cover_matching); // 동적할당된 메모리 해제

    return 0;
}
