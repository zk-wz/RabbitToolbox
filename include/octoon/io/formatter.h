#ifndef OCTOON_FORMATTER_H_
#define OCTOON_FORMATTER_H_

#include <string>
#include <vector>
#include <typeinfo>

#include <octoon/io/serializable.h>
#include <octoon/io/istream.h>
#include <octoon/io/ostream.h>
#include <any.hpp>

namespace octoon
{
    namespace io
    {
        class Formatter
        {
        public:
            virtual serializable deserialize(istream& stream) except = 0;
            virtual void serialize(ostream& stream, serializable obj) except = 0;

            virtual void writeArray(std::vector<type::any>, std::string) except = 0;

            virtual void writeBool(bool, std::string) except = 0;

            virtual void writeChar(char, std::string) except = 0;

            virtual void writeFloat(float, std::string) except = 0;

            virtual void writeDouble(double, std::string)	except = 0;

            virtual void writeInt16(std::int16_t, std::string) except = 0;

            virtual void writeInt32(std::int32_t, std::string) except = 0;

            virtual void writeInt64(std::int64_t, std::string) except = 0;

            virtual void writeUInt16(std::uint16_t, std::string) except = 0;

            virtual void writeUInt32(std::uint32_t, std::string) except = 0;

            virtual void writeUInt64(std::uint64_t, std::string) except = 0;

            virtual void writeValueType(type::any value, std::string name, std::type_info type) except = 0;
        };
    }
}



#endif // OCTOON_FORMATTER_H_