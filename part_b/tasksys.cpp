#include "tasksys.h"


IRunnable::~IRunnable() {}

ITaskSystem::ITaskSystem(int num_threads) {}
ITaskSystem::~ITaskSystem() {}

/*
 * ================================================================
 * Serial task system implementation
 * ================================================================
 */

const char* TaskSystemSerial::name() {
    return "Serial";
}

TaskSystemSerial::TaskSystemSerial(int num_threads): ITaskSystem(num_threads) {
}

TaskSystemSerial::~TaskSystemSerial() {}

void TaskSystemSerial::run(IRunnable* runnable, int num_total_tasks) {
    for (int i = 0; i < num_total_tasks; i++) {
        runnable->runTask(i, num_total_tasks);
    }
}

TaskID TaskSystemSerial::runAsyncWithDeps(IRunnable* runnable, int num_total_tasks,
                                          const std::vector<TaskID>& deps) {
    for (int i = 0; i < num_total_tasks; i++) {
        runnable->runTask(i, num_total_tasks);
    }

    return 0;
}

void TaskSystemSerial::sync() {
    return;
}

/*
 * ================================================================
 * Parallel Task System Implementation
 * ================================================================
 */

const char* TaskSystemParallelSpawn::name() {
    return "Parallel + Always Spawn";
}

TaskSystemParallelSpawn::TaskSystemParallelSpawn(int num_threads): ITaskSystem(num_threads) {
    // NOTE: CS149 students are not expected to implement TaskSystemParallelSpawn in Part B.
}

TaskSystemParallelSpawn::~TaskSystemParallelSpawn() {}

void TaskSystemParallelSpawn::run(IRunnable* runnable, int num_total_tasks) {
    // NOTE: CS149 students are not expected to implement TaskSystemParallelSpawn in Part B.
    for (int i = 0; i < num_total_tasks; i++) {
        runnable->runTask(i, num_total_tasks);
    }
}

TaskID TaskSystemParallelSpawn::runAsyncWithDeps(IRunnable* runnable, int num_total_tasks,
                                                 const std::vector<TaskID>& deps) {
    // NOTE: CS149 students are not expected to implement TaskSystemParallelSpawn in Part B.
    for (int i = 0; i < num_total_tasks; i++) {
        runnable->runTask(i, num_total_tasks);
    }

    return 0;
}

void TaskSystemParallelSpawn::sync() {
    // NOTE: CS149 students are not expected to implement TaskSystemParallelSpawn in Part B.
    return;
}

/*
 * ================================================================
 * Parallel Thread Pool Spinning Task System Implementation
 * ================================================================
 */

const char* TaskSystemParallelThreadPoolSpinning::name() {
    return "Parallel + Thread Pool + Spin";
}

TaskSystemParallelThreadPoolSpinning::TaskSystemParallelThreadPoolSpinning(int num_threads): ITaskSystem(num_threads) {
    // NOTE: CS149 students are not expected to implement TaskSystemParallelThreadPoolSpinning in Part B.
}

TaskSystemParallelThreadPoolSpinning::~TaskSystemParallelThreadPoolSpinning() {}

void TaskSystemParallelThreadPoolSpinning::run(IRunnable* runnable, int num_total_tasks) {
    // NOTE: CS149 students are not expected to implement TaskSystemParallelThreadPoolSpinning in Part B.
    for (int i = 0; i < num_total_tasks; i++) {
        runnable->runTask(i, num_total_tasks);
    }
}

TaskID TaskSystemParallelThreadPoolSpinning::runAsyncWithDeps(IRunnable* runnable, int num_total_tasks,
                                                              const std::vector<TaskID>& deps) {
    // NOTE: CS149 students are not expected to implement TaskSystemParallelThreadPoolSpinning in Part B.
    for (int i = 0; i < num_total_tasks; i++) {
        runnable->runTask(i, num_total_tasks);
    }

    return 0;
}

void TaskSystemParallelThreadPoolSpinning::sync() {
    // NOTE: CS149 students are not expected to implement TaskSystemParallelThreadPoolSpinning in Part B.
    return;
}

/*
 * ================================================================
 * Parallel Thread Pool Sleeping Task System Implementation
 * ================================================================
 */

TaskDep::TaskDep() {
  task_id_ = 0;
  finished_tasks_ = 0;
}
TaskID TaskDep::GetNewTaskID() {
  return task_id_.fetch_add(1);

}

int TaskDep::GetFinishedTaskCount() const  {
  return finished_tasks_.load();
}

void TaskDep::FinishTask(TaskID task_id, std::vector<TaskID>& children_tasks) {
  finished_task_ids_.insert(task_id);
  finished_tasks_.fetch_add(1);
  // remove this parent from all of its children.
  for(TaskID child_task_id: dependent_children_[task_id] ) {
    dependent_parents_[child_task_id].erase(task_id);
    // If child has no parent dependency , we change schedule it
    if(dependent_parents_[child_task_id].empty()) {
      children_tasks.emplace_back(child_task_id);
    }
    // if(dependent_children_[child_task_id].find(task_id) != dependent_children_[child_task_id].end()) {
    //   dependent_children_[child_task_id].erase(task_id);
    // }
    // if(dependent_parents_[child_task_id].empty()) {
    //   children_tasks.emplace_back(child_task_id);
    // }

  }
}
bool TaskSystemParallelThreadPoolSleeping::FinishOneSubTask(TaskID task_id, std::vector<TaskID>& children_tasks) {
  if(--taskid_remain_work_count_map_[task_id] ==0 ) {
    // printf("task:%d finished\n", task_id);
    task_dep_.FinishTask(task_id, children_tasks);
    return true;
    }
  return false; 
}

bool TaskDep::CheckAndGetRunnableTasks(std::vector<TaskID>& tasks) {
  std::vector<TaskID> to_erase;
  for(auto &iter: dependent_parents_) {
    TaskID child_task_id = iter.first;
    // printf("child task id:%d\n", child_task_id  );
    for(auto parent_it=iter.second.begin(); parent_it!=iter.second.end();){
      // printf("   parent: %d, finished:%d\n", *parent_it, CheckTaskFinished(*parent_it));
      if( CheckTaskFinished(*parent_it)){
        parent_it = iter.second.erase(parent_it);
      } else {
        parent_it++;  
      }
    }
    bool not_scheduled = scheduled_task_ids_.find(child_task_id) == scheduled_task_ids_.end() ;
    bool parents_empty =dependent_parents_[child_task_id].empty(); 
    if(not_scheduled && parents_empty){
      scheduled_task_ids_.insert(child_task_id);
      // printf("new task schedule:%d\n", child_task_id);
      tasks.emplace_back(child_task_id);
      to_erase.emplace_back(child_task_id);
    }
  }
  for(TaskID erase_id: to_erase) {
    dependent_parents_.erase(erase_id);
  }
  return !tasks.empty();
}

bool TaskDep::CheckTaskFinished(TaskID task_id) {
  return finished_task_ids_.find(task_id) != finished_task_ids_.end();

}

void TaskDep::GetTaskArg(TaskID task_id, TaskArg& task_arg) {
  const auto& ta = task_args_[task_id];
  task_arg.task_id = ta.task_id;
  task_arg.num_total_tasks = ta.num_total_tasks;
  task_arg.runnable = ta.runnable;
  task_arg.remain_dep_parent_task_count = ta.remain_dep_parent_task_count;
}

void TaskDep::AddTaskDep(TaskID child, std::vector<TaskID> deps, IRunnable* runnable, int num_total_tasks) {
  TaskArg ta;
  ta.task_id = child;
  ta.remain_dep_parent_task_count = deps.size();
  ta.runnable = runnable;
  ta.num_total_tasks = num_total_tasks;
  if(!deps.empty()) {
  for(TaskID task_id: deps) {
    dependent_parents_[child].insert(task_id);
    dependent_children_[task_id].insert(child);
  }

  } else {
    dependent_parents_[child] = {};
  }
  task_args_[child] = ta;

}
void TaskSystemParallelThreadPoolSleeping::threadTask( ) {
  std::unique_lock<std::mutex> lock(mutex_);
  std::vector<TaskID> tasks;
  bool get_new_tasks_to_run = false;
    while(!done_ || !ready_queue_.empty() ) {
    threadArg arg ; 
    bool get_task = false;
    if(!ready_queue_.empty()) {
      arg = ready_queue_.front();
      ready_queue_.pop_front();
      get_task = true;
      // printf("get task\n");
    } else {
      // printf("wait task\n");
      cv_.wait(lock);
      // cv_.wait(lock, [this]{return !ready_queue_.empty() || done_ ;});
    }
    lock.unlock();
    if(get_task) {
      int task_thread_id = arg.task_thread_id;
      int task_id = arg.task_id;
      bool cur_task_finished = false;
      std::vector<TaskID> children_task_to_schedule;
      arg.runnable->runTask(task_thread_id, arg.num_total_tasks);
      {
        std::unique_lock<std::mutex> inner_lock(mutex_);
        // printf("taskid: %d, thread_id: %d finished\n", task_id, task_thread_id);
        cur_task_finished = FinishOneSubTask(task_id, children_task_to_schedule);
        if(!children_task_to_schedule.empty()) {
          for(TaskID child_task_id: children_task_to_schedule){
            ScheduleTaskToReadyQueue(child_task_id);
            // Is sthis ok ?
            // cv_.notify_all();
          }
        }
      }
      // Move notify_all out of mutex scope so that 
      // other threads can wake up and do some work
      // if(!ready_queue_.empty()  ) {
      // }
      if(!children_task_to_schedule.empty() || wait_sync_.load()) {
        cv_.notify_all();
      }
    }
    lock.lock();
  }
}

// bool TaskSystemParallelThreadPoolSleeping::CheckTaskAndMoveToReadyQueue() {
//   std::vector<TaskID> tasks;
//     bool get_new_tasks_to_run = task_dep_.CheckAndGetRunnableTasks(tasks);
//     for(TaskID task_id: tasks) {
//       ScheduleTaskToReadyQueue(task_id);
//     }
//     // tasks.clear();
//   return get_new_tasks_to_run;

// }
// Prerequisite: mutex_ is held
void  TaskSystemParallelThreadPoolSleeping::ScheduleTaskToReadyQueue(TaskID task_id) {
  TaskArg task_arg;
  task_dep_.GetTaskArg(task_id, task_arg);
  bool not_scheduled = scheduled_task_ids_.find(task_id) == scheduled_task_ids_.end() ;
  if(not_scheduled  ){
    scheduled_task_ids_.insert(task_id);
    // printf("new task schedule:%d\n", child_task_id);
    // to_erase.emplace_back(child_task_id);
  }
  for(int i=0; i < task_arg.num_total_tasks; i++) {
    threadArg ta(i, task_arg.num_total_tasks, task_arg.runnable, task_id);
    taskid_remain_work_count_map_[task_id] = task_arg.num_total_tasks;
    ready_queue_.emplace_back(ta);
  }

}
const char* TaskSystemParallelThreadPoolSleeping::name() {
    return "Parallel + Thread Pool + Sleep";
}

TaskSystemParallelThreadPoolSleeping::TaskSystemParallelThreadPoolSleeping(int num_threads): ITaskSystem(num_threads) {
    //
    // TODO: CS149 student implementations may decide to perform setup
    // operations (such as thread pool construction) here.
    // Implementations are free to add new class member variables
    // (requiring changes to tasksys.h).
    //
  done_ = false;
  // task_id_ = 0;
  num_threads_ = num_threads;
  // finished_tasks_ = 0;
  for(int i=0; i < num_threads_; i++) {
    workers_.emplace_back([this]{
      this->threadTask();
    });
  }
}

TaskSystemParallelThreadPoolSleeping::~TaskSystemParallelThreadPoolSleeping() {
    //
    // TODO: CS149 student implementations may decide to perform cleanup
    // operations (such as thread pool shutdown construction) here.
    // Implementations are free to add new class member variables
    // (requiring changes to tasksys.h).
    //
  std::unique_lock<std::mutex> lock(mutex_);
  done_=true;
  lock.unlock();
  cv_.notify_all();
  // printf("destructor\n");
  for(int i=0; i < workers_.size(); i++) {
    if(workers_[i].joinable()) {
      workers_[i].join();
    }
  }
  // printf("exit\n");
}

void TaskSystemParallelThreadPoolSleeping::run(IRunnable* runnable, int num_total_tasks) {


    //
    // TODO: CS149 students will modify the implementation of this
    // method in Parts A and B.  The implementation provided below runs all
    // tasks sequentially on the calling thread.
    //

    // for (int i = 0; i < num_total_tasks; i++) {
    //     runnable->runTask(i, num_total_tasks);
    // }
  std::vector<TaskID> deps;
  runAsyncWithDeps(runnable, num_total_tasks, deps);
  sync();
}

// Two places to shcedule tasks and put tasks to ready_queue_ directly 
// or move tasks in task_queue_ to ready_queue_ at the start of runAsyncWithDeps call
// or at threadTask where each TaskID is done
TaskID TaskSystemParallelThreadPoolSleeping::runAsyncWithDeps(IRunnable* runnable, int num_total_tasks,
                                                    const std::vector<TaskID>& deps) {

    //
    // TODO: CS149 students will implement this method in Part B.
    //

  mutex_.lock();
  TaskID new_task = task_dep_.GetNewTaskID();
  printf("task: %d dep count: %ld, dep id:%d\n", new_task, deps.size(), deps.empty() ? 0 : deps[0]);
  // CheckTaskAndMoveToReadyQueue();
  std::vector<TaskID> new_deps;
  for(TaskID parent_task_id: deps) {
    if(!task_dep_.CheckTaskFinished(parent_task_id)) {
      new_deps.emplace_back(parent_task_id);

    }
  }
  task_dep_.AddTaskDep(new_task, new_deps, runnable, num_total_tasks);
  bool scheduled = false;
  if(new_deps.empty()) {
    ScheduleTaskToReadyQueue(new_task);
    scheduled = true;
  } 
  mutex_.unlock();
  if(scheduled) {
    cv_.notify_all();
  }


  return new_task;
}

void TaskSystemParallelThreadPoolSleeping::sync() {

    //
    // TODO: CS149 students will modify the implementation of this method in Part B.
    //
  std::unique_lock<std::mutex> lock(mutex_);
  // In case all threads atre put to sleep

  wait_sync_.store(true);

  while(!ready_queue_.empty() || task_dep_.GetFinishedTaskCount() != task_dep_.GetTotalTaskCount()  ) {
    // printf("finished task count:%d, task_id:%d\n", finished_tasks_.load(), task_id_.load());
    cv_.wait(lock);
    // printf("finished task count:%d, task_id:%d\n", task_dep_.GetFinishedTaskCount(), task_dep_.GetTotalTaskCount());
  }
  wait_sync_.store(false);
    return;
}
