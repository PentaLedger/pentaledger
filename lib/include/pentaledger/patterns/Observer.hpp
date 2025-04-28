//! \brief IO Industrial Namespaces
//!
//! This file contains doxygen documentation for the specified
//! namespaces included in the project.
//!
//! \copyright
//!
//! This file is part of the flip distribution (https://github.com/xxxx or http://xxx.github.io).
//! Copyright (c) 2023 Joe Turner.
//!
//! This program is free software: you can redistribute it and/or modify
//! it under the terms of the GNU General Public License as published by
//! the Free Software Foundation, version 3.
//!
//! This program is distributed in the hope that it will be useful, but
//! WITHOUT ANY WARRANTY; without even the implied warranty of
//! MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
//! General Public License for more details.
//!
//! You should have received a copy of the GNU General Public License
//! along with this program. If not, see <http://www.gnu.org/licenses/>.
#ifndef _OBSERVER_HPP_
#define _OBSERVER_HPP_

namespace pentaledger
{
    namespace patterns
    {

        //! \brief Observer Template Class
        //! Observer is a behavioral design pattern that allows some
        //! objects to notify other objects about changes in their state.
        //!
        //! The Observer pattern provides a way to subscribe and
        //! unsubscribe to and from these events for any object that
        //! implements a subscriber interface.
        //!
        //! Example:
        //! \code
        //! class TemperatureAlarm : public Observer<Temperature>
        //! {
        //! public:
        //!      TemperatureAlarm() {}
        //!      ~TemperatureAlarm() {}
        //!      void update (Temperature *subject)
        //!         {
        //!         std::cout << "Temperature was changed, sound the alarm"
        //!               << std::endl;
        //!         subject->getTemperature();
        //!        }
        //!  };
        //! \endcode
        template <class T>
        class Observer
        {
        public:
            //! \brief Default constructor
            Observer() {}
            //! Virtual destructor
            virtual ~Observer() {}

            //! \brief Update 
            //! This function is called by the subject when an update
            //! is required.
            virtual void update(T *subject) = 0;
        };

    }
}

#endif
