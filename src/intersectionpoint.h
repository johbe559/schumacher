#ifndef INTERSECTIONPOINT_H
#define INTERSECTIONPOINT_H
#include <sstream>
#include "material.h"
#include "utils.h"
class IntersectionPoint {
public:
	IntersectionPoint() {};
	IntersectionPoint(const glm::vec3& p, const glm::vec3& n, const Material m = Material()) {
		_point = p;
		_surfaceNormal = n;
		_material = m;
	};
	IntersectionPoint(const IntersectionPoint* ip) {
		_point = glm::vec3(ip->getPoint());
		_surfaceNormal = glm::vec3(ip->getNormal());
		_material = Material(ip->getMaterial());
	}
	IntersectionPoint(const IntersectionPoint& ip) {
		_point = ip.getPoint();
		_surfaceNormal = ip.getNormal();
		_material = ip.getMaterial();
	}

	~IntersectionPoint() {};
	std::string asString() const { 
		std::stringstream s;
		s << _point.x << " " << _point.y << " " << _point.z; 
		return s.str();
	}
	glm::vec3 getPoint() const { return _point; }
	glm::vec3 getNormal() const { return _surfaceNormal; }
	Material getMaterial() const { return _material; }

	void setPoint(const glm::vec3 &p) { _point = p; }
	void setNormal(const glm::vec3 &n) { _surfaceNormal = n; }
	void setMaterial(const Material &m) { _material = m; }

private:
	glm::vec3 _point;
	glm::vec3 _surfaceNormal;
	Material _material;
	// Outgoing ray?
};

#endif
