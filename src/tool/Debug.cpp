#include "tool/Debug.hpp"

void Debug::backtrace() {
	DEBUG_IMPLEMENTATION::backtrace();
}

void generate_core_dump(std::string pathname) {
	DEBUG_IMPLEMENTATION::generate_core_dump(pathname);
}
