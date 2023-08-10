# Catacomb Quest - Unreal Engine 5 Components

## HandGrabber Component

### Description
The `UHandGrabber` component allows the player to interact with and manipulate physics objects in the game world by grabbing and releasing them.

### Usage
1. Attach this component to the player's hand or any relevant game object.
2. Call the `Grab` function to grab an object when the player interacts with it.
3. Call the `Release` function to release the currently held object.

### Properties
- `MaxGrabDistance`: The maximum distance at which an object can be grabbed.
- `GrabRadius`: The radius around the player's hand within which objects can be grabbed.
- `HoldDistance`: The distance at which the grabbed object will be held from the player's hand.

### Functions
- `Grab()`: Initiates the grabbing of a nearby object.
- `Release()`: Releases the currently grabbed object.

## TriggerComponent Component

### Description
The `UTriggerComponent` component acts as a trigger zone that detects when an acceptable actor enters and interacts with the associated `UMover` component.

### Usage
1. Attach this component to a trigger zone in the game world.
2. Set an acceptable actor tag that can interact with the trigger.
3. Associate the `UMover` component that should be controlled by this trigger.

### Properties
- `AcceptableActorTag`: The tag of actors that can interact with the trigger.
- `Mover`: The associated `UMover` component that will be controlled by this trigger.

### Functions
- `SetMover(UMover* Mover)`: Associates a `UMover` component with this trigger.

## Mover Component

### Description
The `UMover` component allows an associated object to move back and forth between its original position and a specified offset.

### Usage
1. Attach this component to an object that needs to move.
2. Set the `MoveOffset` to determine the movement direction and distance.
3. Optionally, adjust the `MoveTime` for the duration of each movement cycle.
4. Use the `SetShouldMove(bool ShouldMove)` function to control the movement state.

### Properties
- `MoveOffset`: The displacement by which the object will move from its original position.
- `MoveTime`: The time taken for the object to move from its original position to the target position.

### Functions
- `SetShouldMove(bool ShouldMove)`: Sets whether the object should be in a moving state or not.
