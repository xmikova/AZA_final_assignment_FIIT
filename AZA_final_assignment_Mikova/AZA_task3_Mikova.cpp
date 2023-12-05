#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

//Greedy prístup na riešenie schedulovania jobov tak, aby sme mali vo finále minimálny cost.
vector<int> assignmentGreedy(const vector<vector<int>>& matrix) {
    int n = matrix.size();
    //Inicializujem si vektor, ktorý bude obsahovať scheduled jobs s -1, aby som vedela rozlíšiť neschedulované joby.
    //Tak isto si inicializujem vektor kde budem undržiavať informácie o tom, či už úloha bola priradená. Na začiatku je
    //celý vektor inicializovaný s false.
    vector<int> assignment(n, -1);
    vector<bool> assignedJob(n, false);

    //Pre každý riadok matice vykonávame hľadanie najmenej nákladneho jobu a ak na tejto pozícii
    //job ešte nebol schedulnutý (podmienka !assignedJob[j]), priradíme ho.
    for (int i = 0; i < n; ++i) {
        int minCost = INT_MAX;
        int assignedJobIndex = -1;

        for (int j = 0; j < n; ++j) {
            if (matrix[i][j] < minCost && !assignedJob[j]) {
                minCost = matrix[i][j];
                assignedJobIndex = j;
            }
        }

        //Update vektorov ktoré sa na začiatku inicializovali
        assignment[i] = assignedJobIndex;
        assignedJob[assignedJobIndex] = true;
    }

    return assignment;
}

/*
int main() {
    vector<vector<int>> matrix = {
            {10, 5, 5},
            {2, 4, 10},
            {5, 1, 7}
    };

    vector<int> result = assignmentGreedy(matrix);

    cout << "Assigned Jobs (greedy approach):\n";
    int totalCostGreeedy = 0;
    for (int i = 0; i < result.size(); ++i) {
        cout << "Person " << i + 1 << " assigned to job " << result[i] + 1 << " with cost " << matrix[i][result[i]]
             << "\n";
        totalCostGreeedy += matrix[i][result[i]];
    }

    cout << "Total Cost: " << totalCostGreeedy << endl;
}
*/