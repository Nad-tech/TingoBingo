#include "RobotBrain.h"
#include "Robot.h"

RobotBrain::RobotBrain(Robot& robot, RobotState& robotState) : 
    robot(robot),
    robotState(robotState),
    speechController()
{}

inline Vector2 cart2Screen(Vector2 v)
{
    return {
        SCREEN_WIDTH / 2.0f + v.x,
        SCREEN_HEIGHT / 2.0f - v.y
    };
}

void RobotBrain::Initialise()
{

}

void RobotBrain::Update(float dt)
{
    // Update gaze behaviour according to the current brain state.
    if(robotState.brainState == RobotState::BrainState::Idle)
    {
        AdvanceIdleGaze(dt);
    }
    else if(robotState.brainState == RobotState::BrainState::Searching)
    {
        AdvanceSearch(dt);
    }

    float idleTimeOut = 10.0f;
    idleTimer -= dt;

    //Idle behavior
    if 
    (
        robotState.brainState == RobotState::BrainState::Idle && 
        idleTimer <= 0.0f && 
        !robotState.speaking
    )
    {
        SpeakRandomIdlePhrase();
        
        std::uniform_int_distribution<> dist
        (
            0, robotState.gestures.idleGestureNames.size() - 1
        );
        int idx = dist(gen);
        lastIdleMovement = robotState.gestures.idleGestureNames[idx];
        
        ChooseIdleMovement(true);
        idleTimer = idleTimeOut;
    }
    
    speechController.Update();

    if(speechController.SpeechFinished())
    {
        robotState.speaking = false;
        ChooseIdleMovement(false);
    }
    else {
        robotState.speaking = true;
    }
}

void RobotBrain::Draw() const
{
    DrawLine
    (
        cart2Screen(searchRayOrigin).x, 
        cart2Screen(searchRayOrigin).y, 
        cart2Screen(searchRayEnd).x,
        cart2Screen(searchRayEnd).y,
        RED 
    );
}

void RobotBrain::Speak(std::string text)
{
    speechController.Speak(text);
}

void RobotBrain::SpeakRandomIdlePhrase()
{
 
    std::uniform_int_distribution<> dist(0, phrases.idlePhrases.size() - 1);

    int idx = dist(gen);

    Speak(phrases.idlePhrases[idx]);
}

void RobotBrain::ChooseIdleMovement(bool enable)
{            
    if(enable)
    {
        if(lastIdleMovement == "nod") robotState.gestures.nod = true;
        if(lastIdleMovement == "shakeHead") robotState.gestures.shakeHead = true;
        if(lastIdleMovement == "waveLeft") robotState.gestures.waveLeft = true;
        if(lastIdleMovement == "waveRight") robotState.gestures.waveRight = true;
        if(lastIdleMovement == "shrug") robotState.gestures.shrug = true;
        if(lastIdleMovement == "crouch") robotState.gestures.crouch = true;
        if(lastIdleMovement == "closeLeftEye") robotState.gestures.closeLeftEye = true;
        if(lastIdleMovement == "closeRightEye") robotState.gestures.closeRightEye = true;
        if(lastIdleMovement == "closeRightClamp") robotState.gestures.closeRightClamp = true;
        if(lastIdleMovement == "closeLeftClamp") robotState.gestures.closeLeftClamp = true;
    }
    else
    {
        if(lastIdleMovement == "nod") robotState.gestures.nod = false;
        if(lastIdleMovement == "shakeHead") robotState.gestures.shakeHead = false;
        if(lastIdleMovement == "waveLeft") robotState.gestures.waveLeft = false;
        if(lastIdleMovement == "waveRight") robotState.gestures.waveRight = false;
        if(lastIdleMovement == "shrug") robotState.gestures.shrug = false;
        if(lastIdleMovement == "crouch") robotState.gestures.crouch = false;
        if(lastIdleMovement == "closeLeftEye") robotState.gestures.closeLeftEye = false;
        if(lastIdleMovement == "closeRightEye") robotState.gestures.closeRightEye = false;
        if(lastIdleMovement == "closeRightClamp") robotState.gestures.closeRightClamp = false;
        if(lastIdleMovement == "closeLeftClamp") robotState.gestures.closeLeftClamp = false;
    }
}

void RobotBrain::Search()
{
    robotState.brainState = RobotState::BrainState::Searching;
}

void RobotBrain::AdvanceIdleGaze(float dt)
{
    float pauseMin = 1.0f;
    float pauseMax = 5.0f;

    // Decrease the gaze timer by the time elapsed since the previous frame.
    // When the timer reaches zero, Tingo will choose a new direction to look.
    idleLookTimer -= dt;

    // Only choose a new gaze target when the timer expires.
    // Otherwise, Tingo will continue looking towards his existing target.
    if(idleLookTimer <= 0.0f)
    {
        // Create random distributions for the horizontal and vertical
        // components of the gaze direction.
        // Horizontal movement ranges from -1 (left) to 1 (right).
        // Vertical movement ranges from -0.6 (down) to 0.6 (up).
        // The smaller vertical range makes steep vertical glances less likely.
        std::uniform_real_distribution<float> horizontal(-1.0f, 1.0f);
        std::uniform_real_distribution<float> vertical(-0.6f, 0.6f);

        // Generate a random direction by choosing independent horizontal
        // and vertical values from their respective distributions.
        Vector2 direction =
        {
            horizontal(gen),
            vertical(gen)
        };

        // Calculate the length (magnitude) of the direction vector using
        // the Pythagorean theorem: sqrt(x² + y²).
        // We need this length to convert the vector into a unit direction.
        float length = sqrtf(
            direction.x * direction.x +
            direction.y * direction.y
        );

        // If the vector is extremely close to zero, normalising it could
        // cause division-by-zero or unstable results.
        // Substitute a safe direction pointing to the right instead.
        if(length < 0.001f)
        {
            direction = { 1.0f, 0.0f };
            length = 1.0f;
        }

        // Normalise the direction by dividing each component by its length.
        // This produces a unit vector with a length of 1 while preserving
        // its direction, allowing us to control the target distance separately.
        direction.x /= length;
        direction.y /= length;

        // Get the current position of Tingo's head.
        // This provides the reference point from which the gaze target is placed.
        Vector2 headPosition = robot.GetHead().GetPosition();

        // Set how far away the gaze target should be from the head.
        // This is the distance to the imaginary point Tingo looks towards,
        // not the distance the pupil itself will move.
        const float TARGET_DISTANCE = 300.0f;

        // Calculate the gaze target by moving 300 units from the head's
        // position in the randomly selected direction.
        // Multiplying the unit direction by the target distance determines
        // how far to move along each axis before adding the head position.
        lookTarget =
        {
            headPosition.x + direction.x * TARGET_DISTANCE,
            headPosition.y + direction.y * TARGET_DISTANCE
        };

        // Create a random pause duration between 0.7 and 2.0 seconds.
        // This makes Tingo hold his gaze for varying amounts of time
        // instead of switching direction at regular intervals.
        std::uniform_real_distribution<float> pauseDuration(pauseMin, pauseMax);

        // Store the chosen pause duration.
        // The timer will count down during subsequent updates before
        // Tingo selects another random gaze target.
        idleLookTimer = pauseDuration(gen);
    }

    searchRayOrigin = robot.GetHead().GetPosition();
    searchRayOrigin.y += eyeOffset;
    searchRayEnd = lookTarget;

    // Tell the robot to look towards the current gaze target.
    // This runs every frame, allowing the pupil movement system to
    // smoothly follow the target until a new one is selected.
    robot.LookAt(lookTarget);
}

void RobotBrain::AdvanceSearch(float dt)
{
    // Search behaviour constants.
    const float PAUSE_MIN = 5.0f;
    const float PAUSE_MAX = 15.0f;
    const float TARGET_DISTANCE = 300.0f;

    // Horizontal search movement.
    const float SEARCH_HORIZONTAL_RADIUS = 200.0f;
    const float SEARCH_HORIZONTAL_SPEED = 1.5f;
    const float SEARCH_HORIZONTAL_LIMIT = 0.6f;

    // Vertical search movement.
    const float SEARCH_VERTICAL_RADIUS = 100.0f;
    const float SEARCH_VERTICAL_SPEED = 2.0f;

    // Count down until Tingo chooses a new search location.
    searchLookTimer -= dt;

    if(searchLookTimer <= 0.0f)
    {
        if(robotState.searchType == RobotState::SearchType::Environmental)
        {
            // Generate a random environmental direction.
            std::uniform_real_distribution<float> horizontal(-1.0f, 1.0f);
            std::uniform_real_distribution<float> vertical(-0.6f, 0.6f);

            Vector2 direction =
            {
                horizontal(gen),
                vertical(gen)
            };

            // Calculate the direction vector's length.
            float length = sqrtf(
                direction.x * direction.x +
                direction.y * direction.y
            );

            // Prevent division by zero when normalising.
            if(length < 0.001f)
            {
                direction = { 1.0f, 0.0f };
                length = 1.0f;
            }

            // Normalise the direction vector.
            direction.x /= length;
            direction.y /= length;

            // Get the head's current position.
            Vector2 headPosition = robot.GetHead().GetPosition();

            // Select a new environmental search centre.
            searchCentre =
            {
                headPosition.x + direction.x * TARGET_DISTANCE,
                headPosition.y + direction.y * TARGET_DISTANCE
            };

            // Reset the horizontal and vertical search movement.
            searchHorizontalAngle = 0.0f;
            searchHorizontalDirection = 1.0f;
            searchVerticalAngle = 0.0f;

            // Choose how long to examine this area.
            std::uniform_real_distribution<float> pauseDuration(
                PAUSE_MIN,
                PAUSE_MAX
            );

            searchLookTimer = pauseDuration(gen);
        }
    }

    // Move the horizontal search angle back and forth.
    searchHorizontalAngle +=
        SEARCH_HORIZONTAL_SPEED * searchHorizontalDirection * dt;

    // Reverse direction at the horizontal limits.
    if(searchHorizontalAngle >= SEARCH_HORIZONTAL_LIMIT)
    {
        searchHorizontalAngle = SEARCH_HORIZONTAL_LIMIT;
        searchHorizontalDirection = -1.0f;
    }
    else if(searchHorizontalAngle <= -SEARCH_HORIZONTAL_LIMIT)
    {
        searchHorizontalAngle = -SEARCH_HORIZONTAL_LIMIT;
        searchHorizontalDirection = 1.0f;
    }

    // Advance the vertical search angle.
    searchVerticalAngle += SEARCH_VERTICAL_SPEED * dt;

    // Calculate the horizontal and vertical offsets.
    float horizontalOffset =
        sinf(searchHorizontalAngle) * SEARCH_HORIZONTAL_RADIUS;

    float verticalOffset =
        sinf(searchVerticalAngle) * SEARCH_VERTICAL_RADIUS;

    // Calculate the final gaze target around the search centre.
    lookTarget =
    {
        searchCentre.x + horizontalOffset,
        searchCentre.y + verticalOffset
    };

    searchRayOrigin = robot.GetHead().GetPosition();
    searchRayOrigin.y += eyeOffset;
    searchRayEnd = lookTarget;

    // Tell Tingo to look towards the calculated target.
    robot.LookAt(lookTarget);
}