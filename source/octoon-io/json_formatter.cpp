#include <octoon/io/formatter.h>
#include <octoon/io/json_formatter.h>
#include <octoon/io/stream_reader.h>

namespace octoon
{
    namespace io
    {
        void
        deserialize(istream &stream, const std::string &name, bool &v) except
        {
            JsonObject retval;
            StreamReader reader(stream);
            retval.deserialize(reader);
            v = retval[name];
        }

        void
        deserialize(istream &stream, const std::string &name, float &v) except
        {
            JsonObject retval;
            StreamReader reader(stream);
            retval.deserialize(reader);
            v = retval[name];
        }

        void
        deserialize(istream &stream, const std::string &name, double &v) except
        {
            JsonObject retval;
            StreamReader reader(stream);
            retval.deserialize(reader);
            v = retval[name];
        }

        void
        deserialize(istream &stream, const std::string &name, char &v) except
        {
            JsonObject retval;
            StreamReader reader(stream);
            retval.deserialize(reader);
            v = retval[name];
        }

        void
        deserialize(istream &stream, const std::string &name, unsigned char &v) except
        {
            JsonObject retval;
            StreamReader reader(stream);
            retval.deserialize(reader);
            v = retval[name];
        }

        void
        deserialize(istream &stream, const std::string &name, std::int16_t &v) except
        {
            JsonObject retval;
            StreamReader reader(stream);
            retval.deserialize(reader);
            v = retval[name];
        }

        void
        deserialize(istream &stream, const std::string &name, std::int32_t &v) except
        {
            JsonObject retval;
            StreamReader reader(stream);
            retval.deserialize(reader);
            v = retval[name];
        }

        void
        deserialize(istream &stream, const std::string &name, std::int64_t &v) except
        {
            JsonObject retval;
            StreamReader reader(stream);
            retval.deserialize(reader);
            v = retval[name];
        }

        void
        deserialize(istream &stream, const std::string &name, std::uint16_t &v) except
        {
            JsonObject retval;
            StreamReader reader(stream);
            retval.deserialize(reader);
            v = retval[name];
        }

        void
        deserialize(istream &stream, const std::string &name, std::uint32_t &v) except
        {
            JsonObject retval;
            StreamReader reader(stream);
            retval.deserialize(reader);
            v = retval[name];
        }

        void
        deserialize(istream &stream, const std::string &name, std::uint64_t &v) except
        {
            JsonObject retval;
            StreamReader reader(stream);
            retval.deserialize(reader);
            v = retval[name];
        }


        void
        serialize(ostream &stream, const std::string &name, bool v) except
        {
            JsonObject retval;
            StreamWriter writer(stream);
            retval[name] = v;
            v.serialize(writer);
        }

        void
        serialize(ostream &stream, const std::string &name, float v) except
        {
            JsonObject retval;
            StreamWriter writer(stream);
            retval[name] = v;
            v.serialize(writer);
        }

        void
        serialize(ostream &stream, const std::string &name, double v) except
        {
            JsonObject retval;
            StreamWriter writer(stream);
            retval[name] = v;
            v.serialize(writer);
        }

        void
        serialize(ostream &stream, const std::string &name, char v) except
        {
            JsonObject retval;
            StreamWriter writer(stream);
            retval[name] = v;
            v.serialize(writer);
        }

        void
        serialize(ostream &stream, const std::string &name, unsigned char v) except
        {
            JsonObject retval;
            StreamWriter writer(stream);
            retval[name] = v;
            v.serialize(writer);
        }

        void
        serialize(ostream &stream, const std::string &name, std::int16_t v) except
        {
            JsonObject retval;
            StreamWriter writer(stream);
            retval[name] = v;
            v.serialize(writer);
        }

        void
        serialize(ostream &stream, const std::string &name, std::int32_t v) except
        {
            JsonObject retval;
            StreamWriter writer(stream);
            retval[name] = v;
            v.serialize(writer);
        }

        void
        serialize(ostream &stream, const std::string &name, std::int64_t v) except
        {
            JsonObject retval;
            StreamWriter writer(stream);
            retval[name] = v;
            v.serialize(writer);
        }

        void
        serialize(ostream &stream, const std::string &name, std::uint16_t v) except
        {
            JsonObject retval;
            StreamWriter writer(stream);
            retval[name] = v;
            v.serialize(writer);
        }

        void
        serialize(ostream &stream, const std::string &name, std::uint32_t v) except
        {
            JsonObject retval;
            StreamWriter writer(stream);
            retval[name] = v;
            v.serialize(writer);
        }

        void
        serialize(ostream &stream, const std::string &name, std::uint64_t v) except
        {
            JsonObject retval;
            StreamWriter writer(stream);
            retval[name] = v;
            v.serialize(writer);
        }
    }
}
