#ifndef OCTOON_JSON_FORMATTER_H_
#define OCTOON_JSON_FORMATTER_H_

#include <unordered_map>
#include <functional>
#include <octoon/io/formatter.h>
#include <octoon/io/json_object.h>

namespace octoon
{
    namespace io
    {
        class JsonFormatter:public Formatter
        {
        public:
            virtual void load(istream& stream) except;
            virtual void save(ostream& stream) except;

            virtual void deserialize(const std::string& name, bool& v) except;
            virtual void deserialize(const std::string& name, float& v) except;
            virtual void deserialize(const std::string& name, double& v) except;
            virtual void deserialize(const std::string& name, char& v) except;
            virtual void deserialize(const std::string& name, unsigned char& v) except;
            virtual void deserialize(const std::string& name, std::int16_t& v) except;
            virtual void deserialize(const std::string& name, std::int32_t& v) except;
            virtual void deserialize(const std::string& name, std::int64_t& v) except;
            virtual void deserialize(const std::string& name, std::uint16_t& v) except;
            virtual void deserialize(const std::string& name, std::uint32_t& v) except;
            virtual void deserialize(const std::string& name, std::uint64_t& v) except;


            virtual void serialize(const std::string& name, bool v) except;
            virtual void serialize(const std::string& name, float v) except;
            virtual void serialize(const std::string& name, double v) except;
            virtual void serialize(const std::string& name, char v) except;
            virtual void serialize(const std::string& name, unsigned char v) except;
            virtual void serialize(const std::string& name, std::int16_t v) except;
            virtual void serialize(const std::string& name, std::int32_t v) except;
            virtual void serialize(const std::string& name, std::int64_t v) except;
            virtual void serialize(const std::string& name, std::uint16_t v) except;
            virtual void serialize(const std::string& name, std::uint32_t v) except;
            virtual void serialize(const std::string& name, std::uint64_t v) except;

        private:
            JsonObject obj;
        };
    }
}

#endif // OCTOON_JSON_FORMATTER_H_