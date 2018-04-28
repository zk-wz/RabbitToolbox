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
            virtual void deserialize(istream& stream, bool& v) except = 0;
            virtual void deserialize(istream& stream, float& v) except = 0;
            virtual void deserialize(istream& stream, double& v) except = 0;
            virtual void deserialize(istream& stream, char& v) except = 0;
            virtual void deserialize(istream& stream, unsigned char& v) except = 0;
            virtual void deserialize(istream& stream, std::int16_t& v) except = 0;
            virtual void deserialize(istream& stream, std::int32_t& v) except = 0;
            virtual void deserialize(istream& stream, std::int64_t& v) except = 0;
            virtual void deserialize(istream& stream, std::uint16_t& v) except = 0;
            virtual void deserialize(istream& stream, std::uint32_t& v) except = 0;
            virtual void deserialize(istream& stream, std::uint64_t& v) except = 0;


            virtual void serialize(ostream& stream, bool v) except = 0;
            virtual void serialize(ostream& stream, float v) except = 0;
            virtual void serialize(ostream& stream, double v) except = 0;
            virtual void serialize(ostream& stream, char v) except = 0;
            virtual void serialize(ostream& stream, unsigned char v) except = 0;
            virtual void serialize(ostream& stream, std::int16_t v) except = 0;
            virtual void serialize(ostream& stream, std::int32_t v) except = 0;
            virtual void serialize(ostream& stream, std::int64_t v) except = 0;
            virtual void serialize(ostream& stream, std::uint16_t v) except = 0;
            virtual void serialize(ostream& stream, std::uint32_t v) except = 0;
            virtual void serialize(ostream& stream, std::uint64_t v) except = 0;
        };
    }
}



#endif // OCTOON_FORMATTER_H_