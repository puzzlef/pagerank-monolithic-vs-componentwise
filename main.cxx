#include <cmath>
#include <vector>
#include <string>
#include <cstdio>
#include <iostream>
#include "src/main.hxx"

using namespace std;




template <class G, class H>
void runPagerank(const G& x, const H& xt, int repeat) {
  vector<float> *init = nullptr;

  // Find pagerank using a single thread.
  auto a1 = pagerankMonolithic(xt, init, {repeat});
  auto e1 = l1Norm(a1.ranks, a1.ranks);
  printf("[%09.3f ms; %03d iters.] [%.4e err.] pagerankMonolithic\n", a1.time, a1.iterations, e1);

  // Find pagerank component-wise in topologically-ordered fashion (levelwise).
  auto a2 = pagerankLevelwise(x, xt, init, {repeat});
  auto e2 = l1Norm(a2.ranks, a1.ranks);
  printf("[%09.3f ms; %03d iters.] [%.4e err.] pagerankLevelwise\n", a2.time, a2.iterations, e2);
}


int main(int argc, char **argv) {
  char *file = argv[1];
  int repeat = argc>2? stoi(argv[2]) : 5;
  printf("Loading graph %s ...\n", file);
  auto x  = readMtx(file); println(x);
  loopDeadEnds(x); print(x); printf(" (loopDeadEnds)\n");
  auto xt = transposeWithDegree(x); print(xt); printf(" (transposeWithDegree)\n");
  runPagerank(x, xt, repeat);
  printf("\n");
  return 0;
}
