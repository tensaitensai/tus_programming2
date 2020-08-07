#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <iomanip>
#include <math.h>
#include <numeric>
#include <complex>
#include <queue>
#include <deque>
#include <stack>
#include <map>
#include <unordered_map>
#include <set>
#include <bitset>
#include <functional>
#include <assert.h>
using ll = long long;
#define int ll
#define rng(i, a, b) for (int i = int(a); i < int(b); i++)
#define rep(i, b) rng(i, 0, b)
#define gnr(i, a, b) for (int i = int(b) - 1; i >= int(a); i--)
#define per(i, b) gnr(i, 0, b)
#define eb emplace_back
#define all(x) x.begin(), x.end()
#define SZ(x) ((int)x.size())
#define fi first
#define se second
const int INF = 1e15;
using namespace std;

template <class T>
using vc = vector<T>;
template <class T>
using vvc = vc<vc<T>>;

using pi = pair<int, int>;
using vi = vc<int>;

template <class T>
inline bool chmax(T &a, T b)
{
  if (a < b)
  {
    a = b;
    return true;
  }
  return false;
}
template <class T>
inline bool chmin(T &a, T b)
{
  if (a > b)
  {
    a = b;
    return true;
  }
  return false;
}

#define N 100

signed main()
{
  int i, j, k, l, n, p[N + 1], cost[N + 1][N + 1], s[N + 1][N + 1], min_cost;

  cin >> n;
  for (i = 1; i <= n; i++)
    cin >> p[i - 1] >> p[i];

  // 初期値
  for (i = 1; i <= n; i++)
    cost[i][i] = 0;

  for (l = 2; l <= n; l++)
  { // 行列の個数
    for (i = 1; i <= n - l + 1; i++)
    {
      j = i + l - 1;
      for (k = i; k < j; k++)
      {
        if (k == i)
        {
          min_cost = cost[i][k] + cost[k + 1][j] + p[i - 1] * p[k] * p[j];
          s[i][j] = i;
        }
        else
        {
          if (chmin(min_cost, cost[i][k] + cost[k + 1][j] + p[i - 1] * p[k] * p[j]))
            s[i][j] = k;
        }
      }
      cost[i][j] = min_cost;
    }
  }

  for (i = 1; i <= n; i++)
  {
    for (j = i + 1; j <= n; j++)
    {
      cout << "m[" << i << "][" << j << "] = " << cost[i][j] << "\n";
    }
  }
  for (i = 1; i <= n; i++)
  {
    for (j = i + 1; j <= n; j++)
    {
      cout << "s[" << i << "][" << j << "] = " << s[i][j] << "\n";
    }
  }

  return 0;
}