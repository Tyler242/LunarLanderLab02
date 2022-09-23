#pragma once

#include <cmath>
using namespace std;

#define WEIGHT   15103.000   // Weight in KG
#define GRAVITY     -1.625   // Vertical acceleration due to gravity, in m/s^2
#define THRUST   45000.000   // Thrust of main engine, in Newtons (kg m/s^2)
#define PI       3.14159265358979323846


class LunarModule
{
    private:
        double x = 0;
        double y;
        double v;                   // Total velocity
        double dx;
        double dy;
        double ddx;                 // Total horizontal acceleration
        double ddy;                 // Total vertical acceleration
        double ddxThrust;           // Horizontal acceleration due to thrust
        double ddyThrust;           // Vertical acceleration due to thrust
        double aDegrees;
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

    public:
        // Constructors
        LunarModule(double dx, double dy , double y, double aDegrees);
        //LunarModule(const LunarModule& rhs);

        //
        double get_x() const;
        double get_y() const;

        double get_dx() const;
        double get_dy() const;

        double get_v() const;
        double get_aDegrees() const;

        void update_degrees(double aDegrees);
        void update_position(double t);

};

