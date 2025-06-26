#include <cstdint>     // for std::int16
#include <string>      // for std::string
#include <string_view> // for std::string_view
#include <cassert>     // for assert

#ifndef TASK_H
#define TASK_H

class Task
{
public:
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
        // make sure that each Task object ID's are non-negative
        // NOTE: if s_taskCount = std::numeric_limits<std::int16_t>::max() + 1
        // then we can't construct anymore Task objects
        // because we're assuming that each Task object will
        // get a unique sequential non-negative integer value as its ID
        // we might face integer overflow
        // can better handle this situation via try-and-catch
        assert(m_id >= 0 && "Can't construct anymore Task object");
    }

    static bool setIDCount(std::int16_t initialIDCount);
    static std::int16_t getIDCount() { return s_taskCount; }
    std::int16_t getID() const { return m_id; }

    void setTitle(std::string_view title) { m_title = title; }
    const std::string &getTitle() const { return m_title; }

    void setStatus(Status status) { m_status = status; }
    Status getStatus() const { return m_status; }

    void setCategory(std::string_view category) { m_category = category; }
    const std::string &getCategory() const { return m_category; }

private:
    // applied inline to avoid violating ODR

    // the user should be able to set (or reset)
    // task count to begin ID sequencing from
    // arbitrary number within the range
    // 0 >= && <= (2^16 - 1)
    // ID generator
    static inline std::int16_t s_taskCount{};
    std::int16_t m_id{};
    std::string m_title{};
    Status m_status{};
    std::string m_category{};
};

// applied inline to avoid violating ODR

// returns true, if ID count was set successfully
inline bool Task::setIDCount(std::int16_t initialIDCount)
{
    // we need ID count to be non-negative
    if (initialIDCount < 0)
        return false;

    // 0 >= initialIDCount && initialIDCount <= std::numeric_limits<int16_t>::max()

    s_taskCount = initialIDCount;
    return true;
}

#endif