#ifndef OCTOON_CARVE_POLYHEDRON_H_
#define OCTOON_CARVE_POLYHEDRON_H_


#include <octoon/carve/vertex.h>
#include <octoon/carve/face.h>
#include <vector>

namespace octoon
{
    namespace carve
    {
        class Polyhedron
        {
        public:
            Polyhedron(const std::vector<Vertex>& vertex_lst, const std::vector<Face *>& face_lst);
        private:
            std::vector<Vertex> vertex_list;
            std::vector<Face *> face_list;
        };
    }
}


#endif