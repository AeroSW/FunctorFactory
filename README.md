# FunctorFactory
A basic factory design pattern which is simple and easy to use!

# Copyright
FunctorFactory is a Factory Design Program which brings portability
and ease to implementing a Factory Design Pattern into a project.
Copyright (C) 2017  Kenneth Earl Cornett Jr.

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.
 
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

# Introduction
FunctorFactory is an example of the Factory Design Pattern which allows
the storage of not only objects and their derivations, but also multiple
constructors for each object and their derivation as long as the keys
for each constructor is **unique**.

# Usage
## Conditions
 1. Include the **Macro** in the files with the object's declaration to
 register them.
 2. Name being used to register must not have quotes around it.
 3. Type is the object's class name that is being register, its type if
 you will.
 4. The arguments used in the constructor wishing to be registered, must
 have their types included as well as part of the parameters.
 
## Example Code
    struct Derived : public Base
    {
        Derived(int a, int b, float c);
        Derived(int a, int b);
        Derived(const char * c);
    }
    
    // Example Macros to register the different types of constructors.
    FF_MACRO(name_1, Derived, int, int, float);
    FF_MACRO(name_2, Derived, int, int);
    FF_MACRO(name_3, Derived, const char *);
    
    // Examples on how to create objects after Registering them with the Macro
    Base * b = FunctorFactor::createObject<int, int, float>("name_1", 8, 8, 3.0);
    Derived * d = static_cast<Derived *>(FunctorFactory::createObject<const char*>("name_3","Hello World"));

# Final Comments
The way this Factory class works is once a class/constructor is included,
memory is dynamically allocated for a **Functor** to be used in place of a
templated **create** function for the registered object.  This **Functor** is
then placed in a map to be referenced by the **name**/key specified.

This class/structure is easy to adapt for your personal projects and classes.
Switch out all the return types which are 'Base \*s' with your own object that
will act as the **Base** type in your program.  Feel free to change *FF_MACRO* to
have another name, such as REGISTER or Register_Macro, if you would like.

## Locations
### Line 32
#include "**Base**.h"

### Line 183
static **Base**\* create(A... args);

### Line 225
static **Base**\* createObject(const std::string &skey, A... args);

### Line 257
**Base** \* asw::FunctorFactory::create(A... args){

### Line 263
DerivedFunctor<**Base**\*,A...> \* df = new DerivedFunctor<**Base**\*,A...>(FunctorFactory::create<U,A...>);

### Line 277
**Base** \* asw::FunctorFactory::createObject(const std::string &skey, A... args){

### Line 280
DerivedFunctor<**Base**\*,A...> \* df = static_cast<DerivedFunctor<**Base**\*,A...>\*>(it->second);
