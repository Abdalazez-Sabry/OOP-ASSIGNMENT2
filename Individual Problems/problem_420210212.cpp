#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <cmath>
#include <map>

using namespace std;

vector<string> excuteCmdCommand(string command);
int getNewlineIndex(string s);
vector<string> getWords(string& s);

class Process{
    public:
        string name;
        int pid;
        string sessionName;
        int sessionNum;
        int memUsage;

        void print(){
            cout << left << setw(30) << setfill(' ') << name ;
            cout << right << setw(20) << setfill(' ') << pid;
            cout << " ";
            cout << left << setw(20) << setfill(' ') << sessionName;
            cout << right << setw(15) << setfill(' ') << sessionNum;
            cout << right << setw(15) << setfill(' ') <<  memUsage  << "K" << endl;
        }

        string operator[](string key){
            map<string, int> m = {pair<string, int>("name", 0), pair<string, int>("pid", 1),
            pair<string, int>("sessionName", 2), pair<string, int>("sessionNum", 3), pair<string, int>("memUsage", 4)};

            switch (m[key]){
                case 0:
                    return name;break;
                case 1:
                    return to_string(pid);break;
                case 2:
                    return sessionName;break;
                case 3:
                    return to_string(sessionNum);break;
                case 4:
                    return to_string(memUsage);break;
            }
        }
};

class TaskManager{
    private:
        vector<Process> processes;

        void excuteTasklistCommand(){
            vector<string> cmdOutput = excuteCmdCommand("tasklist");
            removeUnwantedLines(cmdOutput);

            for (string line : cmdOutput){
                saveProcessesInfo(line);
            }
        }

        void removeUnwantedLines(vector<string>& v){
            v.erase(v.begin());
            v.erase(v.begin());
            v.erase(v.begin());
            v.pop_back();
            v.pop_back();
        }

        void saveProcessesInfo(string line){
            vector<string> s = getWords(line);
            if (s[4].find(',') != string::npos){
                s[4].erase(s[4].find(","), 1);
            }

            for (int i = 0; i < processes.size(); i++){
                if (processes[i].name == s[0]){
                    processes[i].memUsage += stoi(s[4]);
                    return;
                }
            }
            Process p{s[0], stoi(s[1]), s[2], stoi(s[3]), stoi(s[4])};
            processes.push_back(p);
        }

        void insertionSort(vector<Process>& v, string key){
            for (int i = 1; i < v.size(); i++){
                int j = i - 1;
                int temp = i;
                while (j >= 0 && isBiggerThanString(v[i][key], v[j][key])){
                    Process temp = v[i];
                    v[i] = v[j];
                    v[j] = temp;

                    i--;
                    j--;
                }
                i = temp;
            }
        }
        bool isBiggerThanString(string first, string second){
            if (isdigit(first[0])){
                return stoi(first) < stoi(second); 
            }else{
                int loopLimit = (first.size() > second.size())? second.size() : first.size();
                for (int i = 0; i < loopLimit; i++){
                    if(tolower(first[i]) == tolower(second[i])){
                        continue;
                    }else{
                        return (tolower(first[i]) < tolower(second[i]));
                    } 
                }
            }    
        return false;
        }

    public:
        TaskManager(){
            excuteTasklistCommand();
        }
        void print(){
            cout << left << setw(30) << setfill(' ') << "Name" ;
            cout << right << setw(20) << setfill(' ') << "PID";
            cout << " ";
            cout << left << setw(20) << setfill(' ') << "Session Name";
            cout << right << setw(15) << setfill(' ') << "Session#";
            cout << right << setw(15) << setfill(' ') <<  "Mem Usage" << endl;
            cout << right << setw(110) << setfill('=') << "" << endl; 

            for (Process p : processes){
                p.print();
            }
        }
        void sortByName(){
            insertionSort(processes, "name");
        }
        void sortByPid(){
            insertionSort(processes, "pid");
        }
        void sortByMemory(){
            insertionSort(processes, "memUsage");
        }

};

vector<string> excuteCmdCommand(string command){
    const char* resultFileName = "tasklist.txt";
    vector<string>result;

    system((command + ">" + resultFileName).c_str());
    ifstream resultFile(resultFileName);
    while (resultFile){
        string line;
        getline(resultFile, line);
        result.push_back(line);
    }
    resultFile.close();
    remove(resultFileName);
    return result;
}

string removePrefixSpaces(string &s){
    for (int i = 0; i < s.size(); i++){
        if (s[i] == ' '){
            s.erase(i, 1);
            i--;
        }else{
            break;
        }
    }
}

vector<string> getWords(string& s){
    vector<string> result;
    string name = s.substr(0, s.find("  "));
    s = s.substr(name.size(), s.size());
    result.push_back(name);
    removePrefixSpaces(s);
    for (int i = 0; i < 4; i++){
        string current = s.substr(0, s.find(" "));
        s = s.substr(current.size(),  s.size());
        removePrefixSpaces(s);
        result.push_back(current);
    }
    return result;
}

int main(){
    TaskManager taskManager;
    cout << "Sorted by Memory:\n" << endl;
    taskManager.sortByMemory();
    taskManager.print();

    cout << "\n\nSorted by name:\n" << endl;
    taskManager.sortByName();
    taskManager.print();

    cout << "\n\nSorted by PID:\n" << endl;
    taskManager.sortByPid();
    taskManager.print();
}