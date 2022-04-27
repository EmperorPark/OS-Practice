#include <iostream>
#include <algorithm>
#include <queue>
#include <cstring>

using namespace std;

typedef struct Process {
    int pid;
    int priority;
    int arrivalTime;
    int burstTime;
    int waitTime;
} Process;

struct diff_SJF
{
    bool operator()(const Process* n1, const Process* n2) {
        return n1->burstTime > n2->burstTime;
    }
};

struct diff_PS
{
    bool operator()(const Process* n1, const Process* n2) {
        return n1->priority > n2->priority;
    }
};


int numOfP;
int fullTime = 0;

void outputWT(Process* p[]);
void FCFS(Process* p[]);
void SJF(Process* p[]);
void PS(Process* p[]);
void RR(Process* p[], int timeSlice);
int diff_FCFS(const void* m, const void* n);

int main(int argc, char* argv[], char* envp[]) {

    cin >> numOfP;
    Process** p = new Process*[numOfP];

    for (int i = 0; i < numOfP; i++) {
        p[i] = new Process();
        cin >> p[i]->pid >> p[i]->priority >> p[i]->arrivalTime >> p[i]->burstTime;
        fullTime += p[i]->burstTime;
    }

    FCFS(p);
    SJF(p);
    PS(p);
    RR(p, 5);

    for (int i = 0; i < numOfP; i++) {
        delete p[i];
    }

    return 0;
}


void outputWT(Process* p[]) {

    cout << "Total burst Time: " << fullTime << endl;

    int sumWT = 0;
    for (int i = 0; i < numOfP; i++) {
        cout << "P" << p[i]->pid << " WT: " << p[i]->waitTime << endl;
        sumWT += p[i]->waitTime;
        p[i]->waitTime = 0;
    }

    cout << "AVG WT: " << (double)sumWT / (double)numOfP << endl;
}

int diff_FCFS(const void* n1, const void* n2) {
    return (*(Process**)n1)->arrivalTime > (*(Process**)n2)->arrivalTime;
}

void FCFS(Process* p[]) {
    cout << "==============FCFS==============" << endl;

    qsort(p, numOfP, sizeof(p[0]), diff_FCFS);

    cout << "Gantt chart=>" << endl;
    int cntAll = 0;
    for (int i = 0; i < numOfP; i++) {
        for (int j = 0; j < p[i]->burstTime; j++) {
            if (j == 0) p[i]->waitTime = cntAll;
            cout << p[i]->pid << " ";
            cntAll++;
        }
    }
    cout << endl;

    outputWT(p);
}

void SJF(Process* p[]) {
    cout << "==============SJF===============" << endl;

    int* tempEachBurst = new int[numOfP + 1];

    for (int i = 0; i < numOfP; i++) {
        tempEachBurst[p[i]->pid] = p[i]->burstTime;
    }

    priority_queue<Process*, vector<Process*>, diff_SJF> sjf_pq;
    int* check = new int[numOfP];
    memset(check, 0, sizeof(int) * numOfP);

    cout << "Gantt chart=>" << endl;
    for (int i = 0; i < fullTime; i++) {
        for (int j = 0; j < numOfP; j++) {
            if (check[j] != 0) continue;
            if (p[j]->arrivalTime == i) {
                sjf_pq.push(p[j]);
                check[j] = 1;
            }
        }

        if (sjf_pq.top()->burstTime == tempEachBurst[sjf_pq.top()->pid]) sjf_pq.top()->waitTime = i;

        cout << sjf_pq.top()->pid << " ";
        tempEachBurst[sjf_pq.top()->pid]--;

        if (tempEachBurst[sjf_pq.top()->pid] == 0) {
            sjf_pq.pop();
        }
    }
    cout << endl;

    outputWT(p);
}



void PS(Process* p[]) {
    cout << "===============PS===============" << endl;

    int* tempEachBurst = new int[numOfP + 1];

    for (int i = 0; i < numOfP; i++) {
        tempEachBurst[p[i]->pid] = p[i]->burstTime;
    }

    priority_queue<Process*, vector<Process*>, diff_PS> ps_pq;
    int* check = new int[numOfP];
    memset(check, 0, sizeof(int) * numOfP);

    cout << "Gantt chart=>" << endl;
    for (int i = 0; i < fullTime; i++) {
        for (int j = 0; j < numOfP; j++) {
            if (check[j] != 0) continue;
            if (p[j]->arrivalTime == i) {
                ps_pq.push(p[j]);
                check[j] = 1;
            }
        }

        if (ps_pq.top()->burstTime == tempEachBurst[ps_pq.top()->pid]) ps_pq.top()->waitTime = i;

        cout << ps_pq.top()->pid << " ";
        tempEachBurst[ps_pq.top()->pid]--;

        if (tempEachBurst[ps_pq.top()->pid] == 0) {
            ps_pq.pop();
        }
    }
    cout << endl;

    outputWT(p);
}


void RR(Process* p[], int timeSlice) {
    cout << "===============RR===============" << endl;

    qsort(p, numOfP, sizeof(p[0]), diff_FCFS);
    
    int* tempEachBurst = new int[numOfP + 1];

    for (int i = 0; i < numOfP; i++) {
        tempEachBurst[p[i]->pid] = p[i]->burstTime;
    }

    cout << "Gantt chart=>" << endl;
    int nowSlice = 0;
    int now = 0;
    for (int i = 0; i < fullTime; i++) {
        
        if (now >= timeSlice) {
            now = 0;
        }
        for (int j = now; ; j++) {
            if (j >= numOfP) j = 0;
            if (tempEachBurst[p[j]->pid] <= 0) {
                continue;
            }
            else {
                now = j;
                break;
            }
        }
        
        if (now >= timeSlice) {
            now = 0;
        }

        if (p[now]->burstTime == tempEachBurst[p[now]->pid]) p[now]->waitTime = i;
        cout << p[now]->pid << " ";
        tempEachBurst[p[now]->pid]--;
        if (tempEachBurst[p[now]->pid] <= 0) {
            nowSlice = -1;
        }
        if (nowSlice % timeSlice == timeSlice-1) {
            now++;
        }
        nowSlice++;
    }
    cout << endl;

    outputWT(p);
}