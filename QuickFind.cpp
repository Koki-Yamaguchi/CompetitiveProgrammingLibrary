struct QuickFind {
        int n;
        vector<int> group;
        vector<vector<int>> item;
        QuickFind(int n_) {
                n = n_;
                group.resize(n_);
                item.resize(n_);
                for (int i = 0; i < n_; i ++) {
                        group[i] = i;
                        item[i].assign(1, i);
                }
        }
        bool same(int x, int y) { return group[x] == group[y]; }
        void merge(int x, int y) {
                if (same(x, y)) return;
                if (item[group[x]].size() < item[group[y]].size()) swap(x, y);
                int gx = group[x], gy = group[y];
                for (int i : item[gy]) group[i] = gx;
                item[gx].insert(item[gx].end(), item[gy].begin(), item[gy].end());
                item[gy].clear();
                n --;
        }
        int get() { return n; }
        int get(int x) { return item[group[x]].size(); }
};
