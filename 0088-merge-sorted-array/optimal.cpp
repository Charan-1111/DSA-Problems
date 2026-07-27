#include <bits/stdc++.h>

using namespace std;

void sortArrays(vector<int> &arr1, vector<int> &arr2) {
    int n = arr1.size();
    int m = arr2.size();
    
    int i = n-1;
    int j = 0;
    
    while(i >= 0 && j < m) {
        if(arr1[i] >= arr2[j]) {
            swap(arr1[i], arr2[j]);
            i--;
            j++;
        } else {
            break;
        }
    }
    
    sort(arr1.begin(), arr1.end());
    sort(arr2.begin(), arr2.end());
}

int main() {
    vector<int> arr1={1, 4, 5, 6};
    vector<int> arr2={2, 7, 8};
    
    
    sortArrays(arr1, arr2);
    
    for(int num : arr1) {
        cout << num << " ";
    }
    cout << endl;
    
    for(int num : arr2) {
        cout << num << " ";
    }
    cout << endl;
    
    return 0;
}


/*
  Time complexity - O(min(n, m)) + O(nlogn) + O(mlogm)
  Space complexity - O(1)
*/
