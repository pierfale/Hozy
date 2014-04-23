#ifndef THREAD_IMPLEMENT_WIN32_HPP
#define THREAD_IMPLEMENT_WIN32_HPP

#ifdef WIN32

#include <windows.h>
#include <iostream>
#include <string>
#include "tool/error/ErrorManager.hpp"
#include "tool/log/Log.hpp"
#include "tool/Convert.hpp"
#include "tool/Function.hpp"
#include "tool/Debug.hpp"

class ThreadImpl_win32 {

	// friend class Thread;

public:
	ThreadImpl_win32();
	template<class Tclass, class Treturn, class... Targs>
	void create(const MemberFunction<Tclass, Treturn, Targs...>& function, Targs... arguments) {
		MemberFunction<Tclass, Treturn, Targs...>* handler = new MemberFunction<Tclass, Treturn, Targs...>(function);
		handler->save_parameter(arguments...);
        _thread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)proxy_member<Tclass, Treturn, Targs...>, handler, 0, &_id);

		if(_thread == NULL)
			throw_error_os(E_THREAD_CREATE_FAILED, GetLastError());
	}
    ~ThreadImpl_win32();

	void join();
	int id();
	bool is_alive();
	static int get_current_thread_id();
	static void sleep(unsigned int ms);

private:
	template<class Tclass, class Treturn, class... Targs>
	static long unsigned int proxy_member(void* arg) {
		MemberFunction<Tclass, Treturn, Targs...>* handler = (MemberFunction<Tclass, Treturn, Targs...>*)arg;

		try {
			MemberFunction<Tclass, Treturn, Targs...>::static_call_with_saved_args(*handler);
		}
		catch(Exception const& e) {
			Log::lerr << std::string(e.what()) << std::endl;
			delete handler;
			return e.get_error_code();
		}
		delete handler;
		return 0;
	}

	ThreadImpl_win32(const ThreadImpl_win32& origin);
	ThreadImpl_win32& operator=(const ThreadImpl_win32& origin);


	DWORD _id;
	HANDLE _thread;


};

#endif

#endif
