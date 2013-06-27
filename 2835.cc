#include <bitset>
#include <cstdio>
#include <cstring>
using namespace std;

#define MAX_N 10
#define MAX_NUM 1000

int main() {
  int N;
  int num;
  int sum_row[MAX_N], sum_col[MAX_N], dia1, dia2;
  bitset<MAX_NUM> exist;
  while (scanf("%d", &N) != EOF && N) {
    memset(sum_col, 0, sizeof(sum_col));
    memset(sum_row, 0, sizeof(sum_row));
    dia1 = dia2 = 0;
    exist.reset();
    bool res = true;
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        scanf("%d", &num);
        if (!exist.test(num)) {
          exist.set(num);
          sum_row[i] += num; 
          sum_col[j] += num;
          if (i == j) {
            dia1 += num;
          }
          if (N - 1 - i == j) {
            dia2 += num;
          }
        } else {
          res = false;
        }
      }
    }
    if (res) {
      if (dia2 == dia1) {
        for (int i = 0; i < N; i++) {
          if (sum_row[i] != dia1 || sum_col[i] != dia1) {
            res = false;
            break;
          }
        }
      } else {
        res = false;
      }
    }
    if (res) {
      printf("Yes\n");
    } else {
      printf("No\n");
    }
  }
  return 0;
}
