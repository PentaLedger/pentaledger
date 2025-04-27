/*
 * @(#) Uncopyable.hpp
 * 
 * @author Joe Turner (joe@agavemountain.com)
 * 
 * Copyright (c) 2011 Exam Cycle, LLC
 * All rights reserved.
 * 
 * This software is confidential and proprietary information of Agave Mountain
 * ("Confidential Information").  You shall not disclose such Confidential
 * Information and shall use it only in accordance with the terms of the
 * license agreement you entered into with Agave Mountain.
 * 
 * Copyright (C) 2011 Exam Cycle, LLC; All right reserved.
 */

#ifndef UNCOPYABLE_H_
#define UNCOPYABLE_H_

namespace pentaledger {
namespace patterns {
	
//! \brief Uncopyable base class.
//!
/// The Uncopyable class is a base class defined for defining that a derived class
/// not be allowed to be copied or assigned.  This assumes that a derived class does not
/// explicitly specify either the copy constructor or assignment operator in which case
/// this class will be ineffective.  This class works by providing private copy constructor and
/// assignement operator that cannot be invoked by the automatically compiler generated versions of a
/// derived class.  Therefore any assignment, or copying done in client code doesn't compile.
//! \code
//! // Example:
/// Class MyClass : Uncopyable
/// {
///   public:
///     MyClass() {};
///     
///    // DO NOT define copy constructor or operator=
/// };
///
///  void SomeFunction()
///  {
///     MyClass class1;
///     MyClass class2(class1);  // won't compile.
///     MyClass class3 = class1; // won't compile either.
/// }
//! \endcode
class Uncopyable
{
protected:
	
	Uncopyable() {}
	~Uncopyable() {}
private:
	Uncopyable(const Uncopyable&);
	Uncopyable& operator=(const Uncopyable&);
};
};
}; //namespace
#endif /*UNCOPYABLE_H_*/
