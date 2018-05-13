There's lots of good stuff in this one!

Start by looking at Player.cpp and see how we transformed a world forward vector into our kart's local space (essentially taking its rotation into account).

Then take a squiz at ThirdPersonCamera.cpp which uses the same technique to transform its offset vector.

If you're feeling brave, the FlyingCamera is your next stop (hopefully the comments help. The mouse look is a good reference for your first person camera). 

You can switch between cameras at the end of Game::Initialise. Both are stored in a Camera pointer called m_currentCam so no other work is required.

The third person camera has a catchup mode enabled which is using a LERP to delay it reaching its proper position.