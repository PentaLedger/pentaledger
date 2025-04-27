/*
 * @(#) Command.hpp
 *
 * @author Joe Turner (joe@agavemountain.com)
 *
 * Copyright (c) 2010 Agave Mountain, Inc.
 * All rights reserved.
 *
 * This software is confidential and proprietary information of Agave Mountain
 * ("Confidential Information").  You shall not disclose such Confidential
 * Information and shall use it only in accordance with the terms of the
 * license agreement you entered into with Agave Mountain.
 *
 * Copyright (C) 2010 Agave Mountain, Inc.; All right reserved.
 */
#ifndef _COMMAND_H_
#define _COMMAND_H_

namespace pentaledger
{
	//! \brief Patterns namespace
	//!
	//! This namespace contains all of the patterns related code for the PentaLedger project.
	//!
	namespace patterns
	{

		/**
		 * \brief Command pattern class.
		 *
		 * The Command pattern interface base class.
		 */
		class Command
		{
		public:
			virtual void execute() = 0;
		};
	}
}; // namespace.

#endif
