/*
 *  glew.cp
 *  glew
 *
 *  Created by Tobias Svensson on 12/10/12.
 *  Copyright (c) 2012 Tobias Svensson. All rights reserved.
 *
 */

#include "glew.h"
#include "glewPriv.h"

CFStringRef glewUUID(void)
{
	Cglew* theObj = new Cglew;
	return theObj->UUID();
}

CFStringRef Cglew::UUID()
{
	return CFSTR("0001020304050607");
}
