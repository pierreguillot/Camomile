/*
 // Copyright (c) 2015-2017 Pierre Guillot.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "PluginParser.h"

void CamomileParser::perform(juce::File const& file)
{
    var main;
    FileInputStream stream(file);
    if(stream.openedOk())
    {
        String line = stream.readNextLine();
        while(line.isNotEmpty())
        {
            main.append(perform(line));
            line = stream.readNextLine();
        }
    }
}

var CamomileParser::perform(String const& line)
{
    
    DynamicObject obj;
    Array<var> array;
    int start = 0, next = line.indexOfChar(' ');
    String const name = (next == -1)  ? line.substring(0) : line.substring(0, next);
    while(next != -1)
    {
        start = next+1;
        next = line.indexOfChar(start+1, ' ');
        String const word = (next == -1)  ? line.substring(0) : line.substring(0, next);
        if(word.startsWithChar('-'))
        {
            array.add(var());
        }
        else
        {
            JSON::parse(StringRef(word));
        }
    }
    
    return var();
}
