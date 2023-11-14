#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Job {
public:
    int deadline;
    int profit;
    int index;

    Job(int d, int p, int i) : deadline(d), profit(p), index(i) {}
};

vector<int> isFeasible(const vector<int>& jobSet, const vector<Job>& sortedJobs) {
    int numJobs = jobSet.size();
    vector<int> schedulingResult(numJobs, -1);
    vector<bool> timeSlotOccupied(numJobs, false);
    Job job = Job(0, 0, 0);

    for (int jobIndex = 0; jobIndex < numJobs; jobIndex++) {

        for (int i = 0; i < sortedJobs.size(); ++i) {
            if (jobSet[jobIndex] == sortedJobs[i].index){
                job = sortedJobs[i];
            }
        }

        for (int slotIndex = min(numJobs, job.deadline) - 1; slotIndex >= 0; slotIndex--) {
            if (!timeSlotOccupied[slotIndex]) {
                schedulingResult[slotIndex] = job.index;
                timeSlotOccupied[slotIndex] = true;
                break;
            }
        }
    }
    return schedulingResult;
}

vector<int> schedule(const vector<Job>& sortedJobs) {
    vector<int> jobSet;

    for (const Job& job : sortedJobs) {
        vector<int> candidateSet = jobSet;
        candidateSet.push_back(job.index);

        vector<int> feasibleSequence = isFeasible(candidateSet, sortedJobs);

        if (count(feasibleSequence.begin(), feasibleSequence.end(), -1) == 0) {
            jobSet = feasibleSequence;
        }
    }

    return jobSet;
}


int main() {
    std::vector<Job> jobs;

    /*
    jobs.push_back(Job(2, 40, 1));
    jobs.push_back(Job(4, 15, 2));
    jobs.push_back(Job(3, 60, 3));
    jobs.push_back(Job(2, 20, 4));
    jobs.push_back(Job(3, 10, 5));
    jobs.push_back(Job(1, 45, 6));
    jobs.push_back(Job(1, 55, 7));
    */

    /*
    jobs.push_back(Job(3, 40, 1));
    jobs.push_back(Job(1, 35, 2));
    jobs.push_back(Job(1, 30, 3));
    jobs.push_back(Job(3, 25, 4));
    jobs.push_back(Job(1, 20, 5));
     */

    std::sort(jobs.begin(), jobs.end(), [](const Job& a, const Job& b) {
        return a.profit > b.profit;
    });

    std::vector<int> optimalSchedule = schedule(jobs);

    if (!optimalSchedule.empty()) {
        std::cout << "Optimal Schedule J: ";
        for (int job : optimalSchedule) {
            std::cout << job << " ";
        }
        std::cout << std::endl;
    } else {
        std::cout << "No optimal schedule found." << std::endl;
    }

    return 0;
}

