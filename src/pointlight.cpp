#include "pointlight.h"

PointLight::PointLight(const glm::vec3 pos, 
				const float& intensity, 
				const glm::vec3 color) {
	_position = pos;
	_intensity = intensity;
	_color = color;
	glm::vec3 d = glm::vec3(0.00001);
	_lowerLeftBack = pos - d;
	_upperRightFront = pos + d; 
	createAABB();
}

PointLight::PointLight(const glm::vec3& lLB,
                         const glm::vec3& uRF,
                         const glm::vec3 p, const float& i, const glm::vec3 c) {
	_lowerLeftBack = lLB;
	_upperRightFront = uRF;
	_position = p;
	_intensity = i;
	_color = c;
	_name = "PointLight";

	createAABB();
}

void PointLight::createAABB() {
	this->_boundingBox = new AABB(_lowerLeftBack, _upperRightFront, _position);
}

IntersectionPoint *PointLight::getIntersection(Ray *r, bool getIntersectionNormals) {
	return this->_boundingBox->getIntersection(r,getIntersectionNormals);
}

IntersectionPoint *PointLight::getIntersectionPoint(Ray *r) const {
	return this->_boundingBox->getIntersection(r);
}
