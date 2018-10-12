// 00Pilot code - main() function
// 
// Initialise system and create playing arena with all actors.
//
// This code has been modified to improve the keyboard handling, allowing 
// multiple keys to be proceesed at once (ie., FIRE & THRUST)

#define WIN32_LEAN_AND_MEAN // Prevents windows.h from importing winsock.h project wide.


#include "QuickDraw.h"
#include "Timer.h"
#include "Room.h"
#include "Ship.h"
#include "Server.h"
#include "GameClientSide.h"

#include <sstream>
#include <process.h> // TODO: discuss our multithreading plan
#include <thread> // TODO: discuss our multithreading plan

// client // function to run client loop execution
Client * client;
void runClient()			// TODO: Move to GameClientSide or Client objects
{
	while (true)
	{
		client->update();
	}
}

// server // function to run server loop execution
Server * server;
void runServer(void *)		// TODO: Move to GameServerSide or Server objects
{
	while (true)
	{
		server->update();
	}
}

// Base game main 
/* TO DO: This will be determining if user is a client or a server 
before deploying relevant quieries and functions..*/

int main(int argc, char * argv [])
{
	std::thread * runThread;
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

	if (argc = 1) {
		client = new Client("127.0.0.1", *ship);
		// run client loop
		runThread = new std::thread(&runClient);
		//_beginthread(runClient, 0, (void*)12, &ship);
		// TO DO: Discuss the use of modern C++11 standard threads, instead of C++98 processes
	}
	else {
		// initialize client/server
		server = new Server(&model, controller);
		// server thread // look into this *****
		_beginthread(runServer, 0, (void*)12);
	}

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

	delete client;
	delete server;
	return 0;
}