class Solution
{
public:
    bool containsPattern(vector<int> &arr, int m, int k)
    {
        for (int i = 0; i < arr.size() - m * (k - 1); i++)
        {
            bool same_ptn = true;
            for (int j = 0; j < m; j++)
            {
                for (int jk = 0; jk < k; jk++)
                {
                    if (arr[i + j + m * jk] != arr[i + j])
                    {
                        same_ptn = false;
                        break;
                    }
                }
                if (!same_ptn)
                    break;
            }
            if (same_ptn)
                return true;
        }
        return false;
    }
};