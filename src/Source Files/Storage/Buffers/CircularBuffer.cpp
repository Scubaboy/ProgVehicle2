#include "CircularBuffer.h"
#include "CommandControllerTypes.h"

using namespace CircularBufferDefition;
using namespace CommandControllerDefinitions;

template<unsigned int length, class T>
CircularBuffer<length, T>::CircularBuffer() : _readIndex(0), _writeIndex(0), _length(length)
{
    _buffer = new T*[_length]{};
}

template<unsigned int length, class T>
CircularBuffer<length, T>::~CircularBuffer()
{
    if (_buffer != nullptr)
    {
        delete _buffer;
    }
}

template<unsigned int length, class T>
bool CircularBuffer<length, T>::IsEmpty()
{
    return  _readIndex == _writeIndex;
}

template<unsigned int length, class T>
void CircularBuffer<length, T>::Append(T* item)
{
    int nextIndex = _writeIndex +1;

    if (nextIndex > _length - 1)
    {
        nextIndex = 0;
    }

    //Check liftime and delete old entity if required!!!!
    _buffer[nextIndex] = item;
    _writeIndex = nextIndex;
}

template<unsigned int length, class T>
T* CircularBuffer<length, T>::Read()
{
    int nextIndex;

    if (_readIndex == _writeIndex)
    {
        return nullptr;
    }

    nextIndex = _readIndex+1;

    auto item = _buffer[nextIndex];
    _buffer[nextIndex] = nullptr;
    _readIndex = nextIndex;

    return item;
}