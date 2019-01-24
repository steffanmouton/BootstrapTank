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



Tank::Tank() 
{

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

	turretO = tankC * glm::mat4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, .5, 0, 1);
	turretC = tankC * glm::mat4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, .5, 0, 1);
	frontO = tankC * glm::mat4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, .75, 0, 0, 1);
	frontC = tankC * glm::mat4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, .75, 0, 0, 1);
	barrelO = turretC * glm::mat4(cos(glm::half_pi<float>()), sin(glm::half_pi<float>()), 0, 
		0, -sin(glm::half_pi<float>()), cos(glm::half_pi<float>()), 0, 0, 0, 0, 1, 0, .5, -.25, 0, 1);
	barrelC = turretC * glm::mat4(cos(glm::half_pi<float>()), sin(glm::half_pi<float>()), 0, 
		0, -sin(glm::half_pi<float>()), cos(glm::half_pi<float>()), 0, 0, 0, 0, 1, 0, .5, -.25, 0, 1);
	barrelTipC = turretC;
	barrelTipO = turretC;
	//bulletO = barrelTipC * glm::mat4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1);

	return true;
}

void Tank::shutdown() {

	Gizmos::destroy();
}

void Tank::update(float deltaTime) {

	// query time since application started
	float time = getTime();

	// rotate camera

	//overhead view
	m_viewMatrix = glm::lookAt(vec3(0, 25, 1),
		vec3(0), vec3(0, 1, 0));

	//side view
	/*m_viewMatrix = glm::lookAt(vec3(0, 1, 10),
		vec3(0), vec3(0, 1, 0));*/

	// wipe the gizmos clean for this frame
	Gizmos::clear();

	// draw a simple grid with gizmos
	vec4 white(1);
	vec4 black(0, 0, 0, 1);
	vec4 red(1, 0, 0, 1);
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

	glm::mat4 * tankPtr = &tankC;
	glm::mat4 * turretPtr = &turretC;
	glm::mat4 * barrelPtr = &barrelC;
	glm::mat4 * frontPtr = &frontC;
	glm::mat4 * bulletPtr = &bulletC;
	
	tankC = identity * tankO;
	turretC = tankC * turretO;
	barrelC = turretC * barrelO;
	frontC = tankC * frontO;
	barrelTipC = turretC * glm::mat4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, .5, 0, 1);

	// demonstrate a few shapes
	//Gizmos::addAABBFilled(vec3(0), vec3(1.5, .5, 1), vec4(0, 0.5f, 1, 1));
	//Gizmos::addSphere(vec3(0,.5,0), 1, 8, 8, vec4(0, 0.5f, 1, 1));

	Gizmos::addAABBFilled(tankC[3].xyz, vec3(1.5, .5, 1), vec4(0, 0.5f, 1, 1), tankPtr);
	Gizmos::addSphere(turretC[3].xyz, 1, 8, 8, vec4(0, 0.5f, 1, 1), turretPtr);
	Gizmos::addCylinderFilled(barrelC[3].xyz, .2, 1, 8, white, barrelPtr);
	Gizmos::addSphere(frontC[3].xyz, .5, 8, 8, red, frontPtr);


	if (bulletExists)
	{
		bulletC *= forwardTrans * forwardTrans;
		Gizmos::addSphere(bulletC[3].xyz, .3, 8, 8, vec4(0, 0.5f, 1, 1), bulletPtr);
	}

	// quit if we press escape
	aie::Input* input = aie::Input::getInstance();

	if(input->isKeyDown(aie::INPUT_KEY_UP))
	{

		tankO *= forwardTrans;
	}

	if (input->isKeyDown(aie::INPUT_KEY_LEFT))
	{
		tankO *= *rotLeft;
	}

	if (input->isKeyDown(aie::INPUT_KEY_DOWN))
	{
		tankO *= backTrans;
	}

	if (input->isKeyDown(aie::INPUT_KEY_RIGHT))
	{
		tankO *= *rotRight;
	}

	if (input->isKeyDown(aie::INPUT_KEY_A))
	{
		turretO *= *rotLeft;
	}

	if (input->isKeyDown(aie::INPUT_KEY_D))
	{
		turretO *= *rotRight;
	}

	if (input->isKeyDown(aie::INPUT_KEY_SPACE))
	{
		shoot();
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
		bulletC = barrelTipC;
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
