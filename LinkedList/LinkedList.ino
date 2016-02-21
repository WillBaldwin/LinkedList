/*
 Name:		LinkedList.ino
 Created:	2/20/2016 4:01:26 PM
 Author:	Will Baldwin
 Editor:	http://www.visualmicro.com
*/

#include "LinkedListLib.h"

// the setup function runs once when you press reset or power the board
void setup() 
{
	LinkedList<uint16_t> linkedList;

	//Initialize the list with ten elements
	for (uint16_t index = 0; index < 9; index++)
	{
		linkedList.Add(index);
	}

	//Remove the first element
	linkedList.RemoveAt(0);

	//Get the stored object at index
	uint16_t value = linkedList.GetAt(0);

	//Get the current number of elements
	uint16_t count = linkedList.Count();

	//Remove the last element
	linkedList.RemoveAt(count-1);

	//Clear the list
	linkedList.Clear;
}

// the loop function runs over and over again until power down or reset
void loop() 
{
  
}
