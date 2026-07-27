#include <iostream>
#include "struct.h"
#include "Global.h"

void initializeRooms()
{
    for (int i = 0; i < MAX_ROOM; i++)
    {
        rooms[i].roomID = "R";

        if (i + 1 < 10)
            rooms[i].roomID += "00";
        else if (i + 1 < 100)
            rooms[i].roomID += "0";

        rooms[i].roomID += to_string(i + 1);

        if (i < 30)
        {
            rooms[i].roomType = "Single";
            rooms[i].price = singlePrice;
        }
        else if (i < 80)
        {
            rooms[i].roomType = "Double";
            rooms[i].price = doublePrice;
        }
        else
        {
            rooms[i].roomType = "Deluxe";
            rooms[i].price = deluxePrice;
        }

        rooms[i].available = true;
    }
}