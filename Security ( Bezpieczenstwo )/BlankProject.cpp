#include <iostream>
#include <vector>
#include <unordered_map>


using namespace std;

const int maximumAi = 1000000;

int sPrimeF[maximumAi + 1];


void update_LCM(int num, unordered_map<int, int>& updateExpMap) {
    int cur;
    int count;
    while (num > 1) {
        cur = sPrimeF[num];
        count = 0;
        while (num % cur == 0) {
            num = num / cur;
            count++;
        }
        updateExpMap[cur] = max(updateExpMap[cur], count);
    }



}
long long calculate_total_divisors(long long m, unordered_map<int, int>& updateExpMap) {
    long long div = 1 % m;
    for (auto& pair : updateExpMap) {
        div = (div * ((pair.second + 1) % m)) % m;
    }
    return div;
}

void compute_smallest_prime() {
    sPrimeF[1] = 1;
    for (int k = 2; k <= maximumAi; k++) {
        if (sPrimeF[k] != 0)continue;
        sPrimeF[k] = k;

        long long start = 1LL * k * k;
        for (long long i = start; i <= maximumAi; i += k) {
            if (sPrimeF[i] == 0) {
                sPrimeF[i] = k;
            }
        }
    }
}



int main()
{
    long long inputM;
    int inputN;

    cin >> inputN >> inputM;

    vector<int> vec(inputN);
    for (int k = 0; k < inputN; k++) {
        int val;
        cin >> val;
        vec[k] = val;
    }
    compute_smallest_prime();
    unordered_map<int, int>updateExpMap;
    for (int l = 0; l < inputN; l++) {
        int num = vec[l];
        update_LCM(num, updateExpMap);
    }
    long long total = calculate_total_divisors(inputM, updateExpMap);
    long long res = total - inputN;
    res %= inputM;
    if (res < 0) {
        res += inputM;
    }
    cout << res << endl;

    return 0;
}