/* bzflag
 * Copyright (c) 1993 - 2001 Tim Riker
 *
 * This package is free software;  you can redistribute it and/or
 * modify it under the terms of the license found in the file
 * named LICENSE that should have accompanied this file.
 *
 * THIS PACKAGE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 */

#include "TimeKeeper.h"
#include "PlatformFactory.h"

TimeKeeper				TimeKeeper::currentTime;
TimeKeeper				TimeKeeper::tickTime;

const TimeKeeper&		TimeKeeper::getCurrent()
{
	currentTime.seconds = PLATFORM->getClock();
	return currentTime;
}

const TimeKeeper&		TimeKeeper::getTick() // const
{
	return tickTime;
}

void					TimeKeeper::setTick()
{
	tickTime.seconds = PLATFORM->getClock();
}
