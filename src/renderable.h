#ifndef RENDERABLE_H
#define RENDERABLE_H

#include "AABB.h"
#include "intersectionpoint.h"
#include "utils.h"

class Renderable {
 public:
    virtual ~Renderable() { delete _boundingBox; };
    AABB *getBoundingBox() { return _boundingBox; };
    virtual IntersectionPoint *getIntersectionPoint(Ray *ray) const = 0;
	std::string getName() const { return _name; };
	virtual std::string asString() const { return "asString() not implemented for " + getName(); };
	void setMaterial(const material_t& m) {
		_material = Material();
		_material.setMaterialType(m);
		if (m == GLASS) {
			_material.setDiffuseColor(glm::vec3(0.0f, 0.0f, 1.0f));
			_material.setRefractionIndex(REFRACTION_GLASS);
			_material.setOpacity(0.03);
			_material.setSpecular(1.0f);
		} else if (m == MARBLE) {
			_material.setDiffuseColor(glm::vec3(1.0f, 1.0f,0.0f));
			_material.setSpecular(0.8f);
		} else if(m == LIGHT) {
			_material.setDiffuseColor(glm::vec3(0.9f));
			_material.setEmission(glm::vec3(1.0f));
		} else if (m == MIRROR) {
			_material.setDiffuseColor(glm::vec3(0.0f, 1.0f, 0.0f));
			_material.setAbsorbtion(0.1f);
			_material.setSpecular(0.8f);
		} else if (m == STONE) {	
			_material.setDiffuseColor(glm::vec3(0.5f,0.5f,0.5f)); // gray
			_material.setRefractionIndex(1.0f); // almost none (float precision)
			_material.setSpecular(0.01f); // diffuse (low specularity)
			_material.setOpacity(1.0f); // completely solid
			_material.setEmission(glm::vec3(0.0f));
			_material.setAbsorbtion(0.8f);
		}
			return;				
	}
	Material getMaterial() const { return _material; }
 protected:
	std::string _name;
    AABB *_boundingBox;
	Material _material;
    virtual void createAABB() = 0;
};

#endif
