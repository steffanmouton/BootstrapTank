#pragma once

#include "Application.h"
#include <glm/mat4x4.hpp>


class Tank : public aie::Application {
public:

	Tank();
	virtual ~Tank();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

protected:

	glm::mat4	m_viewMatrix;
	glm::mat4	m_projectionMatrix;

	bool bulletExists = false;
	float bulletTime = 0;

	const glm::mat4 identity = glm::mat4(1);
	glm::mat4 tank = identity;
	glm::mat4 turret;
	glm::mat4 front;
	glm::mat4 barrel;
	glm::mat4 bullet;

	glm::mat4 forwardTrans = glm::mat4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, .05, 0, 0, 1);
	glm::mat4 backTrans = glm::mat4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, -.05, 0, 0, 1);
	glm::mat4 *rotLeft = new glm::mat4(cos(.025), 0, -sin(.025), 0, 0, 1, 0, 0, sin(.025), 0, cos(.025), 0, 0, 0, 0, 1);
	glm::mat4 *rotRight = new glm::mat4(cos(-.025), 0, -sin(-.025), 0, 0, 1, 0, 0, sin(-.025), 0, cos(-.025), 0, 0, 0, 0, 1);

	void shoot();
	void bulletTimer(float deltaTime);
	void destroyBullet();
};

