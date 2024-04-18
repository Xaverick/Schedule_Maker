#include <iostream>
#include <vector>
#include <algorithm>

// Class to represent a task
class Task {
public:
    int id;
    int duration;
    int deadline;
    int priority;
    int startTime;

    Task(int id, int duration, int deadline, int priority)
        : id(id), duration(duration), deadline(deadline), priority(priority), startTime(0) {}
};

// Class for Dynamic Programming-based Scheduler
class DynamicScheduler {
public:
    std::vector<Task> tasks;
    std::vector<int> dpTable;

    // Function to add a task
    void addTask(int duration, int deadline, int priority) {
        tasks.emplace_back(tasks.size() + 1, duration, deadline, priority);
    }

    // Function to generate an optimized schedule using dynamic programming
    void generateScheduleDP() {
        dpTable.assign(1000, -1); // Initialize DP table with -1

        for (int i = 0; i < tasks.size(); ++i) {
            for (int j = tasks[i].deadline - 1; j >= tasks[i].duration; --j) {
                dpTable[j] = std::max(dpTable[j], dpTable[j - tasks[i].duration] + tasks[i].priority);
            }
        }

        // Backtrack to determine the optimal schedule
        int currentTime = dpTable.size() - 1;
        for (int i = tasks.size() - 1; i >= 0; --i) {
            if (currentTime >= tasks[i].duration && dpTable[currentTime] == dpTable[currentTime - tasks[i].duration] + tasks[i].priority) {
                tasks[i].startTime = currentTime - tasks[i].duration + 1;
                currentTime -= tasks[i].duration;
            }
        }
    }

    // Function to display the optimized schedule
    void displaySchedule() {
        std::cout << "Optimized Schedule:" << std::endl;
        std::cout << "Task ID\tDuration\tDeadline\tPriority\tStart Time" << std::endl;
        for (const auto& task : tasks) {
            std::cout << task.id << "\t" << task.duration << "\t\t" << task.deadline << "\t\t" << task.priority << "\t\t" << task.startTime << std::endl;
        }
        visualizeSchedule(tasks);
    }

    // Function to visualize the schedule
    void visualizeSchedule(const std::vector<Task>& tasks) {
        std::vector<std::vector<char>> timeline(24, std::vector<char>(100, '.')); // 24 hours, 100 slots

        for (const auto& task : tasks) {
            int startSlot = task.startTime * 100 / 24;
            int endSlot = (task.startTime + task.duration) * 100 / 24;
            for (int i = startSlot; i < endSlot; ++i) {
                timeline[task.startTime * 24 / 100][i] = 'X';
            }
        }

        std::cout << "\nTimeline:" << std::endl;
        for (const auto& row : timeline) {
            for (char slot : row) {
                std::cout << slot;
            }
            std::cout << std::endl;
        }
    }
};

// Class for Greedy Scheduler
// Class for Greedy Scheduler
class GreedyScheduler {
public:
    std::vector<Task> tasks;

    // Function to add a task
    void addTask(int duration, int deadline, int priority) {
        tasks.emplace_back(tasks.size() + 1, duration, deadline, priority);
    }

    // Function to sort tasks by earliest deadline first
    void sortTasksByEDF() {
        std::sort(tasks.begin(), tasks.end(), [](const Task& a, const Task& b) {
            return a.deadline < b.deadline;
        });
    }

    // Function to sort tasks by shortest duration first
    void sortTasksByDuration() {
        std::sort(tasks.begin(), tasks.end(), [](const Task& a, const Task& b) {
            return a.duration < b.duration;
        });
    }

    // Function to sort tasks by priority
    void sortTasksByPriority() {
        std::sort(tasks.begin(), tasks.end(), [](const Task& a, const Task& b) {
            return a.priority > b.priority;
        });
    }

    // Function to generate an initial schedule using Earliest Deadline First (EDF)
    void generateScheduleEDF() {
        sortTasksByEDF();
        int currentTime = 0;
        for (auto& task : tasks) {
            task.startTime = currentTime;
            currentTime += task.duration;
        }
    }

    // Function to generate an initial schedule using Round-Robin Scheduling (RR)
    void generateScheduleRR() {
        sortTasksByDuration();
        int currentTime = 0;
        for (auto& task : tasks) {
            task.startTime = currentTime;
            currentTime += task.duration;
        }
    }

    // Function to generate an initial schedule using Deadline-Based Scheduling
    void generateScheduleDeadline() {
        sortTasksByPriority(); // Sort by priority to ensure higher priority tasks are scheduled first
        int currentTime = 0;
        for (auto& task : tasks) {
            task.startTime = currentTime;
            currentTime += task.duration;
        }
    }

    // Function to generate an initial schedule using Shortest Job Next (SJN)
    void generateScheduleSJN() {
        sortTasksByDuration(); // Sort by duration to schedule shorter tasks first
        int currentTime = 0;
        for (auto& task : tasks) {
            task.startTime = currentTime;
            currentTime += task.duration;
        }
    }

    // Function to display the initial schedule generated by Earliest Deadline First (EDF)
    void displayScheduleEDF() {
        std::cout << "Initial Schedule using Earliest Deadline First (EDF):" << std::endl;
        std::cout << "Task ID\tDuration\tDeadline\tPriority\tStart Time" << std::endl;
        for (const auto& task : tasks) {
            std::cout << task.id << "\t" << task.duration << "\t\t" << task.deadline << "\t\t" << task.priority << "\t\t" << task.startTime << std::endl;
        }
        visualizeSchedule(tasks);
    }

    // Function to display the initial schedule generated by Round-Robin Scheduling (RR)
    void displayScheduleRR() {
        std::cout << "Initial Schedule using Round-Robin Scheduling (RR):" << std::endl;
        std::cout << "Task ID\tDuration\tDeadline\tPriority\tStart Time" << std::endl;
        for (const auto& task : tasks) {
            std::cout << task.id << "\t" << task.duration << "\t\t" << task.deadline << "\t\t" << task.priority << "\t\t" << task.startTime << std::endl;
        }
        visualizeSchedule(tasks);
    }

    // Function to display the initial schedule generated by Deadline-Based Scheduling
    void displayScheduleDeadline() {
        std::cout << "Initial Schedule using Deadline-Based Scheduling:" << std::endl;
        std::cout << "Task ID\tDuration\tDeadline\tPriority\tStart Time" << std::endl;
        for (const auto& task : tasks) {
            std::cout << task.id << "\t" << task.duration << "\t\t" << task.deadline << "\t\t" << task.priority << "\t\t" << task.startTime << std::endl;
        }
        visualizeSchedule(tasks);
    }

    // Function to display the initial schedule generated by Shortest Job Next (SJN)
    void displayScheduleSJN() {
        std::cout << "Initial Schedule using Shortest Job Next (SJN):" << std::endl;
        std::cout << "Task ID\tDuration\tDeadline\tPriority\tStart Time" << std::endl;
        for (const auto& task : tasks) {
            std::cout << task.id << "\t" << task.duration << "\t\t" << task.deadline << "\t\t" << task.priority << "\t\t" << task.startTime << std::endl;
        }
        visualizeSchedule(tasks);
    }

    // Function to visualize the schedule
    void visualizeSchedule(const std::vector<Task>& tasks) {
        std::vector<std::vector<char>> timeline(24, std::vector<char>(100, '.')); // 24 hours, 100 slots

        for (const auto& task : tasks) {
            int startSlot = task.startTime * 100 / 24;
                        int endSlot = (task.startTime + task.duration) * 100 / 24;
            for (int i = startSlot; i < endSlot; ++i) {
                timeline[task.startTime * 24 / 100][i] = 'X';
            }
        }

        std::cout << "\nTimeline:" << std::endl;
        for (const auto& row : timeline) {
            for (char slot : row) {
                std::cout << slot;
            }
            std::cout << std::endl;
        }
    }
};




// Console Interface
class ConsoleInterface {
public:
    // Function to display the main menu
    void displayMenu() {
        std::cout << "===== Dynamic Programming-based Scheduling Optimizer =====" << std::endl;
        std::cout << "1. Add Task" << std::endl;
        std::cout << "2. Generate Schedule using Dynamic Programming" << std::endl;
        std::cout << "3. Generate Initial Schedule using Greedy Algorithms" << std::endl;
        std::cout << "4. Exit" << std::endl;
    }

    // Function to get user input for task details
    Task getTaskDetails() {
        int duration, deadline, priority;
        std::cout << "Enter Task Duration: ";
        std::cin >> duration;
        std::cout << "Enter Task Deadline: ";
        std::cin >> deadline;
        std::cout << "Enter Task Priority: ";
        std::cin >> priority;
        return Task(0, duration, deadline, priority);
    }
};

int main() {
    ConsoleInterface console;
    DynamicScheduler dynamicScheduler;
    GreedyScheduler greedyScheduler;

    int choice;
    do {
        console.displayMenu();
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1: {
                Task task = console.getTaskDetails();
                dynamicScheduler.addTask(task.duration, task.deadline, task.priority);
                greedyScheduler.addTask(task.duration, task.deadline, task.priority);
                break;
            }
            case 2: {
                dynamicScheduler.generateScheduleDP();
                dynamicScheduler.displaySchedule();
                break;
            }
            case 3: {
                greedyScheduler.generateScheduleEDF();
                greedyScheduler.displayScheduleEDF();
                greedyScheduler.generateScheduleRR();
                greedyScheduler.displayScheduleRR();
                greedyScheduler.generateScheduleDeadline();
                greedyScheduler.displayScheduleDeadline();
                greedyScheduler.generateScheduleSJN();
                // Display initial schedules generated by greedy algorithms
                break;
            }
            case 4: {
                std::cout << "Exiting program..." << std::endl;
                break;
            }
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
        }
    } while (choice != 4);

    return 0;
}
