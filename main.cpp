#include <iostream>
#include <fstream>
#include "teamtasks.h"
using namespace std;

// Принимаем словарь по значению, чтобы иметь возможность
// обращаться к отсутствующим ключам с помощью [] и получать 0,
// не меняя при этом исходный словарь
void PrintTasksInfo(TasksInfo tasks_info) {
  cout << tasks_info[TaskStatus::NEW] << " new tasks" <<
      ", " << tasks_info[TaskStatus::IN_PROGRESS] << " tasks in progress" <<
      ", " << tasks_info[TaskStatus::TESTING] << " tasks are being tested" <<
      ", " << tasks_info[TaskStatus::DONE] << " tasks are done" << endl;
}

int main()
{
    TeamTasks* tasks = new TeamTasks();
    for(int i = 0; i < 13; i++){
        tasks->AddNewTask("Ivan");
    }
    cout << "Ivan's tasks: ";
    PrintTasksInfo(tasks->GetPersonTasksInfo("Ivan"));

    int task_count = 4;
    cout << "task_count: " << task_count << endl;
    TasksInfo updated_tasks, untouched_tasks;

    tie(updated_tasks, untouched_tasks) = tasks->PerformPersonTasks("Ivan", task_count);

//    cout << "Ivan's updated tasks: ";
//    PrintTasksInfo(updated_tasks);

//    cout << "Ivan's untouched tasks: ";
//    PrintTasksInfo(untouched_tasks);

     cout << "Ivan's tasks: ";
    PrintTasksInfo(tasks->GetPersonTasksInfo("Ivan"));


    task_count = 3;
    cout << "task_count: " << task_count << endl;

    tie(updated_tasks, untouched_tasks) = tasks->PerformPersonTasks("Ivan", task_count);

//    cout << "Ivan's updated tasks: ";
//    PrintTasksInfo(updated_tasks);

//    cout << "Ivan's untouched tasks: ";
//    PrintTasksInfo(untouched_tasks);

     cout << "Ivan's tasks: ";
    PrintTasksInfo(tasks->GetPersonTasksInfo("Ivan"));

    //
    task_count = 7;
    cout << "task_count: " << task_count << endl;

    tie(updated_tasks, untouched_tasks) = tasks->PerformPersonTasks("Ivan", task_count);
    cout << "Ivan's tasks: ";
    PrintTasksInfo(tasks->GetPersonTasksInfo("Ivan"));

    tasks->AddNewTask("Ivan");
    cout << "Ivan's tasks: ";
    PrintTasksInfo(tasks->GetPersonTasksInfo("Ivan"));

    task_count = 13;
    cout << "task_count: " << task_count << endl;

    tie(updated_tasks, untouched_tasks) = tasks->PerformPersonTasks("Ivan", task_count);
     cout << "Ivan's tasks: ";
    PrintTasksInfo(tasks->GetPersonTasksInfo("Ivan"));

    task_count = 14;
    cout << "task_count: " << task_count << endl;

    tie(updated_tasks, untouched_tasks) = tasks->PerformPersonTasks("Ivan", task_count);
     cout << "Ivan's tasks: ";
    PrintTasksInfo(tasks->GetPersonTasksInfo("Ivan"));

    return 0;
}
