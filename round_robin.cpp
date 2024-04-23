#include <iostream>
#include <vector>
#include <queue>
#include <map>
using namespace std;

class Process
{
private:
    string name;
    int arrivalTime;
    int burstTime;

public:
    Process(string n, int at, int bt) : name(n), arrivalTime(at), burstTime(bt) {}

    string getName() const { return name; }
    int getArrivalTime() const { return arrivalTime; }
    int getBurstTime() const { return burstTime; }
};

class Scheduler
{
private:
    vector<Process> processes;
    map<string, pair<int, int>> processInfo;

public:
    Scheduler(vector<pair<string, pair<int, int>>> &v)
    {
        for (auto &p : v)
        {
            processes.push_back(Process(p.first, p.second.first, p.second.second));
            processInfo[p.first] = {p.second.first, p.second.second};
        }
    }

    vector<pair<string, int>> findTime(int timeQuantum)
    {
        int t = 0;
        queue<Process> que;
        que.push(processes[0]);
        int index = 1;
        int n = processes.size();
        vector<pair<string, int>> ans;

        while (!que.empty())
        {
            Process process = que.front();
            que.pop();
            string processName = process.getName();
            int arrivalTime = process.getArrivalTime();
            int burstTime = process.getBurstTime();

            if (t < arrivalTime)
            {
                t = arrivalTime;
            }

            if (burstTime <= timeQuantum)
            {
                t += burstTime;
                while (index < n && t >= processes[index].getArrivalTime())
                {
                    que.push(processes[index]);
                    index++;
                }
                ans.push_back({processName, t});
            }
            else
            {
                t += timeQuantum;
                while (index < n && t >= processes[index].getArrivalTime())
                {
                    que.push(processes[index]);
                    index++;
                }
                que.push(Process(processName, t, burstTime - timeQuantum));
            }
            if(que.empty()){
                if(index<n){
                    que.push(processes[index]);
                    index++;
                }
            }
        }

        return ans;
    }

    void printResults(const vector<pair<string, int>> &ans)
    {
        cout << "Processes completed within the time quantum: " << endl;
        for (const auto &process : ans)
        {
            string processName = process.first;
            int completionTime = process.second;
            int turnaroundTime = completionTime - processInfo[processName].first;
            int waitingTime = turnaroundTime - processInfo[processName].second;
            cout << "process " << processName << " completion time " << completionTime
                 << " TAT " << turnaroundTime << " wait Time " << waitingTime << endl;
        }
        cout << endl;
    }
};

int main()
{
    vector<pair<string, pair<int, int>>> v = {
        {"P1", {5, 5}},
        {"P2", {8, 4}},
        {"P3", {45, 2}},
        {"P4", {50, 1}}};

    int timeQuantum;
    cout << "Enter time quantum: ";
    cin >> timeQuantum;

    Scheduler scheduler(v);
    vector<pair<string, int>> ans = scheduler.findTime(timeQuantum);
    scheduler.printResults(ans);

    return 0;
}
