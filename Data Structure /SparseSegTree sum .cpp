const long long mod = 1e9 + 7;

class SparseSegTree {
private:
    struct Node {
        long long sum = 0;
        long long lazy = 0;
        Node *left = nullptr;
        Node *right = nullptr;
    };

    Node *root = new Node;
    const int n;

    void apply(Node *cur, int len, long long val) {
        val %= mod;
        cur->lazy = (cur->lazy + val) % mod;
        cur->sum = ((cur->sum % mod) + (((val % mod) * (len % mod)) % mod)) % mod;
    }

    void push_down(Node *cur, int l, int r) {
        if (!cur->left) cur->left = new Node;
        if (!cur->right) cur->right = new Node;

        if (cur->lazy == 0) return;

        int m = (l + r) / 2;
        long long val = cur->lazy;

        apply(cur->left, m - l + 1, val);
        apply(cur->right, r - m, val);

        cur->lazy = 0;
    }

    void range_add(Node *cur, int l, int r, int ql, int qr, long long val) {
        if (qr < l || r < ql) return;

        if (ql <= l && r <= qr) {
            apply(cur, r - l + 1, val);
            return;
        }

        push_down(cur, l, r);

        int m = (l + r) / 2;

        range_add(cur->left, l, m, ql, qr, val);
        range_add(cur->right, m + 1, r, ql, qr, val);

        long long leftSum = cur->left ? cur->left->sum : 0;
        long long rightSum = cur->right ? cur->right->sum : 0;

        cur->sum = ((leftSum) % mod + (rightSum) % mod) % mod;
    }

    long long range_sum(Node *cur, int l, int r, int ql, int qr) {
        if (!cur || qr < l || r < ql) return 0;
        if (ql <= l && r <= qr) return cur->sum;
        push_down(cur, l, r);
        int m = (l + r) / 2;
        return ((range_sum(cur->left, l, m, ql, qr)) % mod + (range_sum(cur->right, m + 1, r, ql, qr)) % mod) % mod;
    }

public:
    SparseSegTree(int n) : n(n) {}

    void range_add(int l, int r, long long val) {
        range_add(root, 0, n - 1, l, r, val);
    }

    long long query(int l, int r) {
        return range_sum(root, 0, n - 1, l, r);
    }
};
