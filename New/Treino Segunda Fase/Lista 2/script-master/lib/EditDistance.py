
def solve (i, j, a, b, dp):
 if dp[i][j] != -1: return dp[i][j]
 if i == len(a) or j == len(b):
  dp[i][j] = len(a) - i + len(b) - j
  return dp[i][j]
 dp[i][j] = min (1+solve(i+1,j,a,b,dp), 1+solve(i,j+1,a,b,dp), (0 if a[i] == b[j] else 1) + solve (i+1,j+1,a,b,dp))
 return dp[i][j]

def edit_distance (a, b):
 dp = [[-1 for i in range(len(b)+1)] for i in range (len(a)+1)]
 return solve (0, 0, a, b, dp)
