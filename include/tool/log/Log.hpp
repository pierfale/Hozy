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
    static void send(std::string message, int type_accept);

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

        StringBuf(int type_accept) : Buffer<char>(), std::streambuf(), _type_accept(type_accept) {

        }

        StringBuf(const StringBuf& origin) : Buffer<char>(*this),  std::streambuf(), _type_accept(0) {
            operator=(origin);
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
            send(std::string(get_base(), get_size()), _type_accept);
            clear();
        }

        StringBuf& operator=(const StringBuf& origin) {
            _type_accept = origin._type_accept;
            return *this;
        }

    private:
        int _type_accept;
    };

    /**
         * @brief The OutStream class is and adaptator for the log system
         */
    class OutStream : public std::ostream {

    public:
        OutStream(int type_accept) : OutStream(new StringBuf(type_accept)) {

        }

        OutStream(const OutStream& origin) : std::basic_ios<char>(), std::basic_ostream<char>(), _buffer(nullptr) {
            operator=(origin);
        }

        ~OutStream() {
            delete _buffer;
        }

        void flush() {
            _buffer->flush();
        }

        OutStream& operator=(const OutStream& origin) {
            std::copy(origin._buffer,  origin._buffer+1, _buffer);
            return *this;
        }

    private:
        OutStream(StringBuf* buffer) : std::basic_ios<char>(), std::basic_ostream<char>(buffer), _buffer(buffer) {

        }

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
