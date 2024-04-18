#include <iostream>
#include <vector>

using namespace std;

// Task structure
struct Task {
    int id;
    int duration;
    int profit;
    int resourceRequirement;
    int endTime;
    vector<int> dependencies; // Dependency graph representation

    // Constructor
    Task(int _id, int _duration, int _profit, int _resourceRequirement, int _endTime) :
        id(_id), duration(_duration), profit(_profit),
        resourceRequirement(_resourceRequirement), endTime(_endTime) {}
};



Task takeTaskInput(int taskId) {
    int duration, profit, resourceReq, endTime;

    cout << "Enter details for Task " << taskId << ":" << endl;
    cout << "Duration: ";
    cin >> duration;
    cout << "Profit: ";
    cin >> profit;
    cout << "Resource Requirement: ";
    cin >> resourceReq;
    cout << "End Time: ";
    cin >> endTime;

    return Task(taskId, duration, profit, resourceReq, endTime);
}

// Function to take input for task dependencies
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

int main() {
    int numTasks;
    vector<Task> tasks;

    // Prompt user to enter the number of tasks
    cout << "Enter the number of tasks: ";
    cin >> numTasks;

    // Take input for each task
    for (int i = 1; i <= numTasks; ++i) {
        Task task = takeTaskInput(i);
        tasks.push_back(task);
    }

    // Take input for task dependencies
    for (int i = 0; i < numTasks; ++i) {
        tasks[i].dependencies = takeDependencyInput(tasks[i].id);
    }

    // Display tasks and their dependencies
    for (const auto& task : tasks) {
        cout << "Task " << task.id << " (Duration: " << task.duration
             << ", Profit: " << task.profit << ", Resource Requirement: " << task.resourceRequirement
             << ", End Time: " << task.endTime << ")" << endl;
        
        cout << "Dependencies: ";
        for (int dependency : task.dependencies) {
            cout << dependency << " ";
        }
        cout << endl << endl;
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
