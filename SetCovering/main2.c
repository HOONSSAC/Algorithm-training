#include <stdio.h>

int main() {
	int U[] = { 1,2,3,4,5,6,7,8,9,10 }; // 원소
	int S[100][100] = { {1,2,3,8}, {1,2,3,4,8}, {1,2,3,4}, {2,3,4,5,7,8}, {4,5,6,7}, {5,6,7,9,10},
		{4,5,6,7}, {1,2,4,8}, {6,9}, {6,10} }; // 집합
	
	int s_each_count[] = { 4,5,4,6,4,5,4,4,2,2 }; // 각 집합마다 원소의 개수
	int chk_s[10] = {0,}; // 집합의 사용여부
	int chk_u[10] = {0,}; // 현재 원소가 얼마나 남았는지 현황
	
	int remove_count; // 제거한 횟수
	int u_count = 10; // 원소의 개수
	int max_index = 0; // 가장 u원소를 많이 지우는 집합의 위치
	int max_count = 0; // 집합 중 가장 제거한 횟수
	int s_size;
	int max_size = 0; // 가장 제거한 횟수가 많은 집합의 원소의 개수

	printf("결과\n\n");
	while (u_count != 0) {
		max_count = 0; 
		max_size = 0;
		max_index = 0;

		for (int i = 0; i < 10; i++) {
			s_size = s_each_count[i]; // 한 집합의 원소 개수
			remove_count = 0;

			if (chk_s[i] == 0) { // 집합이 쓰였는지 확인

				for (int j = 0; j < s_size; j++) {
					if (chk_u[S[i][j] - 1] == 0) {
						remove_count++;
					}
				}

				if (max_count < remove_count) {
					max_count = remove_count;
					max_size = s_size;
					max_index = i;
				} // 현재 집합에서 제거한 개수가 max_count 보다 더 큰 경우 그 집합 정보(제거 횟수, 그 집합의 크기, 그 집합의 위치)를 저장.
			}
		}

		u_count -= max_count; // 전체 원소의 개수 - 가장 큰 제거횟수를 가진 경우 
		chk_s[max_index] = 1; // 그 집합을 사용한 여부를 체크한다.
		printf("S%d ", max_index + 1); // 그 집합을 표시해주고
		for (int j = 0; j < max_size; j++) {
			chk_u[S[max_index][j] - 1] = 1;
		} // 집합에 해당하는 원소를 전체 원소에서 빼준다.
	}

	printf("\n");
	return 0;
}