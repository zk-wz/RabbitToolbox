#ifndef OCTOON_SERIALIZABLE_H
#define OCTOON_SERIALIZABLE_H

#include <octoon/io/istream.h>
#include <octoon/io/ostream.h>
#include <octoon/io/binary_writer.h>
#include <octoon/io/stream_writer.h>
#include <octoon/io/binary_reader.h>
#include <octoon/io/stream_reader.h>
#include <octoon/io/serialization_info.h>

namespace octoon
{
    namespace io
    {
        class serializable
        {
        public:
            virtual void GetObjectData(SerializationInfo& info) = 0;
        };
    }
}


#endif 