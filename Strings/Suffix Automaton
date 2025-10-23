struct SuffixAutomaton {
    struct state {
        int len, link, cnt, first_pos;
        map<char, int> next;

        state() { len = cnt = 0, link = first_pos = -1; }
    };

    vector<state> st;
    int lst = 0;

    SuffixAutomaton(const string &s) {
        st.emplace_back();
        for (auto c: s)extend(c);
        build_occurrences();
    }

    void extend(char c) {
        st.emplace_back();
        int cur = st.size() - 1;
        st[cur].len = st[lst].len + 1;
        st[cur].first_pos = st[cur].len - 1;
        st[cur].cnt = 1;

        int p;
        for (p = lst; p != -1 and !st[p].next.count(c); p = st[p].link)
            st[p].next[c] = cur;

        if (p == -1) {
            st[cur].link = 0;
            lst = cur;
            return;
        }

        int q = st[p].next[c];

        if (st[p].len + 1 == st[q].len) {
            st[cur].link = q;
            lst = cur;
            return;
        }

        st.emplace_back(st[q]);
        int clone = st.size() - 1;
        st[clone].len = st[p].len + 1;
        st[clone].first_pos = st[q].first_pos;
        st[clone].cnt = 0;

        for (; p != -1 && st[p].next[c] == q; p = st[p].link)
            st[p].next[c] = clone;

        st[q].link = st[cur].link = clone;
        lst = cur;
    }

    void build_occurrences() {
        vector<int> order(st.size());
        iota(order.begin(), order.end(), 0);
        sort(order.begin(), order.end(), [&](int a, int b) {
            return st[a].len > st[b].len;
        });
        for (int v: order) {
            if (st[v].link >= 0)
                st[st[v].link].cnt += st[v].cnt;
        }
    }

    /// check Finding Patterns
    bool check_Patterns(string s) {
        int u = 0;
        for (auto c: s) {
            if (!st[u].next.count(c)) return 0;
            u = st[u].next[c];
        }
        return 1;
    }

    /// count how many Pattern is occur as substring
    int count_occur(string pattern) {
        int u = 0;
        for (auto c: pattern) {
            if (!st[u].next.count(c)) return 0;
            u = st[u].next[c];
        }
        return st[u].cnt;
    }

    /// count all Distinct Substrings
    int count_distinct_substrings() {
        int tot = 0;
        for (int i = 1; i < st.size(); ++i) {
            tot += st[i].len;
            if (st[i].link != -1) tot -= st[st[i].link].len;
        }
        return tot;
    }

    /// find first occurance of substring s
    int first_occurrence(string s) const {
        int v = 0;
        for (char c: s) {
            if (!st[v].next.count(c))
                return -1;
            v = st[v].next.at(c);
        }
        return st[v].first_pos - s.size() + 1;
    }

    /// match_lengths: for each i, max length of substring ending at i in s that appears in original
    vector<int> match_length(string s) {
        vector<int> match(s.size() + 2, 0);
        int u = 0, l = 0;
        for (int i = 0; i < s.size(); ++i) {
            while (~u and !st[u].next.count(s[i])) {
                u = st[u].link;
                if (~u) l = st[u].len;
            }
            if (u == -1) l = u = 0;
            else u = st[u].next[s[i]], l++;
            match[i] = l;
        }
        return match;
    }
};
