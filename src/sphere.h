#ifndef SPHERE_H
#define SPHERE_H

#include "renderable.h"

class Sphere : public Renderable
{
public:
    Sphere(const float &radius, const glm::vec3 &position);
    ~Sphere() {};
	virtual void createAABB();
    virtual IntersectionPoint *getIntersectionPoint(Ray *ray) const;
private:
	  float _radius;
	  glm::vec3 _position;
};

#endif