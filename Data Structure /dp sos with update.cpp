const int B = 17;
const int M = 8;
const int N = B - M;

const int L = 1 << N;
const int R = 1 << M;

int t1[L][R];
int t2[L][R];

void addSub(int x, int val) {
    int l = x >> M;
    int r = x & (R - 1);

    for (int i = 0; i < R; i++) {
        if ((i & r) == r)
            t1[l][i] += val;
    }
}

int querySub(int x) {
    int l = x >> M;
    int r = x & (R - 1);

    int ans = 0;

    for (int i = 0; i < L; i++) {
        if ((i & l) == i)
            ans += t1[i][r];
    }

    return ans;
}

void addSuper(int x, int val) {
    x = ((1 << B) - 1) ^ x;

    int l = x >> M;
    int r = x & (R - 1);

    for (int i = 0; i < R; i++) {
        if ((i & r) == r)
            t2[l][i] += val;
    }
}

int querySuper(int x) {
    x = ((1 << B) - 1) ^ x;

    int l = x >> M;
    int r = x & (R - 1);

    int ans = 0;

    for (int i = 0; i < L; i++) {
        if ((i & l) == i)
            ans += t2[i][r];
    }

    return ans;
}
