#ifndef OCTOON_SERILIZATION_INFO_H_
#define OCTOON_SERILIZATION_INFO_H_

#include <vector>
#include <string>
#include <any.hpp>

namespace octoon
{
    namespace io
    {
        class SerializationInfo
        {
        public:
            template <class T>
            void addValue(const std::string& name, T && v) except;

            template <class T>
            T getValue(const std::string& name) except;

            std::size_t size() const noexcept;

            type::any& at(std::size_t n) except {return info.at(n);}

            const type::any& at(std::size_t n) const except {return info.at(n);}

            type::any& operator[](std::size_t n) except {return info[n];}

            const type::any& operator[](std::size_t n) const except {return info[n];}
        private:
            std::vector<type::any> info;
        };
    }
}

#endif // OCTOON_SERILIZATION_INFO_H_