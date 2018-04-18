#ifndef OCTOON_JSON_OBJECT_H_
#define OCTOON_JSON_OBJECT_H_

#include <octoon/io/serializable.h>
#include <octoon/runtime/json/json.hpp>

namespace octoon
{
    namespace io
    {
        class JsonObject : public Serializable
        {
        public:
            JsonObject() = default;
            JsonObject(nlohmann::json&& json_)
                :json(json_)
            {
            }

            JsonObject(const nlohmann::json& json_)
                :json(json_)
            {
            }

            template<class T>
            JsonObj& operator[](const T& key)
            {
                return json[key];
            }

            virtual void serialize(BinaryWriter& out) except override
            {
                out.write(json.dump());
            }

            virtual void serialize(StreamWriter& out) except override
            {
                out.write(json.dump());
            }

            static JsonObject deserialize(BinaryReader& in) except
            {
                std::string data = in.readToEnd();
                JsonObject json = nlohmann::json::parse(data.begin(), data.end());
                JsonObject obj(json);
                return json;
            }

            static JsonObject deserialize(StreamReader& in) except
            {
                std::string data = in.readLine();
                JsonObject json = nlohmann::json::parse(data.begin(), data.end());
                JsonObject obj(json);
                return json;
            }
        private:
            using JsonObj = nlohmann::json;
            JsonObj json;
        };
    }
}


#endif