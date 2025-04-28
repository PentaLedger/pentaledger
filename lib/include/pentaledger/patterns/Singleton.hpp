/*
 * @(#) Singleton.hpp
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

#ifndef _SINGLETON_HPP
#define _SINGLETON_HPP

namespace pentaledger
{

  //! Design patterns namespace
  namespace patterns
  {

    /// \brief Meyers singleton pattern class
    ///
    /// This template is used to create a Meyers singleton pattern class
    /// in a consistant manner and in a way which permits easy derivation
    /// and extension of singleton classes not easily accomplished using
    /// other techniques.
    ///
    /// To use this template, you will need to do the following :
    ///   -# Define your class by deriving from a specialization of this
    ///      template.
    ///   -# Ensure that your class includes the template specialization
    ///      as a class friend.
    ///   -# Ensure that your class has a protected constructor.
    ///   -# Ensure that your class has a protected copy constructor.
    ///
    /// \code
    ///     class MySingleton : public Singleton<MySingleton>
    ///     {
    ///       public:
    ///         void    someMethod();
    ///         int     someOtherMethod();
    ///
    ///       protected:
    ///         MySingleton() {};
    ///         MySingleton(MySingleton const &) {};
    ///
    ///         friend class Singleton<MySingleton>;
    ///     };
    /// \endcode
    ///
    /// This template uses the Meyers singleton pattern, which takes advantage
    /// of the fact that static objects within functions or methods are not
    /// initialized until that function or method is called, unlike static
    /// primitives.   This approach has several benefits over other
    /// singleton design patterns:
    ///   -# The reference returned is not as tempting to delete as a
    ///      pointer might be
    ///   -# The singleton is automatically cleaned up by the C++
    ///      teardown code, same as any other static object
    ///   -# No static pointers or static class members are required other
    ///      than the singleton accessor method
    ///
    /// For more information on this and other design patterns, consult
    /// "Effective C++" by Scott Meyers.
    ///
    template <class T>
    class Singleton
    {
    public:
      /// \brief Singleton accessor method
      ///
      /// This method contains a statically allocated instance of the
      /// singleton object and returns a reference to it when asked.
      /// Note that the instance is not initialized until this method
      /// is called, and is automatically cleaned up once the main()
      /// function exits.
      ///
      /// \returns
      ///     Reference to singleton instance
      ///
      static T &instance()
      {
        // Return reference to the static singleton
        static T theInstance;
        return theInstance;
      };
    };

  }

}; // namespace

#endif
