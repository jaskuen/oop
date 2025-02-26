#include "HtmlDecoder.h"
#include <iostream>
#include <sstream>
#include <string>
#include <map>

std::string HtmlDecode(const std::string& html)
{
    std::string possibleEntity, decodedString;
    for (char ch : html)
    {
        if (possibleEntity.size() == 0)
        {
            if (ch != '&')
            {
                decodedString += ch;
                continue;
            }
            possibleEntity += ch;
            continue;
        }
        possibleEntity += ch;
        if (ch == ';')
        {
            if (ENTITY_TO_CHAR.contains(possibleEntity))
            {
                decodedString += ENTITY_TO_CHAR.at(possibleEntity);
            }
            else
            {
                decodedString += possibleEntity;
            }
            possibleEntity = "";
        }
    }
    return decodedString;
}