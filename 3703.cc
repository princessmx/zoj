//2013-06-21 20:16:45  C++	0	180	PrincessMX
#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

#define MAX_NUM_PROBLEM 50
#define MAX_CONTEST_LEN 1000

struct Problem {
  int time;
  int score;
};

struct ProblemCmp {
  inline bool operator() (const Problem& a, const Problem& b) {
    return ((a.time < b.time) ||
           ((a.time == b.time) && a.score > b.score));
  }
};

struct BestStatus {
  int score;
  int penalty;
  int count;
  int end;
};

int main() {
  int N, T, n;
  Problem p[MAX_NUM_PROBLEM + 1];
  BestStatus status[MAX_NUM_PROBLEM + 1][MAX_CONTEST_LEN + 1];
  scanf("%d", &N);
  while (N--) {
    scanf("%d %d", &T, &n);
    for (int i = 1; i <= n; i++) {
      scanf("%d", &p[i].time);
    }
    for (int i = 1; i <= n; i++) {
      scanf("%d", &p[i].score);
    }
    sort(p + 1, p + n + 1, ProblemCmp());
    memset(status, 0, sizeof(status));
    BestStatus s1, s2;
    for (int i = 1; i <= n; i++) {
      for (int j = 0; j <= T; j++) {
        if (p[i].time <= j) {
          s1.score = p[i].score + status[i - 1][j - p[i].time].score;
          s1.end = status[i - 1][j - p[i].time].end + p[i].time;
          s1.penalty = s1.end + status[i - 1][j - p[i].time].penalty;
          s1.count = status[i - 1][j - p[i].time].count + 1;

          s2 = status[i - 1][j];
          if (s1.score > s2.score ||
              (s1.score == s2.score &&
               (s1.count > s2.count ||
                (s1.count == s2.count && s1.penalty < s2.penalty)))) {
            status[i][j] = s1;
          } else {
            status[i][j] = s2;
          }
        } else {
          status[i][j] = status[i - 1][j];
        }
      }
    }
    printf("%d %d %d\n",
           status[n][T].score,
           status[n][T].count,
           status[n][T].penalty);
  }
  return 0;
}
