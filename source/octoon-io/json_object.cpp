#include <octoon/io/stream_writer.h>
#include <octoon/io/stream_reader.h>
#include <octoon/io/json_object.h>

namespace octoon
{
    namespace io
    {
        StreamWriter& operator<<(StreamWriter& s, const JsonObject& j)
        {
            s << j.dump();
            return s;
        }

        StreamReader& operator>>(StreamReader& s, JsonObject& j)
        {
            std::string data = s.readLine();
            j = nlohmann::json::parse(data.begin(), data.end());
            return s;
        }
    }
}
