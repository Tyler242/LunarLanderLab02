/*************************************************************
 * 1. Name:
 *      -your name-
 * 2. Assignment Name:
 *      Lab 02: Apollo 11
 * 3. Assignment Description:
 *      Simulate the Apollo 11 landing
 * 4. What was the hardest part? Be as specific as possible.
 *      -a paragraph or two about how the assignment went for you-
 * 5. How long did it take for you to complete the assignment?
 *      -total time in hours: reading the assignment, submitting, and writing code-
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

    LunarModule lunarModule = LunarModule(dx, dy, y, aDegrees);

    //
    cout << "For the next 5 seconds with the main engine on, the position of the lander is: \n";

    while (t <= 10) {

       // Update degrees again
       if (t == 6) {
           aDegrees = prompt("What is the new angle of the LM where 0 is up (degrees)? ");
           lunarModule.update_degrees(aDegrees);

           cout << "For the next 5 seconds with the main engine on, the position of the lander is: \n";
       }
        
        lunarModule.update_position(t);
        
        // Output
        cout.setf(ios::fixed | ios::showpoint);
        cout.precision(2);
        cout << int(t) << "s - x,y: (" << lunarModule.get_x() << ", " << lunarModule.get_y() 
            << ")m dx,dy: (" << lunarModule.get_dx() << ", " << lunarModule.get_dy() << ")m/s speed:"
            << lunarModule.get_v() << "m/s angle:" << lunarModule.get_aDegrees() << "deg" << endl;
        t++;
    }

    return 0;
}