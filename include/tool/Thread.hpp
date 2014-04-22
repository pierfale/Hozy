#ifndef THREAD_HPP
#define THREAD_HPP

#include "ThreadManager.hpp"
#include "tool/Function.hpp"

#ifdef WIN32
#include "os/win32/ThreadImpl_win32.hpp"
#define THREAD_IMPLEMENTATION ThreadImpl_win32
#elif defined UNIX
#include "os/unix/ThreadImpl_unix.hpp"
#define THREAD_IMPLEMENTATION ThreadImpl_unix
#else
#error "This Operating system is unssuported"
#endif

class Thread {

public:
	Thread();

    template<class Tclass, class Treturn, class... Targs>
    void create(const MemberFunction<Tclass, Treturn, Targs...>& function, Targs... arguments) {
        impl.create(function, arguments...);
        ThreadManager::add(this);
    }

    template<class Tclass, class Treturn, class... Targs>
    void create(const Function<Treturn, Targs...>& function) {
        impl.create(function);
        ThreadManager::add(this);
    }

	void join();
	int id();
	bool is_alive();

	static int get_current_thread_id();
	static void sleep(unsigned int ms);

private:
	THREAD_IMPLEMENTATION impl;


};

#endif // THREAD_HPP
