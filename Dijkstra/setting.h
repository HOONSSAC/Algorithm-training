// 공통적으로 사용되는 설정값들을 정의한 헤더 파일
#ifndef SETTING_H
#define SETTING_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <limits.h>

#define VERTEX_COUNT 10
#define EDGE_COUNT 11

// 간선 구조체 선언
typedef struct {
    int node[2];
    int distance;
} Edge;

#endif 