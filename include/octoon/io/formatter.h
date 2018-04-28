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
            virtual void deserialize(istream& stream, const std::string &name, bool& v) except = 0;
            virtual void deserialize(istream& stream, const std::string &name, float& v) except = 0;
            virtual void deserialize(istream& stream, const std::string &name, double& v) except = 0;
            virtual void deserialize(istream& stream, const std::string &name, char& v) except = 0;
            virtual void deserialize(istream& stream, const std::string &name, unsigned char& v) except = 0;
            virtual void deserialize(istream& stream, const std::string &name, std::int16_t& v) except = 0;
            virtual void deserialize(istream& stream, const std::string &name, std::int32_t& v) except = 0;
            virtual void deserialize(istream& stream, const std::string &name, std::int64_t& v) except = 0;
            virtual void deserialize(istream& stream, const std::string &name, std::uint16_t& v) except = 0;
            virtual void deserialize(istream& stream, const std::string &name, std::uint32_t& v) except = 0;
            virtual void deserialize(istream& stream, const std::string &name, std::uint64_t& v) except = 0;


            virtual void serialize(ostream& stream, const std::string &name, bool v) except = 0;
            virtual void serialize(ostream& stream, const std::string &name, float v) except = 0;
            virtual void serialize(ostream& stream, const std::string &name, double v) except = 0;
            virtual void serialize(ostream& stream, const std::string &name, char v) except = 0;
            virtual void serialize(ostream& stream, const std::string &name, unsigned char v) except = 0;
            virtual void serialize(ostream& stream, const std::string &name, std::int16_t v) except = 0;
            virtual void serialize(ostream& stream, const std::string &name, std::int32_t v) except = 0;
            virtual void serialize(ostream& stream, const std::string &name, std::int64_t v) except = 0;
            virtual void serialize(ostream& stream, const std::string &name, std::uint16_t v) except = 0;
            virtual void serialize(ostream& stream, const std::string &name, std::uint32_t v) except = 0;
            virtual void serialize(ostream& stream, const std::string &name, std::uint64_t v) except = 0;
        };
    }
}



#endif // OCTOON_FORMATTER_H_