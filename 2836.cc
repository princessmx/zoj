#include <algorithm>
#include <cstdio>
#include <set>
using namespace std;

#define MAX_N 10

inline int lcd(int a, int b) {
  if (a < b) {
    swap(a, b);
  }
  while (true) {
    int r = a % b;
    if (r == 0) {
      break;
    }
    a = b;
    b = r;
  }
  return b;
}

inline int lcm(int a, int b) {
  return a * b / lcd(a, b);
}

int main() {
  int n, m, count, a[MAX_N];
  set<int> uniq;
  long long num;
  while (scanf("%d %d", &n, &m) != EOF) {
    count = 0;
    num = 0;
    uniq.clear();
    for (int i = 0; i < n; i++) {
      scanf("%d", &a[count]);
      if (uniq.count(a[count]) == 0) {
        uniq.insert(a[count]);
        count++;
      }
    }
    n = 1 << count;
    for (int i = 1; i < n; i++) {
      int j = i, cur = 0, l = 1;
      count = 0;
      while (j) {
        if (j & 1) {
          l = lcm(l, a[cur]);
          count++;
        }
        cur++;
        j >>= 1;
      }
      if (count & 1) {
        num += m / l;
      } else {
        num -= m / l;
      }
    }
    printf("%lld\n", num);
  }
  return 0;
}
