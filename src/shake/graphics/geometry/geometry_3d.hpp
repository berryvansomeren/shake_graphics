#ifndef A_GEOMETRY_3D_HPP
#define A_GEOMETRY_3D_HPP

#include <memory>

namespace shake {
namespace graphics {

//----------------------------------------------------------------
class AGeometry3D
{
public:
    using Ptr = std::shared_ptr<AGeometry3D>;

public:
    virtual void draw() const   = 0;

protected:
    virtual ~AGeometry3D() {}
};

} // namespace graphics
} // namespace shake

#endif // A_GEOMETRY_3D_HPP
