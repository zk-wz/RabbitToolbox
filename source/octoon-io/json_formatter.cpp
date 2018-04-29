#include <octoon/io/formatter.h>
#include <octoon/io/json_formatter.h>
#include <octoon/io/stream_reader.h>

namespace octoon
{
    namespace io
    {
        void load(istream& stream) except
        {
            obj.serialize(stream);
        }

        void save(ostream& stream) except
        {
            obj.deserialize(stream);
        }

        void
        deserialize(const std::string &name, bool &v) except
        {
            v = obj[name].get<bool>();
        }

        void
        deserialize(const std::string &name, float &v) except
        {
            v = obj[name].get<float>();
        }

        void
        deserialize(const std::string &name, double &v) except
        {
            v = obj[name].get<double>();
        }

        void
        deserialize(const std::string &name, char &v) except
        {
            v = obj[name].get<char>();
        }

        void
        deserialize(const std::string &name, unsigned char &v) except
        {
            v = obj[name].get<unsigned char>();
        }

        void
        deserialize(const std::string &name, std::int16_t &v) except
        {
            v = obj[name].get<std::int16_t>();
        }

        void
        deserialize(const std::string &name, std::int32_t &v) except
        {
            v = obj[name].get<std::int32_t>();
        }

        void
        deserialize(const std::string &name, std::int64_t &v) except
        {
            v = obj[name].get<std::int64_t>();
        }

        void
        deserialize(const std::string &name, std::uint16_t &v) except
        {
            v = obj[name].get<std::uint16_t>();
        }

        void
        deserialize(const std::string &name, std::uint32_t &v) except
        {
            v = obj[name].get<std::uint32_t>();
        }

        void
        deserialize(const std::string &name, std::uint64_t &v) except
        {
            v = obj[name].get<std::uint64_t>();
        }


        void
        serialize(const std::string &name, bool v) except
        {
            obj[name] = v;
        }

        void
        serialize(const std::string &name, float v) except
        {
            obj[name] = v;
        }

        void
        serialize(const std::string &name, double v) except
        {
            obj[name] = v;
        }

        void
        serialize(const std::string &name, char v) except
        {
            obj[name] = v;
        }

        void
        serialize(const std::string &name, unsigned char v) except
        {
            obj[name] = v;
        }

        void
        serialize(const std::string &name, std::int16_t v) except
        {
            obj[name] = v;
        }

        void
        serialize(const std::string &name, std::int32_t v) except
        {
            obj[name] = v;
        }

        void
        serialize(const std::string &name, std::int64_t v) except
        {
            obj[name] = v;
        }

        void
        serialize(const std::string &name, std::uint16_t v) except
        {
            obj[name] = v;
        }

        void
        serialize(const std::string &name, std::uint32_t v) except
        {
            obj[name] = v;
        }

        void
        serialize(const std::string &name, std::uint64_t v) except
        {
            obj[name] = v;
        }
    }
}
