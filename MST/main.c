#include <stdio.h>
#include <windows.h>
#include "Kruskal.h"
#include "Prim.h"

int main(void){
    srand(time(NULL));

    int n = VERTEX_COUNT; // 정점의 수
    int m = EDGE_COUNT; // 간선의 수

    LARGE_INTEGER frequency; // 초당 카운트
    LARGE_INTEGER start, end; // 시작 및 종료 값
    double elapsedTime; // 실행 시간

    // 초당 카운트 획득
    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&start);

    //KruskalMST(n, m);
    PrimMST(n, m);

    QueryPerformanceCounter(&end); // 종료 시간 획득
    // 실행 시간 계산
    elapsedTime = (double)(end.QuadPart - start.QuadPart) / frequency.QuadPart;
    // 실행 시간 출력
    printf("Execution time: %f seconds\n", elapsedTime);

    return 0;
}