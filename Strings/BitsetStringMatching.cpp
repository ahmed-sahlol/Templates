template<int N, int ALPHA = 26>
struct BitsetStringMatching {
    bitset<N> mask[ALPHA];
    string text;

    BitsetStringMatching() {}

    BitsetStringMatching(const string &s) { build(s); }

    void build(const string &s) {
        text = "#" + s;
        for (int i = 0; i < ALPHA; i++) mask[i].reset();
        for (int i = 1; i < text.size(); i++) mask[text[i] - 'a'].set(i);
    }

    int countMatches(const string &pat) {
        int n = text.size() - 1;
        int m = pat.size();
        if (m > n) return 0;
        bitset<N> cur;
        cur.set();
        for (int i = 0; i < m; i++) {
            int c = pat[i] - 'a';
            cur &= (mask[c] >> i);
        }
        return cur.count();
    }

    vector<int> getPositions(const string &pat) {
        int n = text.size() - 1;
        int m = pat.size();
        vector<int> ans;
        if (m > n)return ans;
        bitset<N> cur;
        cur.set();
        for (int i = 0; i < m; i++) {
            int c = pat[i] - 'a';
            cur &= (mask[c] >> i);
        }
        for (int i = 1; i + m - 1 <= n; i++) if (cur[i]) ans.push_back(i);
        return ans;
    }

    int countInRange(const string &pat, int l, int r) {
        int n = text.size() - 1;
        int m = pat.size();
        if (r - l + 1 < m) return 0;
        bitset<N> cur;
        cur.set();
        for (int i = 0; i < m; i++) {
            int c = pat[i] - 'a';
            cur &= (mask[c] >> i);
        }
        int R = r - m + 1;
        return (cur >> l).count() - (cur >> (R + 1)).count();
    }

    void update(int idx, char c) {
        mask[text[idx] - 'a'][idx] = 0;
        text[idx] = c;
        mask[text[idx] - 'a'][idx] = 1;
    }
};
