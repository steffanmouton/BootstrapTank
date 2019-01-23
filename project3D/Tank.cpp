#define GLM_FORCE_SWIZZLE

#include "Tank.h"
#include "Gizmos.h"
#include "Input.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "Application3D.h"

using glm::vec3;
using glm::vec4;
using glm::mat4;
using aie::Gizmos;



Tank::Tank() {

}

Tank::~Tank() {

}

bool Tank::startup() {

	setBackgroundColour(0.25f, 0.25f, 0.25f);

	// initialise gizmo primitive counts
	Gizmos::create(10000, 10000, 10000, 10000);

	// create simple camera transforms
	m_viewMatrix = glm::lookAt(vec3(10), vec3(0), vec3(0, 1, 0));
	m_projectionMatrix = glm::perspective(glm::pi<float>() * 0.25f,
		getWindowWidth() / (float)getWindowHeight(),
		0.1f, 1000.f);

	return true;
}

void Tank::shutdown() {

	Gizmos::destroy();
}

void Tank::update(float deltaTime) {

	// query time since application started
	float time = getTime();

	// rotate camera
	m_viewMatrix = glm::lookAt(vec3(0, 25, 1),
		vec3(0), vec3(0, 1, 0));

	// wipe the gizmos clean for this frame
	Gizmos::clear();

	// draw a simple grid with gizmos
	vec4 white(1);
	vec4 black(0, 0, 0, 1);
	for (int i = 0; i < 21; ++i) {
		Gizmos::addLine(vec3(-10 + i, 0, 10),
			vec3(-10 + i, 0, -10),
			i == 10 ? white : black);
		Gizmos::addLine(vec3(10, 0, -10 + i),
			vec3(-10, 0, -10 + i),
			i == 10 ? white : black);
	}

	// add a transform so that we can see the axis
	Gizmos::addTransform(mat4(1));

	turret = tank * glm::mat4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, .5, 0, 1);
	front = tank * glm::mat4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1);
	barrel = turret * glm::mat4(cos(glm::half_pi<float>()), sin(glm::half_pi<float>()), 0, 0, -sin(glm::half_pi<float>()), cos(glm::half_pi<float>()), 0, 0, 0, 0, 1, 0, .5, 0, 0, 1);

	glm::mat4 * tankPtr = &tank;
	glm::mat4 * turretPtr = &turret;
	glm::mat4 * barrelPtr = &barrel;
	glm::mat4 * frontPtr = &front;


	// demonstrate a few shapes
	//Gizmos::addAABBFilled(vec3(0), vec3(1.5, .5, 1), vec4(0, 0.5f, 1, 1));
	//Gizmos::addSphere(vec3(0,.5,0), 1, 8, 8, vec4(0, 0.5f, 1, 1));

	Gizmos::addAABBFilled(tank[3].xyz, vec3(1.5, .5, 1), vec4(0, 0.5f, 1, 1), tankPtr);
	Gizmos::addSphere(turret[3].xyz, 1, 8, 8, vec4(0, 0.5f, 1, 1), turretPtr);
	Gizmos::addCylinderFilled(barrel[3].xyz, .2, 1, 8, white, barrelPtr);
	Gizmos::addSphere(front[3].xyz, .75, 8, 8, vec4(0, 0.5f, 1, 1), frontPtr);


	if (bulletExists)
	{
		bullet *= forwardTrans * forwardTrans;
		Gizmos::addSphere(bullet[3].xyz, .3, 8, 8, vec4(0, 0.5f, 1, 1));
	}

	// quit if we press escape
	aie::Input* input = aie::Input::getInstance();

	if(input->isKeyDown(aie::INPUT_KEY_UP))
	{

		tank *= forwardTrans;
	}

	if (input->isKeyDown(aie::INPUT_KEY_LEFT))
	{
		tank *= *rotLeft;
	}

	if (input->isKeyDown(aie::INPUT_KEY_DOWN))
	{
		tank *= backTrans;
	}

	if (input->isKeyDown(aie::INPUT_KEY_RIGHT))
	{
		tank *= *rotRight;
	}

	if (input->isKeyDown(aie::INPUT_KEY_SPACE))
	{
		shoot();
	}

	if (input->isKeyDown(aie::INPUT_KEY_A))
	{
		turret *= *rotLeft;
	}

	if (input->isKeyDown(aie::INPUT_KEY_D))
	{
		turret *= *rotRight;
	}

	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();

	bulletTimer(deltaTime);
	
	if (bulletTime > 2)
		destroyBullet();

}

void Tank::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// update perspective in case window resized
	m_projectionMatrix = glm::perspective(glm::pi<float>() * 0.25f,
		getWindowWidth() / (float)getWindowHeight(),
		0.1f, 1000.f);

	// draw 3D gizmos
	Gizmos::draw(m_projectionMatrix * m_viewMatrix);

	// draw 2D gizmos using an orthogonal projection matrix (or screen dimensions)
	Gizmos::draw2D((float)getWindowWidth(), (float)getWindowHeight());
}

void Tank::shoot()
{

	if (!bulletExists)
	{
		bulletExists = true;
		bullet = front;
	}
}

void Tank::bulletTimer(float deltaTime)
{
	if (bulletExists)
	{
		bulletTime += deltaTime;
	}
}

void Tank::destroyBullet()
{
	bulletExists = false;
	bulletTime = 0;
}
