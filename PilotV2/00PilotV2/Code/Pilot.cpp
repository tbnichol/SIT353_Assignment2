// 00Pilot code - main() function
// 
// Initialise system and create playing arena with all actors.
//
// This code has been modified to improve the keyboard handling, allowing 
// multiple keys to be proceesed at once (ie., FIRE & THRUST)


#include "QuickDraw.h"
#include "Timer.h"

#include "Room.h"
#include "Ship.h"

#include <sstream>

int main(int argc, char * argv [])
{
	QuickDraw window;
	View & view = (View &) window;
	Controller & controller = (Controller &) window;

	Room model (-500, 500, 500, -500);
	Ship * ship = new Ship (controller, Ship::INPLAY, "You");
	model.addActor (ship);

	// Add some opponents. These are computer controlled - for the moment...
	Ship * opponent;
	opponent= new Ship (controller, Ship::AUTO, "Mick");
	model.addActor (opponent);
	opponent = new Ship (controller, Ship::AUTO, "Jane");
	model.addActor (opponent);
	opponent = new Ship (controller, Ship::AUTO, "Cedrick");
	model.addActor (opponent);

	// Create a timer to measure the real time since the previous game cycle.
	Timer timer;
	timer.mark (); // zero the timer.
	double lasttime = timer.interval ();
	double avgdeltat = 0.0;

	double scale = 1.0;

	while (true)
	{
		// Calculate the time since the last iteration.
		double currtime = timer.interval ();
		double deltat = currtime - lasttime;

		// Run a smoothing step on the time change, to overcome some of the
		// limitations with timer accuracy.
		avgdeltat = 0.2 * deltat + 0.8 * avgdeltat;
		deltat = avgdeltat;
		lasttime = lasttime + deltat;

		// Allow the environment to update.
		model.update (deltat);

		// Schedule a screen update event.
		view.clearScreen ();
		double offsetx = 0.0;
		double offsety = 0.0;
		(*ship).getPosition (offsetx, offsety);
		model.display (view, offsetx, offsety, scale);

		std::ostringstream score;
		score << "Score: " << ship->getScore ();
		view.drawText (20, 20, score.str (), 0, 0, 255);
		view.swapBuffer ();
	}

	return 0;
}

