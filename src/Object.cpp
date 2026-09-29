#include "Object.h"
#include "raylib.h"
#include <cmath>

void Object::Initialise()
{

}

void Object::UpdateObject(
    float dt,
    Vector2 mousePosition,
    bool mousePressed
)
{
    
    //=================================================
    // Check whether the mouse clicked the object
    //=================================================
    //
    // CheckCollisionPointRec asks:
    //
    // "Is the mouse position inside the collision
    // rectangle?"
    //
    // We ALSO check mousePressed.
    //
    // Both must be true.
    //
    if (
        CheckCollisionPointRec(mousePosition, collisionBox)
        && mousePressed
    )
    {
        // Toggle the dragging state.
        //
        // If it was false:
        //
        //     false -> true
        //
        // If it was true:
        //
        //     true -> false
        //
        heldByMouse = !heldByMouse;


        // -------------------------------------------------
        // Remember where inside the object we clicked.
        // -------------------------------------------------
        //
        // Without this, the object would jump so that its
        // centre was directly underneath the mouse.
        //
        // mouseGrabOffset remembers the difference between
        // the mouse position and the object's anchor point.
        //
        mouseGrabOffset =
        {
           // mousePosition.x - anchorPoint.x,
           // mousePosition.y - anchorPoint.y
        };
    }


    //=================================================
    // Move the object while it is being dragged
    //=================================================
    //
    if (heldByMouse)
    {
        // Move the anchor point to follow the mouse.
        //
        // We subtract mouseGrabOffset so that the object
        // stays grabbed at the same point where the user
        // originally clicked it.
        //
        /*anchorPoint =
        {
            mousePosition.x - mouseGrabOffset.x,
            mousePosition.y - mouseGrabOffset.y
        };*/
    }


    //=================================================
    // Move the collision box
    //=================================================
    //
    // The collision box belongs to the object, so when
    // the anchor moves, the collision box must move too.
    //
    // We add collisionOffset because the visible image
    // may not be centred inside the sprite frame.
    //
    //collisionBox.x =
        //anchorPoint.x + collisionOffset.x;

    //collisionBox.y =
        //anchorPoint.y + collisionOffset.y;
}



//====================================================
// IsHeldByMouse
//
// Returns whether the object is currently being
// dragged by the mouse.
//
// Returns:
//     true  = object is being held
//     false = object is not being held
//
//====================================================

bool Object::IsHeldByMouse() const
{
    return heldByMouse;
}



//====================================================
// DrawCollisionBox
//
// Draws the collision rectangle around the object.
//
// This is mainly a DEBUGGING tool so we can see
// exactly where Raylib thinks the collision area is.
//
//====================================================

void Object::DrawCollisionBox()
{
    DrawRectangleLines
    (
        collisionBox.x,
        collisionBox.y,
        collisionBox.width,
        collisionBox.height,
        RED
    );
}



//====================================================
// GetCollisionBox
//
// Returns the object's current collision rectangle.
//
// Other parts of the program can use this to check
// collisions with this object.
//
//====================================================

Rectangle Object::GetCollisionBox()
{
    return collisionBox;
}



//====================================================
// SetName
//
// Gives the object a name.
//
// This can be useful for identifying different objects,
// for example:
//
//     "Ball"
//     "Book"
//     "Guitar"
//     "Toy"
//====================================================

void Object::SetName(std::string name)
{
    objectName = name;
}



//====================================================
// GetName
//
// Returns the object's current name.
//====================================================

std::string Object::GetName()
{
    return objectName;
}