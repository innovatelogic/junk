#pragma once

#include <thread>
#include <mutex>
#include <condition_variable>

namespace junk
{
class task_queue_probe_a
{
    class ThreadPool;

    class Worker
    {
        public:
            Worker(ThreadPool &s) : pool(s){}
            void operator()();
        private:
            ThreadPool &pool;
    };

    class ThreadPool
    {
        public:
            ThreadPool(size_t);

            template<class F>
            void enqueue(F f);
            ~ThreadPool();

        private:
            friend class Worker;

            // track threads
            std::vector<std::thread> workers;

            // tasks
            std::deque<std::function<void()>> tasks;

            //sync 
            std::mutex queue_mutex;
            std::condition_variable condition;
            bool stop;
    };

    void Worker::operator()()
    {
        std::function<void()> task;

        while(true)
        {
            {
                // acquire lock
                std::unique_lock<std::mutex> lock(pool.queue_mutex);

                while (!pool.stop && pool.tasks.empty()){
                    pool.condition.wait(lock);
                }

                if (pool.stop){
                    return;
                }

               // task =
            }
        }
    }
}
}
