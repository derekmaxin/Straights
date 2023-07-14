#ifndef _DECORATOR_H_
#define _DECORATOR_H

#include "component.h"

class Decorator: public Component {
	protected:
		Component *component;
	public:
		Decorator( Component *component );
		virtual ~Decorator();
};

#endif
