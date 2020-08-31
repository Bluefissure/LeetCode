typedef pair<int,int> P;
class Solution {
public:
    bool vis[30][30];
    P dir[4] = {
        P(0,1), P(0, -1), P(-1,0), P(1,0)
    };
    void BFS(vector<vector<int>>& grid, int x, int y){
        int n = grid.size();
        int m = grid[0].size();
        queue<P> Q;
        Q.push(P(x, y));
        while(!Q.empty()){
            P p = Q.front();
            Q.pop();
            int i = p.first;
            int j = p.second;
            if (vis[i][j]) continue;
            vis[i][j] = 1;
            for (int k = 0; k < 4; k++){
                P d = dir[k];
                int ii = i + d.first, jj = j + d.second;
                if (ii>=0 && ii<n && jj>=0 && jj<m && grid[ii][jj] && !vis[ii][jj])
                    Q.push(P(ii,jj));
            }
        }
    }
    bool checkDisConn(vector<vector<int>>& grid){
        int n = grid.size();
        int m = grid[0].size();
        memset(vis, 0, sizeof(vis));
        bool searched = false;
        for (int i = 0; i < n; i++){
            for (int j = 0; j < m; j++){
                if(grid[i][j]){
                    BFS(grid, i, j);
                    searched = true;
                    break;
                }
            }
            if (searched) break;
        }
        for (int i = 0; i < n; i++){
            for (int j = 0; j < m; j++){
                if(grid[i][j] && !vis[i][j]){
                    return true;
                }
            }
        }
        return false;
    }
    int minDays(vector<vector<int>>& grid) {
        int n = grid.size();
        int m = grid[0].size();
        if (checkDisConn(grid)) return 0;
        for (int i = 0; i < n; i++){
            for (int j = 0; j < m; j++){
                if(grid[i][j]){
                    grid[i][j] = 0;
                    if (checkDisConn(grid)) return 1;
                    grid[i][j] = 1;
                }
            }
        }
        return 2;
    }
};