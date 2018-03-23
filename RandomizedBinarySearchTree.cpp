unsigned long xor128() {
        static unsigned long x = 123456789, y = 362436069, z = 521288629, w = 88675123;
        unsigned long t = (x ^ (x << 11));
        x = y; y = z; z = w;
        return (w = (w ^ (w >> 19)) ^ (t ^ (t >> 8)));
}

struct node_t {
        int sz;
        long long val, add, sum;
        shared_ptr<node_t> lchild, rchild;
        node_t(long long val, int sz, long long add, long long sum, shared_ptr<node_t> lchild, shared_ptr<node_t> rchild)
                     : val(val), sz(sz), add(add), sum(sum), lchild(lchild), rchild(rchild) {}
};

using node = shared_ptr<node_t>;

int size(node t) { return !t ? 0 : t->sz; }
long long sum(node t) { return !t ? 0 : t->sum; }

node add(node v, long long a) {
        if (!v) return NULL;
        int sz = v->sz;
        return node(new node_t(v->val, sz, v->add + a, v->sum + a * sz, v->lchild, v->rchild));
}

node new_node(long long val) {
        return node(new node_t(val, 1, 0, val, NULL, NULL));
}

node make_node(long long val, node left, node right, long long a) {
        int sz = size(left) + size(right) + 1;
        return node(new node_t(val, sz, a, sum(left) + sum(right) + val + a * sz, left, right));
}

node merge(node left, node right) {
        if (!left || !right) return !left ? right : left;
        if (int(xor128() % (size(left) + size(right)) < size(left))) {
                if (left->add == 0) { 
                        return make_node(left->val, left->lchild, merge(left->rchild, right), 0);
                }
                node lv = add(left->lchild, left->add);
                node rv = merge(add(left->rchild, left->add), right);
                return make_node(left->val + left->add, lv, rv, 0);
        } else {
                if (right->add == 0) {
                        return make_node(right->val, merge(left, right->lchild), right->rchild, 0);
                }
                node lv = merge(left, add(right->lchild, right->add));
                node rv = add(right->rchild, right->add);
                return make_node(right->val + right->add, lv, rv, 0);
        }
}

pair<node, node> split(node t, int k) { //[0, k), [k, n)
        if (k == 0) return pair<node, node>(NULL, t);
        if (k >= size(t)) return pair<node, node>(t, NULL);
        if (size(t->lchild) >= k) {
                auto left = split(t->lchild, k);
                auto rv = make_node(t->val, left.second, t->rchild, t->add);
                if (t->add == 0) return make_pair(left.first, rv);
                return make_pair(add(left.first, t->add), rv);
        } else {
                auto right = split(t->rchild, k - size(t->lchild) - 1);
                auto lv = make_node(t->val, t->lchild, right.first, t->add);
                if (t->add == 0) return make_pair(lv, right.second);
                return make_pair(lv, add(right.second, t->add));
        }
}

node find(node tree, int k) {
        while (tree != NULL) {
                int sz = size(tree->lchild);
                if (sz > k) tree = tree->lchild;
                else if (sz == k) return tree;
                else {
                        tree = tree->rchild;
                        k -= sz + 1;
                }
        }
        return tree;
}
