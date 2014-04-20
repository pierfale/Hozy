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

class ThreadImpl_win32 {

	// friend class Thread;

public:
	ThreadImpl_win32();
	/*
	template<class Tclass>
	void create(void(Tclass::*function)(), Tclass* instance) {
		MemberFunction<Tclass>* arg = new MemberFunction<Tclass>(function, instance);

		_thread = CreateThread(NULL, 0, MemberFunction<Tclass>::run, arg, 0, &_id);

		if(_thread == NULL)
			fatal_error("Thread create error : "+Ct::to_string((int)GetLastError()));
	}*/

	template<class Tclass, class Treturn, class... Targs>
	void create(const MemberFunction<Tclass, Treturn, Targs...>& function, Targs... arguments) {
		MemberFunction<Tclass, Treturn, Targs...>* handler = new MemberFunction<Tclass, Treturn, Targs...>(function);
		handler->save_parameter(arguments...);
        _thread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)proxy_member<Tclass, Treturn, Targs...>, handler, 0, &_id);

		if(_thread == NULL)
			throw_error_os(E_THREAD_CREATE_FAILED, GetLastError());
	}

	void join();
	int id();
	static int get_current_thread_id();

private:
	template<class Tclass, class Treturn, class... Targs>
	static long unsigned int proxy_member(void* arg) {
		MemberFunction<Tclass, Treturn, Targs...>* handler = (MemberFunction<Tclass, Treturn, Targs...>*)arg;
		MemberFunction<Tclass, Treturn, Targs...>::static_call_with_saved_args(*handler);
		delete handler;
		return 0;
	}


	DWORD _id;
	HANDLE _thread;


};

#endif

#endif
