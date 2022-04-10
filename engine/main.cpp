#include "Field.h"
#include "Fighter.h"
#include "Network.h"


void main()
{
	auto _field = std::make_shared<engine::Field>(11, 22);
	auto _fighter = std::make_unique<engine::Fighter>(_field, std::make_pair(3, 3), 13);
	_fighter->Run();
	system("pause");
}
