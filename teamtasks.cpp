#include "teamtasks.h"
#include <iostream>

TeamTasks::TeamTasks()
{
}

const TasksInfo &TeamTasks::GetPersonTasksInfo(const string &person) const
{
    for(auto& i_person: developers){
        if(i_person.personName == person){
            return i_person.tasks;
        }
    }
}

void TeamTasks::AddNewTask(const string &person)
{
    bool isPersonExists = false;
    pair<TaskStatus, int> newIssue = make_pair(TaskStatus::NEW, 1);

    for(auto& i_person: developers){
        if(i_person.personName == person){
            if(i_person.tasks.count(TaskStatus::NEW) == 0){
                i_person.tasks.insert(newIssue);
            } else {
                i_person.tasks[TaskStatus::NEW] = ++i_person.tasks.at(TaskStatus::NEW);
            }
            isPersonExists =true;
          //  cout << "if#1" << endl;
            break;
        }
    }
    if(!isPersonExists){
        Person newDev;
        newDev.personName = person;
        newDev.tasks.insert(newIssue);
        developers.push_back(newDev);
      //  cout << "if#2" << endl;
    }
}

tuple<TasksInfo, TasksInfo> TeamTasks::PerformPersonTasks(const string &person,
                                                          int task_count)
{
    TasksInfo developerTasks = GetPersonTasksInfo(person);
    //тестирующий код
    //developerTasks = {{TaskStatus::NEW, 3},{TaskStatus::IN_PROGRESS, 2},
    //                  {TaskStatus::TESTING, 4},{TaskStatus::DONE, 1}};
    //
    if(developerTasks.find(TaskStatus::IN_PROGRESS) == developerTasks.end()){
        developerTasks[TaskStatus::IN_PROGRESS] = 0;
    }
    if(developerTasks.find(TaskStatus::TESTING) == developerTasks.end()){
        developerTasks[TaskStatus::TESTING] = 0;
    }
    if(developerTasks.find(TaskStatus::DONE) == developerTasks.end()){
        developerTasks[TaskStatus::DONE] = 0;
    }
    if(task_count <= 0){
        return{};
    }
    TasksInfo updatedDeveloperTasks;
    TasksInfo remainedDeveloperTasks;

    int previous_item_second = 0;
    int task_count_for_remain = task_count;
    for(const auto& item: developerTasks){
        if(item.first == TaskStatus::NEW){
            previous_item_second = item.second;
            int rem = 0;
            rem = item.second - task_count_for_remain > 0 ?
                       item.second - task_count_for_remain: 0;
            if(rem > 0){
                remainedDeveloperTasks[item.first] = rem;
            }
            task_count_for_remain = task_count_for_remain - item.second > 0 ?
                        task_count_for_remain - item.second : 0 ;
            continue;
        }
        int upd = task_count - previous_item_second > 0 ?
                    previous_item_second : task_count;
        int rem = item.second - task_count_for_remain > 0 ?
                    item.second - task_count_for_remain : 0;
        if(upd > 0){
            updatedDeveloperTasks[item.first] = upd;
            remainedDeveloperTasks[item.first] = rem;
        } else {
            break;
        }
        task_count = task_count - previous_item_second > 0 ?
                    task_count - previous_item_second : 0 ;
        task_count_for_remain = task_count_for_remain - item.second > 0 ?
                    task_count_for_remain - item.second : 0 ;
        previous_item_second = item.second;
    }
    //применяем изменения к разработчику
    tuple<TasksInfo, TasksInfo, string> t = tie(updatedDeveloperTasks,
                                                 remainedDeveloperTasks, person);
    applyTasks(t);
    //
    return tie(updatedDeveloperTasks, remainedDeveloperTasks);
}


 void TeamTasks::applyTasks(tuple<TasksInfo, TasksInfo, string>& cortege)
{
    TasksInfo newPersonTasks;

    TasksInfo updated, untouched;
    string personName;
    tie(updated, untouched, personName) = cortege;

    TasksInfo oldPersonTasks;
    oldPersonTasks = GetPersonTasksInfo(personName);

    if(oldPersonTasks.find(TaskStatus::IN_PROGRESS) == oldPersonTasks.end()){
        oldPersonTasks[TaskStatus::IN_PROGRESS] = 0;
    }
    if(oldPersonTasks.find(TaskStatus::TESTING) == oldPersonTasks.end()){
        oldPersonTasks[TaskStatus::TESTING] = 0;
    }
    if(oldPersonTasks.find(TaskStatus::DONE) == oldPersonTasks.end()){
        oldPersonTasks[TaskStatus::DONE] = 0;
    }

    std::map<TaskStatus, int>::const_iterator it = oldPersonTasks.begin();
    while(it != oldPersonTasks.end()){
        TaskStatus currentStatus = (*it).first ;
        int upd = untouched[currentStatus] + updated[currentStatus];
        if(upd > 0)
            newPersonTasks[currentStatus] = upd;
        it++;
    }

    setPersonTasks(newPersonTasks, personName);
    return;
}


 void TeamTasks::setPersonTasks(const TasksInfo &tasks, const string &person)
 {
     unsigned i = 0;
     bool isExists = false;
     for(auto& i_person: this->developers){

         if(i_person.personName == person){
            isExists = true;
            break;
         }
         i++;
     }
     if(isExists) this->developers[i].tasks = tasks;
     return;
 }


