#pragma once

namespace CircularBufferDefition
{
    template<unsigned int length, class T>
    class CircularBuffer
    {
        public:
            CircularBuffer();
            ~CircularBuffer();
            T* Read();
            void Append(T* item);
            bool IsEmpty();
        private:
            int _readIndex;
            int _writeIndex;
            int _length;
            T** _buffer;
    };
}
