#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>

using namespace std;


// A class to represent a task;
class Task{
private:
    string description;
    bool isCompleted;
public:
    Task(string desc = "",bool status = false): description(desc),isCompleted(status){}

    string getDescription() const{
        return description;
    }    

    bool getStatus() const{
        return isCompleted;
    }

    void markCompleted(){
        isCompleted=true;
    }

    void setDescription(const string& desc){
        description = desc;
    }

    void setStatus(bool status){
        isCompleted = status;
    }

};

class ToDoList{
private:
    Task *tasks[100];  //It can hold upto 100 tasks
    int taskCount;

    void loadFromFile(){
        ifstream infile("tasks.txt");
        if(!infile){
            cerr<<" Could not open the file for reading! "<<endl;
            return;
        }

        string description;
        bool status;
        taskCount=0;
        while(infile>> std::ws && getline(infile,description)){
            infile>> status;
            tasks[taskCount++]= new Task(description,status);
        }
        infile.close();
    }

    void saveToFile() const{
        ofstream outfile("tasks.txt");
        if(!outfile){
            cerr << "Could not open the file for writing!" << endl;
            return;
        }
        for (int i = 0; i < taskCount; i++){
            outfile<< tasks[i]->getDescription()<<endl;
            outfile<< tasks[i]->getStatus()<<endl;
            }
            outfile.close();
    }

public:

    ToDoList(): taskCount(0){
        loadFromFile();
    }

    ~ToDoList(){
        for (int i = 0; i < taskCount; i++) {
            delete tasks[i];
        }
        }

    void addTask(const string& description){
        if(taskCount<100){
            tasks[taskCount++]= new Task(description);
            cout<<"Task added Successfully."<<endl;
            saveToFile();
        }
        else{
            cout<<"Task list is full. Cannot add more tasks."<<endl;
        }
    }

    void markTaskCompleted(int taskNumber){
        if(taskNumber>0&& taskNumber<= taskCount){
            tasks[taskNumber-1]->markCompleted();
            cout<<"Task marked as completed."<<endl;
            saveToFile();
        }
        else{
            cout<<"Invalid task number."<<endl;
        }
    }
    

    void removeTask(int taskNumber) {
        if (taskNumber > 0 && taskNumber <= taskCount) {
            delete tasks[taskNumber - 1];
            for (int i = taskNumber; i < taskCount; ++i) {
                tasks[i - 1] = tasks[i];
            }
            taskCount--;
            cout << "Task removed successfully." << endl;
            saveToFile();
        } else {
            cout << "Invalid task number." << endl;
        }
    }

    void viewTasks() const{
        if(taskCount==0){
            cout<<"No tasks available."<<endl;
            return;
        }

cout << "\nCurrent Tasks:\n";
        cout << left << setw(5) << "No." << setw(50) << "Description" << setw(15) << "Status" << endl;
        cout << "---------------------------------------------------------------" << endl;

        for (int i = 0; i < taskCount; ++i) {
            cout << left << setw(5) << i + 1 
                 << setw(50) << tasks[i]->getDescription()
                 << setw(15) << (tasks[i]->getStatus() ? "Completed" : "Not Completed") 
                 << endl;
        }        
    }
};

// Function declarations
void showMenu();
void handleMenuChoice(ToDoList& toDoList, int choice);

int main() {
    ToDoList toDoList;
    int choice;

    while (true) {
        showMenu();
        cin >> choice;
        handleMenuChoice(toDoList, choice);
    }

    return 0;
}

void showMenu() {
    cout << "\nTo-Do List Application\n";
    cout << "1. Add Task\n";
    cout << "2. Mark Task as Completed\n";
    cout << "3. View Tasks\n";
    cout << "4. Remove Task\n";
    cout << "5. Exit\n";
    cout << "Enter your choice: ";
}

void handleMenuChoice(ToDoList& toDoList, int choice) {
    switch (choice) {
        case 1: {
            cout << "Enter the description of the task: ";
            cin.ignore(); // To ignore the newline character left in the buffer
            string description;
            getline(cin, description);
            toDoList.addTask(description);
            break;
        }
        case 2: {
            cout << "Enter the task number to mark as completed: ";
            int taskNumber;
            cin >> taskNumber;
            toDoList.markTaskCompleted(taskNumber);
            break;
        }
        case 3:
            toDoList.viewTasks();
            break;
        case 4: {
            cout << "Enter the task number to remove: ";
            int taskNumber;
            cin >> taskNumber;
            toDoList.removeTask(taskNumber);
            break;
        }
        case 5:
            cout << "Exiting..." << endl;
            exit(0);
        default:
            cout << "Invalid choice. Please try again." << endl;
    }
}