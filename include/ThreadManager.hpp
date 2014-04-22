#ifndef THREAD_MANAGER_H
#define THREAD_MANAGER_H

#include "tool/Singleton.hpp"
#include "tool/Mutex.hpp"

class Thread;

class ThreadManager : public Singleton<ThreadManager> {

    friend class Singleton<ThreadManager>;
public:
    static void add(Thread* thread);
	static void wait_all();

protected:
    void initialize();
    void destroy();

private:
    ThreadManager();
    ThreadManager(const ThreadManager& origin);
    ThreadManager& operator=(const ThreadManager& origin);

	void manage();

    std::vector<Thread*> _thread_list;
	Thread* _manage_thread;
	static Mutex _mutex_thread_list;
	bool _alive;

};

#endif
