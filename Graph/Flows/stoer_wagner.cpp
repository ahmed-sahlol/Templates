// Stoer–Wagner global min‐cut on an undirected weighted graph.
// n = number of vertices, weight[u][v] = weight of edge u–v (0 if none).
// Returns the weight of the minimum cut separating the vertices into two nonempty sets.
ll stoer_wagner(int n, vector<vector<ll>>& weight) {
    vector<bool> alive(n, true);
    vector<ll> best(n), dist(n);
    ll min_cut = LLONG_MAX;

    for(int phase = n; phase > 1; --phase) {
        fill(dist.begin(), dist.end(), 0);
        vector<bool> added(n, false);
        int prev = -1;
        // "Maximum‐weight‐search" (like Prim's)
        for(int i = 0; i < phase; ++i) {
            int pick = -1;
            for(int j = 0; j < n; ++j) {
                if (alive[j] && !added[j] && (pick == -1 || dist[j] > dist[pick]))
                    pick = j;
            }
            added[pick] = true;
            if (i == phase - 1) {
                // last added in this phase: consider cut between 'pick' and the rest
                if (dist[pick] < min_cut) 
                    min_cut = dist[pick];
                // merge 'pick' into 'prev'
                for(int v = 0; v < n; ++v) {
                    weight[prev][v] += weight[pick][v];
                    weight[v][prev] = weight[prev][v];
                }
                alive[pick] = false;
            }
            else {
                prev = pick;
                // grow the set
                for(int v = 0; v < n; ++v) {
                    if (alive[v] && !added[v])
                        dist[v] += weight[pick][v];
                }
            }
        }
    }
    return min_cut;
}
//////// 
/// globalMinCut paths
using vi = vector<int>;
pair<int, vi> globalMinCut(vector<vi> mat) {
    pair<int, vi> best = {INT_MAX, {}};
    int n = mat.size();
    vector<vi> co(n);
    for (int i = 0; i < n; i++) co[i] = {i};
 
    for (int ph = 1; ph < n; ph++) {
        vi w = mat[0];
        size_t s = 0, t = 0;
        for (int it = 0; it < n - ph; it++) { // O(V^2) => O(E log V) with prio. queue
            w[t] = INT_MIN;
            s = t, t = max_element(all(w)) - w.begin();
            for (int i = 0; i < n; i++) w[i] += mat[t][i];
        }
        best = min(best, {w[t] - mat[t][t], co[t]});
        
        // Merge nodes s and t
        co[s].insert(co[s].end(), all(co[t]));
        for (int i = 0; i < n; i++) mat[s][i] += mat[t][i];
        for (int i = 0; i < n; i++) mat[i][s] = mat[s][i];
        mat[0][t] = INT_MIN; // Mark t as removed
    }
    return best;
}
