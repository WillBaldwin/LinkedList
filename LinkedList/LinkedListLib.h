/*
Name:		LinkedListLib.h
Created:	2/20/2016 4:01:26 PM
Author:	Will Baldwin
Editor:	http://www.visualmicro.com
*/

#ifndef _LINKEDLISTLIB_h
#define _LINKEDLISTLIB_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif



template <typename ListType>

class LinkedList
{
private:
	struct ListElement
	{
		ListElement* pPreviousElement; //link to previous element
		ListElement* pNextElement;    //link to next element
		ListType object;      //object to store in the element
	};
	ListElement* _pLastElement;
	ListElement* _pFirstElement;
	uint16_t _count;

public:
	LinkedList()
	{
		_count = 0;
	};

	~LinkedList()
	{
		if (_count > 0)
		{
			//Clear the List in order to free memory
			Clear();
		}
	};

	void Add(ListType object)
	{
		InsertAt(_count, object);
	};

	//Places a new element at a specific index moving
	//any existing elements over one to make room.
	//
	//If index is out-of-range nothing happens
	void InsertAt(uint16_t index, ListType object)
	{
		if (index > _count) return; /*beyond bounds do nothing*/

									//Create a new element
		ListElement* pNewListElement = new ListElement;

		//Store the object in the element
		pNewListElement->object = object;

		if (_count == 0)
		{
			//Add first element to an empty list
			_pLastElement = pNewListElement;
			_pFirstElement = pNewListElement;
			_pFirstElement->pNextElement = pNewListElement;
			_pFirstElement->pPreviousElement = pNewListElement;
			_count = 1;
		}
		else if (_count > 0)
		{
			bool insertingAtBegining = (index == 0);
			bool insertingAtEnd = (index == _count);

			ListElement* pListElementToAddBefore = GetElementAt(index);
			if (pListElementToAddBefore == nullptr) return;

			//insert into the list
			pNewListElement->pPreviousElement = pListElementToAddBefore->pPreviousElement;
			pNewListElement->pNextElement = pListElementToAddBefore;

			pListElementToAddBefore->pPreviousElement->pNextElement = pNewListElement;
			pListElementToAddBefore->pPreviousElement = pNewListElement;

			if (insertingAtBegining)
			{
				_pFirstElement = pNewListElement;
			}

			if (insertingAtEnd)
			{
				_pLastElement = pNewListElement;
			}

			_count++;
		}
	};

	//Removes an element at a specific index moving
	//any existing elements over one.
	//
	//If index is out-of-range nothing happens
	void RemoveAt(uint16_t index)
	{
		if (index > _count - 1) return; /*beyond bounds do nothing*/

		bool removingFromBegining = (index == 0);
		bool removingFromEnd = (index == _count - 1);

		ListElement* pListElementToRemove = GetElementAt(index);
		if (pListElementToRemove == nullptr) return;

		//Update the previous element
		pListElementToRemove->pPreviousElement->pNextElement
			= pListElementToRemove->pNextElement;

		//Update the next element
		pListElementToRemove->pNextElement->pPreviousElement
			= pListElementToRemove->pPreviousElement;

		if (removingFromBegining)
		{
			_pFirstElement = pListElementToRemove->pNextElement;
		}

		if (removingFromEnd)
		{
			_pLastElement = pListElementToRemove->pPreviousElement;
		}

		//Recover Memory
		delete pListElementToRemove;

		_count--;
	};

	//Returns an object at a specific index
	//
	//If index is out-of-range returns NULL
	ListType GetAt(uint16_t index)
	{
		if (index > _count - 1) return NULL; /*return NULL*/

		ListElement* pListElement = GetElementAt(index);
		if (pListElement == nullptr) return NULL;

		return pListElement->object;
	};

	//returns the number of elements int the list
	uint16_t Count()
	{
		return _count;
	};

	//clears the list
	void Clear()
	{
		while (_count > 0)
		{
			//Remove the last item
			RemoveAt(_count - 1);
		}
	};

private:
	ListElement* GetElementAt(uint16_t index)
	{
		if (_count == 0) return nullptr;

		ListElement* pListElement = _pFirstElement;
		//Find the element at index position
		uint16_t i = 0;
		while (i < index)
		{
			pListElement = pListElement->pNextElement; i++;
		}
		return pListElement;
	};
};


#endif
