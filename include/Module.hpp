#ifndef MODULE_H
#define MODULE_H

/**
 * @brief The Module class is a prototype for all module
 */
class Module {

    public:
        virtual void run(void* arg) = 0;

    protected:
        Module();
};

#endif // MODULE_H
