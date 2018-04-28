#ifndef OCTOON_JSON_FORMATTER_H_
#define OCTOON_JSON_FORMATTER_H_

#include <octoon/io/formatter.h>
#include <octoon/io/json_object.h>

namespace octoon
{
    namespace io
    {
        class JsonFormatter:public Formatter
        {
        public:
            virtual serializable deserialize(istream& stream) except override;
            virtual void serialize(ostream& stream, serializable obj) except override;
        };
    }
}



#endif // OCTOON_JSON_FORMATTER_H_