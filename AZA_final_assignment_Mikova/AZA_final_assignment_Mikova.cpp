#include <iostream>
#include <vector>

void schedule(int n, const std::vector<int>& deadline, std::vector<int>& J) {
    J.clear();
    J.push_back(1);

    for (int i = 2; i <= n; i++) {
        std::vector<int> K = J;
        int j = 0;
        while (j < K.size() && deadline[i] < deadline[K[j]])
            j++;

        K.insert(K.begin() + j, i);

        if (isFeasible(K, deadline)) {
            J = K;
        }
    }
}

int main()
{
    int n = 5;
    std::vector<int> deadline = { 2, 4, 3, 2, 3, 1, 1 };
    std::vector<int> profit = { 40, 15, 15, 20, 10, 45, 55 };
    std::vector<int> J;
    std::vector<int> sortedDeadline;


    std::vector<std::pair<int, int>> jobs;
    for (int i = 0; i < n; i++) {
        jobs.push_back(std::make_pair(deadline[i], profit[i]));
    }

    std::sort(jobs.begin(), jobs.end(), [](const std::pair<int, int>& a, const std::pair<int, int>& b) {
        return a.first > b.first;
        });

    for (const auto& job : jobs) {
        sortedDeadlines.push_back(job.first);
    }

    // Pass the sorted deadlines to the schedule function
    schedule(n, sortedDeadlines, J);


	cout << "Hello CMake." << endl;
	return 0;
}
