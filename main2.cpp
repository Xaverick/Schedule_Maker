#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Task structure
class Task {
public:
    int id;
    int duration;
    int profit;
    int resourceRequirement;
    int endTime;
    vector<int> dependencies; 
    Task(int _id, int _duration, int _profit, int _resourceRequirement, int _endTime, vector<int> _dependencies) {
        id = _id;
        duration = _duration;
        profit = _profit;
        resourceRequirement = _resourceRequirement;
        endTime = _endTime;
        dependencies = _dependencies;
    }
};


vector<Task> tasks;
int availableResources = 0;


vector<int> takeDependencyInput(int taskId) {
    int numDependencies;
    vector<int> dependencies;

    cout << "Enter number of dependencies for Task " << taskId << ": ";
    cin >> numDependencies;
    if(numDependencies > 0){
        cout << "Enter dependencies for Task " << taskId << " (space-separated task IDs): ";
        for (int i = 0; i < numDependencies; ++i) {
            int dependency;
            cin >> dependency;
            dependencies.push_back(dependency);
        }
    }
    else{
        dependencies.push_back(0);
    }

    return dependencies;
}


void takeTaskInput() {
    int numTasks;
    cout<<"Enter how many tasks you want to add: ";
    cin>>numTasks;
    cout<<endl;
    int duration, profit, resourceReq, endTime;

    for(int i = 1; i <= numTasks; ++i) {

        cout << "Enter details for Task " << i << ":" << endl;
        cout << "Duration: ";
        cin >> duration;
        cout << "Profit: ";
        cin >> profit;
        cout << "Resource Requirement: ";
        cin >> resourceReq;
        cout << "End Time: ";
        cin >> endTime;
        vector<int> dependencies = takeDependencyInput(i);

        tasks.push_back(Task(i, duration, profit, resourceReq, endTime, dependencies));

    }

}

void showInputedSchedule() {
    
    cout << "| TASK ID: |" << "| DURATION |" << "| PROFIT  |" << "| RESOURCE REQUIREMENT |" 
                << "| END TIME ||"<< " DEPENDENCIES " << endl;


    for (const auto& task : tasks) {
        cout <<"|     "<< task.id <<"    |" << "|     " << task.duration << "    |" << "|   " << task.profit << "   |" 
            <<"|           "<< task.resourceRequirement << "          |" << "|    "<< task.endTime << "     || ";

        
        for (int dependency : task.dependencies) {
            cout << dependency << " ";
        }
        cout << endl;
    }
}

void showOptimizedSchedule(vector<Task> tasks) {
    
    cout << "| TASK ID: |" << "| DURATION |" << "| PROFIT  |" << "| RESOURCE REQUIREMENT |" 
                << "| END TIME ||"<< endl;


    for (const auto& task : tasks) {
        cout <<"|     "<< task.id <<"    |" << "|     " << task.duration << "    |" << "|   " << task.profit << "   |" 
            <<"|           "<< task.resourceRequirement << "          |" << "|    "<< task.endTime << "     || ";


        cout << endl;
    }
}

// Function to check if all dependencies are satisfied for a task
bool areDependenciesSatisfied(const Task& task, const vector<Task>& tasks, const vector<vector<int>>& dp, int r) {
    for (int dep : task.dependencies) {
        if (dp[dep][r] == 0) {
            return false;
        }
    }
    return true;
}

pair<int, vector<vector<int>>> maximizeProfit() {
    int maxDuration = 5;

    // Sort tasks by their end time
    sort(tasks.begin(), tasks.end(), [](const Task& a, const Task& b) {
        return a.endTime > b.endTime;
    });

    int n = tasks.size();

    vector<vector<int>> dp(n + 1, vector<int>(maxDuration + 1, 0));

    for (int i = 1; i <= n; ++i) {
        // Iterate through each possible duration
        for (int j = 1; j <= maxDuration; ++j) {
            // Check if the current task can be completed within the deadline
            if (j >= tasks[i - 1].duration) {
                // Check if all dependencies are satisfied
                bool dependenciesSatisfied = true;
                for(int dep : tasks[i-1].dependencies){
                    if(dp[dep][j] == 0 && dep > 0){
                        dependenciesSatisfied = false;
                        break;
                    }
                }
                // Include the current task if it satisfies the resource constraint and dependencies are satisfied
                if (tasks[i - 1].resourceRequirement <= availableResources && dependenciesSatisfied) {
                    dp[i][j] = max(dp[i - 1][j], tasks[i - 1].profit + dp[i - 1][j - tasks[i - 1].duration]);
                }
            } else {
                // Exclude the current task if it can't be completed within the deadline
                dp[i][j] = dp[i - 1][j];
            }
        }
    }

    return {dp[n][maxDuration], dp};
}


vector<Task> extractOptimizedSchedule(const vector<vector<int>>& dp, const vector<Task>& tasks, int availableResources) {
    int maxDuration = dp[0].size() - 1;
    vector<Task> optimizedSchedule;

    for (int i = tasks.size(); i > 0; --i) {
        if (dp[i][maxDuration] != dp[i - 1][maxDuration]) {
            optimizedSchedule.push_back(tasks[i - 1]);
            maxDuration -= tasks[i - 1].duration;
            availableResources -= tasks[i - 1].resourceRequirement;
        }
    }

    // Reverse the schedule to maintain the original order
    reverse(optimizedSchedule.begin(), optimizedSchedule.end());

    return optimizedSchedule;
}

int main() {

    int maxProfit = 0;
    int flag = true;
    int option;
    while(flag){
        
        cout << "1. Add Task" << endl;
        cout << "2. Show Scheduled Task" << endl;
        cout << "3. Set Total Resources" << endl;
        cout << "4. Build Optimized Schedule" << endl;
        cout << "5. Show Optimized Schedule" << endl;
        cout << "6. Exit";
        cout<<endl;
        cout<<"Enter your option: ";
        cin>>option;
        cout<<endl<<endl;

        if(option == 1){
            takeTaskInput();
        }
        else if(option == 2){
            showInputedSchedule();
            
        }
        else if(option == 3){
            int totalResources;
            cout<<"Enter Total Resources: ";
            cin>>totalResources;
            availableResources = totalResources;

        }
        else if(option == 4){
            pair<int, vector<vector<int>>> result = maximizeProfit();
            maxProfit = result.first;
            cout << "Maximum Profit: " << maxProfit << endl;
            cout << "Optimized Schedule Built Successfully!" << endl;
        }
        else if(option == 5){
            if(maxProfit == 0) {
                cout << "Optimized Schedule not available. Please build it first." << endl;
            } else {
                pair<int, vector<vector<int>>> result = maximizeProfit();
                vector<Task> optimizedSchedule = extractOptimizedSchedule(result.second, tasks, availableResources);
                showOptimizedSchedule(optimizedSchedule);
            }
        }
        else if(option == 6){
            flag = false;
        }
        else{
            cout<<"Invalid Option"<<endl;
        }
    }

    return 0;
}






// tasks.push_back(Task(1, 1, 100, 1, 2, {0})); // Task 1
// tasks.push_back(Task(2, 5, 500, 2, 5, {0})); // Task 2
// tasks.push_back(Task(3, 3, 150, 3, 5, {0})); // Task 3
