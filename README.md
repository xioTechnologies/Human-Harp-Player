Human-Harp-Player
=================

The Human Harp Player is a music controller based on interaction with an extendible cord under constant tension.  The Player provides measurements of the cord: extension, velocity, angle (azimuth and elevation) and angular rate (for detecting plucks).  The Player incorporates an [x-OSC](http://www.x-io.co.uk/x-osc/) to interface to host software via Wi-Fi.

Counts vary between 7800 counts/m and 1000 counts/m when fully extended, average = 8900.

See [Human Harp](http://humanharp.org/) for more information about the project.

PCB
---

The PCB was designed in [EAGLE Version 6.6](http://www.cadsoftusa.com/).  It was fabricated by [OSH Park](https://oshpark.com/) and is available to [purchase on their site](https://oshpark.com/shared_projects/F7BSWUvG).

<img src="https://raw.githubusercontent.com/xioTechnologies/Human-Harp-Player/master/PCB/Images/OSH%20Park%20Preview.png"/>

Firmware
--------

The Human Harp Player uses a Microchip [dsPIC33EP512GM604](http://www.microchip.com/wwwproducts/Devices.aspx?product=dsPIC33EP512GM604) 16-bit [DSC](http://en.wikipedia.org/wiki/Digital_signal_controller) running at 140 MHz (70 MIPS).  The firmware was developed using Microchip's free [MPLABX IDE v2.15](http://www.microchip.com/pagehandler/en-us/family/mplabx/) and [XC16 v1.21 C compiler](http://www.microchip.com/pagehandler/en_us/devtools/mplabxc/).  The PCB incorporates an ICSP header compatible with Microchip programming tools such as the [PICkit 3](http://www.microchip.com/Developmenttools/ProductDetails.aspx?PartNO=PG164130) or [ICD 3](http://www.microchip.com/Developmenttools/ProductDetails.aspx?PartNO=DV164035).

Test App
--------

The Human Harp Player Test App is a cross-platform application for visualising measurement data (distance, velocity, azimuth, elevation and angular rate) in real-time using [Processing](http://www.processing.org/).  Messages from the Player ("Reset", "Zero", "Sleep", "Firmware: vX.X") are displayed in the output console.  Clicking the window sends a 'zero' command.

<img src="https://raw.githubusercontent.com/xioTechnologies/Human-Harp-Player/master/Test%20App/Screenshot.png"/>

The Processing sketch requires the [oscP5 library](http://www.sojamo.de/libraries/oscP5/) to send and receive OSC messages.  To use this library, copy the entire *oscP5* directory (.zip available in the repository) into a directory named *"libraries"* in Processing Sketchbook location (see: *File* > *Preferences* > *Sketchbook location*).  A tutorial for sending and receiving OSC messages in Processing is available on the [codasign](http://learning.codasign.com/index.php?title=Sending_and_Receiving_OSC_Data_Using_Processing) website.

**Windows 7 Firewall:**  When running the processing application for the first time you will be prompted to grant network access to Java by Windows Firewall.  Java must be given access "Public" access else network communication will not be possible.  These permission can be modified any time through *Control Panel* > *Windows Firewall* > *"Change settings"*.
