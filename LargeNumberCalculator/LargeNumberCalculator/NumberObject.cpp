#include "NumberObject.h"

ostream& operator<<(ostream& out, NumberObject& object)
{
	object.output(); // cout<<Integer;
	return out;
}