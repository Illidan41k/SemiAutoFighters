#include "Field.h"
#include "Fighter.h"
#include "Network.h"


void main()
{
	auto _field = std::make_shared<Field>(10);
	auto _fighter = std::make_unique<engine::Fighter>(_field, std::make_pair(3, 3));
	_fighter->Run();
	system("pause");
}
