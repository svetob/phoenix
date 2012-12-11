/*
 *  glewPriv.h
 *  glew
 *
 *  Created by Tobias Svensson on 12/10/12.
 *  Copyright (c) 2012 Tobias Svensson. All rights reserved.
 *
 */

#include <CoreFoundation/CoreFoundation.h>

#pragma GCC visibility push(hidden)

class Cglew {
	public:
		CFStringRef UUID(void);
};

#pragma GCC visibility pop
