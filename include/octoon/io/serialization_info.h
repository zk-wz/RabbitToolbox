#ifndef OCTOON_SERILIZATION_INFO_H_
#define OCTOON_SERILIZATION_INFO_H_

#include <vector>
#include <map>
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
            void addValue(const std::string& name, const T & v) except
            {
                info.insert(std::make_pair<std::string,type::any>(name, v));
            }

            template <class T>
            T getValue(const std::string& name) except
            {
                return info[name];
            }
            
            std::map<std::string, type::any> info;
        };
    }
}

#endif // OCTOON_SERILIZATION_INFO_H_