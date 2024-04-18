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

    tasks.push_back(Task(1, 1, 100, 1, 2, {0})); // Task 1
    tasks.push_back(Task(2, 5, 500, 2, 5, {0})); // Task 2
    tasks.push_back(Task(3, 3, 150, 3, 5, {0})); // Task 3
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


// Function to check if all dependencies are satisfied for a task
bool areDependenciesSatisfied(const Task& task, const vector<Task>& tasks, const vector<vector<int>>& dp, int availableResources) {
    for (int dependency : task.dependencies) {
        if (dp[dependency][availableResources] == 0) {
            return false; // Dependency not satisfied
        }
    }
    return true; // All dependencies satisfied
}


// Main algorithm to maximize profit
// Main algorithm to maximize profit
int maximizeProfit() {
    int n = tasks.size();

    // Create and initialize dp array
    vector<vector<int>> dp(n + 1, vector<int>(availableResources + 1, 0));

    // Sort tasks by end time
    sort(tasks.begin(), tasks.end(), [](const Task& a, const Task& b) {
        return a.endTime < b.endTime;
    });

    // Iterate over tasks
    for (int i = 1; i <= n; ++i) {
        Task task = tasks[i - 1];
        for (int r = 0; r <= availableResources; ++r) {
            // Exclude the current task if it falls outside its time window
            if (task.endTime > r) {
                dp[i][r] = dp[i - 1][r];
                continue;
            }

            // Check if resource requirement of current task can be satisfied
            if (task.resourceRequirement <= r) {
                // Include the current task only if all dependencies are satisfied
                if (areDependenciesSatisfied(task, tasks, dp, r)) {
                    dp[i][r] = max(dp[i][r], task.profit + dp[i - 1][r - task.resourceRequirement]);
                }
            }

            // Update dp table if excluding the task leads to higher profit
            dp[i][r] = max(dp[i][r], dp[i - 1][r]);
        }
    }

    // Return the maximum profit
    return dp[n][availableResources];
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
        cout << "6. Exit" << endl;
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
            maxProfit = maximizeProfit();
        
        }
        else if(option == 5){
            cout<<"Maximum Profit: "<<maxProfit<<endl;
            
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














// int main() {
//     // Initialize tasks
//     vector<Task> tasks;

//     // Add tasks to the vector with their respective attributes
//     tasks.push_back(Task(1, 10, 100, 1, 0, 20)); // Task 1
//     tasks.push_back(Task(2, 15, 150, 2, 5, 25)); // Task 2
//     tasks.push_back(Task(3, 20, 200, 3, 10, 30)); // Task 3
//     tasks.push_back(Task(4, 10, 100, 1, 15, 35)); // Task 4

//     // Initialize dependency graph
//     tasks[1].dependencies.push_back(0); // Task 2 depends on Task 1
//     tasks[2].dependencies.push_back(1); // Task 3 depends on Task 2
//     tasks[3].dependencies.push_back(2); // Task 4 depends on Task 3

//     // Display tasks and their dependencies
//     for (const auto& task : tasks) {
//         cout << "Task " << task.id << " (Duration: " << task.duration
//              << ", Profit: " << task.profit << ", Resource Requirement: " << task.resourceRequirement
//              << ", Start Time: " << task.startTime << ", End Time: " << task.endTime << ")" << endl;
        
//         cout << "Dependencies: ";
//         for (int dependency : task.dependencies) {
//             cout << dependency + 1 << " "; // Adding 1 to convert 0-indexed dependency to 1-indexed task ID
//         }
//         cout << endl << endl;
//     }

//     return 0;
// }


// void takeTaskInput() {
//     // int numTasks;
//     // cout<<"Enter how many tasks you want to add: ";
//     // cin>>numTasks;
//     // cout<<endl;
//     // int duration, profit, resourceReq, endTime;

//     // for(int i = 1; i <= numTasks; ++i) {

//     //     cout << "Enter details for Task " << i << ":" << endl;
//     //     cout << "Duration: ";
//     //     cin >> duration;
//     //     cout << "Profit: ";
//     //     cin >> profit;
//     //     cout << "Resource Requirement: ";
//     //     cin >> resourceReq;
//     //     cout << "End Time: ";
//     //     cin >> endTime;
//     //     vector<int> dependencies = takeDependencyInput(i);

//     //     tasks.push_back(Task(i, duration, profit, resourceReq, endTime, dependencies));

//     // }

//     tasks.push_back(Task(1, 1, 100, 1, 2, {0})); // Task 1
//     tasks.push_back(Task(2, 5, 500, 2, 5, {0})); // Task 2
//     tasks.push_back(Task(3, 3, 150, 3, 5, {0})); // Task 3
// }
