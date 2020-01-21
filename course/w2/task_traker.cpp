#include <iostream>
#include <vector>
#include <string>
#include <tuple>
#include <map>

enum class TaskStatus 
{
    NEW,          // новая
    IN_PROGRESS,  // в разработке
    TESTING,      // на тестировании
    DONE          // завершена
};

// Объявляем тип-синоним для map<TaskStatus, int>,
// позволяющего хранить количество задач каждого статуса
using TasksInfo = std::map<TaskStatus, int>;

class TeamTasks
{
public:
    // Получить статистику по статусам задач конкретного разработчика
    const TasksInfo& GetPersonTasksInfo(const std::string& person) const 
    {
         return m_infos.at(person);
    }
  
    // Добавить новую задачу (в статусе NEW) для конкретного разработчитка
    void AddNewTask(const std::string& person)
    {
        m_infos[person][TaskStatus::NEW]++;
    }
  
    // Обновить статусы по данному количеству задач конкретного разработчика,
    // подробности см. ниже
    std::tuple<TasksInfo, TasksInfo> PerformPersonTasks(const std::string& person, int task_count)
    {
        TasksInfo dec;
        TasksInfo add;
        TasksInfo not_upd;

        int left = task_count;

        for (size_t e = static_cast<size_t>(TaskStatus::NEW); e != static_cast<size_t>(TaskStatus::DONE); e++)
        {
            //std::cout << ">>>> " << std::endl;
            const TaskStatus _e = static_cast<TaskStatus>(e);

            if (left == 0){
                continue;
            }
            //std::cout << ": " << left << std::endl;
            const int curr_size = m_infos[person][_e];

            int to_mod = left > curr_size ? curr_size : left;

            dec[_e] = to_mod;

            //std::cout << "status: " << e + 1  << " " << to_mod << std::endl;
            add[static_cast<TaskStatus>(e + 1)] = to_mod;

            left -= to_mod;
        }

        //std::cout << "add: " << std::endl;
        for (size_t k = static_cast<size_t>(TaskStatus::NEW); k <= static_cast<size_t>(TaskStatus::DONE); k++)
        {
            const TaskStatus _e = static_cast<TaskStatus>(k);
            
            if (_e != TaskStatus::DONE){
                not_upd[_e] = m_infos[person][_e] - dec[_e];
            }
            
            m_infos[person][_e] -= dec[_e];
            m_infos[person][_e] += add[_e];
        }

        clean_map(not_upd);
        clean_map(add);
        clean_map(m_infos[person]);

        return {add,  not_upd};
    }


    void clean_map(TasksInfo &m)
    {
        for (auto it = m.cbegin(); it != m.cend();)
        {
            if (it->second == 0)
            {
                it = m.erase(it);
            }
            else
            {
                ++it;
            }
        }
    }

private:
    std::map<std::string, TasksInfo> m_infos;
};


void PrintTasksInfo(TasksInfo tasks_info) 
{
    std::cout << tasks_info[TaskStatus::NEW] << " new tasks" <<
        ", " << tasks_info[TaskStatus::IN_PROGRESS] << " tasks in progress" <<
        ", " << tasks_info[TaskStatus::TESTING] << " tasks are being tested" <<
        ", " << tasks_info[TaskStatus::DONE] << " tasks are done" << std::endl;
}

int main() 
{
    TeamTasks tasks;
    tasks.AddNewTask("A");
    tasks.AddNewTask("A");
    tasks.AddNewTask("A");
    tasks.AddNewTask("A");
    tasks.AddNewTask("A");

    //PrintTasksInfo(tasks.GetPersonTasksInfo("A"));

    TasksInfo updated_tasks, untouched_tasks;

    std::tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("A", 5);
    std::tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("A", 5);
    std::tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("A", 1);

    //PrintTasksInfo(tasks.GetPersonTasksInfo("A"));

    tasks.AddNewTask("A");
    tasks.AddNewTask("A");
    tasks.AddNewTask("A");
    tasks.AddNewTask("A");
    tasks.AddNewTask("A");

    //PrintTasksInfo(tasks.GetPersonTasksInfo("A"));

    std::tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("A", 2);

    PrintTasksInfo(updated_tasks);
    PrintTasksInfo(untouched_tasks);

    //PrintTasksInfo(tasks.GetPersonTasksInfo("A"));

    /*std::cout << "Updated Ivan's tasks: ";
    PrintTasksInfo(updated_tasks);

    std::cout << "Untouched Ivan's tasks: ";
    PrintTasksInfo(untouched_tasks);

    std::tie(updated_tasks, untouched_tasks) =
        tasks.PerformPersonTasks("Ivan", 2);
    std::cout << "Updated Ivan's tasks: ";
    PrintTasksInfo(updated_tasks);
    std::cout << "Untouched Ivan's tasks: ";
    PrintTasksInfo(untouched_tasks);*/

    return 0;
}

/*

#include <algorithm>
#include <map>
#include <string>
#include <tuple>
#include <vector>

using namespace std;

// Выделим в отдельную функцию получение следующего по приоритету типа задачи
// Функция налагает требование на входной параметр: он не должен быть равен DONE
// При этом task_status явно не сравнивается с DONE, что позволяет
// сделать эту функцию максимально эффективной
TaskStatus Next(TaskStatus task_status) {
  return static_cast<TaskStatus>(static_cast<int>(task_status) + 1);
}

// Объявляем тип-синоним для map<TaskStatus, int>,
// позволяющего хранить количество задач каждого статуса
using TasksInfo = map<TaskStatus, int>;

class TeamTasks {
public:
  // Получить статистику по статусам задач конкретного разработчика
  const TasksInfo& GetPersonTasksInfo(const string& person) const;

  // Добавить новую задачу (в статусе NEW) для конкретного разработчика
  void AddNewTask(const string& person);

  // Обновить статусы по данному количеству задач конкретного разработчика
  tuple<TasksInfo, TasksInfo> PerformPersonTasks(
      const string& person, int task_count);

private:
  map<string, TasksInfo> person_tasks_;
};

const TasksInfo& TeamTasks::GetPersonTasksInfo(const string& person) const {
  return person_tasks_.at(person);
}

void TeamTasks::AddNewTask(const string& person) {
  ++person_tasks_[person][TaskStatus::NEW];
}

// Функция для удаления нулей из словаря
void RemoveZeros(TasksInfo& tasks_info) {
  // Соберём те статусы, которые нужно убрать из словаря
  vector<TaskStatus> statuses_to_remove;
  for (const auto& task_item : tasks_info) {
    if (task_item.second == 0) {
      statuses_to_remove.push_back(task_item.first);
    }
  }
  for (const TaskStatus status : statuses_to_remove) {
    tasks_info.erase(status);
  }
}


tuple<TasksInfo, TasksInfo> TeamTasks::PerformPersonTasks(
    const string& person, int task_count) {
  TasksInfo updated_tasks, untouched_tasks;
  
  // Здесь и далее мы будем пользоваться тем фактом, что в std::map оператор [] 
  // в случае отсутствия ключа инициализирует значение по умолчанию,
  // если это возможно.
  // std::map::operator[] ->
  // http://ru.cppreference.com/w/cpp/container/map/operator_at
  TasksInfo& tasks = person_tasks_[person];

  // Посчитаем, сколько задач каждого из статусов нужно обновить, 
  // пользуясь тем фактом, что по умолчанию enum class инциализирует значения
  // от нуля по возрастанию.
  // enum class -> http://ru.cppreference.com/w/cpp/language/enum
  for (TaskStatus status = TaskStatus::NEW;
       status != TaskStatus::DONE;
       status = Next(status)) {
    // Считаем обновлённые
    updated_tasks[Next(status)] = min(task_count, tasks[status]);
    // Считаем, сколько осталось обновить
    task_count -= updated_tasks[Next(status)];
  }

  // Обновляем статус текущих задач в соответствии с информацией об обновлённых 
  // и находим количество нетронутых
  for (TaskStatus status = TaskStatus::NEW;
       status != TaskStatus::DONE;
       status = Next(status)) {
    untouched_tasks[status] = tasks[status] - updated_tasks[Next(status)];
    tasks[status] += updated_tasks[status] - updated_tasks[Next(status)];
  }
  // По условию, DONE задачи не нужно возвращать в не обновлённых задачах
  tasks[TaskStatus::DONE] += updated_tasks[TaskStatus::DONE];

  // По условию в словарях не должно быть нулей
  RemoveZeros(updated_tasks);
  RemoveZeros(untouched_tasks);

  return {updated_tasks, untouched_tasks};
}
*/
