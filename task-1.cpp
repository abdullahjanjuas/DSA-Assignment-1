#include<iostream>
#include<ctime>
#include<cstdlib>

using namespace std;

class Process
{
public:
    int process_id;
    int execution_time;
    int remaining_time;
    Process* next;

    Process(int id, int exec_time)
    {
        process_id = id;
        execution_time = exec_time;
        remaining_time = exec_time;
        next = NULL;
    }
};

//Circular Linked List Methods
void insertAtTail(Process* &head, int id, int exec)
{
    //If list is empty, insert at head
    if (head == NULL)
    {
        Process* n = new Process(id, exec);
        n->next = n;
        head = n;
        return;
    }

    //For a filled list
    Process* n = new Process(id, exec);
    Process* temp = head;
    while (temp->next != head)
    {
        temp = temp->next;
    }
    temp->next = n;
    n->next = head;
}

// Deletion Function
void deleteProcess(Process* &head, int id)
{
    if (head == NULL)
        return;

    //Find the process to delete
    Process* temp = head;
    Process* prev = NULL;

    do {
        if (temp->process_id == id) {
            if (temp == head) {
                // If there's only one process
                if (temp->next == head) {
                    delete temp;
                    head = NULL;
                    return;
                }

                // Deleting the head process
                Process* tail = head;
                while (tail->next != head)
                    tail = tail->next;
                tail->next = head->next;
                head = head->next;
                delete temp;
                return;
            } else {
                //Deleting a middle or last process
                prev->next = temp->next;
                delete temp;
                return;
            }
        }

        prev = temp;
        temp = temp->next;
    } while (temp != head);
}

// Display processes and their remaining times
void display(Process* head) {
    if (head == NULL) return;
    Process* temp = head;
    do {
        cout << "Process " << temp->process_id << " - Remaining Time: " << temp->remaining_time << endl;
        temp = temp->next;
    } while (temp != head);
    cout << endl;
}

//Optinal Task
//Check if a new process arrives
bool checkNewProcess() {
    // Simulating random arrival of a new process (20% chance per cycle)
    return rand() % 5 == 0;
}

// Function to handle new process arrival
void addNewProcess(Process* &head, int &nextProcessId) {
    if (checkNewProcess()) {
        int execTime = rand() % 10 + 1;  // Assign random execution time between 1 and 10
        insertAtTail(head, nextProcessId++, execTime);
        cout << "New process with ID " << nextProcessId - 1 << " and execution time " << execTime << " arrives.\n";
    }
}

//Round robin scheduling
void roundRobin(Process* &head, int quantum) {
    if (!head) return;

    Process* current = head;
    int cycle = 1;
    int nextProcessId = 4;  // Start with ID 4 for new processes

    while (head) {
        cout << "Cycle " << cycle++ << ":\n";
        Process* temp = head;

        do {
            // Process runs for at most quantum time or less if it has less remaining time.
            if (temp->remaining_time > 0) {
                int timeAllocated = min(temp->remaining_time, quantum);
                temp->remaining_time -= timeAllocated;
                cout << "Process " << temp->process_id << " runs for " 
                     << timeAllocated << " units. Remaining time: " 
                     << temp->remaining_time << "\n";
            }

            // If the process finishes, remove it from the list.
            if (temp->remaining_time == 0) {
                cout << "Process " << temp->process_id << " completes.\n";
                Process* nextProcess = temp->next;
                deleteProcess(head, temp->process_id);  // Remove the process
                temp = nextProcess;  // Move to the next process
                break;
            } else {
                temp = temp->next;
            }
            
        } while (temp != head && head);

        // Check and handle new process arrival after every cycle
        addNewProcess(head, nextProcessId);

        // Display the state of the system after each cycle.
        if (head) {
            cout << "State of system after this cycle:\n";
            display(head);
        }
    }
}

// Main function
int main() {
    srand(time(0));  // Seed for random number generator

    Process* head = NULL;

    // Inserting initial processes
    insertAtTail(head, 1, 10);  // P1 with 10 time units
    insertAtTail(head, 2, 5);   // P2 with 5 time units
    insertAtTail(head, 3, 8);   // P3 with 8 time units

    int quantum = 3;  // Time allocated per process per cycle

    // Run Round-Robin scheduling
    roundRobin(head, quantum);

    return 0;
}
