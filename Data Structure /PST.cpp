struct Node {
    Node *l, *r;
    int val = 0;

    Node() : l(nullptr), r(nullptr) {}

    Node(int val) : l(nullptr), r(nullptr), val(val) {}

    Node(Node *l, Node *r) : l(l), r(r) {
        if (l) val += l->val;
        if (r) val += r->val;
    }
};

struct PST {
    int n;

    PST(int n) : n(n) {}

    Node merge(const Node &x, const Node &y) {
        Node ret;
        ret.val = x.val + y.val;
        return ret;
    }

    Node *build(vector<int> &a, int lx, int rx) {
        if (lx == rx)return new Node(a[lx]);
        int mid = (lx + rx) >> 1;
        return new Node(build(a, lx, mid), build(a, mid + 1, rx));
    }

    Node *build(vector<int> &a) { return build(a, 0, n - 1); }

    Node *set(Node *v, int idx, int val, int lx, int rx) {
        if (lx == rx)return new Node(val);
        int mid = (lx + rx) >> 1;
        if (idx <= mid)return new Node(set(v->l, idx, val, lx, mid), v->r);
        return new Node(v->l, set(v->r, idx, val, mid + 1, rx));
    }

    Node *set(Node *v, int idx, int val) { return set(v, idx, val, 0, n - 1); }

    Node query(Node *v, int l, int r, int lx, int rx) {
        if (rx < l || lx > r)return Node();
        if (l <= lx && rx <= r)return *v;
        int mid = (lx + rx) >> 1;
        Node left = query(v->l, l, r, lx, mid);
        Node right = query(v->r, l, r, mid + 1, rx);
        return merge(left, right);
    }

    Node query(Node *v, int l, int r) { return query(v, l, r, 0, n - 1); }
};
