#include "Ducks.h"

using namespace std;

void DrawDuck(Duck const& duck)
{
	duck.Display();
}

void PlayWithDuck(Duck& duck)
{
	DrawDuck(duck);
	duck.Quack();
	duck.Fly();
	duck.Dance();
	cout << endl;
}

int main()
{
	ModelDuck modelDuck;
	PlayWithDuck(modelDuck);

	modelDuck.SetFlyBehavior(FlyWithWings);
	PlayWithDuck(modelDuck);
	modelDuck.SetFlyBehavior(FlyWithJetEngine);
	PlayWithDuck(modelDuck);

	modelDuck.SetQuackBehavior(SqueakBehavior);
	PlayWithDuck(modelDuck);

	modelDuck.SetDanceBehavior(DanceWaltz);
	PlayWithDuck(modelDuck);
	modelDuck.SetDanceBehavior(DanceMinuet);
	PlayWithDuck(modelDuck);
}
