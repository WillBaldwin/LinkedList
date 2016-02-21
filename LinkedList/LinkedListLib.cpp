/*
 Name:		LinkedListLib.cpp
 Created:	2/20/2016 4:01:26 PM
 Author:	Will
 Editor:	http://www.visualmicro.com
*/

#include "LinkedListLib.h"
#include <assert.h>

template <typename Object>
LinkedList<Object>::LinkedList()
{
	_count = 0;
}

template <typename Object>
LinkedList<Object>::~LinkedList()
{
	if (_count > 0)
	{
		//Clear the List in order to free memory
		Clear();
		assert(_count == 0);
	}
}

template <typename Object>
void LinkedList<Object>::Add(Object object)
{
	//Create a new List element
	ListElement* pNewListElement = new ListElement;

	//Store the template object in the item
	pNewListElement->object = object;

	if (_count == 0)
	{
		//Add first element to the empty list
		_pFirstElement = pNewListElement;
		_pFirstElement->pNextElement = pNewListElement;
		_pFirstElement->pPreviousElement = pNewListElement;

		_pLastElement = pNewListElement;
		_pLastElement->pNextElement = pNewListElement;
		_pLastElement->pPreviousElement = pNewListElement;
		_count = 1;
	}
	else if (_count > 0)
	{
		//Add this item to the end of the list
		pNewListElement->pNextElement = _pFirstElement;  //last element loops to first element
		pNewListElement->pPreviousElement = _pLastElement;

		//update the current last element to point to this new element
		_pLastElement->pNextElement = pNewListElement;

		//update the last element
		_pLastElement = pNewListElement;
		_count++;
	}
}

template <typename Object>
void LinkedList<Object>::AddAfter(uint16_t index, Object object)
{
	ListElement* pListElementToAddAfter = GetElementAt(index);
	ListElement* pListElementNew = new ListElement;
}


template <typename Object>
void LinkedList<Object>::RemoveAt(uint16_t index)
{
	ListElement* pListElementToRemove = GetElementAt(index);

	//Update the previous element
	pListElementToRemove->pPreviousElement->pNextElement
		= pListElementToRemove->pNextElement;

	//Update the next element
	pListElementToRemove->pNextElement->pPreviousElement
		= pListElementToRemove->pPreviousElement;

	//Recover Memory
	delete pListElementToRemove;

	_count--;
}

template <typename Object>
void LinkedList<Object>::ReplaceAt(uint16_t index, Object object)
{
	ListElement* pListElementToReplace = GetElementAt(index);
}


template <typename Object>
Object LinkedList<Object>::GetAt(uint16_t index)
{
	ListElement* pListElement = GetElementAt(index);
	return pListElement->object;
};

template <typename Object>
uint16_t LinkedList<Object>::Count()
{
	return _count;
}

template <typename Object>
void LinkedList<Object>::Clear()
{
	while (_count > 0)
	{
		//Remove the last item
		RemoveAt(_count - 1);
	}
}


