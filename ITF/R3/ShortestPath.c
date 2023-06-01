#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#define NON -1
#define G_SIZE 5
#define Q_SIZE 100
#define ROOT -2
int G[G_SIZE][G_SIZE] = {{0, 1, 0, 0, 0},
                         {0, 0, 0, 0, 0},
                         {1, 0, 0, 1, 0},
                         {0, 1, 0, 0, 1},
                         {0, 0, 1, 0, 0}};
int visited[G_SIZE];
int Q[Q_SIZE];
int Qf, Qr;

void initQ() {
  for (int i = 0; i < Q_SIZE; i++) {
    Q[i] = 0;
  }
  Qf = Qr = 0;
}

void enqueue(int e) {
  if (Qr == Q_SIZE) {
    fprintf(stderr, "Error:queue overflow.\n");
    exit(1);
  }
  Q[Qr++] = e;
}

int dequeue() {
  if (Qf == Qr) {
    fprintf(stderr, "Error:queue underflow.\n");
    exit(1);
  }
  return Q[Qf++];
}

bool emptyQ() {
  if (Qf == Qr)
    return true;
  else
    return false;
}

// 幅優先探索でsからtまでの最短距離を求める(visited配列の要素はそれぞれ初期位置を0基準とした深さを表す)
int shortestPath1(int s, int t) {
  int depth = 0;
  for (int i = 0; i < G_SIZE; i++) visited[i] = NON;
  visited[s] = 0;
  initQ();
  enqueue(s);
  while (!emptyQ()) {
    int v = dequeue();
    depth = visited[v];
    if (v == t) return depth;
    for (int j = 0; j < G_SIZE; j++) {
      if (G[v][j] == 1 && visited[j] == NON) {
        visited[j] = depth + 1;
        enqueue(j);
      }
    }
  }
  return NON;
}

// 幅優先探索でsからtまでの最短距離を求める(visited配列の要素はそれぞれ親ノードを表す)
int shortestPath2(int s, int t) {
  for (int i = 0; i < G_SIZE; i++) visited[i] = NON;
  visited[s] = ROOT;
  initQ();
  enqueue(s);
  while (!emptyQ()) {
    int v = dequeue();
    if (v == t) return 1;
    for (int j = 0; j < G_SIZE; j++) {
      if (G[v][j] == 1 && visited[j] == NON) {
        visited[j] = v;
        enqueue(j);
      }
    }
  }
  return NON;
}

void getPath(int t) {
  initQ();
  int v = t;
  enqueue(v);
  while (visited[v] != ROOT) {
    v = visited[v];
    enqueue(v);
  }
  printf("Path: ");
  for (int i = Qr - 1; i >= 0; i--) {
    printf("%d ", Q[i]);
  }
  putchar('\n');
}

int main() {
  int s, t;
  printf("Start:");
  scanf("%d", &s);
  printf("Goal:");
  scanf("%d", &t);
  if (shortestPath2(s, t) == 1)
    getPath(t);
  else
    printf("Failed to search any route from %d to %d.", s, t);
  return 0;
}