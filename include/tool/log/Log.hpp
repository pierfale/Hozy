#ifndef LOG_HPP
#define LOG_HPP

#include <iostream>
#include <sstream>
#include <vector>

#include "AbstractLog.hpp"
#include "LogFile.hpp"
#include "LogStream.hpp"
#include "tool/Singleton.hpp"
#include "tool/Buffer.hpp"


/**
 * enumeration which contains the stream type
 */
enum LogType {
    LOG_INFO        = 1,
    LOG_WARNING     = 1 << 1,
    LOG_ERROR       = 1 << 2,
    LOG_DEBUG       = 1 << 4
};

/** Singleton Log class
 *  Allow the addition of outputStream and the diffusion of message on them
 */
class Log : public Singleton<Log> {
    friend class Singleton<Log>;

    public:
        ~Log() {}

        /**
         * @brief send the message to all output stream added which allow the types of the stream
         * @param message
         * @param level
         */
        static void send(std::string message, int stream_types);

        /**
         * @brief add on output stream
         * @param log
         */
        static void add(AbstractLog* log);

    protected:
        virtual void initialize() {}
        virtual void destroy();




    private:

        Log();

        /**
         * @brief _logs list of output stream
         */
        std::vector<AbstractLog*> _logs;

        /**
         * @brief The StringBuf class contains output stream data
         */
        class StringBuf : public Buffer<char>, public std::streambuf {

            public:

                StringBuf(int level) : Buffer<char>(), _level(level) {

                }

                /**
                 * flush data when buffer is destroy
                 */
                ~StringBuf() {

                }

                /**
                 * @brief overflow add caractere to the buffer and flush it when encounters a return line
                 * @param c
                 * @return
                 */
                int overflow (int c = EOF) {
                    add(c);

                    if(c == '\n') {
                        flush();
                    }
                    return 0;
                }

                /**
                 * @brief flush send data to the output stream and clear buffer
                 */
                void flush() {
                    send(std::string(base(), size()), _level);
                    clear();
                }

            private:
                int _level;
        };

        /**
         * @brief The OutStream class is and adaptator for the log system
         */
        class OutStream : public std::ostream {

            public:
                OutStream(int level) : std::ostream(_buffer = new StringBuf(level)) {

                }

                ~OutStream() {
                    delete _buffer;
                }

                void flush() {
                    _buffer->flush();
                }

            private:
                StringBuf* _buffer;

        };

        public:
            /**
             * @brief lout standard log output stream
             */
            static OutStream lout;
            /**
             * @brief lout standard warning log output stream
             */
            static OutStream lwarning;
            /**
             * @brief lerr standard error log output stream
             */
            static OutStream lerr;
            /**
             * @brief lerr standard debug log output stream
             */
            static OutStream ldebug;
};


#endif // LOG_H
