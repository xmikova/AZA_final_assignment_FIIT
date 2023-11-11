#include <iostream>
#include <vector>
#include <algorithm>

class Job {
public:
    int deadline;
    int profit;
    int index;

    Job(int d, int p, int i) : deadline(d), profit(p), index(i) {}
};

bool isFeasible(const std::vector<int>& schedule, const std::vector<Job>& jobs) {
    std::vector<int> jobScheduled(jobs.size(), 0);
    int currentTime = 0;

    for (int i : schedule) {
        const Job& job = jobs[i - 1];
        if (jobScheduled[i - 1] == 0) {
            jobScheduled[i - 1] = 1;
            currentTime += job.profit;

            if (currentTime > job.deadline) {
                return false;
            }
        }
        else {
            return false;
        }
    }

    return true;
}

std::vector<int> schedule(int n, std::vector<Job>& jobs) {
    std::vector<int> J;

    for (int i = 2; i <= n; i++) {
        std::vector<Job> K = jobs;
        int j = 0;
        while (j < K.size() && jobs[i].deadline < K[j].deadline)
            j++;

        K.insert(K.begin() + j, jobs[i]);

        if (isFeasible(J, K)) {
            J.clear();
            for (const Job& job : K) {
                J.push_back(job.index);
            }
        }
    }

    return J;
}

int main() {
    int n = 5;
    std::vector<Job> jobs;
    std::vector<int> J;

    jobs.push_back(Job(2, 40, 1));
    jobs.push_back(Job(4, 15, 2));
    jobs.push_back(Job(3, 15, 3));
    jobs.push_back(Job(2, 20, 4));
    jobs.push_back(Job(3, 10, 5));

    std::sort(jobs.begin(), jobs.end(), [](const Job& a, const Job& b) {
        return a.deadline > b.deadline;
        });

    J = schedule(n, jobs);

    if (isFeasible(J, jobs)) {
        std::cout << "Optimal Schedule J: ";
        for (int job : J) {
            std::cout << job << " ";
        }
        std::cout << std::endl;
    }
    else {
        std::cout << "The schedule is not feasible." << std::endl;
    }

    return 0;
}
