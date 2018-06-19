#ifndef TEAMTASKS_H
#define TEAMTASKS_H
#include <map>
#include <vector>
#include "D:/Main/nlohmann_json_release/json.hpp"
using json = nlohmann::json;
using namespace std;

// Перечислимый тип для статуса задачи
enum class TaskStatus {
  NEW,          // новая
  IN_PROGRESS,  // в разработке
  TESTING,      // на тестировании
  DONE          // завершена
};

// Объявляем тип-синоним для map<TaskStatus, int>,
// позволяющего хранить количество задач каждого статуса
using TasksInfo = map<TaskStatus, int>;


class TeamTasks
{
public:
    TeamTasks();
public:
  // Получить статистику по статусам задач конкретного разработчика
  const TasksInfo& GetPersonTasksInfo(const string& person) const;

  // Добавить новую задачу (в статусе NEW) для конкретного разработчитка
  void AddNewTask(const string& person);

  // Обновить статусы по данному количеству задач конкретного разработчика,
  // подробности см. ниже
    tuple<TasksInfo, TasksInfo> PerformPersonTasks(const string& person, int task_count);

private:
  struct Person{
      string personName;
      TasksInfo tasks;
  };
  vector<Person> developers;
  void setPersonTasks(const TasksInfo& tasks, const string& person);
  void applyTasks(tuple<TasksInfo, TasksInfo, string> &cortege);
};


#endif // TEAMTASKS_H
