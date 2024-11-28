# THIS CHEAT NO LONGER WORKS (kinda)
**This is really easy to get working again** add your own driver & add the new offsets of UC (I will not help u tho)

# What is this and why?
My private Apex Legends SRC code. I worked on this with NXTG3N before he got cut due to Activision's lawyers. I’ve decided to release this for educational purposes, as I no longer use this SRC, and a lot of the code is poor.
This SRC can easily be updated to newer Apex versions—just add your own driver and update the offsets. Note that this was my first external cheat; before this, I only made internals.

# Features

## Glow
- Ignore Self
- Glow Mode (satic or dynamic)
- Satic Glow Color
- Veiw Model Glow
- Glow ID

## ESP
- Ignore Self
- Max Distance
- Bone
- Boxs 2d
- Snaplines
- Crosshair

## Aimbot
- Ingore Knocked
- Show Fov Circle
- Fov Circle Size
- Max Distance
- Speed

## Skin Changer
- One Size Fits All
- Skin ID
- Randomize

## Other
- Stream Proof

# Code overview

## Improvements

Ok, first off, ESP, skeleton, etc., was kinda an afterthought. This is evident in the render loop where I call the ESP function to render. Now, this is fine, but we are reading the player and bone array in the overlay function, which will cause massive overlay FPS drops.

[Esp being called in the overlay loop 😑](https://github.com/TheRealJoelmatic/apex-matic/blob/main/usermode/overlay/overlay.cpp#L185)

[Then readin the enity list again 😑](https://github.com/TheRealJoelmatic/apex-matic/blob/main/usermode/modules/features/esp.cppL24)

This is fine, I guess, for internal cheats where reads & writes are much faster, but it’s a no-go for externals. For example, in my CS2 cheat, I read the entity list once in a thread and grab all the info needed (like health, etc.), then I put it in a struct:

``` c++
struct player {
    uintptr_t CSPlayerPawn;
    bool isLocalPlayer;

    std::string name;
    int health;
    float distance;
    bool isAlive;

    int teamID;

    bool sameteam;
    bool isVisable;


    vec3 position3d;
    vec2 position2d;

    std::map<std::string, vec3> BonePosition3d;
    std::map<std::string, vec2> BonePosition2d;
}
```

Then we can just do the drawing in the overlay in bulk, saving on massive performance.

## What Went Well

Not bad for my first external—could be better. It has many good features that work well.

# References 

- https://github.com/Gerosity/zap-client ( Massive credit )
- https://github.com/Nexilist/xap-client
- https://www.unknowncheats.me/forum/apex-legends/319804-apex-legends-reversal-structs-offsets.html
- https://github.com/Sndix/Apex-Legends-Simple-Glow
- https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-setwindowdisplayaffinity
- https://github.com/noahswtf/external-overlay/tree/main
- https://github.com/ocornut/imgui
- https://github.com/TheCruZ/kdmapper
- some more I forgot

# Tools used

- https://www.cheatengine.org/
- https://hex-rays.com/ida-pro/
- https://github.com/ReClassNET/ReClass.NET
- https://github.com/AndnixSH/Il2CppDumper-GUI
- https://code.visualstudio.com/
- https://visualstudio.microsoft.com/vs/
