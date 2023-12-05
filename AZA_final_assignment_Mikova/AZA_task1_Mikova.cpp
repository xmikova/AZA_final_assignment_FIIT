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

//Funkcia isFeasible pre funkciu schedule podľa zadania, kde si vopred definujeme koľko máme time slotov
//a postupne do nich schedulujeme jobs. Funkcia vracia vektor s už novou postupnosťou jobs.
vector<int> isFeasible(const vector<int>& jobSet, const vector<Job>& sortedJobs) {
    int numJobs = jobSet.size();
    vector<int> schedulingResult(numJobs, -1); //Výsledný vektor nainicializujeme všade s -1
    vector<bool> timeSlotOccupied(numJobs, false);
    Job job = Job(0, 0, 0);

    //V hlavnom for loope prechádzam všetky jobs ktoré mám vo vektore, ktorý posúvam funkcii ako parameter.
    for (int jobIndex = 0; jobIndex < numJobs; jobIndex++) {

        //Vo všetktých jobs ktoré máme sorted podľa profitu hľadáme tie, ktoré
        //nám funkcia schedule poslala ako kandidátov
        for (int i = 0; i < sortedJobs.size(); ++i) {
            if (jobSet[jobIndex] == sortedJobs[i].index){
                job = sortedJobs[i];
            }
        }

        //Pre každý vybratý job z kandidátov teraz prechádzam jeho možnými deadlinami spôsobom že scheduling
        //sa začína od posledného možného slotu. Ak je prázdny, vložíme tam tento job, ak nie pokračujeme.
        for (int slotIndex = min(numJobs, job.deadline) - 1; slotIndex >= 0; slotIndex--) {
            if (!timeSlotOccupied[slotIndex]) {
                schedulingResult[slotIndex] = job.index;
                timeSlotOccupied[slotIndex] = true;
                break;
            }
        }
    }

    //Vraciam tento výsledok, podľa ktorého schedule funkcia neskôr vie, či funkcia je Feasible
    return schedulingResult;
}

//Hlavná funkcia schedule, ktorí vytvára postupne vektory kandidátov na sledovanie toho, či sú feasible,
//ktorá na konci vráti optimálny finálny výsledok.
vector<int> schedule(const vector<Job>& sortedJobs) {
    vector<int> jobSet;

    //Prechádzam zosortovanými jobmi a vytváram set kandidátov
    for (const Job& job : sortedJobs) {
        vector<int> candidateSet = jobSet;
        candidateSet.push_back(job.index);

        //Checkujem feasibility
        vector<int> feasibleSequence = isFeasible(candidateSet, sortedJobs);

        //Set kandidátov je feasible iba ak nám funkcia vrátila vektor kde sa nenachádza na žiadnom mieste -1,
        //pretože to znamená, že sa nepodarilo naschedulovať všetky jobs
        if (count(feasibleSequence.begin(), feasibleSequence.end(), -1) == 0) {
            jobSet = feasibleSequence;
        }
    }

    return jobSet;
}

/*
int main() {
    std::vector <Job> jobs;

    jobs.push_back(Job(3, 40, 1));
    jobs.push_back(Job(1, 35, 2));
    jobs.push_back(Job(1, 30, 3));
    jobs.push_back(Job(3, 25, 4));
    jobs.push_back(Job(1, 20, 5));


    std::sort(jobs.begin(), jobs.end(), [](const Job &a, const Job &b) {
        return a.profit > b.profit;
    });

    std::vector<int> optimalSchedule = schedule(jobs);

    if (!optimalSchedule.empty()) {
        std::cout << "Optimal Schedule: ";
        for (int job: optimalSchedule) {
            std::cout << job << " ";
        }
        std::cout << std::endl;
    } else {
        std::cout << "No optimal schedule found." << std::endl;
    }

    return 0;
}
*/