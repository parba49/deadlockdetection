#include <iostream>
using namespace std;

#define MAX_PROCESSES 10
#define MAX_RESOURCES 10

int allocation[MAX_PROCESSES][MAX_RESOURCES];
int request[MAX_PROCESSES][MAX_RESOURCES];
int available[MAX_RESOURCES];
int resources[MAX_RESOURCES];
int work[MAX_RESOURCES];
int marked[MAX_PROCESSES];

int main() {
    int num_processes, num_resources;

    // Input number of processes and resources
    cout << "Enter the number of processes: ";
    cin >> num_processes;

    cout << "Enter the number of resources: ";
    cin >> num_resources;

    // Input total resources
    for (int i = 0; i < num_resources; i++) {
        cout << "Enter the total amount of Resource R" << i + 1 << ": ";
        cin >> resources[i];
    }

    // Input request matrix
    cout << "Enter the request matrix:\n";
    for (int i = 0; i < num_processes; i++) {
        for (int j = 0; j < num_resources; j++) {
            cin >> request[i][j];
        }
    }

    // Input allocation matrix
    cout << "Enter the allocation matrix:\n";
    for (int i = 0; i < num_processes; i++) {
        for (int j = 0; j < num_resources; j++) {
            cin >> allocation[i][j];
        }
    }

    // Initialize available resources
    for (int j = 0; j < num_resources; j++) {
        available[j] = resources[j];
        for (int i = 0; i < num_processes; i++) {
            available[j] -= allocation[i][j];
        }
    }

    // Initialize marked array and work vector
    for (int i = 0; i < num_processes; i++) {
        marked[i] = 0;  // Unmarked
    }

    for (int j = 0; j < num_resources; j++) {
        work[j] = available[j];  // Work = Available resources
    }

    // Try to mark processes that can be completed
    for (int i = 0; i < num_processes; i++) {
        if (marked[i] == 0) {
            bool can_be_processed = true;

            // Check if request[i] <= work, if so, process can be finished
            for (int j = 0; j < num_resources; j++) {
                if (request[i][j] > work[j]) {
                    can_be_processed = false;
                    break;
                }
            }

            if (can_be_processed) {
                marked[i] = 1;  // Mark process as completed

                // Simulate releasing resources after completing the process
                for (int j = 0; j < num_resources; j++) {
                    work[j] += allocation[i][j];  // Add allocation to work
                }
            }
        }
    }

    // Check for unmarked processes (deadlock)
    bool deadlock = false;
    for (int i = 0; i < num_processes; i++) {
        if (marked[i] == 0) {
            deadlock = true;
            break;
        }
    }

    if (deadlock) {
        cout << "Deadlock detected\n";
    } else {
        cout << "No deadlock possible\n";
    }

    return 0;
}
