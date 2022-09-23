/*************************************************************
 * 1. Name:
 *      Caleb Rasmussen & Tyler Shellman
 * 2. Assignment Name:
 *      Lab 02: Apollo 11
 * 3. Assignment Description:
 *      Simulate the Apollo 11 landing
 * 4. What was the hardest part? Be as specific as possible.
 *      The hardest part of this assessment was knowing if we
 *      properly implement the solution since the example test
 *      case was wrong. All our numbers seem to be moving the in
 *      right directions and are similar to last time, so
 *      hopefully, it all works correctly.
 * 5. How long did it take for you to complete the assignment?
 *      2.5 hours each
 *****************************************************************/

#include <iostream>
#include <cmath>
using namespace std;

#include "LunarModule.h"


/**************************************************
 * PROMPT
 * A generic function to prompt the user for a double
 * INPUT
 *      message : the message to display to the user
 * OUTPUT
 *      response : the user's response
 ***************************************************/
double prompt(string message) {
    cout << message;

    double response;
    cin >> response;

    return response;
}


/****************************************************************
 * MAIN
 ****************************************************************/
int main()
{
    // Prompt for input and variables to be computed
    double dx = prompt("What is your horizontal velocity (m/s)? ");
    double dy = prompt("What is your vertical velocity (m/s)? ");
    double y = prompt("What is your altitude (m)? ");
    double aDegrees = prompt("What is the angle of the LM where 0 is up (degrees)? ");
    double t = 1;

    // Create LunarModule object with user inputs
    LunarModule lunarModule = LunarModule(dx, dy, y, aDegrees);


    // Loops 10, twice for each time
    cout << "\nFor the next 5 seconds with the main engine on, the position of the lander is: \n\n";

    while (t <= 10) {

       // Update degrees again
       if (t == 6) {
           aDegrees = prompt("\nWhat is the new angle of the LM where 0 is up (degrees)? ");
           lunarModule.update_degrees(aDegrees);

           cout << "\nFor the next 5 seconds with the main engine on, the position of the lander is: \n\n";
       }
        
        lunarModule.update_position(t);
        
        // Output
        cout.setf(ios::fixed | ios::showpoint);
        cout.precision(2);
        cout << int(t) 
            << "s - x,y:(" << lunarModule.getX() << ", " << lunarModule.getY() 
            << ")m  dx,dy:(" << lunarModule.getDx() << ", " << lunarModule.getDy() 
            << ")m/s  speed:" << lunarModule.getV() 
            << "m/s  angle:" << lunarModule.getADegrees() << "deg" << endl;

        t++; // increase time
    }

    return 0;
}