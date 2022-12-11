// ---------------------------------------------------------------------
// CFXS Framework Platform Module <https://github.com/CFXS/CFXS-Platform>
// Copyright (C) 2022 | CFXS / Rihards Veips
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>
// ---------------------------------------------------------------------
// [CFXS] //
#pragma once

#include <CFXS/Base/Time.hpp>
#include <CFXS/Base/Function.hpp>

namespace CFXS {

    using TaskFunction = Function<void(void* userData)>;
    class Task {
        enum class Type : uint32_t { SINGLE_SHOT, PERIODIC };

    public:
        static constexpr auto MAX_GROUP_INDEX = 8;
        using Group_t                         = uint32_t;

        /////////////////////////////////////////////////////////////////////////////
        /// Enable processing
        /// \note call this only after creating all task groups
        static void EnableProcessing();

        /////////////////////////////////////////////////////////////////////////////
        /// Create task group
        /// \param group task group
        /// \param capacity prealloc size and max task count in group
        /// \return bool - true if group created successfully
        static bool AddGroup(Group_t group, size_t capacity);

        static bool AddGroups(std::initializer_list<std::pair<Group_t, size_t>>&& groups) {
            bool addedAll = true;
            for (const auto& g : groups) {
                if (!AddGroup(g.first, g.second))
                    addedAll = false;
            }
            return addedAll;
        }

        /////////////////////////////////////////////////////////////////////////////
        /// Process all tasks in group
        /// \param group task group
        static void ProcessGroup(Group_t group);

        /////////////////////////////////////////////////////////////////////////////
        /// Create periodic task
        /// \param group task group
        /// \param name task label
        /// \param func function to queue
        /// \param period trigger period in ms
        /// \return Task* - pointer to created task or nullptr if creation failed
        static Task* Create(Group_t group, const char* name, const TaskFunction& func, Time_t period);

        /////////////////////////////////////////////////////////////////////////////
        /// Queue single shot task
        /// \param group task group
        /// \param func function to queue
        /// \param delay trigger delay from current timestamp
        /// \return bool - true if queued successfully
        static bool Queue(Group_t group, const TaskFunction& func, Time_t delay = 0);

        /////////////////////////////////////////////////////////////////////////////
        /// Get task currently being processed
        /// \param group task group
        /// \return Task* - pointer to current task being processed
        static Task* GetCurrentTask(Group_t group);

        const TaskFunction& GetFunction() const;

        Group_t GetGroup() const;
        void SetGroup(Group_t group);

        Group_t GetPeriod() const;
        void SetPeriod(Time_t period);

        void Delete() {
            m_Delete = true;
        }

        bool Enabled() const {
            return m_Enabled;
        }

        constexpr void SetEnabled(bool state) {
            if (!m_ProcessTime)
                m_ProcessTime = CFXS::Time::ms + m_Period;
            m_Enabled = state;
        }

        constexpr void Delay(CFXS::Time_t delay_ms) {
            m_ProcessTime += delay_ms;
        }

        constexpr void Start() {
            SetEnabled(true);
        }

        constexpr void Stop() {
            SetEnabled(false);
        }

        constexpr const char* GetName() const {
            return m_Name;
        }

    private:
        Task(Group_t group, const char* name, const TaskFunction& func, Type type, Time_t period = 0);

    private:
        Group_t m_Group;
        const char* m_Name;
        TaskFunction m_Function;
        Time_t m_ProcessTime;
        Time_t m_Period;
        Type m_Type;
        bool m_Enabled = false;
        bool m_Delete  = false;
    };

} // namespace CFXS
