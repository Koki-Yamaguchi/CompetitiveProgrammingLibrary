struct state { int y, x; }
static const int dx[] = {1, 0, -1, 0}, dy[] = {0, 1, 0, -1};
        vector<vector<int>> used(h, vector<int> (w, -1));
        queue<state> q;
        q.push({sy, sx});
        used[sy][sx] = 0;
        while (!q.empty()) {
                state p = q.front(); q.pop();
                for (int d = 0; d < 4; d ++) {
                        int xx = p.x + dx[d], yy = p.y + dy[d];
                        if (xx < 0 || xx >= w || yy < 0 || yy >= h) continue;
                        if (used[yy][xx] != -1 || s[yy][xx] == '#') continue;
                        used[yy][xx] = used[p.y][p.x] + 1;
                        q.push({yy, xx});
                }
        }
