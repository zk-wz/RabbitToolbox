#ifndef OCTOON_BINARY_FORMATTER_H_
#define OCTOON_BINARY_FORMATTER_H_

#include <octoon/io/formatter.h>

namespace octoon
{
    namespace io
    {
        class BinaryFormatter:public Formatter
        {
        public:
            virtual serializable deserialize(istream& stream) except override;
            virtual void serialize(ostream& stream, serializable obj) except override;
        };
    }
}



#endif // OCTOON_BINARY_FORMATTER_H_