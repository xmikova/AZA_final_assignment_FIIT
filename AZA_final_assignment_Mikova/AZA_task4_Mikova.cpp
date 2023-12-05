#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

//Dynamic prístup na riešenie schedulovania jobov tak, aby sme mali vo finále minimálny cost.
vector<int> assignmentDynamic(const vector<vector<int>>& matrix) {
    int n = matrix.size(); //Veľkosť matice

    //Inicializácia tabuľky dp ktorá je používaná pri dynamic prístupe
    vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));

    //Prechádzam celú maticu
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            dp[i][j] = INT_MAX;
            for (int k = 1; k <= i; ++k) {
                //Minimálna hodnota pre danú pozíciu v tabuľke dp
                dp[i][j] = min(dp[i][j], matrix[k - 1][j - 1] + dp[i - k][j - 1]);
            }
        }
    }

    //Inicializácia vektorov, v assignedJobs udržiavam informácie o tom ktoré už boli priradené a do assignments
    //pridávam už finálne výsledky
    vector<bool> assignedJob(n, false);
    vector<int> assignments;
    int remainingWorkers = n;

    //Rekonštrukcia priradení z tabuľky dp (bottom-up prístup)
    for (int j = n; j > 0; j--) {
        int bestAssignment = -1;
        for (int k = 0; k < n; k++) {
            //Nájdenie najlepšieho priradenia pre daný job
            if (!assignedJob[k] && (bestAssignment == -1 || dp[remainingWorkers][j] == matrix[k][j - 1] + dp[remainingWorkers - k - 1][j - 1])) {
                bestAssignment = k;
            }
        }

        //Ak sa podarilo nájsť v predchádzajúcej časti priradenie
        if (bestAssignment != -1) {
            assignedJob[bestAssignment] = true;
            assignments.push_back(bestAssignment);
            remainingWorkers--;
        }
    }

    return assignments;
}


int main() {
    vector<vector<int>> matrix = {
            {10, 5, 5},
            {2, 4, 10},
            {5, 1, 7}
    };

    vector<int> assignments = assignmentDynamic(matrix);

    int totalCostDynamic = 0;
    for (int i = 0; i < assignments.size(); ++i) {
        cout << "Person " << i + 1 << " assigned to Job " << assignments[i] + 1 << " with cost " << matrix[i][assignments[i]] << "\n";
        totalCostDynamic += matrix[i][assignments[i]];
    }

    cout << "Total Cost: " << totalCostDynamic << endl;

    return 0;
}
