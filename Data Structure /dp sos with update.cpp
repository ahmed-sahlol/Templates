#include <bits/stdc++.h>
#define int long long
using namespace std;

const int B = 17;
const int M = 8;
const int N = B - M;

const int L = 1 << N;
const int R = 1 << M;

int t1[ L ][ R ];
int t2[ L ][ R ];

void addSub ( int x, int val ) {
    int l = x >> M;
    int r = x & ( R - 1 );
    for ( int i = 0 ; i < R ; i++ ) {
        if ( ( i & r ) == r ) t1[ l ][ i ] += val;
    }
}

int querySub ( int x ) {
    int l = x >> M;
    int r = x & ( R - 1 );
    int ans = 0;
    for ( int i = 0 ; i < L ; i++ ) {
        if ( ( i & l ) == i ) ans += t1[ i ][ r ];
    }

    return ans;
}

void addSuper ( int x, int val ) {
    x = ( ( 1 << B ) - 1 ) ^ x;
    int l = x >> M;
    int r = x & ( R - 1 );
    for ( int i = 0 ; i < R ; i++ ) {
        if ( ( i & r ) == r ) t2[ l ][ i ] += val;
    }
}

int querySuper ( int x ) {
    x = ( ( 1 << B ) - 1 ) ^ x;
    int l = x >> M;
    int r = x & ( R - 1 );
    int ans = 0;
    for ( int i = 0 ; i < L ; i++ ) {
        if ( ( i & l ) == i ) ans += t2[ i ][ r ];
    }
    return ans;
}

void solve ( ) {
    int n;
    cin >> n;
    vector< int > a ( n ), b ( n );
    for ( int i = 0 ; i < n ; i++ ) cin >> a[ i ];
    for ( int i = 0 ; i < n ; i++ ) cin >> b[ i ];
    int ans = 0;
    for ( int i = 0 ; i < n ; i++ ) {
        ans += querySub ( a[ i ] ) + querySuper ( a[ i ] );
        addSub ( a[ i ] , 1 );
        addSuper ( a[ i ] , 1 );
    }
    for ( int i = 0 ; i < n ; i++ ) {
        addSub ( a[ i ] , -1 );
        addSuper ( a[ i ] , -1 );
        ans -= querySub ( a[ i ] ) + querySuper ( a[ i ] );

        ans += querySub ( b[ i ] ) + querySuper ( b[ i ] );
        addSub ( b[ i ] , 1 );
        addSuper ( b[ i ] , 1 );
        cout << ans << ' ';
    }
}

int32_t main ( ) {
    ios_base::sync_with_stdio ( false );
    cin . tie ( 0 );
    cout . tie ( 0 );
    int _ = 1; //cin >> _;
    for ( int i = 1 ; i <= _ ; i++ ) {
        solve ( );
        cout << '\n';
    }
}
