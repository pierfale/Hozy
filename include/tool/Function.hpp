#ifndef FUNCTION_HPP
#define FUNCTION_HPP

/**
 *  @brief Store argument with variadic template
 *
 */
template <class... Args>
struct Arguments;

/**
 * @brief stop case for recursive resolving of setting argument and calling function
 */
template<>
struct Arguments<> {

    /**
     * @brief set empty on no argument case
     */
    void set() {

    }

    //TODO check and return if Treturn is not void
    template<class TFunction, class... Tprevious>
    void call(TFunction&& function, Tprevious&&... arguments) {
        std::forward<TFunction>(function)(std::forward<Tprevious>(arguments)...);
    }

    //TODO check and return if Treturn is not void
    template<class Tclass, class TFunction, class... Tprevious>
    void call_member(Tclass&& instance, TFunction&& function, Tprevious&&... arguments) {
        (std::forward<Tclass>(instance)->*std::forward<TFunction>(function))(std::forward<Tprevious>(arguments)...);
    }

};

template<class Thead, class... Ttail>
struct Arguments<Thead, Ttail...>  : Arguments<Ttail...> {

    void set(Thead& head,  Ttail... tail) {
        _arg = head;
        Arguments<Ttail...>::set(tail...);
    }

    template<class TFunction, class... Tprevious>
    void call(TFunction&& function, Tprevious&&... arguments) {
        return Arguments<Ttail...>::call(std::forward<TFunction>(function), std::forward<Tprevious>(arguments)..., _arg);
    }

    template<class Tclass, class TFunction, class... Tprevious>
    void call_member(Tclass&& instance, TFunction&& function, Tprevious&&... arguments) {
        return Arguments<Ttail...>::call_member(std::forward<Tclass>(instance), std::forward<TFunction>(function), std::forward<Tprevious>(arguments)..., _arg);
    }


    Thead _arg;
};

/**
 * @brief generic class representing function pointor
 */
template<class Treturn, class... Targs>
class Function {

public:

    /**
     * @brief Function initiliasize call with null function pointor
     */
    Function() : _function(nullptr), _arguments() {

    }

    /**
     * @brief Function initilialize class with function parameter
     */
    Function(Treturn(*function)(Targs...)) : _function(function) {

    }

    /**
     * @brief Function copy constructor
     * @param copy
     */
    Function(const Function& copy) : _function(copy._function), _arguments(copy._arguments) {

    }

    virtual ~Function() {

    }

    /**
     * @brief save_parameter register parameter for use it on a call_saved_args call
     * @param arguments
     */
    virtual void save_parameter(Targs... arguments) {
        _arguments.set(arguments...);
    }

    /**
     * @brief call function with argument parameter
     * @param arguments
     * @return
     */
    virtual Treturn call(Targs... arguments) {
        _function(arguments...);
    }

    /**
     * @brief call_saved_args call function with saved parameter
     * @return
     */
    virtual Treturn call_saved_args() {
        _arguments.call(_function);
    }

    static Treturn static_call(Function<Treturn, Targs...>& function, Targs... arguments) {
        return function.call(arguments...);
    }

    static Treturn static_call_with_saved_args(Function<Treturn, Targs...>& function) {
        return function.call_saved_args();
    }

private:
    Treturn(*_function)(Targs...) ;
    Arguments<Targs...> _arguments;

};

template<class Tclass, class Treturn, class... Targs>
class MemberFunction : Function<Treturn, Targs...> {

public:
    MemberFunction(Tclass* instance, Treturn(Tclass::*function)(Targs...)) : _instance(instance), _member_function(function), _arguments() {

    }

    MemberFunction(const MemberFunction& copy) : Function<Treturn, Targs...>(copy), _instance(nullptr), _member_function(nullptr), _arguments() {
        operator=(copy);
    }

    Treturn call(Targs... arguments) {
        (_instance->*_member_function)(arguments...);
    }

    Treturn call_saved_args() {
        _arguments.call_member(_instance, _member_function);
    }

    virtual void save_parameter(Targs... arguments) {
        _arguments.set(arguments...);
    }

    static Treturn static_call(MemberFunction<Tclass, Treturn, Targs...>& function, Targs... arguments) {
        return function.call(arguments...);
    }

    static Treturn static_call_with_saved_args(MemberFunction<Tclass, Treturn, Targs...>& function) {
        return function.call_saved_args();
    }

    MemberFunction& operator=(const MemberFunction& origin) {
        _instance = origin._instance;
        _member_function = origin._member_function;
        _arguments = origin._arguments;
        return *this;
    }

private:
    Tclass* _instance;
    Treturn(Tclass::*_member_function)(Targs...);
    Arguments<Targs...> _arguments;
};

#endif
