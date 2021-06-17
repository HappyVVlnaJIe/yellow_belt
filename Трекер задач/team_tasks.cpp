#include <iostream>
#include <map>

using namespace std;

//// Перечислимый тип для статуса задачи
//enum class TaskStatus {
//    NEW,          // новая
//    IN_PROGRESS,  // в разработке
//    TESTING,      // на тестировании
//    DONE          // завершена
//};
//
//// Объявляем тип-синоним для map<TaskStatus, int>,
//// позволяющего хранить количество задач каждого статуса
//using TasksInfo = map<TaskStatus, int>;

class TeamTasks {
public:
    // Получить статистику по статусам задач конкретного разработчика
    const TasksInfo& GetPersonTasksInfo(const string& person) const {
        return this->team_tasks.at(person);
    }

    // Добавить новую задачу (в статусе NEW) для конкретного разработчитка
    void AddNewTask(const string& person) {
        team_tasks[person][TaskStatus::NEW]++;
    }

    // Обновить статусы по данному количеству задач конкретного разработчика,
    tuple<TasksInfo, TasksInfo> PerformPersonTasks(
        const string& person, int task_count) {
        if (this->team_tasks.find(person)==this->team_tasks.end()) {
            TasksInfo a, b;
            return make_tuple(a, b);
        }
        map<TaskStatus, int> changes;
        map<TaskStatus, int> old;
        TasksInfo& person_tasks = this->team_tasks.at(person);
        TaskStatus current_status = TaskStatus::NEW;
        bool end = false; 
        int add = 0, count;
        while (!end) {
            switch (current_status)
            {
            case TaskStatus::NEW:
                
                    count = max(0, person_tasks[current_status]-task_count);
                    if (count == 0) {
                        add = person_tasks[current_status];
                        person_tasks[current_status] = 0;
                        task_count -= add;
                    }
                    else {
                        person_tasks[current_status] -= task_count;
                        old[current_status] = person_tasks[current_status];
                        add = task_count; 
                        task_count = 0;
                    }
                
                current_status = TaskStatus::IN_PROGRESS;
                break;

            case TaskStatus::IN_PROGRESS:
                if (add != 0) {
                    changes[current_status] = add;
                }
                
                    count = max(0, person_tasks[current_status] - task_count);
                    if (count == 0) {
                        add = person_tasks[current_status];
                        person_tasks[current_status] = 0;
                        task_count -= add;
                    }
                    else {
                        person_tasks[current_status] -= task_count;
                        old[current_status] = person_tasks[current_status];
                        add = task_count;
                        task_count = 0;
                    }
                
                current_status = TaskStatus::TESTING;
                break;

            case TaskStatus::TESTING:
                if (add != 0) {
                    changes[current_status] = add;
                }
               
                    count = max(0, person_tasks[current_status] - task_count);
                    if (count == 0) {
                        add = person_tasks[current_status];
                        person_tasks[current_status] = 0;
                        task_count -= add;
                    }
                    else {
                        person_tasks[current_status] -= task_count;
                        old[current_status] = person_tasks[current_status];
                        add = task_count;
                        task_count = 0;
                    }
                
                current_status = TaskStatus::DONE;
                break;

            case TaskStatus::DONE:
                if (add != 0) {
                    changes[current_status] = add;
                }
                
                    /*count = max(0, person_tasks[current_status] - task_count);
                    if (count == 0) {
                        add = person_tasks[current_status];
                        person_tasks[current_status] = 0;
                        task_count -= add;
                    }
                    else {
                        person_tasks[current_status] -= task_count;
                        //old[current_status] = person_tasks[current_status];
                        add = task_count;
                        task_count = 0;
                    }*/
                
                end = true;
                break;

            default:
                break;
            }
        }
        
        end = false;
        current_status = TaskStatus::NEW;
        while (!end) {
            switch (current_status)
            {
            case TaskStatus::NEW:
                person_tasks[current_status] += changes[current_status];
                if (person_tasks[current_status] == 0) {
                    person_tasks.erase(current_status);
                }
                if (changes[current_status] == 0) {
                    changes.erase(current_status);
                }
                if (old[current_status] == 0) {
                    old.erase(current_status);
                }
                current_status = TaskStatus::IN_PROGRESS;
                break;

            case TaskStatus::IN_PROGRESS:
                person_tasks[current_status] += changes[current_status];
                if (person_tasks[current_status] == 0) {
                    person_tasks.erase(current_status);
                }
                if (changes[current_status] == 0) {
                    changes.erase(current_status);
                }
                if (old[current_status] == 0) {
                    old.erase(current_status);
                }
                current_status = TaskStatus::TESTING;
                break;

            case TaskStatus::TESTING:
                person_tasks[current_status] += changes[current_status];
                if (person_tasks[current_status] == 0) {
                    person_tasks.erase(current_status);
                }
                if (changes[current_status] == 0) {
                    changes.erase(current_status);
                }
                if (old[current_status] == 0) {
                    old.erase(current_status);
                }
                current_status = TaskStatus::DONE;
                break;

            case TaskStatus::DONE:
                person_tasks[current_status] += changes[current_status];
                if (person_tasks[current_status] == 0) {
                    person_tasks.erase(current_status);
                }
                if (changes[current_status] == 0) {
                    changes.erase(current_status);
                }
                if (old[current_status] == 0) {
                    old.erase(current_status);
                }
                end = true;
                break;

            default:
                break;
            }
        }
        return make_tuple(changes, old);
    }
private:
    map<string,TasksInfo> team_tasks;
};

void PrintTasksInfo(TasksInfo tasks_info) {
    cout << tasks_info[TaskStatus::NEW] << " new tasks" <<
        ", " << tasks_info[TaskStatus::IN_PROGRESS] << " tasks in progress" <<
        ", " << tasks_info[TaskStatus::TESTING] << " tasks are being tested" <<
        ", " << tasks_info[TaskStatus::DONE] << " tasks are done" << endl;
}

int main() {
    TeamTasks tasks;
    for (int i = 0; i < 5; ++i) {
        tasks.AddNewTask("Ivan");
    };
    cout << "Ivan's tasks: ";
    PrintTasksInfo(tasks.GetPersonTasksInfo("Ivan"));

    TasksInfo updated_tasks, untouched_tasks;

    tie(updated_tasks, untouched_tasks) =
        tasks.PerformPersonTasks("Ivan", 5);
    cout << "Updated Ivan's tasks: ";
    PrintTasksInfo(updated_tasks);
    cout << "Untouched Ivan's tasks: ";
    PrintTasksInfo(untouched_tasks);

    tie(updated_tasks, untouched_tasks) =
        tasks.PerformPersonTasks("Ivan", 5);
    cout << "Updated Ivan's tasks: ";
    PrintTasksInfo(updated_tasks);
    cout << "Untouched Ivan's tasks: ";
    PrintTasksInfo(untouched_tasks);

    tie(updated_tasks, untouched_tasks) =
        tasks.PerformPersonTasks("Ivan", 1);
    cout << "Updated Ivan's tasks: ";
    PrintTasksInfo(updated_tasks);
    cout << "Untouched Ivan's tasks: ";
    PrintTasksInfo(untouched_tasks);

    for (int i = 0; i < 5; ++i) {
        tasks.AddNewTask("Ivan");
    };

    tie(updated_tasks, untouched_tasks) =
        tasks.PerformPersonTasks("Ivan", 2);
    cout << "Updated Ivan's tasks: ";
    PrintTasksInfo(updated_tasks);
    cout << "Untouched Ivan's tasks: ";
    PrintTasksInfo(untouched_tasks);

    tie(updated_tasks, untouched_tasks) =
        tasks.PerformPersonTasks("Ivan", 4);
    cout << "Updated Ivan's tasks: ";
    PrintTasksInfo(updated_tasks);
    cout << "Untouched Ivan's tasks: ";
    PrintTasksInfo(untouched_tasks);


    return 0;
}