#include <iostream>
#include <climits>
#include <vector>

using namespace std;


pair<vector<int>, vector<int>> probHelper(int& position, const string& str) {
    vector<int> greenMinimum(3);
    vector<int> greenMaximum(3);
    char node = str[position++];
    if (node == '0') {
        greenMaximum = { 0,1,0 };
        greenMinimum = { 0,1,0 };
        return { greenMinimum,greenMaximum };
    }
    if (node == '1') {
        pair<vector<int>, vector<int>> nodeChild = probHelper(position, str);
        for (int k = 0; k < 3; k++) {
            int tmpMax = INT_MIN;
            int tmpMin = INT_MAX;
            for (int j = 0; j < 3; j++) {
                if (k == j) {
                    continue;
                }
                int countG = 0;
                if (k == 1) {
                    countG++;
                }
                if (nodeChild.second[j] + countG > tmpMax) {
                    tmpMax = nodeChild.second[j] + countG;
                }
                if (nodeChild.first[j] + countG < tmpMin) {
                    tmpMin = nodeChild.first[j] + countG;
                }

            }
            greenMaximum[k] = tmpMax;
            greenMinimum[k] = tmpMin;
        }
        return { greenMinimum,greenMaximum };
    }
    if (node == '2') {
        pair<vector<int>, vector<int>> leftChild = probHelper(position, str);
        pair<vector<int>, vector<int>> rightChild = probHelper(position, str);
        for (int k = 0; k < 3; k++) {
            int tmpMax = INT_MIN;
            int tmpMin = INT_MAX;
            for (int j = 0; j < 3; j++) {
                if (k == j) {
                    continue;
                }
                for (int c = 0; c < 3; c++) {
                    if (c == j || c == k) {
                        continue;
                    }
                    int countToAdd = 0;
                    if (k == 1) {
                        countToAdd = 1;
                    }
                    if (leftChild.second[j] + rightChild.second[c]+ countToAdd > tmpMax) {
                        tmpMax = leftChild.second[j] + rightChild.second[c]+ countToAdd;
                    }
                    if (leftChild.first[j] + rightChild.first[c]+ countToAdd < tmpMin) {
                        tmpMin = leftChild.first[j] + rightChild.first[c]+ countToAdd;
                    }
                }
            }
            greenMaximum[k] = tmpMax;
            greenMinimum[k] = tmpMin;
        }
        return { greenMinimum,greenMaximum };

    }
    return { greenMinimum,greenMaximum };
    

}


int main()
{
    int position = 0;
    string str;
    cin >> str;
    
    pair<vector<int>, vector<int>> final = probHelper(position, str);
    int minRes = INT_MAX;
    int maxRes = INT_MIN;
    
    for (int c = 0; c < 3; c++) {
        maxRes = max(final.second[c], maxRes);
        minRes = min(final.first[c], minRes);
    }

    cout << maxRes << " " << minRes << "\n";
    return 0;
}