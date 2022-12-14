/*************************************************************
 * Source File:
 *    LunarModule.cpp
 * Author:
 *    Caleb Rasmussen & Tyler Shellman
 * Summary:
 *    This file contains the definitions for the LunarModule 
 *	  methods. 
 **************************************************************/

#include "LunarModule.h"

/**************************************************
 * LUNAR MODULE DEFUALT CONSTRUCTORS
 * Constructor that takes user inputs to init object
 * and set the member variables.
 * INPUT
 *      dx 
 *		dy
 *		y
 *		aDegrees
 * OUTPUT
 *      None
 ***************************************************/
LunarModule::LunarModule(double dx, double dy, double y, double aDegrees) {
	this->dx = dx;
	this->dy = dy;
	this->y = y;
	this->aDegrees = aDegrees;

	// compute acceleration
	accelerationThrust = computeAcceleration(THRUST, WEIGHT);

	update_degrees(aDegrees);
}

/**************************************************
 * LUNAR MODULE COPY CONSTRUCTOR
 * Copys current object to a new object passed by
 * reference
 * INPUT
 *      rhs	: new object to be copied to 
 * OUTPUT
 *      None
 ***************************************************/
LunarModule::LunarModule(const LunarModule& rhs) {
	*this = rhs;
}

/**************************************************
 * UPDATE DEGREES
 * Update degrees from passed value, computes new
 * acceleration and updates related mmember variables
 * INPUT
 *		aDegrees
 * OUTPUT
 *      None
 ***************************************************/
void LunarModule::update_degrees(double aDegrees) {
	this->aDegrees = aDegrees; // update degrees

	// compute acceleration components
	aRadians = radiansFromDegrees(aDegrees);
	ddxThrust = computeHorizontalComponent(aRadians, accelerationThrust);
	ddyThrust = computeVerticalComponent(aRadians, accelerationThrust);

	// Add acceleration from gravity to get the 
	// total vertical acceleration.
	ddy = ddyThrust + GRAVITY;
}

/**************************************************
 * UPDATE POSITION
 * Updates lunar module position by computing 
 * velocity and distance based on passed time. 
 * INPUT
 *		t : time, in seconds
 * OUTPUT
 *      None
 ***************************************************/
void LunarModule::update_position(double t) {
	// compute velocity components
	// We use ddxThrust here because gravity does not have an effect on 
	// horizontal acceleration so ddxThrust and ddx would be the same.
	dx = computeVelocity(dx, ddxThrust, t);
	dy = computeVelocity(dy, ddy, t);

	// compute total velocity (both components together)
	v = computeTotalComponent(dx, dy);

	// Compute the new coordinates based on the current coordinate,
	// velocity, acceleration, and time interval.
	x = computeDistance(x, dx, ddxThrust, t);
	y = computeDistance(y, dy, ddy, t);


}

/***************************************************
 * GET X
 * X Getter
 * INPUT
 *     N/A
 * OUTPUT
 *     x 
 **************************************************/
double LunarModule::getX() const {
	return x;
}

/***************************************************
 * GET X
 * x Getter
 * INPUT
 *     N/A
 * OUTPUT
 *     x
 **************************************************/
double LunarModule::getY() const {
	return y;
}

/***************************************************
 * GET DX
 * dx Getter
 * INPUT
 *     N/A
 * OUTPUT
 *     dx
 **************************************************/
double LunarModule::getDx() const {
	return dx;
}

/***************************************************
 * GET DY
 * dy Getter
 * INPUT
 *     N/A
 * OUTPUT
 *     dy
 **************************************************/
double LunarModule::getDy() const {
	return dy;
}

/***************************************************
 * GET V
 * V Getter
 * INPUT
 *     N/A
 * OUTPUT
 *     V
 **************************************************/
double LunarModule::getV() const {
	return v;
}

/***************************************************
 * GET ADEGEES
 * aDegrees Getter
 * INPUT
 *     N/A
 * OUTPUT
 *     x
 **************************************************/
double LunarModule::getADegrees() const {
	return aDegrees;
}


/***************************************************
 * COMPUTE DISTANCE
 * Apply inertia to compute a new position using the distance equation.
 * The equation is:
 *     s = s + v t + 1/2 a t^2
 * INPUT
 *     s : original position, in meters
 *     v : velocity, in meters/second
 *     a : acceleration, in meters/second^2
 *     t : time, in seconds
 * OUTPUT
 *     s : new position, in meters
 **************************************************/
double LunarModule::computeDistance(double s, double v, double a, double t) {
	return s + (v * t) + (0.5 * a * t * t);
}

/**************************************************
 * COMPUTE ACCELERATION
 * Find the acceleration given a thrust and mass.
 * This will be done using Newton's second law of motion:
 *     f = m * a
 * INPUT
 *     f : force, in Newtons (kg * m / s^2)
 *     m : mass, in kilograms
 * OUTPUT
 *     a : acceleration, in meters/second^2
 ***************************************************/
double LunarModule::computeAcceleration(double f, double m) {
	return f / m;
}

/***********************************************
 * COMPUTE VELOCITY
 * Starting with a given velocity, find the new
 * velocity once acceleration is applied. This is
 * called the Kinematics equation. The
 * equation is:
 *     v = v + a t
 * INPUT
 *     v : velocity, in meters/second
 *     a : acceleration, in meters/second^2
 *     t : time, in seconds
 * OUTPUT
 *     v : new velocity, in meters/second
 ***********************************************/
double LunarModule::computeVelocity(double v, double a, double t) {
	return v + (a * t);
}


/***********************************************
 * COMPUTE VERTICAL COMPONENT
 * Find the vertical component of a velocity or acceleration.
 * The equation is:
 *     cos(a) = y / total
 * This can be expressed graphically:
 *      x
 *    +-----
 *    |   /
 *  y |  / total
 *    |a/
 *    |/
 * INPUT
 *     a : angle, in radians
 *     total : total velocity or acceleration
 * OUTPUT
 *     y : the vertical component of the total
 ***********************************************/
double LunarModule::computeVerticalComponent(double a, double total) {
	return cos(a) * total;
}


/***********************************************
 * COMPUTE HORIZONTAL COMPONENT
 * Find the horizontal component of a velocity or acceleration.
 * The equation is:
 *     sin(a) = x / total
 * This can be expressed graphically:
 *      x
 *    +-----
 *    |   /
 *  y |  / total
 *    |a/
 *    |/
 * INPUT
 *     a : angle, in radians
 *     total : total velocity or acceleration
 * OUTPUT
 *     x : the vertical component of the total
 ***********************************************/
double LunarModule::computeHorizontalComponent(double a, double total) {
	return sin(a) * total;
}

/************************************************
 * COMPUTE TOTAL COMPONENT
 * Given the horizontal and vertical components of
 * something (velocity or acceleration), determine
 * the total component. To do this, use the Pythagorean Theorem:
 *    x^2 + y^2 = t^2
 * where:
 *      x
 *    +-----
 *    |   /
 *  y |  / total
 *    | /
 *    |/
 * INPUT
 *    x : horizontal component
 *    y : vertical component
 * OUTPUT
 *    total : total component
 ***********************************************/
double LunarModule::computeTotalComponent(double x, double y) {
	return sqrt((x * x) + (y * y));
}


/*************************************************
 * RADIANS FROM DEGEES
 * Convert degrees to radians:
 *     radians / 2pi = degrees / 360
 * INPUT
 *     degrees : degrees from 0 to 360
 * OUTPUT
 *     radians : radians from 0 to 2pi
 **************************************************/
double LunarModule::radiansFromDegrees(double degrees) {
	return (degrees / 360) * (2 * PI);
}
