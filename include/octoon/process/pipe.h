#ifndef OCTOON_PROCESS_COMMAND_H_
#define OCTOON_PROCESS_COMMAND_H_

#include <iostream>
#include <cstdio>

namespace octoon
{
    namespace process
    {
        class ProcessStreamBuf : public std::streambuf
        {
        public:
            ProcessStreamBuf(FILE* f)
                :f_(f), buf_size_(1024), pbuf_(0)
            {
                pbuf_ = new char[buf_size_];
                setp(pbuf_, pbuf_ + buf_size_);
            }
            ~ProcessStreamBuf();
        private:
            FILE * f_;
            const size_t buf_size_;
            char* pbuf_;
        };
    }
}

#endif