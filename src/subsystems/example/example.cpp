#include "example.hpp"
#include <Arduino.h>


void ExampleSubsystem::setup()
{
    /*
    setup code here
    */
}



void ExampleSubsystem::loop()
{
    switch (state)
    {
    case EXAMPLE_RUNNING:
        /*
        running loop code here
        */
        break;

    case EXAMPLE_NOT_RUNNING:
        /*
        not running loop code here
        */
        break;

    } // end of switch btw
}