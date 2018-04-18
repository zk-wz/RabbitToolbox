#ifndef OCTOON_SERIALIZABLE_H
#define OCTOON_SERIALIZABLE_H

#include <octoon/io/istream.h>
#include <octoon/io/ireader.h>
#include <octoon/io/ostream.h>
#include <octoon/io/iwriter.h>

namespace octoon
{
    namespace io
    {
        class serializable
        {
        public:
            virtual void serialize(IWriter& out) = 0;
        };
    }
}


#endif 