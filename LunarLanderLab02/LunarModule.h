/*************************************************************
 * Header File:
 *    LunarModule.h
 * Author:
 *    Caleb Rasmussen & Tyler Shellman
 * Summary:
 *    This file contains the definition for the LunarModule
 *    class, which similates the lunar module.
 **************************************************************/

#include <cmath>
using namespace std;

#define WEIGHT   15103.000   // Weight in KG
#define GRAVITY     -1.625   // Vertical acceleration due to gravity, in m/s^2
#define THRUST   45000.000   // Thrust of main engine, in Newtons (kg m/s^2)
#define PI       3.14159265358979323846

/****************************************************************
 * LunarModule 
 * Class that simulates lunar module movement. 
 ****************************************************************/
class LunarModule
{
    public:
        // Constructors
        LunarModule(double dx, double dy , double y, double aDegrees);
        LunarModule(const LunarModule& rhs);

        // Updates methods
        void update_degrees(double aDegrees);
        void update_position(double t);

        // Member variables Getters 
        double getX() const;
        double getY() const;

        double getDx() const;
        double getDy() const;

        double getV() const;
        double getADegrees() const;

private:
    // User input member variables 
    double x = 0;
    double y;
    double v;                   // Total velocity
    double dx;
    double dy;
    double aDegrees;

    // computed member variables
    double ddx;                 // Total horizontal acceleration
    double ddy;                 // Total vertical acceleration
    double ddxThrust;           // Horizontal acceleration due to thrust
    double ddyThrust;           // Vertical acceleration due to thrust
    double aRadians;            // Angle in radians
    double accelerationThrust;  // Acceleration due to thrust 

    // Compute methods
    double computeDistance(double s, double v, double a, double t);
    double computeAcceleration(double f, double m);
    double computeVelocity(double v, double a, double t);
    double computeVerticalComponent(double a, double total);
    double computeHorizontalComponent(double a, double total);
    double computeTotalComponent(double x, double y);
    double radiansFromDegrees(double degrees);
};

