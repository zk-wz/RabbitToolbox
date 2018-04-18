#ifndef OCTOON_CARVE_EDGE_H_
#define OCTOON_CARVE_EDGE_H_

#include <octoon/carve/vertex.h>
#include <vector>

namespace octoon
{
    namespace carve
    {
        class Edge
        {
        public:
            Edge(Vertex* begin, Vertex* end);

        private:
            Vertex* begin;
            Vertex* end;
        };
    }
}


#endif