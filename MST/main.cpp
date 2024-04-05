#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// 부모 노드를 찾는 함수
int getParent(int parent[], int x){
    // 루트 노드가 아니라면, 루트 노드를 찾을 때까지 재귀 호출
	if(parent[x] == x)
        return x;
    return parent[x] = getParent(parent, parent[x]);
}

// 두 부모 노드를 합치는 함수
void unionParent(int parent[], int a, int b){
	a = getParent(parent, a); // a의 부모를 찾음
    b = getParent(parent, b); // b의 부모를 찾음
    
    // 더 작은 부모를 가지도록 설정
    if(a < b) parent[b] = a;
    else parent[a] = b;
}

// 같은 부모를 가지는지 확인
int findParent(int parent[], int a, int b){
	a = getParent(parent, a); // a의 부모를 찾음
    b = getParent(parent, b); // b의 부모를 찾음
    
    // 같은 부모를 가지면 1, 아니면 0
    if(a == b)
        return 1;
    return 0;
}

// 간선 클래스 선언
class Edge{
public:
	int node[2]; // 간선이 연결하는 두 정점
    int distance; // 간선의 길이
    Edge(int a, int b, int distance){
    	this->node[0] = a; // 첫번째 노드
        this->node[1] = b; // 두번째 노드
        this->distance = distance; // 간선의 가중치
    }
    bool operator < (Edge &edge){
        // 거리(비용)가 짧은 순서대로 정렬
    	return this->distance < edge.distance;
    }
};

int main(void){
	int n = 7; // 정점 7개
    int m = 11; // 간선 11개
    
    vector<Edge> v;
    v.push_back(Edge(1, 7, 12));
	v.push_back(Edge(1, 5, 17));
	v.push_back(Edge(1, 4, 28));
	v.push_back(Edge(1, 2, 67));
	v.push_back(Edge(2, 4, 24));
	v.push_back(Edge(2, 5, 62));
	v.push_back(Edge(3, 5, 20));
	v.push_back(Edge(3, 6, 37));
	v.push_back(Edge(4, 7, 13));
	v.push_back(Edge(5, 6, 45));
	v.push_back(Edge(5, 7, 73));
    
    // 간선의 비용을 기준으로 오름차순 정렬
    sort(v.begin(), v.end());
    
    // 각 정점이 포함된 그래프가 어디인지 저장 => 어느 부모에 속했는지 
    int parent[n];
    for(int i = 0; i < n; i++){
    	// 일단 자기자신이 부모가 되도록 설정
    	parent[i] = i;
    }
    
    int sum = 0; // 간선의 길이 합
    for(int i = 0; i < v.size(); i++){
    	// 사이클이 발생하지 않는 경우에만 그래프에 포함
        if(!findParent(parent, v[i].node[0] - 1, v[i].node[1] - 1)){
        	// v[i].node[0] - 1 : 간선에서의 첫번째 노드
        	// v[i].node[1] - 1 : 간선에서의 두번째 노드
        	sum += v[i].distance;
            unionParent(parent, v[i].node[0] - 1, v[i].node[1] - 1);
        }
    }
    
    printf("%d\n", sum);
    
    return 0;
}