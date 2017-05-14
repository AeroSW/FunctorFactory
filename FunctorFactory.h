/*!
 *	\author Kenneth Earl Cornett Jr.
 *	\date 2017.05.13
 *	\file FunctorFactory.h
 *	
 *	\copyright
 *	FunctorFactory is a Factory Design Program which brings portability
 *	and ease to implementing a Factory Design Pattern into a project.
 *	
 *	Copyright (C) 2017  Kenneth Earl Cornett Jr.
 *	
 *	This program is free software: you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation, either version 3 of the License, or
 *	(at your option) any later version.
 *	
 *	This program is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.
 *	
 *	You should have received a copy of the GNU General Public License
 *	along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef FUNCTOR_FACTORY_H
#define FUNCTOR_FACTORY_H

#include <map>
#include <string>

#include "Base.h"

namespace asw{

/*!
 *	\mainpage
 *	\section copyr_sec Copyright
 *	\copyright
 *	FunctorFactory is a Factory Design Program which brings portability
 *	and ease to implementing a Factory Design Pattern into a project.
 *	
 *	Copyright (C) 2017  Kenneth Earl Cornett Jr.
 *	
 *	This program is free software: you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation, either version 3 of the License, or
 *	(at your option) any later version.
 *	
 *	This program is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.
 *	
 *	You should have received a copy of the GNU General Public License
 *	along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *	
 *	\section intro_sec Introduction
 *
 *	FunctorFactory is an example of a Factory Design Pattern which
 *	allows the storage of not only many derived objects of *Base*, but also
 *	many constructors for each derived class.  As long as the arguments and
 *	the key are correctly known and used when requesting the creation of an
 *	object, then the object will be created correctly as long as it was
 *	registered with the FF_MACRO.
 *
 *	Registering classes and their appropriate constructors with FF_MACRO
 *	also ensures proper cleanup on termination of the program.
 *
 *	\section usage_sec Usage
 *	Usage for FF_MACRO
 *	1.	Include it in header file for the derived class.
 *	2.	Name does not have quotes, and can not be a C/C++ Keyword
 *	3.	Type is the type of the object being registered.
 *	4.	Any other argument must be the type of argument accepted by the constructor for the object being registered.
 *
 *	This is a derived class from an example Base class included in this
 *	set.
 *
 *	\code
 *
 *	struct Derived : public Base{
 *		Derived(int, int, float);
 *		Derived(int, int);
 *		Derived(const char *);
 *	}
 *	FF_MACRO(name_1, Derived, int, int, float);
 *	FF_MACRO(name_2, Derived, int, int);
 *	FF_MACRO(name_3, Derived, const char *);
 *
 *	Base * b = FunctorFactory::createObject<int, int, float>("name_1", 8, 8, 3.0);
 *	Derived * d = static_cast<Derived*>(FunctorFactory::createObject<const char*>("name_3","Hello World"));
 *
 *	\endcode
 *
 *	\section fin_sec Final Comments
 *	The way this Factory class works is once a class/constructor is
 *	included, memory is dynamically allocated for a DerivedFunctor
 *	object which stores a reference to the templated create function
 *	for this constructor.  It is then stored in the registry map with
 *	the key passed in by the user.
 *
 *	When using this structure for you personal programs, all that is
 *	needing to be done is switch out Base\* with [Your Base Class]\*'s
 *	name, then include the FF_MACRO registration in the classes you are
 *	wanting to register into the Factory design.
 */
struct FunctorFactory{
	private:
		/*!
		 *	\namespace asw
		 *	\class Functor
		 *	\brief A base class for easy storage into the registry
		 *	mapping for the unique templated DerivedFunctors.
		 *	\details This Functor Base class gives a common type
		 *	for all DerivedFunctor types which inherit from this
		 *	class.
		 */
		class Functor{ // Base Functor
			public:
				/*! \brief Destructor for the Base Functor */
				virtual ~Functor(){}
		};
		/*!
		 *	\class DerivedFunctor<Typename R, Typename... A>
		 *	\brief DerivedFunctor used to store templated create
		 *	methods from FunctorFactory class.
		 *	\details A class designed to store templated functions,
		 *	specifically FunctorFactory's templated static create
		 *	method.  It acts as a function by taking the Variadic
		 *	templated arguments.
		 */
		template<typename R, typename... A>
		struct DerivedFunctor : public Functor{ // Templated Derived Functors
			/*!
			 *	\brief Constructor for templated Derived Functor class.
			 *	\details Regular constructor for a templated
			 *	DerivedFunctor class.
			 *
			 *	\param f A function pointer for the function this class is
			 *	suppose to mimic.
			 */
			DerivedFunctor(R (*f)(A...)); // Regular Constructor
			/*!
			 *	\brief Copy Constructor for DerivedFunctor objects.
			 *	\details The copy constructor for the DerivedFunctor
			 *	object.  It copies the Function Pointer into this object's
			 *	function pointer.
			 *	
			 *	\param df A DerivedFunctor object to copy.
			 */
			DerivedFunctor(const DerivedFunctor<R,A...>& df); // Copy Constructor
			/*!
			 *	\brief Destructor for a DerivedFunctor object.
			 */
			virtual ~DerivedFunctor(); // Virtual Destructor
			/*!
			 *	\brief Overloaded () operator to give functionlike usage.
			 *	\details Overloaded () operator to allow use of
			 *	DerivedFunctor objects as if the are actual functions.
			 *
			 *	\param args... Are the arguments required by the function
			 *	this DerivedFunctor is representing.
			 *	\return R is the return type for the function which this
			 *	DerivedFunctor is representing.
			 *	\exception Any exception which would be thrown by the
			 *	representing Function
			 */
			virtual R operator()(A... args); // Overloaded () to allow function like use.
			/*!
			 *	\brief Overloaded assignment operator
			 *	\details Overloaded assignment operator which allows this
			 *	DerivedFunctor to represent the same function as the
			 *	DerivedFunctor being assigned to it.
			 */
			virtual DerivedFunctor<R,A...>& operator=(const DerivedFunctor<R,A...>& df); // Overloaded = to allow assignment
			
			private:
				R (*_f)(A...); //!< The actual function being called when overloaded () operator is used.
		};
		static std::map<std::string,Functor*>& getMap(); // Map pairing string keys to their Functors(stored as Base Functors)
		template<typename U, typename... A> // Templated create function which will create the derived objects being requested!
		static Base * create(A... args);
	public:
		/*!
		 *	\brief Registrator class which will register a create
		 *	Functor to create an object of type U with A... arguments.
		 *	\details Registers a DerivedFunctor object which acts as the
		 *	creator for an object of type U with A... as its constructor
		 *	arguments.
		 */
		template<typename U, typename... A> // Registrator class which registers objects
		struct Registrator{
			/*!
			 *	\brief Constructor for Registrator
			 *	\details A constructor for the Registrator. This is how to
			 *	register functions in a temporary way.
			 *
			 *	\param key The key to associate with this creator.
			 */
			Registrator(const std::string &key);
			/*!
			 *	\brief Destructor for Registrator
			 *	\details Destructor for Registrator, deallocates the Functor
			 *	created by the constructor of this class.
			 */
			virtual ~Registrator();
			private:
				std::string m_key;
		};
		/*!
		 *	\brief Creates the object referenced by the search key.
		 *	\details Creates the object with the constructor taking
		 *	Args... based on the key provided.
		 *	
		 *	\param skey The search key for the constructor of the object
		 *	being sought to be created.
		 *	\param args... The arguments required by that constructor.
		 *	\return Returns the reference to the requested object if it
		 *	exists, else it returns 'nullptr'.
		 *	\exception std::exception Throws an exception or any exception the
		 *	constructor of this requested object can throw.
		 */
		template<typename... A>
		static Base * createObject(const std::string &skey, A... args);
};

}
// Implementation of the derived functor's methods
template<typename R, typename... A> // Basic Constructor.
asw::FunctorFactory::DerivedFunctor<R,A...>::DerivedFunctor(R (*f)(A...)){
	_f = f;
}
template<typename R, typename... A> // Copy Constructor.
asw::FunctorFactory::DerivedFunctor<R,A...>::DerivedFunctor(const FunctorFactory::DerivedFunctor<R,A...>& df){
	_f = df._f;
}
template<typename R, typename... A> // Destructor
asw::FunctorFactory::DerivedFunctor<R,A...>::~DerivedFunctor(){}

// Overloaded Operators for Derived Functor
template<typename R, typename... A> // Overloaded () operator
R asw::FunctorFactory::DerivedFunctor<R,A...>::operator()(A... args){
	return _f(args...);
}
template<typename R, typename... A> // Overloaded = operator
asw::FunctorFactory::DerivedFunctor<R,A...>& asw::FunctorFactory::DerivedFunctor<R,A...>::operator=(const FunctorFactory::DerivedFunctor<R,A...>& df){
	_f = df._f;
}

std::map<std::string,asw::FunctorFactory::Functor*>& asw::FunctorFactory::getMap(){ // Get map class
	static std::map<std::string,asw::FunctorFactory::Functor*> m_map; // The actual map storing the functors.
	return m_map;
}

template<typename U, typename... A>
Base * asw::FunctorFactory::create(A... args){
	return new U(args...);
}

template<typename U, typename... A>
asw::FunctorFactory::Registrator<U,A...>::Registrator(const std::string &key){
	DerivedFunctor<Base*,A...> * df = new DerivedFunctor<Base*,A...>(FunctorFactory::create<U,A...>);
	getMap()[key] = df;
	m_key = key;
}
template<typename U, typename... A>
asw::FunctorFactory::Registrator<U,A...>::~Registrator(){
	auto it = getMap().find(m_key); // Find in case this Registrator's key still exists
	if(it != getMap().end()){ 	// Check if it does exist
		delete it->second; 		// If so, delete the Functor
		getMap().erase(it); 	// Erase it from the mapping. Cleanup is important!
	}
}

template<typename... A>
Base * asw::FunctorFactory::createObject(const std::string &skey, A... args){
	auto it = getMap().find(skey);
	if(it == getMap().end()) return nullptr;
	DerivedFunctor<Base*,A...> * df = static_cast<DerivedFunctor<Base*,A...>*>(it->second);
	return (*df)(args...);
}

	#ifndef FF_MACRO // The register macro to include in header files
		/*!
		 *	\def FF_MACRO(NAME, TYPE, ...)
		 *	Registers a derived object into the factory.
		 *	\param NAME The name to register as the key for the object (Do not use quotes).
		 *	\param TYPE The object's type.
		 *	\param ... The arguments' types associated with this registry's
		 *	creation.
		 */
		#define FF_MACRO(NAME,TYPE,...)\
			namespace { \
				::asw::FunctorFactory::Registrator<TYPE,##__VA_ARGS__> registrator_##NAME(#NAME); \
			}
	#endif

#endif // FUNCTOR_FACTORY_H
