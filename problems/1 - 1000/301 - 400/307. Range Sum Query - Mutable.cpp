struct SegmentTree {
    int32_t tree[4 * 30000] = {0};

    void build(std::vector<int32_t>& nums, int32_t node, int32_t l, int32_t r) {
        if(l == r) tree[node] = nums[l] & nums[r]; 
        else {
            int32_t mid = (l + r) / 2;
            build(nums, 2 * node, l, mid);
            build(nums, 2 * node + 1, mid + 1, r);
            tree[node] = tree[2 * node] + tree[2 * node + 1];
        }
    }

    void update(int32_t node, int32_t l, int32_t r, int32_t idx, int32_t val) {
        if(l == r) tree[node] = val;
        else {
            int32_t mid = (l + r) / 2;
            if(idx <= mid) update(2 * node, l, mid, idx, val);
            else update(2 * node + 1, mid + 1, r, idx, val);

            tree[node] = tree[2 * node] + tree[2 * node + 1];
        }
    }

    int32_t query(int32_t node, int32_t l, int32_t r, int32_t left, int32_t right) {
        if(left > right) return 0;
        if(l == left && r == right) return tree[node];

        int32_t mid = (l + r)/2;
        int32_t lSum = query(2 * node, l, mid, left, std::min(right, mid));
        int32_t rSum = query(2 * node + 1, mid + 1, r, std::max(left, mid + 1), right);
        return lSum + rSum;
    }
};

class NumArray {
private:
    int32_t n;
    SegmentTree st;

public:
    NumArray(std::vector<int32_t>& nums) {
        n = nums.size();
        st.build(nums, 1, 0, n - 1);
    }
    
    void update(int32_t index, int32_t val) {
        st.update(1, 0, n - 1, index, val);
    }
    
    int32_t sumRange(int32_t left, int32_t right) {
        return st.query(1, 0, n - 1, left, right);
    }
};

/*
 * Your NumArray object will be instantiated and called as such:
 * NumArray* obj = new NumArray(nums);
 * obj->update(index,val);
 * int param_2 = obj->sumRange(left,right);
 */
