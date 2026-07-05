struct Node {
    int left = 0, right = 0, val = 0;
    Node(){}
    Node (int v) : val(v){}
};
struct PST {

    vector<Node> nodes;
    int L, R;

    PST(int l, int r) {
        L = l;
        R = r;
        nodes.reserve(1e7);
        nodes.push_back({});
    }

    void merge(Node &ans, const Node & lf, const Node & ri) {
        ans.val = lf.val + ri.val;
    }

    int create_node() {
        nodes.push_back({});
        return nodes.size() - 1;
    }

    int set(int idx, int val, int ni, int lx, int rx) {
        int id = create_node();
        if(rx - lx == 1) {
            nodes[id] = Node(nodes[ni].val + val);
            return id;
        }

        int mid = (lx + rx) >> 1;

        nodes[id].left = nodes[ni].left;
        nodes[id].right = nodes[ni].right;

        if(idx < mid)
            nodes[id].left = set(idx, val, nodes[ni].left, lx, mid);
        else
            nodes[id].right = set(idx, val, nodes[ni].right, mid, rx);

        merge(nodes[id], nodes[nodes[id].left], nodes[nodes[id].right]);
        return id;
    }

    int set(int idx, int val, int version) {
        return set(idx, val, version, L, R + 1);
    }

    Node get(int l, int r, int ni, int lx, int rx) {
        if(ni == 0) return nodes[ni];
        if(lx >= r || rx <= l)
            return Node();
        if(lx >= l && rx <= r)
            return nodes[ni];

        int mid = (lx + rx) >> 1;

        Node ans = Node();
        merge(ans, get(l, r, nodes[ni].left, lx, mid), get(l, r, nodes[ni].right, mid, rx));
        return ans;
    }
    int get(int l, int r, int version) {
        return get(l, r, version, L, R + 1).val;
    }

    int get_kth(int k, int node_l, int node_r, int lx, int rx) {
        if(nodes[node_r].val - nodes[node_l].val < k)
            return -1;
        if(rx - lx == 1)
            return lx;
        int mid = (lx + rx) >> 1;
        int cnt = nodes[nodes[node_r].left].val - nodes[nodes[node_l].left].val;
        if (cnt >= k) {
            return get_kth(k, nodes[node_l].left, nodes[node_r].left, lx, mid);
        } else {
            return get_kth(k - cnt, nodes[node_l].right, nodes[node_r].right, mid, rx);
        }
    }

    int get_kth(int k, int node_l, int node_r) {
        return get_kth(k, node_l, node_r, L, R + 1);
    }
};
