// [CFXS] //
#include <CFXS/Platform/Task.hpp>
#include <CFXS/Platform/CPU.hpp>
#include <CFXS/Base/Debug.hpp>
#include <CFXS/Base/Time.hpp>

namespace CFXS {

    using Group_t = Task::Group_t;

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    static bool s_GlobalEnable = false;

    struct TaskGroupEntry {
        Task* currentTask;
        Task** tasks;
        size_t capacity;
        bool exists = false;
    };
    static std::array<TaskGroupEntry, Task::MAX_GROUP_INDEX> s_TaskGroups;
    ////////////////////////////////////////////////////////////////////////////////////////////////////

    static bool GroupExists(Group_t group) {
        CFXS_ASSERT(group < Task::MAX_GROUP_INDEX, "Invalid task group index");
        return s_TaskGroups[group].exists;
    }

    static bool GroupFull(Group_t group) {
        CFXS_ASSERT(group < Task::MAX_GROUP_INDEX, "Invalid task group index");
        auto& taskGroup = s_TaskGroups[group];
        for (auto i = 0; i < taskGroup.capacity; i++) {
            if (taskGroup.tasks[i] == nullptr)
                return false;
        }
        return true;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    // Static

    __used Task** s_TestTaskArray = nullptr;
    void Task::EnableProcessing() {
        asm volatile("" ::"m"(s_TestTaskArray));

        s_GlobalEnable = true;
    }

    // TODO: placement option - pass preallocated region
    bool Task::AddGroup(Group_t group, size_t capacity) {
        CFXS_ASSERT(group < Task::MAX_GROUP_INDEX, "Invalid task group index");
        if (s_GlobalEnable) {
            CFXS_ERROR("[Task] Task processing is enabled - group add not allowed");
            return false;
        }

        if (GroupExists(group)) {
            CFXS_ERROR("[Task] Group %lu already exists", group);
            return false;
        } else {
            auto& taskGroup = s_TaskGroups[group];
            taskGroup.tasks = new Task*[capacity];
            if (taskGroup.tasks) {
                memset(taskGroup.tasks, 0, sizeof(Task*) * capacity);
                taskGroup.capacity = capacity;
                taskGroup.exists   = true;
                CFXS_printf("[Task] Added task group %lu with capacity %u\t[task array @ %p]\n", group, capacity, taskGroup.tasks);
                return true;
            } else {
                CFXS_ERROR("Failed to create task group %lu with capacity %u", group, capacity);
                return false;
            }
        }
    }

    void Task::ProcessGroup(Group_t group) {
        if (!s_GlobalEnable) {
            CFXS_ERROR("[Task] Task processing not enabled");
            return;
        }

        if (!GroupExists(group)) {
            CFXS_ERROR("[Task] Group %lu does not exist", group);
            return;
        }

        auto& taskGroup = s_TaskGroups[group];
        for (auto i = 0; i < taskGroup.capacity; i++) {
            auto* task = taskGroup.tasks[i];
            if (!task || !task->m_Enabled)
                continue;

            if (CFXS::Time::ms >= task->m_ProcessTime) {
                taskGroup.currentTask = task;

                switch (task->m_Type) {
                    case Type::PERIODIC: {
                        task->m_ProcessTime = CFXS::Time::ms + task->m_Period;
                        if (task->m_Function)
                            task->m_Function();
                        if (task->m_Delete) {
                            taskGroup.tasks[i] = nullptr;
                            delete task;
                        }
                        break;
                    }
                    case Type::SINGLE_SHOT: {
                        if (task->m_Function)
                            task->m_Function();
                        taskGroup.tasks[i] = nullptr;
                        delete task;
                        break;
                    }
                    default: CFXS_ERROR("[Task] Unknown type %lu (group %lu)", (uint32_t)task->m_Type, group);
                }
            }
        }
    }

    static void InsertTask(Group_t group, Task* task) {
        auto& taskGroup = s_TaskGroups[group];
        for (auto i = 0; i < taskGroup.capacity; i++) {
            if (taskGroup.tasks[i] == nullptr) {
                taskGroup.tasks[i] = task;
                return;
            }
        }
    }

    Task* Task::Create(Group_t group, const char* name, const TaskFunction& func, Time_t period) {
        if (!GroupExists(group)) {
            CFXS_ERROR("[Task::Create] Group %lu does not exist", group);
            return nullptr;
        }
        if (GroupFull(group)) {
            CFXS_ERROR("[Task::Create] Group %lu is full", group);
            return nullptr;
        }

        Task* task;
        CFXS::CPU::SafeExec([&]() {
            task = new Task(group, name, func, Type::PERIODIC, period);
            InsertTask(group, task);
        });

        if (task) {
            task->m_ProcessTime = 0;
            CFXS_printf("[Task@%p] Create Periodic Task %p (\"%s\") in group %lu with period %llums\n",
                        task,
                        func.GetFunctionPointer(),
                        name,
                        group,
                        period);
        } else {
            CFXS_ERROR("[Task] Failed to create task");
        }

        return task;
    }

    bool Task::Queue(Group_t group, const TaskFunction& func, Time_t delay) {
        if (!GroupExists(group)) {
            CFXS_ERROR("[Task::Queue] Group %lu does not exist", group);
            return false;
        }
        if (GroupFull(group)) {
            CFXS_ERROR("[Task::Queue] Group %lu is full", group);
            return false;
        }

        Task* task;
        CFXS::CPU::SafeExec([&]() {
            task = new Task(group, "Queued Task", func, Type::SINGLE_SHOT, delay);
            InsertTask(group, task);
        });

        task->m_Enabled = true;

        return task;
    }

    Task* Task::GetCurrentTask(Group_t group) {
        if (!GroupExists(group)) {
            CFXS_ERROR("[Task] Group %lu does not exist", group);
            return nullptr;
        }

        return s_TaskGroups[group].currentTask;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    // Member

    Task::Task(Group_t group, const char* name, const TaskFunction& func, Type type, Time_t period) :
        m_Group(group), m_Name(name), m_Function(func), m_ProcessTime(Time::ms + period), m_Period(period), m_Type(type) {
    }

    const TaskFunction& Task::GetFunction() const {
        return m_Function;
    }

    Group_t Task::GetGroup() const {
        return m_Group;
    }

    void Task::Task::SetGroup(Group_t group) {
        if (GroupExists(group)) {
            m_Group = group;
        } else {
            CFXS_ERROR("[Task] Group %lu does not exist", group);
        }
    }

    Group_t Task::GetPeriod() const {
        return m_Period;
    }

    void Task::SetPeriod(Time_t period) {
        m_Period = period;
    }

} // namespace CFXS
