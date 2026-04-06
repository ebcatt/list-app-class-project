#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <limits>
//Sleep and <unistd.h> is a linux library, so we need to use a
// preprocessor directive to include the windows.h library for windows users. -Emily Catt


#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#define sleep(x) Sleep(1000 * (x))
#else
#include <unistd.h>
#endif 
using namespace std;
//Everyone please PR this program and test it out!
//Added task structure to supprot mutliple values for a givin task. Discription & Due Date.
//Added priority level by Nick
struct Task
{
   string taskDescription;
   string taskDueDate;
   string taskTag; // NEW - User Category/tag --Emily Catt
   bool isComplete = false;
   int priority;
};
// Function: displayMainMenu
// Simple main menu that displays user options using cout.
void DisplayMainMenu()
{
   cout << "\n1. Add task" << endl;
   cout << "2. View all tasks" << endl;
   cout << "3. Remove task" << endl;
   cout << "4. Mark task complete" << endl;
   cout << "5. Filter tasks by tag" << endl;
   cout << "6. Search task" << endl;
   cout << "7. Edit task" << endl;
   cout << "8. Exit" << endl;
   cout << "Enter Choice (1-8): ";
};
// Function: addTask by S
// Allows the user to type in a string for the task input, then adds the task to the vector.
void addTask(vector<Task>& tasks)
{
    Task newTask;
    cout << "Enter task description: ";
    //cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, newTask.taskDescription);
    cout << "Enter due date (ex. 09/23/2026): ";
    getline(cin, newTask.taskDueDate);
    cout << "Enter a tag of category (ex. Work, School, Personal): ";
    getline(cin, newTask.taskTag);
    cout << "Enter priority (1=High, 2=Medium, 3=Low): ";
    cin >> newTask.priority;
    while (newTask.priority < 1 || newTask.priority > 3) {
        cout << "Invalid priority entered. Please re-enter a valid priority (1=High, 2=Medium, 3=Low)." << endl;
        cin >> newTask.priority;
    };
    tasks.push_back(newTask);
    cout << "\n--- Task has been added ---" << endl;
}
/* Function: viewTasks by Emily Catt
* -------------------
* Displays all tasks currently stored in the task list.
* Parameters:
*   tasks - a vector of strings, where each string is a task
*         - If no tasks exist, prints "No tasks available." */
void viewTasks(const vector<Task>& tasks) {
   // If the vector is empty, let the user know
   if (tasks.empty()) {
       cout << "No tasks available.\n";
   }
   else {
       cout << "\n--- Current Tasks ---\n";
       // Loop through each task and display it with an index
       for (size_t i = 0; i < tasks.size(); ++i) {
           cout << i + 1 << ". " << tasks[i].taskDescription
                << " | Due: " << tasks[i].taskDueDate
                        << " | Priority: " << tasks[i].priority
                << " | Tag: " << tasks[i].taskTag // NEW Added tags -- Emily Catt
                << " | Status: " << (tasks[i].isComplete ? "[Complete]" : "[Incomplete]") << "\n";
       }
   }
}
//remove tasks by Emily Catt
//calls viewTask to displays tasks then lets the user remove a task
void removeTask(vector<Task>& tasks) {
    cout << "\n--- Remove a Task ---\n";
    viewTasks(tasks);
    cout << "Enter the number of the task to remove (0 to cancel): ";
    int index;
    cin >> index;
    if (index == 0) {
        cout << "Cancelled.\n";
        return;
    }
    if (index < 1 || index >(int)tasks.size()) {
        cout << "Invalid number.\n";
    }
    else {
        cout << "Task \n" << tasks[index - 1].taskDescription << "Due: " << tasks[index - 1].taskDueDate << "\n removed.\n";
        tasks.erase(tasks.begin() + (index - 1));
    }
}
// For PBI_14 completeTask. Allows the user to mark a task as complete. This function
// displays the current tasks then asks the user which task they would like to mark as complete.
// Some basic error handling has also been built into this.
void completeTask(vector<Task>& tasks) {
    if (tasks.empty())
    {
        cout << "No tasks available.\n";
        return;
    }
    cout << "\n--- Mark Task Complete/Incomplete ---\n";
    for (size_t i = 0; i < tasks.size(); ++i)
    {
        cout << i + 1 << ". " << tasks[i].taskDescription
            << " | Due Date: " << tasks[i].taskDueDate
            << " | Tag: " << tasks[i].taskTag
            << " | Priority: " << tasks[i].priority
            << " | Status: " << (tasks[i].isComplete ? "[Complete]" : "[Incomplete]")
            << "\n";
    }
    cout << "\nEnter the number of the task to toggle (0 to cancel): ";
    int index;
    cin >> index;
    if (index == 0)
    {
        cout << "Cancelled.\n";
        return;
    }
    if (index < 1 || index >(int)tasks.size())
    {
        cout << "Invalid number.\n";
    }
    else {
        tasks[index - 1].isComplete = !tasks[index - 1].isComplete;
        cout << "Task \"" << tasks[index - 1].taskDescription << "\" marked as "
            << (tasks[index - 1].isComplete ? "Complete.\n" : "Incomplete.\n");
    }
}
/* Function: filterByTag by Emily Catt
* Allows the user to view tasks filtered by a tag/category. */
void filterByTag(const vector<Task>& tasks) {
    if(tasks.empty()){
        cout << "No tasks available.\n";
        return;
    }
    cout << "\n--- Filter Tasks by Tag ---\n";
    cout << "Enter a tag to filter by (case-sensitive): ";
    string tagInput;
    getline(cin, tagInput);
    cout << "\n--- Tasks with Tag: " << tagInput << " ---\n";
    bool found = false;
    for (size_t i = 0; i < tasks.size(); ++i) {
        if (tasks[i].taskTag == tagInput) {
            cout << i + 1 << ". " << tasks[i].taskDescription
                 << " | Due Date: " << tasks[i].taskDueDate
                 << " | Tag: " << tasks[i].taskTag
                 << " | Priority: " << tasks[i].priority
                 << " | Status: " << (tasks[i].isComplete ? "[Complete]" : "[Incomplete]") << "\n";
            found = true;
        }
    }
    if (!found)
            cout << "No tasks found under that tag.\n";
}
void editTask(vector<Task>& tasks) 
{
    if(tasks.empty())
    {
        cout << "No Tasks available.\n";
        return;
    }
    cout << "\n--- Edit a Task ---\n";
    viewTasks(tasks);
    cout << "Enter the number of the task to edit (0 to cancel): ";
    int index;
    cin >> index;
    if(index == 0)
    {
        cout << "Cancelled.\n";
        return;
    }
    if(index < 1 || index > (int)tasks.size())
    {
        cout << "Invalid number.\n";
        return;
    }
    Task& task = tasks[index - 1];
    cout << "\nEditing task: " << task.taskDescription
         << " | Due Date: " << task.taskDueDate
         << " | Tag: " << task.taskTag
         << " | Priority: " << task.priority << endl;
    int choice;
    do {
        cout << "Choose what you would like to edit:\n";
        cout << "1. Description\n2. Due Date\n3. Priority\n4. Tag\n5. Exit\n\nEnter choice: ";
        cin >> choice;
        switch(choice) 
        {
            case 1: 
            {
                cout << "Enter new description: ";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                getline(cin, task.taskDescription);
                cout << "Description has been updated.\n";
                break;
            }
            case 2: 
            {
                cout << "Enter new due date (ex. 09/23/2026): ";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                getline(cin, task.taskDueDate);
                cout << "Due date has been updated.\n";
                break;
            }
            case 3: 
            {
                cout << "Enter new Priority (1=High, 2=Medium, 3=Low): ";
                cin >> task.priority;
                while(task.priority < 1 || task.priority > 3) 
                {
                    cout << "Invalid priority, please enter 1-3: ";
                    cin >> task.priority;
                }
                cout << "Task priority has been updated.\n";
                break;
            }
            case 4: 
            {
                cout << "Enter new tag: ";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                getline(cin, task.taskTag);
                cout << "Tag has been updated.\n";
                break;
            }
            case 5:
                cout << "Cancelled.\n";
                break;
            default:
                cout << "Invalid choice.\n";
        }
    } while (choice != 5);
}
void searchTask(const vector<Task>& tasks)
{
    if (tasks.empty())
    {
        cout << "You have no tasks.\n";
        return;
    };
    cout << "Enter a keyword to search: ";
    string keyword;
    getline(cin, keyword);
    cout << "\n--- Search Results ---\n";
    bool found = false;
    for (size_t i = 0; i < tasks.size(); ++i)
    {
        if (tasks[i].taskDescription.find(keyword) != string::npos || tasks[i].taskDueDate.find(keyword) != string::npos
            || (keyword == "1" && tasks[i].priority == 1)
            || (keyword == "2" && tasks[i].priority == 2)
            || (keyword == "3" && tasks[i].priority == 3)
            || (keyword == "high" && tasks[i].priority == 1)
            || (keyword == "medium" && tasks[i].priority == 2)
            || (keyword == "low" && tasks[i].priority == 3))
        {
            cout << i + 1 << ". " << tasks[i].taskDescription
                << " | Due Date: " << tasks[i].taskDueDate
                << " | Tag: " << tasks[i].taskTag
                << " | Priority: " << tasks[i].priority
                << " | Status: " << (tasks[i].isComplete ? "[Complete]" : "[Incomplete]")
                << "\n";
            found = true;
        }
    }
    if (!found){
        cout << "No tasks matched search.\n";
    }
}
/* Function: saveFile by CW
 * This function saves the vector of tasks to a file so that it can be referenced upon reopening the program */
void saveFile(const vector<Task>& tasks) {
    std::ofstream out("Tasks.txt");
    for (const auto& task : tasks) { //Added const becasue of cppcheck warning.
        out << task.taskDescription << ";" << task.taskDueDate << ";" << task.taskTag << ";" << task.isComplete << ";" << task.priority << "\n";
    }
}
/* Function: loadTasks by CW
 * This funciton loads any previous tasks that were entered during a previous session. */
void loadTasks(vector<Task>& tasks) {
    ifstream myFile("Tasks.txt");
    if (!myFile) {
        return;
    }
        string line;
        while (getline(myFile, line)) {
                Task t;
                string part;
                stringstream ss(line);
                
        if (!getline(ss, t.taskDescription, ';')) continue;
        if (!getline(ss, t.taskDueDate, ';')) continue;
        if(!getline(ss, t.taskTag, ';')) continue;
        if (!getline(ss, part, ';')) continue;
        t.isComplete = (part == "1");
        if (getline(ss, part, ';')) {
            try { t.priority = stoi(part); }
            catch (...) { t.priority = 2; }
        }
        else {
            t.priority = 2;
        }
        tasks.push_back(t);
    }
}
//Function: Execute Choice
//moves our switch case from main to a function
void executeChoice(int choice, vector<Task>& tasks) {
        switch(choice){
                case 1: addTask(tasks); break;
                case 2: viewTasks(tasks); break;
                case 3: removeTask(tasks); break;
                case 4: completeTask(tasks); break;
                case 5: filterByTag(tasks); break;
                case 6: searchTask(tasks); break;
                case 7: editTask(tasks); break;
                case 8:
                        cout << "Closing program..." << endl;
                        saveFile(tasks);
                        sleep(1);
                        exit(0);
                default:
                        cout << "Error: Please enter a number from 1 to 8." << endl;
                        cin >> choice;
                        executeChoice(choice, tasks);
                }
        return;
}

/*
int main() {
    vector<Task> tasks;
    loadTasks(tasks);
    int choice;
    cout << "*****************************************" << endl;
    cout << "Welcome to the awesome todo list manager!" << endl;
    cout << "*****************************************" << endl;
    while(true){
        DisplayMainMenu();
        //Prevents infinite loop if the user enters a string into the DisplayMainMenu()
        if(!(cin >> choice)) 
        {
            cout << "Please enter a number (1-8).\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        if (choice < 1 || choice > 8) 
        {
            cout << "Please enter a valid option (1-8).\n";
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // drop rest of line
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        executeChoice(choice, tasks);
    };
};
*/
