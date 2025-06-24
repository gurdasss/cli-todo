#include <cstdint>     // for std::int16
#include <string>      // for std::string
#include <string_view> // for std::string_view

#ifndef TASK_H
#define TASK_H

class Task
{
public:
    // the user should be able to set (or reset)
    // task count to begin ID sequencing from
    // arbitrary number.
    static std::int16_t s_taskCount;

    // Status is a member type
    enum Status
    {
        pending,
        inProgress,
        done,
    };

    Task(std::string_view title, Status status, std::string_view category)
        : // generate a new unique ID for newly constructed Task object
          m_id{++s_taskCount},
          m_title{title},
          m_status{status},
          m_category{category}
    {
    }

    std::int16_t getID() const { return m_id; }

    void setTitle(std::string_view title) { m_title = title; }
    const std::string &getTitle() const { return m_title; }

    void setStatus(Status status) { m_status = status; }
    Status getStatus() const { return m_status; }

    void setCategory(std::string_view category) { m_category = category; }
    const std::string &getCategory() const { return m_category; }

private:
    std::int16_t m_id{};
    std::string m_title{};
    Status m_status{};
    std::string m_category{};
};

// applied inline to avoid violate ODR

// ID generator
inline std::int16_t Task::s_taskCount{};

#endif