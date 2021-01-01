#include <bits/stdc++.h>

using namespace std;

// checks whether the point is inside the convex hull or not
bool inside(vector<pair<int, int>> convex_hull, pair<int, int> p)
{
    // initialize centroid of convex hull
    pair<int, int> mid = {0, 0};

    int n = convex_hull.size();

    // multiplying with n to avoid floating point arithmetic
    p.first *= n;
    p.second *= n;
    for (int i = 0; i < n; ++i) {
        mid.first += convex_hull[i].first;
        mid.second += convex_hull[i].second;
        convex_hull[i].first *= n;
        convex_hull[i].second *= n;
    }

    // if mid and given point lies always
    // on same side w.r.t every edge of convex hull
    // then point lies inside the convex hull
    for (int i = 0, j; i < n; ++i) {
        j = (i + 1) % n;
        int x1 = convex_hull[i].first, x2 = convex_hull[j].first;
        int y1 = convex_hull[i].second, y2 = convex_hull[j].second;
        int a1 = y1 - y2;
        int b1 = x2 - x1;
        int c1 = x1 * y2 - y1 * x2;
        int for_mid = a1 * mid.first +b1 * mid.second + c1;
        int for_p = a1 * p.first + b1 * p.second + c1;
        if (for_mid * for_p < 0) return false;
    }

    return true;
}

// square of distance between two input points
int sq_dist(pair<int, int> p1, pair<int, int> p2)
{
    return (p1.first - p2.first) * (p1.first - p2.first) +
           (p1.second - p2.second) * (p1.second - p2.second);
}

// checks whether point crosses convex hull or not
int orientation(pair<int, int> a, pair<int, int> b,
                pair<int, int> c)
{
    int val = (b.second - a.second) * (c.first - b.first) -
              (c.second - b.second) * (b.first - a.first);

    if (val == 0) return 0;
    if (val > 0) return 1;
    return -1;
}

// add a point p to given convex hull
void add_point(vector<pair<int, int>> &a, pair<int, int> p)
{
    // if point is inside p
    if (inside(a, p)) return;

    // point having minimum distance from point p
    int idx = 0;
    int n = a.size();
    for (int i = 1; i < n; ++i) {
        if (sq_dist(p, a[i]) < sq_dist(p, a[idx])) idx = i;
    }

    // find upper tangent
    int up = idx;
    while (orientation(p, a[up], a[(up + 1) % n]) >= 0)
    {
        up = (up + 1) % n;
    }

    // find lower tangent
    int low = idx;
    while (orientation(p, a[low], a[(n + low - 1) % n]) <= 0)
    {
        low = (n + low - 1) % n;
    }

    // initialize result
    vector<pair<int, int>> ret;

    // making final hull by traversing points
    // from up to low of given convex hull
    int current = up;
    ret.push_back(a[current]);
    while (current != low)
    {
        current = (current + 1) % n;
        ret.push_back(a[current]);
    }

    // modify original vector
    ret.push_back(p);
    a.clear();
    for (int i = 0; i < ret.size(); ++i) {
        a.push_back(ret[i]);
    }
}

int main() {
    vector<pair<int, int>> convex_hull;
    convex_hull.push_back({0, 0});
    convex_hull.push_back({3, -1});
    convex_hull.push_back({4, 5});
    convex_hull.push_back({-1, 4});
    int n = convex_hull.size();

    pair<int, int> add_p = {100, 100};
    add_point(convex_hull, add_p);

    // print the modified convex hull
    for (auto element : convex_hull) {
        cout << "(" << element.first << ", "
             << element.second << ")";
    }

    return 0;
}
