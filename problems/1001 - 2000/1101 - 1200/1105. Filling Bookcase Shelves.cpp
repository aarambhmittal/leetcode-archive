class Solution {
private:
    int32_t n;
    std::vector<std::vector<int32_t>> memo;
    
public:
    int32_t minHeightShelves(std::vector<std::vector<int32_t>>& books, int shelfWidth) {
        n = books.size();
        memo.assign(n, std::vector<int32_t>(shelfWidth + 1, 0));
        
        std::function<int32_t(int32_t, int32_t, int32_t)> helper = 
        [&](int32_t i, int32_t remWidth, int32_t curHeight) -> int32_t {         
            if(i == n - 1) {
                if(remWidth >= books[i][0]) return std::max(curHeight, books[i][1]);
                return curHeight + books[i][1];
            }
            if(memo[i][remWidth] != 0) return memo[i][remWidth];
            
            // add to curr shelf
            int32_t curr = (remWidth >= books[i][0])? 
            helper(i + 1, remWidth - books[i][0], std::max(curHeight, books[i][1])): -1;
            // add to next shelf
            int32_t next = curHeight + helper(i + 1, shelfWidth - books[i][0], books[i][1]);
            
            memo[i][remWidth] = (curr == -1)? next: std::min(curr, next);
            return memo[i][remWidth]; 
        };
        return helper(0, shelfWidth, 0);
    }
};
