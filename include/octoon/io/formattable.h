#ifndef OCTOON_FORMATTABLE_H_
#define OCTOON_FORMATTABLE_H_

#include <octoon/io/istream.h>
#include <octoon/io/ostream.h>
#include <octoon/io/binary_writer.h>
#include <octoon/io/stream_writer.h>
#include <octoon/io/binary_reader.h>
#include <octoon/io/stream_reader.h>
#include <octoon/io/formatter.h>

namespace octoon
{
    namespace io
    {
        class formattable
        {
        public:
            virtual void load(Formatter& formatter) = 0;
            virtual void save(Formatter& formatter) = 0;
        };
    }
}


#endif 