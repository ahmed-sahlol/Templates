// Patterns must be distinct
struct AhoCorasick {
    // Number of nodes & Number of patterns
    int N, P;

    /// Change this for the patterns structure
    const int A = 26;
    const char neutral = 'a';

    vector<vector<int>> next;
    vector<int> link, out_link;
    vector<vector<int>> out;
//    vector<vector<int>> dp;

    /*
     * next : Normal trie links
     * link : Longest proper prefix equals to this suffix
     * out_link : First suffix that has a match in it
     * out : the indices of the matched patterns in this node
    */

    AhoCorasick() : N(0), P(0) { node(); }

    int node() {
        next.emplace_back(A, 0);
        link.emplace_back(0);
        out_link.emplace_back(0);
        out.emplace_back(0);
        return N++;
    }

    inline int get(char c) { return c - neutral; }

    int add_pattern(const string &patt) {
        int u = 0;
        for (auto &c: patt) {
            if (!next[u][get(c)]) next[u][get(c)] = node();
            u = next[u][get(c)];
        }
        out[u].push_back(P);
        return P++;
    }

    void compute() {
        queue<int> q;
        q.push(0);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int c = 0; c < A; ++c) {
                int v = next[u][c];
                if (!v) next[u][c] = next[link[u]][c];
                else {
                    link[v] = u ? next[link[u]][c] : 0;
                    out_link[v] = out[link[v]].empty() ? out_link[link[v]] : link[v];
                    q.push(v);
                }
            }
        }
        //dp.assign(N, vector<int>(A, -1));
    }

//    int advance(int u, char c) {
//        if (!u || next[u][get(c)]) return next[u][get(c)];
//        if (~dp[u][get(c)]) return dp[u][get(c)];
//        int &ret = dp[u][get(c)];
//        ret = advance(link[u], c);
//        return ret;
//    }

    int advance(int u, char c) {
        while (u && !next[u][get(c)]) u = link[u];
        u = next[u][get(c)];
        return u;
    }
};
