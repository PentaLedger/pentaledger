//! \brief IO Industrial Namespaces
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
#include <vector>
#include "patterns/Observer.hpp"

namespace ioi
{
    namespace patterns
    {
        //! \brief Subject
        //!
        template <class T>
        class Subject
        {
        public:
            Subject() {}
            virtual ~Subject() {}
            void attach(Observer<T> &observer)
            {
                m_observers.push_back(&observer);
            }

            //! \brief Notify observers
            //! This function will notify all observers that are 
            //! registered.
            void notify()
            {
                std::vector<Observer<T> *>::iterator it;
                for (it = m_observers.begin(); it != m_observers.end(); it++)
                    (*it)->update(static_cast<T *>(this));
            }

        private:
            std::vector<Observer<T> *> m_observers;
        };
    }

}