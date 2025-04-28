/*
 * @(#) {%filename%}
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
#ifndef _WORDWRAP_H_
#define _WORDWRAP_H_

#include <string>

namespace pentaledger
{
    namespace utility
    {

        /**
         * This is a word wrap function that will add line breaks.
         *
         * Word wrap is the additional feature of most text editors, word processors,
         * and web browsers, of breaking lines between and not within words, except
         * when a single word is longer than a line.
         *
         * @param str The input string to be word-wrapped
         * @param width The maximum line width (default: 80 characters)
         * @return A new string with appropriate line breaks inserted
         */
        std::string wordwrap(const std::string &str, int width = 80);

    }
}

#endif
