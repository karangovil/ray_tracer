#ifndef OBJECT_H
#define OBJECT_H

#include <memory>
#include <optional>

#include <common.h>

namespace RT
{

struct tuple;
struct intersection;
struct material;
struct matrix4x4;
struct ray;

struct object : public std::enable_shared_from_this<object>
{
public:
    virtual ~object() = default;

    virtual std::shared_ptr<object> create() const = 0;
    virtual std::shared_ptr<object> clone() const = 0;

    virtual matrix4x4 transform() const = 0;
    virtual material const& mat() const = 0;

    virtual void set_transform(matrix4x4 t) = 0;
    virtual void set_material(material m) = 0;
    
    virtual tuple normal_at(tuple world_point) const;
    virtual opt_int_v_t intersect(ray const& world_ray) const;
    virtual std::shared_ptr<const object> get_object_sp() const;

private:
    virtual tuple local_normal_at(tuple local_point) const = 0;
    virtual opt_int_v_t local_intersect(ray const& local_ray) const = 0;
};

} // end namespace RT
#endif
