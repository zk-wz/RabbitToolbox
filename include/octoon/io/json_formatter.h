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
            JsonFormatter() except;
            virtual serializable deserialize(istream& stream) except;
            virtual void serialize(ostream& stream, serializable obj) except;
            virtual void writeValueType(type::any value, std::string name, std::type_info type) except;
        private:
            std::unordered_map<std::size_t, std::function<void toJson(JsonObject&, type::any,std::string)>> to_json_mapper;
            std::unordered_map<std::size_t, std::function<void fromJson(const JsonObject&, type::any &,std::string)>> from_json_mapper;
        };

        template <class T>
        void toJson(JsonObject& json, type::any value,std::string name)
        {
            json[name] = type::any_cast<T>(value);
        }
    }
}

#endif // OCTOON_JSON_FORMATTER_H_