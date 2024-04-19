#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define FILE_PATH "sample.txt" // 원본 데이터 파일 경로
#define ENCODED_FILE_PATH "sample.enc" // 인코딩된 파일 경로
#define ALPHABET_SIZE 26 // 알파벳 개수
#define MAX_TREE_HT 100 // 트리의 최대 높이

// 허프만 트리 노드 구조체
struct MinHeapNode {
    char item; // 문자
    unsigned freq; // 빈도수
    struct MinHeapNode *left, *right; // 왼쪽, 오른쪽 자식 노드
};

// 허프만 트리 구조체
struct MinHeap {
    unsigned size; // 크기
    unsigned capacity; // 용량
    struct MinHeapNode** array; // 노드 배열
};

// 새로운 노드 생성
struct MinHeapNode* newNode(char item, unsigned freq) { 
  // 노드 구조체 동적 할당
  struct MinHeapNode* temp = (struct MinHeapNode*)malloc(sizeof(struct MinHeapNode));
  temp->item = item; // 문자 설정
  temp->freq = freq; // 빈도수 설정
  temp->left = temp->right = NULL; // 자식 노드 초기화
  return temp; // 노드 반환
}

// 새로운 허프만 트리 생성
struct MinHeap* createMinHeap(unsigned capacity) {
  // 허프만 트리 구조체 동적 할당
  struct MinHeap* minHeap = (struct MinHeap*)malloc(sizeof(struct MinHeap));
  minHeap->size = 0; // 크기 초기화
  minHeap->capacity = capacity; // 용량 설정
  // 노드 배열 동적 할당
  minHeap->array = (struct MinHeapNode**)malloc(minHeap->capacity * sizeof(struct MinHeapNode*));
  return minHeap; // 허프만 트리 반환
}

// 노드 교환
void swapMinHeapNode(struct MinHeapNode** a, struct MinHeapNode** b) {
  struct MinHeapNode* t = *a; // 임시 노드
  // 노드 교환
  *a = *b;
  *b = t;
}

// 최소 힙 구조 유지
void minHeapify(struct MinHeap* minHeap, int idx) {
  int smallest = idx; // 최소값 인덱스
  int left = 2 * idx + 1; // 왼쪽 자식 인덱스
  int right = 2 * idx + 2; // 오른쪽 자식 인덱스

  // 왼쪽 자식이 루트보다 작은 경우
  if (left < minHeap->size && minHeap->array[left]->freq < minHeap->array[smallest]->freq)
    smallest = left; // 최소값 인덱스 변경
  // 오른쪽 자식이 루트보다 작은 경우
  if (right < minHeap->size && minHeap->array[right]->freq < minHeap->array[smallest]->freq)
    smallest = right; // 최소값 인덱스 변경
  // 최소값 인덱스가 변경된 경우
  if (smallest != idx) {
    // 노드 교환
    swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);
    minHeapify(minHeap, smallest); // 재귀 호출
  }
}

// 최소값 추출
struct MinHeapNode* extractMin(struct MinHeap* minHeap) {
  struct MinHeapNode* temp = minHeap->array[0]; // 루트 노드 추출
  minHeap->array[0] = minHeap->array[minHeap->size - 1]; // 마지막 노드를 루트로 이동 
  --minHeap->size; // 크기 감소
  minHeapify(minHeap, 0); // 최소 힙 구조 유지
  return temp; // 추출한 노드 반환
}

// 노드 삽입
void insertMinHeap(struct MinHeap* minHeap, struct MinHeapNode* minHeapNode) {
  ++minHeap->size; // 크기 증가
  int i = minHeap->size - 1; // 마지막 인덱스

  // 부모 노드가 존재하고 새로운 노드의 빈도수가 부모 노드의 빈도수보다 작은 경우
  while (i && minHeapNode->freq < minHeap->array[(i - 1) / 2]->freq) {
    minHeap->array[i] = minHeap->array[(i - 1) / 2]; // 부모 노드를 자식 노드로 이동
    i = (i - 1) / 2; // 부모 노드 인덱스로 이동
  }
  minHeap->array[i] = minHeapNode; // 새로운 노드 삽입
}

// 최소 힙 구조 생성
void buildMinHeap(struct MinHeap* minHeap) {
  int n = minHeap->size - 1; // 마지막 인덱스
  // 마지막 노드의 부모 노드부터 루트 노드까지 최소 힙 구조 유지
  for (int i = (n - 1) / 2; i >= 0; --i)
    minHeapify(minHeap, i);
}

// 리프 노드인지 확인
int isLeaf(struct MinHeapNode* root) {
  // 왼쪽, 오른쪽 자식 노드가 없는 경우 리프 노드
  return !(root->left) && !(root->right);
}

// 허프만 트리 생성 및 초기화
struct MinHeap* createAndBuildMinHeap(char data[], int freq[], int size) {
  struct MinHeap* minHeap = createMinHeap(size); // 허프만 트리 생성
  for (int i = 0; i < size; ++i)
    minHeap->array[i] = newNode(data[i], freq[i]); // 노드 생성
  minHeap->size = size; // 크기 설정
  buildMinHeap(minHeap); // 허프만 트리 초기화
  return minHeap; // 허프만 트리 반환
}

// 허프만 트리 생성
struct MinHeapNode* buildHuffmanTree(char data[], int freq[], int size) {
  struct MinHeapNode *left, *right, *top; // 왼쪽, 오른쪽 자식 노드, 부모 노드
  
  // 허프만 트리 생성 및 초기화
  struct MinHeap* minHeap = createAndBuildMinHeap(data, freq, size);

  // 트리 노드가 1개가 될 때까지 반복
  while (minHeap->size != 1) {
    // 가장 작은 두 노드 추출
    left = extractMin(minHeap);
    right = extractMin(minHeap); 

    // 새로운 노드 생성
    top = newNode('$', left->freq + right->freq);
    top->left = left; // 왼쪽 자식 노드 설정
    top->right = right; // 오른쪽 자식 노드 설정
    insertMinHeap(minHeap, top); // 새로운 노드 삽입
  }
  
  // 허프만 트리의 루트 노드 반환
  return extractMin(minHeap);
}

// 허프만 코드를 계산하고 저장하는 함수
void printCodes(struct MinHeapNode* root, int arr[], int top, char codes[ALPHABET_SIZE][MAX_TREE_HT]) {
  // 왼쪽 자식 노드가 있는 경우
  if (root->left) {
    arr[top] = 0;
    // 왼쪽 자식 노드로 이동 후 재귀 호출
    printCodes(root->left, arr, top + 1, codes);
  }

  // 오른쪽 자식 노드가 있는 경우
  if (root->right) {
    arr[top] = 1;
    // 오른쪽 자식 노드로 이동 후 재귀 호출
    printCodes(root->right, arr, top + 1, codes);
  }

  // 리프 노드인 경우
  if (isLeaf(root)) {
    printf("%c: ", root->item);
    char tempCode[MAX_TREE_HT]; // 임시 코드 배열

    for (int i = 0; i < top; ++i) {
      printf("%d", arr[i]);
      tempCode[i] = arr[i] + '0'; // 숫자를 문자로 변환하여 저장
    }
  
    tempCode[top] = '\0'; // 문자열 종료
    strcpy(codes[root->item - 'a'], tempCode); // 코드 배열에 복사
    printf("\n");
  }
}

// 허프만 코드를 계산하고 저장하는 함수
void HuffmanCodes(char data[], int freq[], int size, char codes[ALPHABET_SIZE][MAX_TREE_HT]) {
  // 허프만 트리 생성
  struct MinHeapNode* root = buildHuffmanTree(data, freq, size);
  int arr[MAX_TREE_HT], top = 0;
  printCodes(root, arr, top, codes); // 허프만 코드를 계산하고 저장합니다.
}

// 파일을 인코딩하여 저장하는 함수
void encodeFile(char codes[ALPHABET_SIZE][MAX_TREE_HT]) {
  FILE* file = fopen(FILE_PATH, "r"); // 원본 데이터 파일
  FILE* encodedFile = fopen(ENCODED_FILE_PATH, "w"); // 인코딩된 파일
  if (file == NULL || encodedFile == NULL) {
    printf("파일을 열 수 없습니다.\n");
    return;
  }

  char ch;
  // 파일에서 문자를 읽어 허프만 코드로 변환하여 파일에 씁니다.
  while ((ch = fgetc(file)) != EOF) {
    if (isalpha(ch)) {
      ch = tolower(ch); // 대문자일 경우 소문자로 변환
      fputs(codes[ch - 'a'], encodedFile); // 해당 문자의 허프만 코드를 파일에 씁니다.
    }
  }

  fclose(file);
  fclose(encodedFile);
}

// 파일을 디코딩하여 저장하는 함수
void decodeFile(struct MinHeapNode* root, const char* encodedFilePath, const char* decodedFilePath) {
  FILE* encodedFile = fopen(encodedFilePath, "r"); // 인코딩된 파일
  FILE* decodedFile = fopen(decodedFilePath, "w"); // 디코딩된 파일
  if (encodedFile == NULL || decodedFile == NULL) {
    printf("파일을 열 수 없습니다.\n");
    return;
  }

  // 루트 노드를 현재 노드로 설정
  struct MinHeapNode* currentNode = root;
  char ch;

  // 인코딩된 파일에서 문자를 읽어 디코딩하여 파일에 씁니다.
  while ((ch = fgetc(encodedFile)) != EOF) {
    if (ch == '0') {
      currentNode = currentNode->left;
    } else if (ch == '1') {
      currentNode = currentNode->right;
    }

    // 리프 노드에 도달했을 경우
    if (isLeaf(currentNode)) {
      fputc(currentNode->item, decodedFile); // 문자를 파일에 씁니다.
      currentNode = root; // 다시 루트 노드로 돌아갑니다.
    }
  }

  fclose(encodedFile);
  fclose(decodedFile);
}

// 메인 함수
int main() {
  FILE* file; // 파일 포인터
  int freq[ALPHABET_SIZE] = {0}; // 알파벳 빈도수 배열
  char data[ALPHABET_SIZE]; // 알파벳 배열
  int index = 0; // 알파벳 배열 인덱스
  char ch; // 문자

  // 파일 열기
  file = fopen(FILE_PATH, "r");
  if (file == NULL) {
    printf("파일을 열 수 없습니다.\n");
    return 1;
  }

  // 파일에서 알파벳 빈도수 계산
  while ((ch = fgetc(file)) != EOF) {
    // 알파벳인 경우 빈도수 증가
    if (isalpha(ch)) { 
      ch = tolower(ch); // 대문자일 경우 소문자로 변환
      freq[ch - 'a']++;
    }
  }
  fclose(file); // 파일 닫기

  // 알파벳 배열에 빈도수가 0이 아닌 문자 저장
  for (int i = 0; i < ALPHABET_SIZE; i++) {
    if (freq[i] > 0) {
      data[index] = i + 'a';
      index++;
    }
  }

  // 각 문자의 출현 빈도 출력
  for (int i = 0; i < ALPHABET_SIZE; i++) {
    if (freq[i] > 0) {
      printf("%c: %d\n", i + 'a', freq[i]);
    }
  }

  // 허프만 코드를 계산하고 인코딩하는 과정
  char codes[ALPHABET_SIZE][MAX_TREE_HT] = {0}; // 문자별 허프만 코드를 저장할 배열
  HuffmanCodes(data, freq, index, codes); // 허프만 코드를 계산하고 저장합니다.
  encodeFile(codes); // 원본 데이터 파일을 인코딩하여 저장합니다.

  // 디코딩 과정
  struct MinHeapNode* root = buildHuffmanTree(data, freq, index); // 허프만 트리 재구성
  decodeFile(root, ENCODED_FILE_PATH, "sample.dec"); // 인코딩된 파일을 디코딩하여 sample.dec 파일로 저장

  return 0;
}
