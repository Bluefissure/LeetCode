#define LL long long
#define pb push_back
class Solution {
public:
    LL MOD = 1e9+7;
    LL fact[1005];
    void initFact(){
        LL f = 1;
        fact[0] = f;
        for (LL i=1;i<=1000;i++){
            fact[i] = (fact[i-1] * i) % MOD;
        }
    }
    void exgcd(LL a,LL b,LL& d,LL& x,LL& y){
        if(!b) { d = a; x = 1; y = 0; }
        else{ exgcd(b, a%b, d, y, x); y -= x*(a/b); }
    }
    LL inv(LL a, LL p){
        LL d,x,y;
        exgcd(a,p,d,x,y);
        return d == 1 ? (x+p)%p : -1;
    }
    LL handleSubTree(vector<int> & nums){
        if (nums.size()<=1) return 1;
        vector<int> leftT, rightT;
        for (int i=1;i<nums.size();i++){
            if (nums[i]<nums[0]) leftT.pb(nums[i]);
            else rightT.pb(nums[i]);
        }
        LL invL = leftT.size()>1?inv(fact[leftT.size()], MOD):1;
        LL invR = rightT.size()>1?inv(fact[rightT.size()], MOD):1;
        LL ans = ((fact[nums.size()-1] * invL) % MOD * invR) % MOD;
        ans = (ans * handleSubTree(leftT)) % MOD;
        ans = (ans * handleSubTree(rightT)) % MOD;
        return ans;
    }
    int numOfWays(vector<int>& nums) {
        initFact();
        return (int)((handleSubTree(nums)+MOD-1)%MOD);
    }
};