#ifndef A_GEOMETRY_2D_HPP
#define A_GEOMETRY_2D_HPP

#include <memory>

namespace shake {
namespace graphics {

//----------------------------------------------------------------
class AGeometry2D
{
public:
    using Ptr = std::shared_ptr<AGeometry2D>;

public:
    virtual void draw() const   = 0;

protected:
    virtual ~AGeometry2D() {}


};

} // namespace graphics
} // namespace shake

#endif // A_GEOMETRY_2D_HPP
