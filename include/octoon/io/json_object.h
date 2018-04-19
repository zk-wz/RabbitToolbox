#ifndef OCTOON_JSON_OBJECT_H_
#define OCTOON_JSON_OBJECT_H_

#include <octoon/io/serializable.h>
#include <octoon/runtime/json/json.hpp>

namespace octoon
{
	using nlohmann_json = ::nlohmann::json;
    namespace io
    {
        class OCTOON_EXPORT JsonObject : public serializable, public nlohmann_json
        {
        public:
            JsonObject() = default;
            JsonObject(nlohmann_json&& json_)
                :nlohmann_json(json_)
            {
            }

            JsonObject(const nlohmann_json& json_)
                :nlohmann_json(json_)
            {
            }

            virtual void serialize(BinaryWriter& out) except override
            {
				//TODO
                //out.write(dump());
            }

            virtual void serialize(StreamWriter& out) except override
            {
                out.write(dump());
            }

            static JsonObject deserialize(BinaryReader& in) except
            {
                //TODO
                //std::string data = in.readToEnd();
                //nlohmann_json json = nlohmann_json::parse(data.begin(), data.end());
                //return JsonObject(json);
                return nlohmann_json();
            }

            static JsonObject deserialize(StreamReader& in) except
            {
                std::string data = in.readLine();
                nlohmann_json json = nlohmann_json::parse(data.begin(), data.end());
                return JsonObject(json);
            }
        };

        //StreamWriter& operator<<(StreamWriter& s, const JsonObject& j);
        //StreamReader& operator>>(StreamReader& s, JsonObject& j);
        //TODO
        //BinaryWriter& operator<<(BinaryWriter& s, const JsonObject& j);
    }
}


#endif