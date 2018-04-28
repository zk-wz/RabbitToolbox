#include <octoon/io/formatter.h>
#include <octoon/io/json_formatter.h>
#include <octoon/io/stream_reader.h>

namespace octoon
{
    namespace io
    {
        JsonFormatter::JsonFormatter() except
        {
            mapper.insert(std::make_pair(typeid(bool).hash_code(), &toJson<bool>));
            mapper.insert(std::make_pair(typeid(float).hash_code(), &toJson<float>));
            mapper.insert(std::make_pair(typeid(double).hash_code(), &toJson<double>));
            mapper.insert(std::make_pair(typeid(char).hash_code(), &toJson<char>));
            mapper.insert(std::make_pair(typeid(unsigned char).hash_code(), &toJson<unsigned char>));
            mapper.insert(std::make_pair(typeid(std::int16_t).hash_code(), &toJson<std::int16_t>));
            mapper.insert(std::make_pair(typeid(std::int32_t).hash_code(), &toJson<std::int32_t>));
            mapper.insert(std::make_pair(typeid(std::int64_t).hash_code(), &toJson<std::int64_t>));
            mapper.insert(std::make_pair(typeid(std::uint16_t).hash_code(), &toJson<std::uint16_t>));
            mapper.insert(std::make_pair(typeid(std::uint32_t).hash_code(), &toJson<std::uint32_t>));
            mapper.insert(std::make_pair(typeid(std::uint64_t).hash_code(), &toJson<std::uint64_t>));
        }

        void JsonFormatter::deserialize(istream& stream) except override
        {
            JsonObject retval;
            StreamReader reader(stream);

        }

        void JsonFormatter::serialize(ostream& stream, serializable obj) except override
        {
            SerializationInfo info;
            JsonObject retval;
            obj.GetObjectData(info);

            for (auto & each : info.info)
            {
                mapper[each.second.type().hash_code()](
                    retval[each.first],
                    each.second,
                    each.first);
            }

            retval.serialize(stream);
        }
    }
}
