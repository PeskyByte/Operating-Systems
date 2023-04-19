// Hashem Mohammad Al-Jarrah - section 2
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

struct process{
    string name;
    int arrival_time, processing_time;
    int response = 0 /* 1st start - arrive */,
        turnaround = 0 /* end - arrive */,
        delay = 0 /* turnaround - processing */;
};

bool comp(process a, process b){
    if (a.arrival_time == b.arrival_time)
        return a.processing_time > b.processing_time;
    return a.arrival_time < b.arrival_time;
}

bool LongestTask(process a, process b){
    if (a.processing_time == b.processing_time)
        return a.arrival_time < b.arrival_time;
    return a.processing_time > b.processing_time;
}

void LJF(vector<process> &allProcesses, int &time){
    for (int i = 0; i < allProcesses.size(); i++){

        if (i != 0 && allProcesses[i].arrival_time > time){
            time += allProcesses[i].arrival_time - time;
        }

        allProcesses[i].response = time - allProcesses[i].arrival_time;
        time += allProcesses[i].processing_time;
        allProcesses[i].turnaround = time - allProcesses[i].arrival_time;
        allProcesses[i].delay = allProcesses[i].turnaround - allProcesses[i].processing_time;

        int idx = i + 1;
        while (idx < allProcesses.size() && allProcesses[idx].arrival_time < time){
            idx++;
        }
        sort(allProcesses.begin() + i + 1, allProcesses.begin() + idx, LongestTask);
    }
}

int main()
{
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);

    int n, time = 0;
    cin >> n;
    vector<process> allProcesses;
    for (int i = 0; i < n; i++)
    {
        string s;
        cin >> s;
        int a, b;
        cin >> a >> b;
        process x;
        x.name = s;
        x.arrival_time = a;
        x.processing_time = b;
        allProcesses.push_back(x);
    }

    sort(allProcesses.begin(), allProcesses.end(), comp);
    LJF(allProcesses, time);

    string order = "";
    for (auto x : allProcesses){
        cout << x.name << ": (turnaround=" << x.turnaround << ", delay=" << x.delay << ", response=" << x.response << ")\n";
        order += x.name;
    }
    cout<<order;
    return 0;
}

/*
    Test Cases:

    5
    A 0 3
    C 4 4
    B 2 6
    D 6 5
    E 8 2

    5
    A 0 3
    C 0 4
    B 0 6
    D 0 5
    E 0 2

    5
    A 0 3
    C 4 4
    B 8 6
    D 14 5
    E 19 2

    5
    A 0 1
    C 4 1
    B 6 1
    D 8 1
    E 10 1
*/
