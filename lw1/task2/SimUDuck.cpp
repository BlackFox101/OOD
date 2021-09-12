#include "Ducks.h"

using namespace std;

void DrawDuck(Duck const& duck)
{
	duck.Display();
}

void PlayWithDuck(Duck& duck)
{
	DrawDuck(duck);
	//duck.Quack();
	duck.Fly();
	//duck.Dance();
	cout << endl;
}

int main()
{
	ModelDuck modelDuck;
	modelDuck.Fly();

	modelDuck.SetFlyBehavior(make_unique<FlyWithWings>());
	modelDuck.Fly();
	modelDuck.Fly();

	modelDuck.SetFlyBehavior(make_unique<FlyWithJetEngine>());
	modelDuck.Fly();
	modelDuck.Fly();
	modelDuck.Fly();

	modelDuck.SetFlyBehavior(make_unique<FlyWithWings>());
	modelDuck.Fly();
	modelDuck.Fly();

	modelDuck.SetFlyBehavior(make_unique<FlyNoWay>());
	modelDuck.Fly();
	modelDuck.Fly();
}
