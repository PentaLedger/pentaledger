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
#include <string>
#include <vector>
#include <sstream>
#include "pentaledger/utility/wordwrap.h"

namespace pentaledger {
namespace utility {

std::string wordwrap(const std::string& str, int width) 
{
    // Handle empty string or invalid width
    if (str.empty() || width <= 0) {
        return str;
    }

    std::stringstream ss(str);
    std::string word;
    std::string result;
    int currentLineLength = 0;

    while (ss >> word) {
        // If adding this word would exceed the width
        if (currentLineLength + word.length() > width) {
            // If this is not the first word on the line, add a newline
            if (currentLineLength > 0) {
                result += '\n';
                currentLineLength = 0;
            }
            
            // If the word itself is longer than width, we have to break it
            if (word.length() > width) {
                // Break the word into chunks of 'width' characters
                for (size_t i = 0; i < word.length(); i += width) {
                    if (i > 0) {
                        result += '\n';
                    }
                    result += word.substr(i, width);
                }
                currentLineLength = word.length() % width;
                if (currentLineLength == 0) {
                    currentLineLength = width;
                }
            } else {
                result += word;
                currentLineLength = word.length();
            }
        } else {
            // Add space if this is not the first word on the line
            if (currentLineLength > 0) {
                result += ' ';
                currentLineLength++;
            }
            result += word;
            currentLineLength += word.length();
        }
    }

    return result;
}

} // namespace utility
} // namespace pentaledger


