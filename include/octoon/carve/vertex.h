#ifndef OCTOON_CARVE_VERTEX_H_
#define OCTOON_CARVE_VERTEX_H_

#include <octoon/math/math.h>

namespace octoon
{
    namespace carve
    {
        class Vertex
        {
        public:
            Vertex(float x, float y, float z);
            Vertex(math::Vector3& v);
        private:
            math::Vector3 point;
        };
    }
}


#endif