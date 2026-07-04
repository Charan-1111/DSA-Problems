# Prefix Sum + Hash Map Pattern: Number of Subarrays With Sum

## Brute Force

Generate every subarray and maintain a running sum.

``` cpp
int cnt=0;
for(int i=0;i<nums.size();i++){
    int sum=0;
    for(int j=i;j<nums.size();j++){
        sum+=nums[j];
        if(sum==goal) cnt++;
    }
}
```

Time: **O(n²)**, Space: **O(1)**.

## Optimized Idea

Let `prefix[i]` be the sum from index `0` to `i`.

For a subarray `(j+1...i)`:

    subarraySum = prefix[i] - prefix[j]

To obtain `goal`:

    prefix[j] = prefix[i] - goal

Therefore, while traversing the array, we only need to know **how many
previous prefix sums equal `currentPrefix - goal`**.

## Code

``` cpp
int numSubarraysWithSum(vector<int>& nums, int goal) {
    unordered_map<int,int> mp;
    int sum=0, totalCnt=0;

    for(int x: nums){
        sum += x;

        if(sum==goal)
            totalCnt++;

        if(mp.find(sum-goal)!=mp.end())
            totalCnt += mp[sum-goal];

        mp[sum]++;
    }

    return totalCnt;
}
```

## Cleaner Version

``` cpp
unordered_map<int,int> mp;
mp[0]=1;

int sum=0, ans=0;

for(int x: nums){
    sum += x;
    ans += mp[sum-goal];
    mp[sum]++;
}
```

Initializing `mp[0]=1` automatically counts subarrays starting at index
0.

## Pattern Recognition

Use Prefix Sum + Hash Map when asked to:

-   Count subarrays with sum = K
-   Find longest subarray with sum = K
-   Binary Subarrays With Sum
-   Continuous Subarray Sum
-   Subarray Sum Equals K

## Complexity

-   Time: **O(n)**
-   Space: **O(n)**

The map stores `prefixSum -> frequency`, allowing each element to be
processed exactly once.
