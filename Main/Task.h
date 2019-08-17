#pragma once

namespace TaskManager_n
{
    enum Priority: unsigned char
    {
        PRIORITY_LOW,
        PRIORITY_MEDIUM,
        PRIORITY_HIGH
    };

    class Task
    {
    private:
        unsigned int id;
        TaskManager_n::Priority priority;
    public:
        Task();
        virtual ~Task();

        virtual void init() = 0;
        virtual void go() = 0;
        virtual void terminate() = 0;
        
        const unsigned int &getId() const;
        const TaskManager_n::Priority &getPriority() const;

        void setId(const unsigned int&);
        void setPriority(const TaskManager_n::Priority&);
    };
}
