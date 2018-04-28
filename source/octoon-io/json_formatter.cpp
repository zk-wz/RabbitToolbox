#include <octoon/io/formatter.h>
#include <octoon/io/json_formatter.h>
#include <octoon/io/stream_reader.h>

namespace octoon
{
    namespace io
    {
        serializable JsonFormatter::deserialize(istream& stream) except override
        {
            JsonObject retval;
            StreamReader reader(stream);
            reader.
        }

        void JsonFormatter::serialize(ostream& stream, serializable obj) except override
        {
            SerializationInfo info;
            obj.GetObjectData(info);

            for (std::size_t i = 0; i < info.size(); ++i)
            {
                auto each = info[i];
                
            }
        }
    }
}
