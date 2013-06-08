//2013-06-07 18:17:38  C++  50	180	PrincessMX
#include <bitset>
#include <cstdio>
#include <vector>
using namespace std;

#define MAX_N 100

int AddRelation(int n, int k, vector<bitset<MAX_N> >* relation) {
  int add = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < i; j++) {
      if (!(*relation)[i].test(j) &&
          ((*relation)[i] & (*relation)[j]).count() >= k) {
        add++;
        (*relation)[i].set(j);
        (*relation)[j].set(i);
      }
    }
  }
  return add;
}

int main() {
  vector<bitset<MAX_N> > relation;
  for (int i = 0; i < MAX_N; i++) {
    relation.push_back(bitset<MAX_N>());
  }
  int T;
  int n, m, k;
  int u, v;
  int add, new_add;
  scanf("%d", &T);
  for (int t = 0; t < T; t++) {
    scanf("%d %d %d", &n, &m, &k);
    for (int i = 0; i < n; i++) {
      relation[i].reset();
    }
    for (int i = 0; i < m; i++) {
      scanf("%d %d", &u, &v);
      relation[u].set(v);
      relation[v].set(u);
    }
    add = 0;
    int max_relation = n * (n - 1) / 2;
    do {
      new_add = AddRelation(n, k, &relation);
      add += new_add;
    } while (m + add < max_relation && new_add);
    printf("%d\n", add);
  }
  return 0;
}
