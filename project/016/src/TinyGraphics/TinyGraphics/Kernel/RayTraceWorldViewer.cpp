#include "RayTraceWorldViewer.h"

#include "World3D.h"
#include "Camera.h"
#include "Graphics2D.h"
#include "Object3D.h"
#include "Light.h"
#include "Material.h"
#include "Texture.h"
#include "Primitive2D.h"
#include "ColorRGB.h"
#include "Ray.h"
#include "Vector3D.h"

#include <math.h>
#include <vector>

namespace TinyGraphics {

  struct RayTraceWorldViewer::Impl {
    const World3D *world;
    const Camera *camera;
    int specular_depth;
    int transmit_depth;
    Impl(const World3D *world, const Camera *camera,
         int specular_depth, int transmit_depth)
      : world(world), camera(camera), specular_depth(specular_depth),
        transmit_depth(transmit_depth) {}

    typedef std::vector<Object3D *> ObjectStack;
    ColorRGB ray_trace(const Ray& ray, int specular_depth, 
                       int transmit_depth, const ObjectStack& object_stack) const;

    real get_refraction_index(const Object3D *obj) const {
      if (obj == 0)
        return world->get_refraction_index();
      else
        return obj->get_material().refraction_index;
    }

    ColorRGB shade(Object3D *hit_object, const ColorRGB& texture_color,
                   const Point3D& hit_point, int plane_idx,
                   const Vector3D& normal, const Vector3D& sight) const;

    Vector3D reflect(const Vector3D& vec, const Vector3D& normal) const {
      return (2 * normal.dot_product(vec))*normal - vec;
    }

    // compute the refract_ray and modify object_stack
    // return true if need no total internal reflection occur
    bool refract(Object3D *hit_object, const Point3D& hit_point,
                 const Vector3D& sight, const Vector3D& normal,
                 bool shoot_into, ObjectStack& object_stack,
                 Ray& refract_ray) const {

      const Material& material = hit_object->get_material();
      real cur_idx, next_idx;
      if (shoot_into) {
        Object3D *top_obj = object_stack.back();
        cur_idx = get_refraction_index(top_obj);
        next_idx = material.refraction_index;
        object_stack.push_back(hit_object);
      } else {
        cur_idx = material.refraction_index;
        Object3D *top_obj = object_stack.back();
        if (top_obj != hit_object) {
          cur_idx = material.refraction_index;
          next_idx = get_refraction_index(top_obj);
        } else {
          do {
            object_stack.pop_back();
            top_obj = object_stack.back();
          } while (top_obj != 0 && !top_obj->contain(hit_point));
          next_idx = get_refraction_index(top_obj);
        }
      }

      refract_ray.origin = hit_point;
      real r = cur_idx / next_idx;
      real c = normal.dot_product(sight);
  
      real t = 1 - r*r * (1 - c*c);
      if (t > TG_EPSILON) {
        refract_ray.direction = (r*c - sqrt(t))*normal - r*sight;
        return true;
      }
      return false;   // total internal reflection
    }
  };

  RayTraceWorldViewer::RayTraceWorldViewer(const World3D *world, const Camera *camera,
                                           int specular_depth, int transmit_depth)
    : pimpl(new Impl(world, camera, specular_depth, transmit_depth)) {}

  RayTraceWorldViewer::~RayTraceWorldViewer() {
    delete pimpl;
  }

  const Camera *RayTraceWorldViewer::get_camera() const {
    return pimpl->camera;
  }

  void RayTraceWorldViewer::set_camera(const Camera *camera) {
    pimpl->camera = camera;
  }

  void RayTraceWorldViewer::draw(Graphics2D *graphics) const {
    graphics->draw_background(pimpl->world->get_background_color());

    int nu, nv;
    pimpl->camera->get_vpw_resolution(nu, nv);
 
    Impl::ObjectStack stack;
    stack.reserve(pimpl->transmit_depth + 1);
    stack.push_back(0);
    for (int y = 0; y <=nv; ++y) {
      for (int x = 0; x <= nu; ++x) {
        Ray ray(pimpl->camera->get_ray(x, y));
        ColorRGB color = pimpl->ray_trace(ray, pimpl->specular_depth,
                                          pimpl->transmit_depth, stack);
        graphics->set_pixel(IntPoint2D(x, y), color);
      }
    }
  }

  ColorRGB RayTraceWorldViewer::Impl::shade(Object3D *hit_object, const ColorRGB& texture_color,
                                            const Point3D& hit_point, int plane_idx,
                                            const Vector3D& normal, const Vector3D& sight) const {
    // set ambient color
    const Material& material = hit_object->get_material();

    ColorRGB color = material.k_ambient * texture_color * world->get_ambient_color();

    World3D::LightIterator itor = world->get_light_iterator();
    while (itor.has_next()) {
      const Light* li = itor.next();
      real light_hit = 0;
      Ray light_ray;
      if (!li->illuminate(hit_point, light_ray)) continue;
    
      bool in_shadow = false;
      while (true) {
        Vector3D light_normal;
        int idx;
        Object3D *obj = world->intersect(light_ray, light_hit, light_normal, idx);

        if (obj == 0 || obj == hit_object) break;  // eventually hit the target or casually hit nothing

        const Material& material = obj->get_material();

        if (material.k_transparency == 0) {
          in_shadow = true;    // light can't hit the object
          break;
        }

        Point3D light_hit_point = light_ray.point_at(light_hit);

        ColorRGB texture_color;
        if (material.texture == 0)
          texture_color = material.color;
        else
          texture_color = material.texture->get_color(obj->get_plane_coord(idx, light_hit_point));

        // shoot through transparent objects
        light_ray.origin = light_hit_point;
        light_ray.color *= material.k_transparency * texture_color;
      }

      if (in_shadow) continue;

      Point3D ray_hit_point = light_ray.point_at(light_hit);
      real dist = (ray_hit_point - hit_point).norm();
      if (dist > TG_EPSILON) continue;  // not the same point

      Vector3D light = -light_ray.direction;

      ColorRGB diffuse_color = material.k_diffuse * light_ray.color * 
                               texture_color * normal.dot_product(light);
      // prevent a light inside a object or some other reason
      // leading to negative color
      diffuse_color.clamp();

      Vector3D half = light + sight;
      half.normalize();
      ColorRGB specular_color;
      real cos_phi = normal.dot_product(half);
      // prevent unexpected color accumulated
      // when cos_phi < 0 but shineness is even
      if (cos_phi > 0)
        specular_color = material.k_specular * light_ray.color *
                         pow(cos_phi, material.shininess);

      color += diffuse_color + specular_color;
    }
    return color;
  }

  ColorRGB RayTraceWorldViewer::Impl::ray_trace(const Ray& ray, int specular_depth, int transmit_depth,
                                                const ObjectStack& object_stack) const {
    real min_dist = 0;
    Vector3D normal;

    int plane_idx;
    Object3D *hit_object = world->intersect(ray, min_dist, normal, plane_idx);
    if (hit_object == 0)       // nothing hit, return background color
      return world->get_background_color();

    Point3D hit_point = ray.point_at(min_dist);
    const Material& material = hit_object->get_material();

    ColorRGB texture_color;
    if (material.texture == 0)
      texture_color = material.color;
    else
      texture_color = material.texture->get_color(hit_object->get_plane_coord(plane_idx, hit_point));

    Vector3D sight = -ray.direction;

    bool shoot_into = true;
    if (normal.dot_product(sight) < 0) {
      normal = -normal;
      shoot_into = false;
    }

    ColorRGB color = shade(hit_object, texture_color, hit_point, plane_idx, normal, sight);
  
    if (specular_depth > 0 && material.k_specular != 0) {       // specular ray
      Ray reflect_ray;
      reflect_ray.origin = hit_point;
      reflect_ray.direction = reflect(sight, normal);

      color += material.k_specular *
               ray_trace(reflect_ray, specular_depth-1,
                         transmit_depth, object_stack);
    }

    if (transmit_depth > 0 && material.k_transparency != 0) {   // transmitted ray
      Ray refract_ray;
      ObjectStack copy_stack(object_stack);
      if (refract(hit_object, hit_point, sight, normal, shoot_into,
                  copy_stack, refract_ray)) {
        color += material.k_transparency * texture_color * 
                 ray_trace(refract_ray, specular_depth,
                           transmit_depth-1, copy_stack);
      }
    }

    color.clamp();

    return color;
  }
}
