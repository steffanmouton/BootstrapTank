# Bootstrap Tank Documentation

Steffan Mouton

s188045

Math for Games Assessment

## Requirements Documentation

- Description of Problem
  - Name: Graphical Test Application
  - Problem Statement: Create a program that utilizes stack classes to simulate two teams fighting against each other.
  - Problem Specification: Make use of Math Libraries (personal or glm) to utilize vectors and matrices to draw objects to the screen. Controlled via Matrix hierarchies, you should be able to create a tank and move it about the screen.

- Input Information
  - N/A
- Output Information
  - Draws tank to screen.

- User Interface Information
  - Description: The user can control the tank base using the arrow keys. The turret can be controlled using the A and D keys. Space bar fires the cannon.

## Design Documentation

- System Architecture Description
  - C++,. Utilizing AIE Bootstrap's 3D Project provided code and classes. Tank Class inherits from Bootstrap's Application class.
- Information about the objects
  - *Class Information*
    - Name: Tank
      - Description: Contains data for the tank's object locations in space via matrices, along with some basic methods for bootstrap.
      - Base Class: Application
      - Class Attributes
        - Name: bulletExists
          - Description: Bool to control if bullet is drawn to screen or not
          - Type: bool
          - Range of Acceptable Values: true or false
        - Name: bulletC
          - Description: Bullet's current transform matrix
          - Type: mat4
          - Range of Acceptable Values: mat4 containing floats
        - Name: bulletO
          - Description: Bullet's offset transform matrix. Ensures relative positioning to tank
          - Type: mat4
          - Range of Acceptable Values: mat4 containing floats
        - Name: identity
          - Description: transform matrix for world. Never changes
          - Type: mat4
          - Range of Acceptable Values: mat4 containing floats
        - Name: tankC
          - Description: tank's current transform matrix.
          - Type: mat4
          - Range of Acceptable Values: mat4 containing floats
        - Name: tankO
          - Description: tank's offset transform matrix. Ensures relative positioning to world(identity)
          - Type: mat4
          - Range of Acceptable Values: mat4 containing floats
        - Name: turretC
          - Description: turrets's current transform matrix.
          - Type: mat4
          - Range of Acceptable Values: mat4 containing floats
        - Name: turretO
          - Description: turret's offset transform matrix. Ensures relative positioning to tank
          - Type: mat4
          - Range of Acceptable Values: mat4 containing floats
        - Name: frontC
          - Description: front of tank's current transform matrix
          - Type: mat4
          - Range of Acceptable Values: mat4 containing floats
        - Name: frontO
          - Description: front of tank's offset transform matrix. Ensures relative positioning to tank
          - Type: mat4
          - Range of Acceptable Values: mat4 containing floats
        - Name: barrelC
          - Description: barrel's current transform matrix
          - Type: mat4
          - Range of Acceptable Values: mat4 containing floats
        - Name: barrelTipC
          - Description: barrel tip's transform matrix. Ensures relative positioning to tank so bullet appears in correct place
          - Type: mat4
          - Range of Acceptable Values: mat4 containing floats
        - Name: forwardTrans
          - Description: Transform matrix to move tank or bullet forward
          - Type: mat4
          - Range of Acceptable Values: mat4 containing floats
        - Name: backTrans
          - Description: Transform matrix to move tank or bullet backward
          - Type: mat4
          - Range of Acceptable Values: mat4 containing floats
        - Name: *rotLeft
          - Description: Transform matrix pointer to rotate turret counterclockwise
          - Type: mat4
          - Range of Acceptable Values: mat4 containing floats
        - Name: *rotRight
          - Description: Transform matrix to rotate turret clockwise
          - Type: mat4
          - Range of Acceptable Values: mat4 containing floats
      - Class Operations
        - Prototype: Tank();
          - Description: default constructor for tank
          - Pre-Conditions: Instance of the game is started and set up
          - Post-Conditions: Tank exists
          - Visibility: Public
        - Prototype: ~Tank();
          - Description: default destructor for tank
          - Pre-Conditions: Instance of the game is destroyed
          - Post-Conditions: Tank no longer exists
          - Visibility: Public
        - Prototype: bool startup();
          - Description: On starting an instance of tank app, initial game logic is set up, including camera position and all initial transform matrices
          - Pre-Conditions: An instance of tank app is created and starts to run
          - Post-Conditions: initial transform matrices and logic are set up
          - Visibility: Public
        - Prototype: void shutdown();
          - Description: destroys all bootstrap Gizmos in the tank app
          - Pre-Conditions: An instance of tank app is created and is running
          - Post-Conditions: game is no longer running, Gizmos are destroyed
          - Visibility: Public
        - Prototype: void update(float);
          - Description: Every frame, game logic is performed and updated
          - Pre-Conditions: An instance of tank app is created and is running
          - Post-Conditions: all transform matrices and game logic is current and correct based on user input
          - Visibility: Public
        - Prototype: void draw();
          - Description: Draws all bootstrap gizmos to screen based on current transform matrices
          - Pre-Conditions: An instance of tank app is created and is running
          - Post-Conditions: all proper gizmos are drawn to screen
          - Visibility: Public
        - Prototype: void shoot();
          - Description: sets bulletExists to true so bullet can be drawn to screen. Set's bullet current transform to the tip of the tank barrel.
          - Pre-Conditions: Instance of the game is running is updating.
          - Post-Conditions: Bullet exists at tip of barrel, will now draw to screen
          - Visibility: Protected
        - Prototype: void bulletTimer(float);
          - Description: Keeps track of the lifetime of a bullet
          - Pre-Conditions: Instance of game is running and is updating
          - Post-Conditions: bullet's lifetime (bulletTime) is incremented by deltaTime
          - Visibility: Protected
        - Prototype: void destroyBullet();
          - Description: sets bulletExists to false and bulletTime to 0, no longer drawing it to screen
          - Pre-Conditions: game is running and updating
          - Post-Conditions: bullet is no longer drawn to screen and lifetime is reset
          - Visibility: Protected

## tank.h
```tank.h
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

	//trackers for the bullet to draw correctly
	bool bulletExists = false;
	float bulletTime = 0;

	glm::mat4 bulletC;
	glm::mat4 bulletO;

	//identity matrix for consistency
	const glm::mat4 identity = glm::mat4(1);

	//matrices that track the individual parts of the tank
	
	glm::mat4 tankC = identity;
	glm::mat4 tankO = identity;

	glm::mat4 turretC;
	glm::mat4 turretO;

	glm::mat4 frontC;
	glm::mat4 frontO;

	glm::mat4 barrelC;
	glm::mat4 barrelO;
	glm::mat4 barrelTipC;

	//Transform matrices used in moving the tank by multiplying with current transform
	glm::mat4 forwardTrans = glm::mat4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, .05, 0, 0, 1);
	glm::mat4 backTrans = glm::mat4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, -.05, 0, 0, 1);
	glm::mat4 *rotLeft = new glm::mat4(cos(.025), 0, -sin(.025), 0, 0, 1, 0, 0, sin(.025), 0, cos(.025), 0, 0, 0, 0, 1);
	glm::mat4 *rotRight = new glm::mat4(cos(-.025), 0, -sin(-.025), 0, 0, 1, 0, 0, sin(-.025), 0, cos(-.025), 0, 0, 0, 0, 1);

	//fires a bullet
	void shoot();
	//tracks lifetime of bullet
	void bulletTimer(float deltaTime);
	//removes bullet from screen
	void destroyBullet();
};
```

## tank.cpp
```
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

	//initial definition of matrices that track the individual parts of the tank
	turretO = tankC * glm::mat4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, .5, 0, 1);
	turretC = tankC * glm::mat4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, .5, 0, 1);
	frontO = tankC * glm::mat4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, .75, 0, 0, 1);
	frontC = tankC * glm::mat4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, .75, 0, 0, 1);
	barrelO = turretC * glm::mat4(cos(glm::half_pi<float>()), sin(glm::half_pi<float>()), 0, 
		0, -sin(glm::half_pi<float>()), cos(glm::half_pi<float>()), 0, 0, 0, 0, 1, 0, .5, -.25, 0, 1);
	barrelC = turretC * glm::mat4(cos(glm::half_pi<float>()), sin(glm::half_pi<float>()), 0, 
		0, -sin(glm::half_pi<float>()), cos(glm::half_pi<float>()), 0, 0, 0, 0, 1, 0, .5, -.25, 0, 1);
	barrelTipC = turretC;

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

	//side view - uncomment to change camera
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

	//updating the current position of objects on screen

	//pointers for use in bootstrap gizmo drawing
	glm::mat4 * tankPtr = &tankC;
	glm::mat4 * turretPtr = &turretC;
	glm::mat4 * barrelPtr = &barrelC;
	glm::mat4 * frontPtr = &frontC;
	glm::mat4 * bulletPtr = &bulletC;

	//logic for updating all the parts of the tank moving together
	tankC = identity * tankO;
	turretC = tankC * turretO;
	barrelC = turretC * barrelO;
	frontC = tankC * frontO;
	barrelTipC = turretC * glm::mat4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, .5, 0, 1);

	Gizmos::addAABBFilled(tankC[3].xyz, vec3(1.5, .5, 1), vec4(0, 0.5f, 1, 1), tankPtr);
	Gizmos::addSphere(turretC[3].xyz, 1, 8, 8, vec4(0, 0.5f, 1, 1), turretPtr);
	Gizmos::addCylinderFilled(barrelC[3].xyz, .2, 1, 8, white, barrelPtr);
	Gizmos::addSphere(frontC[3].xyz, .5, 8, 8, red, frontPtr);

	//logic for drawing the bullet to the screen
	if (bulletExists)
	{
		bulletC *= forwardTrans * forwardTrans;
		Gizmos::addSphere(bulletC[3].xyz, .3, 8, 8, vec4(0, 0.5f, 1, 1), bulletPtr);
	}

	// quit if we press escape
	aie::Input* input = aie::Input::getInstance();

	//user input controls for the tank
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

	//updating lifetime of bullet
	bulletTimer(deltaTime);

	//remove bullet from game if it has existed for more than 2 seconds
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
	//initial check to see if there is already a bullet. Will not draw a new bullet if 
	//one already exists
	if (!bulletExists)
	{
		bulletExists = true;
		bulletC = barrelTipC;
	}
}

void Tank::bulletTimer(float deltaTime)
{
	//tracks lifetime of bullet while it exists
	if (bulletExists)
	{
		bulletTime += deltaTime;
	}
}

void Tank::destroyBullet()
{
	//destroys the bullet and resets lifetime to 0
	bulletExists = false;
	bulletTime = 0;
}
```