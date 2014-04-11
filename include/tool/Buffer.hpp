#ifndef BUFFER_HPP
#define BUFFER_HPP

#define ALLOCATION_UNIT 64

template<class T>
/**
 * @brief The Buffer class allow store data of type T
 */
class Buffer {

public:
    /**
     * @brief Buffer construct buffer and allocate ALLOCATION_UNIT octet
     */
    Buffer() : _allocated(ALLOCATION_UNIT*sizeof(T)), _cursor(0) {
        _buffer = (T*)malloc(_allocated);
    }

    /**
     * Free the busy space by buffer
     */
    ~Buffer() {
        free(_buffer);
    }

    /**
     * @brief add type to the buffer end and reallocate it if necessary
     * @param type
     */
    void add(T type) {
        check_allocated_space(_buffer+_cursor, sizeof(T));
        *(_buffer+_cursor) = type;
        _cursor += 1;
    }

    /**
     * @brief add all data contains contains in the buffer with size of parameter size and reallocate it if necessary
     * @param buffer
     * @param size
     */

    void add(T* buffer, unsigned int size) {
        check_allocated_space(_buffer+_cursor, size);
        memcpy((char*)(_buffer+_cursor), buffer, size);
        _cursor += size;
    }

    /**
     * @brief size of the data contains in the buffer
     * @return
     */
    unsigned int size() {
        return _cursor;
    }

    /**
     * @brief clear remove all data contains in the buffer
     */
    void clear() {
        _cursor = 0;
    }

    /**
     * @brief base return pointor to the begining of the buffer
     * @return
     */
    T* base() {
        return _buffer;
    }

    /**
     * @brief ptr return pointer to the end of the data
     * @return
     */
    T* ptr() {
        return _buffer+_cursor;
    }

private:
    /**
     * @brief check_allocated_space check if the buffer need to be reallocate
     * @param base
     * @param size
     */
    void check_allocated_space(T* base, unsigned int size) {
        if(base+size >= _buffer+_allocated) {
            while(base+size >= _buffer+_allocated)
                _allocated *= 2;
            _buffer = (T*)realloc(_buffer, _allocated);
        }
    }

    /**
     * @brief _buffer : the buffer memory
     */
    T* _buffer;
    /**
     * @brief _allocated : size of the allocated space in buffer
     */
    unsigned int _allocated;
    /**
     * @brief _cursor : size of the data
     */
    unsigned int _cursor;

};

#endif
