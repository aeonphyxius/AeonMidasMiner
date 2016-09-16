/****************************************************************************
Copyright (c) 2016 Alejandro Santiago Varela

http://www.aeonphyxius.com

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/

#ifndef MIDAS_GENDELEGATE_H
#define MIDAS_GENDELEGATE_H

#include <iostream>
#include <string>
#include <cstring>
#include <typeinfo>

class EventData;

using namespace std;

/**
* This Delegate class encapsulates the class object and function when registering an
* event in the EventManager. 
*
*/

class GenericDelegate
{	
	//Create some typedefs to manage references easier
	typedef void *InstancePtr;
	typedef void(*InternalFunction)(InstancePtr, EventData*);	

public:
	GenericDelegate() = default;
	~GenericDelegate(){
		delete object;
	}

	template <class C, void (C::*Function)(EventData*)>
	static GenericDelegate* create(C* obj)
	{	
		GenericDelegate* del = new GenericDelegate();		
		del->Bind<C, Function>(obj);
		return del;
	}

	void OnEvent(EventData* ARG0)
	{
		return func(object, ARG0);
	}

	const std::string getClassTypeName() const{
		return delegate_class_name;	
	}


private:
	template <class C, void (C::*Function)(EventData*)>
	void Bind(C* obj)
	{		
		delegate_class_name = typeid(C).name();
		object = obj;
		func = &ClassMethod<C, Function>;
	}

	template <class C, void (C::*Function)( EventData*)>
	static void ClassMethod(InstancePtr ptr, EventData* ARG0)
	{
		return (static_cast<C*>(ptr)->*Function)(ARG0);
	}

	InternalFunction func;				/* Function to be called when the event is raised */
	InstancePtr object;					/* object registering this delegate */	
	std::string delegate_class_name;	/*class name of the object creating the delegate */

};

#endif #endif /* defined( MIDAS_GENDELEGATE_H )*/