# Invictus 2.0 : Software
## Description
This repository contains all software for the boards external and internal to the rocket.
All boards use an RP2040 chip.
Each folder contains a PlatformIO project.

## Main Systems
- Mission Control (MC)
    - 1 x Telemetry Board
- Filling Station (FS)
    - 1 x Telemetry Board
    - 1 x CANha Board
- Ignition "Station"
    - 1 x Ignition Board
- Rocket (R)
    - 1 x Telemetry Board
    - 1 x OBC
    - 2 x CANha Board
  
## Boards
### Telemetry (MC)
#### Purpose:
Estabilishing OTA communication between the MC computer and the FS

### Telemetry (FS)
#### Purpose:
Estabilishing OTA communication between the FS and the MC computer 
Running the Filling State Machine
Requesting sensor values to the CANha boards and forwarding them to the MC when requested
Receiving the commands from MC and sending them to the correct CANha board

### CANha (FS)
#### Purpose:
Reading sensor values and sending them to the telemetry board when requested
Actuating the valves / servos as requested by the telemetry board
#### Sequence Diagram:
![CANha Sequence Diagram](docs/CANha/canha_seq.svg)

### Ignition Board
#### Purpose:
Running the Ignition State Machine
Actuating the e-matches when the fire command is received (if the ignition state machine is in the correct state)

### OBC (On-Board Computer)
#### Purpose:
Reading the Avionics sensors, running the Kalman filter and sending the data to the Telemetry board

