#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

//Trieda Job, ktorá udržiava infomráciu o indexe, deadline, a profite každého jobu.
class Job {
public:
    int deadline;
    int profit;
    int index;

    Job(int d, int p, int i) : deadline(d), profit(p), index(i) {}
};

//Štruktúra DisjointSet, kde si udržiavam funkcie na pracovanie s disjoint sets.
struct DisjointSet
{
    int *parent;

    //Funkcia pre inicializáciu disjoint setu.
    void makeset(int n)
    {
        parent = new int[n + 1];

        for (int i = 0; i <= n; i++)
            parent[i] = i;
    }

    //Nájdenie setu, do ktorého prvok patrí
    int find(int s)
    {
        int root = s;
        while (parent[root] != root) {
            root = parent[root];
        }

        //Path compression - aktualizácia rodičovských pointrov v ceste od daného prvku k jeho koreňu,
        // aby sa zrýchlilo následné vyhľadávanie.
        int current = s;
        while (current != root) {
            int next = parent[current];
            parent[current] = root;
            current = next;
        }
        return root;
    }

    //Zlúčenie dvoch množín
    void merge(int u, int v)
    {
        parent[v] = u;
    }
};


//Funkcia, ktorá vráti najmenšieho člena zo setu
int small(DisjointSet ds,int setContainingMinDeadline)
{
    return ds.find(setContainingMinDeadline);
}

//Funkcia vykonávajúca scheduling pomocou disjoint sets, ktorá využíva funkciu small, ktorá nám vracia
//najmenšieho člena setu. Podľa výsledku tejto funkcie viem, či job schedulovať alebo nie.
std::vector<std::vector<int>> scheduleDisjoint(const std::vector<Job> &jobs, int n)
{
    DisjointSet ds;

    //Nájdem si maximálny deadline a podľa toho vytváram disjoint sety ako je písane v zadaní
    int max = INT_MIN;
    for (const Job &job : jobs)
        max = std::max(max, job.deadline);
    ds.makeset(max);

    std::vector<std::vector<int>> result;

    for (const Job &job : jobs)
    {
        //Nájdenie setu S, ktorý obsahuje minimum(deadline,n)
        int setContainingMinDeadline = std::min(ds.find(job.deadline), static_cast<int>(jobs.size()));

        //Zavolá sa funkcia small(S) a keď je výsledok 0 tak job neschedulujem
        if (small(ds, setContainingMinDeadline) == 0)
            continue;

        //Inak si uložím výsledok (index jobu a kedy bol naschedulovaný) do vektora, ktorý budem potom eventuálne zoraďovať,
        //aby som dostala finálny výsledok
        std::vector<int> jobInfo;
        jobInfo.push_back(small(ds, setContainingMinDeadline));
        jobInfo.push_back(job.index);
        result.push_back(jobInfo);

        //Set S mergujem podľa zadania so setom, ktorý obsahuje small(S) - 1
        ds.merge(ds.find(setContainingMinDeadline - 1), setContainingMinDeadline);
    }

    return result;
}

/*
int main() {
    std::vector<Job> jobs;
    int n = static_cast<int>(jobs.size());

    jobs.push_back(Job(3, 40, 1));
    jobs.push_back(Job(1, 35, 2));
    jobs.push_back(Job(1, 30, 3));
    jobs.push_back(Job(3, 25, 4));
    jobs.push_back(Job(1, 20, 5));

    std::vector<std::vector<int>> optimalSchedule2 = scheduleDisjoint(jobs, n);
    std::sort(optimalSchedule2.begin(), optimalSchedule2.end(), [](std::vector<int> &a, const std::vector<int> &b) {
        return a[0] < b[0];
    });

    if (!optimalSchedule2.empty()) {
        std::cout << "Optimal Schedule (disjoint set approach): ";
        for (const std::vector<int> &info: optimalSchedule2) {
            std::cout << info[1] << " ";
        }
        std::cout << std::endl;
    } else {
        std::cout << "No optimal schedule found." << std::endl;
    }
}
*/