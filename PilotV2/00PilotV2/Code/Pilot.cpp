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

#include <sstream>
#include <process.h> // TODO: discuss our multithreading plan
#include <thread> // TODO: discuss our multithreading plan

// client // function to run client loop execution
Client * client;
void runClient()
{
	while (true)
	{
		client->update();
	}
}

// server // function to run server loop execution
Server * server;
void runServer(void *)
{
	while (true)
	{
		server->update();
	}
}

// Base game main 
/* TO DO: This will be determining if user is a client or a server
before deploying relevant quieries and functions..*/

int main(int argc, char * argv[])
{
	std::thread * runThread;
	QuickDraw window;
	View & view = (View &)window;
	Controller & controller = (Controller &)window;

	Room model(-500, 500, 500, -500);

	// Create a timer to measure the real time since the previous game cycle.
	Timer timer;
	timer.mark(); // zero the timer.
	double lasttime = timer.interval();
	double avgdeltat = 0.0;

	double scale = 1.0;

	bool amClient = false;

	// initialize client/server //
	// server
	if (argc > 2) {
		// broaden display
		scale = 0.8;
		server = new Server(&model, controller);

		// server thread
		//runThread = new std::thread(&runServer);
		_beginthread(runServer, 0, (void*)12);
	}
	// client
	else {
		amClient = true;

		// create player ship
		Ship * ship = new Ship(controller, Ship::INPLAY, "You");
		model.addActor(ship);

		if (argc == 1)
		{
			// query client for server address
			std::cout << "Enter the IP address of the server you wish to connect to: " << std::endl;
			char input[16];
			std::cin >> input;

			// pass to server
			client = new Client(input, *ship);
		}
		else
		{
			client = new Client(argv[1], *ship);
		}

		// run client loop
		runThread = new std::thread(&runClient);
	}

	while (true)
	{
		// Calculate the time since the last iteration.
		double currtime = timer.interval();
		double deltat = currtime - lasttime;

		// Run a smoothing step on the time change, to overcome some of the
		// limitations with timer accuracy.
		avgdeltat = 0.2 * deltat + 0.8 * avgdeltat;
		deltat = avgdeltat;
		lasttime = lasttime + deltat;

		// Allow the environment to update.
		model.update(deltat);

		// Schedule a screen update event.
		view.clearScreen();

		// score 
		std::ostringstream txtDisplay;

		// display
		double x = 0, y = 0;
		if (amClient)
		{
			// camera
			client->player_ship->getPosition(x, y);

			// score
			txtDisplay << "Score: " << client->player_ship->getScore();
		}
		else
		{
			txtDisplay << "Server initialised. \nIP: " << argv[1] << "\nName: " << argv[2];
		}
		// display text
		view.drawText(20, 20, txtDisplay.str(), 0, 0, 255);

		model.display(view, x, y, scale);

		view.swapBuffer();
	}

	delete client;
	delete server;
	return 0;
}