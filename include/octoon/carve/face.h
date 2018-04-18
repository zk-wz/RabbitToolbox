#ifndef OCTOON_CARVE_FACE_H_
#define OCTOON_CARVE_FACE_H_

#include <octoon/carve/vertex.h>
#include <vector>

namespace octoon
{
    namespace carve
    {
        class Face
        {
        public:
            Face(const std::vector<Vertex *>& vertex_lst);

        private:
            std::vector<Vertex *> vertex_list;
            bool is_closed;
        };
    }
}


#endif