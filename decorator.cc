#include "component.h"
#include "decorator.h"

Decorator::Decorator( Component *component ) : component{component} {}

Decorator::~Decorator() { delete component; }
