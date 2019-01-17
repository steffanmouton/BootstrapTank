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
};

