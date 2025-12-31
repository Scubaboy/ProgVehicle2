#pragma once

namespace CoreQueueDefinition
{
    template <typename T>  
    class CoreQueueWrite
    {
        public:
            

            virtual bool TryEnqueue(const T* item) = 0; //Pure virtual function
            
       // protected:
        //    queue_t _queue;
    };

    template <typename T>
    class CoreQueueRead
    {
        public:
            virtual bool IsQueueEmpty() = 0; //Pure virtual function
            virtual bool TryDequeue(T* item) = 0; //Pure virtual function
    };
}