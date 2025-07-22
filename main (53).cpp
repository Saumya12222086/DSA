#include <bits/stdc++.h>
using namespace std;

class SegmentTree {
public:
    vector<int> seg;
    int size;
    int levels;

    SegmentTree(int n) {
        size = 1 << n; 
        seg.resize(4 * size);
        levels = n;
    }

    void build(vector<int>& arr, int idx, int l, int r, int level) {
        if (l == r) {
            seg[idx] = arr[l];
            return;
        }

        int mid = (l + r) / 2;
        build(arr, 2 * idx + 1, l, mid, level - 1);
        build(arr, 2 * idx + 2, mid + 1, r, level - 1);

        if (level % 2 == 1) 
            seg[idx] = seg[2 * idx + 1] | seg[2 * idx + 2];
        else 
            seg[idx] = seg[2 * idx + 1] ^ seg[2 * idx + 2];
    }

    void update(int idx, int l, int r, int pos, int val, int level) {
        if (l == r) {
            seg[idx] = val;
            return;
        }

        int mid = (l + r) / 2;
        if (pos <= mid)
            update(2 * idx + 1, l, mid, pos, val, level - 1);
        else
            update(2 * idx + 2, mid + 1, r, pos, val, level - 1);

        if (level % 2 == 1)
            seg[idx] = seg[2 * idx + 1] | seg[2 * idx + 2];
        else
            seg[idx] = seg[2 * idx + 1] ^ seg[2 * idx + 2];
    }

    int getResult() {
        return seg[0];
    }
};

int main() {
    int n, m;
    cin >> n >> m;
    int size = 1 << n;
    vector<int> arr(size);
    for (int i = 0; i < size; ++i)
        cin >> arr[i];

    SegmentTree st(n);
    st.build(arr, 0, 0, size - 1, n);

    while (m--) {
        int pos, val;
        cin >> pos >> val;
        st.update(0, 0, size - 1, pos - 1, val, n); 
        cout << st.getResult() << endl;
    }

    return 0;
}
