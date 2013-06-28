#include <bitset>
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

#define MAX_N 1000

struct Koopa {
  int time;
  int parent;
  vector<int> children;
};

struct KoopaDP {
  int sum;
  int conquer;
  int left;
  int left_sum;
};

Koopa koopa[MAX_N];
KoopaDP dp[MAX_N];
bitset<MAX_N> root;

void ComputeSum(int r) {
  dp[r].sum = koopa[r].time;
  for (int i = 0; i < koopa[r].children.size(); i++) {
    int child = koopa[r].children[i];
    ComputeSum(child);
    dp[r].sum += dp[child].sum;
  }
}

void ComputeLeft(int r) {
  for (int i = 0; i < koopa[r].children.size(); i++) {
    int child = koopa[r].children[i];
    ComputeLeft(child);
    dp[r].left_sum += dp[child].left;
  }
  for (int i = 0; i < koopa[r].children.size(); i++) {
    int child = koopa[r].children[i];
    dp[r].left = max(
        dp[r].left, dp[r].left_sum - dp[child].left + dp[child].sum);
  }
}

void ComputeConquer(int r) {
  if (koopa[r].children.size() == 1) {
    dp[r].conquer = dp[r].sum;
    return;
  }
  for (int i = 0; i < koopa[r].children.size(); i++) {
    for (int j = 0; j < koopa[r].children.size(); j++) {
      if (i == j) {
        continue;
      }
      int child1 = koopa[r].children[i];
      int child2 = koopa[r].children[j];
      ComputeConquer(child1);
      dp[r].conquer = max(
          dp[r].conquer,
          dp[r].left_sum - dp[child1].left - dp[child2].left + dp[child1].conquer + dp[child2].sum + koopa[r].time);
    }
  }

}

int main() {
  int n;

  while (scanf("%d", &n) != EOF && n) {
    memset(dp, 0, sizeof(dp));
    root.reset();
    for (int i = 0; i < n; i++) {
      scanf("%d", &koopa[i].time);
      koopa[i].children.clear();
      dp[i].conquer = koopa[i].time;
    }
    for (int i = 0; i < n; i++) {
      scanf("%d", &koopa[i].parent);
      if (koopa[i].parent != -1) {
        koopa[koopa[i].parent].children.push_back(i);
      } else {
        root.set(i);
      }
    }

    int max_time = 0;
    for (int i = 0; i < n - 1; i++) {
      if (root.test(i)) {
        ComputeSum(i);
        max_time += dp[i].sum;
      }
    }
    ComputeSum(n - 1);
    ComputeLeft(n - 1);
    ComputeConquer(n - 1);
    max_time += dp[n - 1].conquer;

    printf("%d\n", max_time);
  }
  return 0;
}
