⚙️ How It Works

1. Press Start
	Engine starts
	Gear indicator turns green
	Start button turns red and changes to Stop
 	Accelerator button (A) becomes enabled
2. Press and hold A (Accelerator)
	Speed increases
	Distance traveled increases
	Temperature increases
	Fuel decreases
3. Overheating Behavior
	If temperature exceeds threshold:
		Temperature indicator turns red
		Speed automatically reduces
4. Release Accelerator
	Speed gradually decreases
	Vehicle slows down

🖱 Accelerator Behavior
  To continuously accelerate:
	Keep the mouse cursor pressed on A
	Moving the cursor away from the button will cause deceleration

🧪 Run Modes
 1️⃣ Debug Mode
	Fast simulation
	Distance, fuel, and temperature change quickly
	Useful for testing

2️⃣  Release Mode
	Realistic simulation timing
	Fuel decreases every 36 km
	Temperature increases every 10 km

🔧 Adjustable Parameters
	You can modify the following constants to experiment with behavior:
		MILAGE
		averageDistanceToRaiseTemp
	Reducing these values makes changes visible faster.

⚠️ Known Issue
   There is a minor UI interaction bug:
   If you press and hold the A button for a long time:
	Releasing the mouse while the cursor remains over the button may continue acceleration.
	Moving the cursor away stops acceleration.
	Clicking once resets normal behavior.
  This is a known interaction issue related to mouse event handling.

🛠 Built With
	Qt 6
	QML
	C++
	CMake

Detail description

🚗 Meter Console Hood
Qt/QML Instrument Cluster Simulation (Automotive-Inspired Design)

A modular, event-driven instrument cluster simulation built using Qt 6 (C++ backend) and QML frontend, designed to mimic real automotive dashboard behavior including speed, fuel consumption, temperature dynamics, and engine state transitions.
This project focuses on clean architecture, state-driven behavior, and real-time simulation modeling.

📌 Key Features
   Core Instrumentation
	Dynamic Speedometer (Acceleration / Deceleration model)
	Fuel Gauge with distance-based consumption logic
	Temperature Gauge with progressive thermal modeling
	Distance Traveled (Odometer-style accumulation)
	Gear State Indicator
	Engine Start / Stop State Machine

  Safety & Simulation Logic
	Overheating detection
	Automatic speed reduction during overheating
	Fuel exhaustion state handling
	Real-time property updates via Qt signal/slot mechanism

  User Interaction
	Accelerator (press-and-hold behavior)
	Fuel refill slider
	Visual state transitions (color-coded indicators)

🧠 System Architecture (MVVM-Inspired Design)

	This project follows an MVVM-style separation adapted for Qt/QML.

	+-------------------+
	|        View       |
	|   (QML Layer)     |
	+-------------------+
        	  ↑
	          |  Property Bindings
	          |  Signals
	          ↓
	+-------------------+
	|    ViewModel      |
	| SpeedTempAndDistanceCtrl (C++)
	+-------------------+
        	  ↑
	          |  State logic
	          ↓
	+-------------------+
	|      Model        |
	|  Internal State   |
	|  Distance, Fuel,  |
	|  Temp, Engine     |
	+-------------------+

🔹 1. View (QML Layer)
      Responsible for:
	Rendering gauges and indicators
	Handling user interaction
	Binding to exposed C++ properties
	Visual state transitions (colors, animations)

     The UI layer contains:
	SpeedMeter.qml
	TemperatureGauge.qml
	CustomGauge.qml
	Main layout

   The view contains no business logic.

🔹 2. ViewModel (C++ Controller Layer)
      SpeedTempAndDistanceCtrl
      Responsibilities:
 	Exposes Q_PROPERTY values to QML
	Emits change notifications
	Handles:
		Acceleration logic
		Distance accumulation
		Fuel consumption
		Temperature rise model
		Overheat handling
		Engine state transitions
     All simulation timing and calculations are handled here.
     This layer acts as the reactive bridge between UI and simulation logic.

🔹 3. Model (Internal State)
     Maintains precise internal values:
  	m_speed
	m_fuel
	m_distanceTraveled
	m_distanceForFuelConsumption
	m_temperature
	Engine State enum
     Key Design Principle:
	Internal precision uses double for accurate accumulation.
	UI formatting is handled separately.

⚙️ Simulation Logic Overview
	Acceleration Model
		Press-and-hold interaction
		Speed increases incrementally
		Distance accumulated based on:

			distance = speed × (intervalSeconds / 3600)

	Fuel Consumption
		Fuel decreases after predefined mileage threshold
		Accumulated fractional distance tracked internally
		Prevents precision loss

 	Temperature Model
		Temperature increases per defined travel distance
		Overheat threshold triggers:
			Speed reduction
			Indicator color change

	State Machine
	Engine States:
		OFF
		RUNNING
		FUEL_FINISHED
		OVERHEATED

State transitions are handled deterministically in the controller.

🧪 Runtime Modes
	Debug Mode
		Accelerated simulation
		Fast state transitions
		Used for testing and validation

	Release Mode
		Realistic simulation intervals
		Fuel decreases every 36 km
		Temperature increases every 10 km
		Designed to mimic real vehicle behavior

⚠️ Known Limitation
   There is a minor mouse interaction issue:
   If the accelerator is held for an extended duration:
	Releasing the mouse while cursor remains over the button may continue acceleration.
	Moving cursor outside resets behavior.
	Clicking once restores normal interaction.

   Root cause: mouse press/release event handling and hover state overlap.
   This can be improved using:
	Explicit pressed state tracking
	Pointer handlers
	QML TapHandler / DragHandler refinement

🛠 Technical Stack
	Qt 6
	QML (Qt Quick)
	C++17
	CMake
	Signal/Slot architecture
	Property binding system

🎯 Engineering Goals
   This project demonstrates:
	Clean separation of UI and logic
	Precision handling of accumulated physical values
	Event-driven state management
	Real-time simulation modeling
	Automotive-inspired safety behavior
	C++/QML integration patterns
	Scalable architecture ready for extension
