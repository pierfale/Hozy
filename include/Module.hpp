#ifndef MODULE_H
#define MODULE_H

/**
 * @brief The Module class is a prototype for all module
 */
class Module {

	public:

        /**
         * @brief run method call when module runtime start
         */
        virtual void run() = 0;

    protected:
        Module();
		virtual ~Module();
};

#endif // MODULE_H
