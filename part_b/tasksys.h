#ifndef _TASKSYS_H
#define _TASKSYS_H

#include "itasksys.h"
#include <condition_variable>
#include <atomic>
#include <thread>
#include <deque>
#include <mutex>
#include <unordered_set>
#include <unordered_map>


/*
 * TaskSystemSerial: This class is the student's implementation of a
 * serial task execution engine.  See definition of ITaskSystem in
 * itasksys.h for documentation of the ITaskSystem interface.
 */
class TaskSystemSerial: public ITaskSystem {
    public:
        TaskSystemSerial(int num_threads);
        ~TaskSystemSerial();
        const char* name();
        void run(IRunnable* runnable, int num_total_tasks);
        TaskID runAsyncWithDeps(IRunnable* runnable, int num_total_tasks,
                                const std::vector<TaskID>& deps);
        void sync();
};

/*
 * TaskSystemParallelSpawn: This class is the student's implementation of a
 * parallel task execution engine that spawns threads in every run()
 * call.  See definition of ITaskSystem in itasksys.h for documentation
 * of the ITaskSystem interface.
 */
class TaskSystemParallelSpawn: public ITaskSystem {
    public:
        TaskSystemParallelSpawn(int num_threads);
        ~TaskSystemParallelSpawn();
        const char* name();
        void run(IRunnable* runnable, int num_total_tasks);
        TaskID runAsyncWithDeps(IRunnable* runnable, int num_total_tasks,
                                const std::vector<TaskID>& deps);
        void sync();
};

/*
 * TaskSystemParallelThreadPoolSpinning: This class is the student's
 * implementation of a parallel task execution engine that uses a
 * thread pool. See definition of ITaskSystem in itasksys.h for
 * documentation of the ITaskSystem interface.
 */
class TaskSystemParallelThreadPoolSpinning: public ITaskSystem {
    public:
        TaskSystemParallelThreadPoolSpinning(int num_threads);
        ~TaskSystemParallelThreadPoolSpinning();
        const char* name();
        void run(IRunnable* runnable, int num_total_tasks);
        TaskID runAsyncWithDeps(IRunnable* runnable, int num_total_tasks,
                                const std::vector<TaskID>& deps);
        void sync();
};
struct threadArg {
  int task_thread_id;
  int num_total_tasks;
  int task_id;
  IRunnable* runnable = nullptr;

  threadArg() {

  }
  threadArg(const threadArg& arg) {
    task_thread_id = arg.task_thread_id;
    num_total_tasks = arg.num_total_tasks;
    runnable = arg.runnable;
    task_id = arg.task_id;
  }
  threadArg(int thread_id, int total_task, IRunnable* run, int taskid ) {
    task_thread_id = thread_id;
    num_total_tasks = total_task;
    runnable = run;
    task_id = taskid;
  }
};


struct TaskArg {
  int task_id;
  IRunnable* runnable;
  int num_total_tasks;
  int remain_dep_parent_task_count;
  TaskArg(int taskid, IRunnable* run, int num_task, int task_dep_count) {
    task_id = taskid;
    runnable = run;
    num_total_tasks = num_task;
    remain_dep_parent_task_count = task_dep_count;
  }
  TaskArg(const TaskArg& other) {
    task_id = other.task_id;
    runnable = other.runnable;
    num_total_tasks = other.num_total_tasks;
    remain_dep_parent_task_count = other.remain_dep_parent_task_count;
  }
  TaskArg() {

  }
}; 

class TaskDep{
public:
  TaskDep();
  void AddTaskDep(TaskID child, std::vector<TaskID> deps, IRunnable* runnable, int num_total_tasks);
  // Who is responsible for call this function?
  // I guess we should just iterate all task_id to see 
  // if we can schedule them.
  // void CheckAndRemoveDep(TaskID child_task_id);
  void FinishTask(TaskID task_id, std::vector<TaskID>& children_tasks);
  TaskID GetNewTaskID();
  int GetFinishedTaskCount() const ;
  int GetTotalTaskCount() const { return task_id_.load();}
  bool CheckTaskFinished(TaskID task_id);
  bool CheckAndGetRunnableTasks(std::vector<TaskID>& tasks);
  bool HasTaskToSchedule() const { return !dependent_parents_.empty();}
  void GetTaskArg(TaskID task_id, TaskArg& task_arg);

private:
  std::atomic<TaskID> task_id_;
  std::unordered_map<TaskID, std::unordered_set<TaskID>> dependent_parents_;
  std::unordered_map<TaskID, std::unordered_set<TaskID>> dependent_children_;
  std::unordered_set<TaskID> finished_task_ids_;
  std::unordered_set<TaskID> scheduled_task_ids_;
  std::unordered_map<TaskID, TaskArg> task_args_;
  std::atomic<int> finished_tasks_;

 
};
/*
 * TaskSystemParallelThreadPoolSleeping: This class is the student's
 * optimized implementation of a parallel task execution engine that uses
 * a thread pool. See definition of ITaskSystem in
 * itasksys.h for documentation of the ITaskSystem interface.
 */
class TaskSystemParallelThreadPoolSleeping: public ITaskSystem {
    public:
        TaskSystemParallelThreadPoolSleeping(int num_threads);
        ~TaskSystemParallelThreadPoolSleeping();
        const char* name();
        void run(IRunnable* runnable, int num_total_tasks);
        TaskID runAsyncWithDeps(IRunnable* runnable, int num_total_tasks,
                                const std::vector<TaskID>& deps);
        void sync();

private:
  void threadTask( );

  bool FinishOneSubTask(TaskID task_id, std::vector<TaskID>& children_task) ;
  void ScheduleTaskToReadyQueue(TaskID task_id);
  // void CheckFinishedParentTask(TaskID task_id, )
  // bool CheckTaskAndMoveToReadyQueue();

  // bool CheckAndMoveTaskToReadyQueue(TaskID child_task_id);
  // void CheckAndNotify(TaskID child_task_id);
  std::vector<std::thread> workers_;
  int num_threads_;
  bool done_;
  std::atomic<bool> wait_sync_;
  std::mutex mutex_;
  std::condition_variable cv_;
  std::deque<threadArg> ready_queue_;
  std::unordered_map<TaskID, int> taskid_remain_work_count_map_;
  std::unordered_set<TaskID> scheduled_task_ids_;
  TaskDep task_dep_;


};

#endif
