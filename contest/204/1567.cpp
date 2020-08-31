class Solution {
public:
    int getMaxLen(vector<int>& nums) {
        int dp[2][100005];
        dp[0][0] = nums[0]<0?1:-1;
        dp[1][0] = nums[0]>0?1:-1;
        for (int i=1;i<nums.size();i++){
            if(nums[i]==0){
                dp[0][i] = -1;
                dp[1][i] = -1;
            }else if(nums[i] > 0){
                dp[0][i] = dp[0][i-1]>=0?dp[0][i-1] + 1:-1;
                dp[1][i] = dp[1][i-1]>=0?dp[1][i-1] + 1:1;
            }else{
                dp[0][i] = dp[1][i-1]>=0?dp[1][i-1] + 1:1;
                dp[1][i] = dp[0][i-1]>=0?dp[0][i-1] + 1:-1;
            }
        }
        int ans = 0;
        for (int i=0;i<nums.size();i++){
            // cout << dp[1][i] << " ";
            ans = max(ans, dp[1][i]);
        }
        // cout<<endl;
        // for (int i=0;i<nums.size();i++){
        //     cout << dp[0][i] << " ";
        // }
        return ans;
    }
};