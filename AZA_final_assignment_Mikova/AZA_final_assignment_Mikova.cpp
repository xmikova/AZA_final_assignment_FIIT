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

struct DisjointSet
{
    int *parent;
    int depth;

    // Constructor
    void makeset(int n)
    {
        parent = new int[n + 1];

        // Every node is a parent of itself
        for (int i = 0; i <= n; i++)
            parent[i] = i;
    }

    // Path Compression
    int find(int s)
    {
        /* Make the parent of the nodes in the path
        from u--> parent[u] point to parent[u] */
        int root = s;
        while (parent[root] != root) {
            root = parent[root];
        }

        // Path Compression: Update parent pointers
        int current = s;
        while (current != root) {
            int next = parent[current];
            parent[current] = root;
            current = next;
        }

        return root;
    }

    // Makes u as parent of v.
    void merge(int u, int v)
    {
        //update the greatest available
        //free slot to u
        parent[v] = u;
    }
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

int findMaxDeadline(const std::vector<Job> &jobs, int n)
{
    int ans = INT_MIN;
    for (const Job &job : jobs)
        ans = std::max(ans, job.deadline);
    return ans;
}

int small(DisjointSet ds,int setContainingMinDeadline)
{
    return ds.find(setContainingMinDeadline);
}

bool sortByDeadline(const std::vector<int> &a, const std::vector<int> &b)
{
    // Compare the deadlines of two jobs for sorting
    return a[0] < b[0];
}

std::vector<std::vector<int>> scheduleDisjoint(const std::vector<Job> &jobs, int n)
{
    // Find the maximum deadline among all jobs and
    // create a disjoint set data structure with
    // maxDeadline disjoint sets initially.
    int maxDeadline = findMaxDeadline(jobs, n);
    DisjointSet ds;
    ds.makeset(findMaxDeadline(jobs, n));

    std::vector<std::vector<int>> result;

    // Traverse through all the jobs
    for (const Job &job : jobs)
    {
        // Find the set S containing the minimum of its deadline and n
        int setContainingMinDeadline = std::min(ds.find(job.deadline), static_cast<int>(jobs.size()));

        // If smallest member of set S is 0, reject the job
        if (small(ds, setContainingMinDeadline) == 0)
            continue;

        // Store the information in the result vector
        std::vector<int> jobInfo;
        jobInfo.push_back(small(ds, setContainingMinDeadline));
        jobInfo.push_back(job.index);
        result.push_back(jobInfo);

        // Merge S with the set containing small(S)−1
        ds.merge(ds.find(setContainingMinDeadline - 1), setContainingMinDeadline);
    }

    return result;
}

int main() {
    std::vector<Job> jobs;
    int n = static_cast<int>(jobs.size()); //vector size

    /*
    jobs.push_back(Job(2, 40, 1));
    jobs.push_back(Job(4, 15, 2));
    jobs.push_back(Job(3, 60, 3));
    jobs.push_back(Job(2, 20, 4));
    jobs.push_back(Job(3, 10, 5));
    jobs.push_back(Job(1, 45, 6));
    jobs.push_back(Job(1, 55, 7));
    */

    jobs.push_back(Job(3, 40, 1));
    jobs.push_back(Job(1, 35, 2));
    jobs.push_back(Job(1, 30, 3));
    jobs.push_back(Job(3, 25, 4));
    jobs.push_back(Job(1, 20, 5));


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

    std::vector<std::vector<int>> optimalSchedule2 = scheduleDisjoint(jobs,n);
    std::sort(optimalSchedule2.begin(), optimalSchedule2.end(), sortByDeadline);

    if (!optimalSchedule2.empty()) {
        std::cout << "Optimal Schedule J (disjoint set approach): ";
        for (const std::vector<int> &info : optimalSchedule2)
        {
            std::cout << info[1] << " ";
        }
        std::cout << std::endl;
    } else {
        std::cout << "No optimal schedule found." << std::endl;
    }

    return 0;
}

