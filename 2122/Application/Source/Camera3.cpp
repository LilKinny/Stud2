#include "Camera3.h"
#include "Application.h"
#include "Mtx44.h"
#include <conio.h>
#include <stdio.h>
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif
Camera3::Camera3()
{
}
Camera3::~Camera3()
{
}

void Camera3::Init(const Vector3& pos, const Vector3& target, const Vector3& up)
{
    Rock = -6, Rock2 = -6, Rock3 = -6;
    minx = -25, maxx = 200, minz = -70, maxz = 275;
    waterstart = 150, waterend = 185;
    prosstartx = -25, prosendx = -8;
    prosstartz = 256, prosendz = 275;
    angstartx = 150, angendx = 180;
    angstartz = 192, angendz = 210;
    trapstartz = 40, trapendz = 60;
    trapstartx = 20; trapendx = 35;
    talk_prospector = false;
    talk_trapper = false;
    talk_angler = false;
    phase_angler = 0;
    phase_prospector = 0;
    phase_trapper = 0;
    leshystartx = 69, leshyendx = 80;
    leshystartz = -40; leshyendz = -25;


    this->position = defaultPosition = pos;
    this->target = defaultTarget = target;
    Vector3 view = (target - position).Normalized();
    Vector3 right = view.Cross(up);
    right.y = 0;
    right.Normalize();
    this->up = defaultUp = right.Cross(view).Normalized();
}

void Camera3::Update(double dt)
{

    float CAMERA_SPEED = 25.f;
    float ZOOM_SPEED = 10.f;
    Vector3 view = (target - position).Normalized();
    Vector3 right = view.Cross(up);
    Vector3 pos;
    if (Application::IsKeyPressed(VK_RIGHT))
    {
        float yaw = -CAMERA_SPEED * static_cast<float>(dt);
        Mtx44 rotation;
        rotation.SetToRotation(yaw, 0, 1, 0);
        up = rotation * up;
        view = rotation * view;
        target = position + view;
    }
    if (Application::IsKeyPressed(VK_LEFT))
    {
        float yaw = CAMERA_SPEED * static_cast<float>(dt);
        Mtx44 rotation;
        rotation.SetToRotation(yaw, 0, 1, 0);
        up = rotation * up;
        view = rotation * view;
        target = position + view;
    }
    if (Application::IsKeyPressed(VK_DOWN))
    {
        float pitch = -CAMERA_SPEED * static_cast<float>(dt);
        Vector3 view = (target - position).Normalized();
        Vector3 right = view.Cross(up);
        right.y = 0;
        right.Normalize();
        up = right.Cross(view).Normalized();
        Mtx44 rotation;
        rotation.SetToRotation(pitch, right.x, right.y, right.z);
        view = rotation * view;
        target = position + view;
    }
    if (Application::IsKeyPressed(VK_UP))
    {
        float pitch = CAMERA_SPEED * static_cast<float>(dt);
        Vector3 view = (target - position).Normalized();
        Vector3 right = view.Cross(up);
        right.y = 0;
        right.Normalize();
        up = right.Cross(view).Normalized();
        Mtx44 rotation;
        rotation.SetToRotation(pitch, right.x, right.y, right.z);
        view = rotation * view;
        target = position + view;
    }
    if (Application::IsKeyPressed(VK_SHIFT))
    {
        ZOOM_SPEED = 5.f;
        CAMERA_SPEED = 15.f;
    }
    else {
        ZOOM_SPEED = 5.f;
        CAMERA_SPEED = 15.f;
    }
    if (Application::IsKeyPressed('W'))
    {
        pos = view;
        pos.y = 0;
        position += pos * ZOOM_SPEED * static_cast<float>(dt);
        target = position + view;
        posx = position.x;
        posz = position.z;
    }
    if (Application::IsKeyPressed('S'))
    {
        pos = view;
        pos.y = 0;
        position -= pos * ZOOM_SPEED * static_cast<float>(dt);
        target = position + view;
        posx = position.x;
        posz = position.z;
    }
    if (Application::IsKeyPressed('A'))
    {
        position -= right * ZOOM_SPEED * static_cast<float>(dt);
        target = position + view;
        posx = position.x;
        posz = position.z;
    }
    if (Application::IsKeyPressed('D'))
    {
        position += right * ZOOM_SPEED * static_cast<float>(dt);
        target = position + view;
        posx = position.x;
        posz = position.z;
    }
    if (Application::IsKeyPressed('R'))
    {
        Reset();
    }
    //if (waterstart < position.z < waterend)
    //    position.x = waterstart;

    else if (position.x < minx) {
        position.x = minx;
    }
    else if (position.x > maxx) {
        position.x = maxx;
    }

    else  if (position.z < minz) {
        position.z = minz;
    }
    else  if (position.z > maxz) {
        position.z = maxz;
    }
    else  if (position.z > waterstart && position.z < waterend) {
        position.z = waterstart;
    }
    else  if (position.z > waterstart - 10 && position.z < waterend + 10) {
        updatetext = "Press E to teleport across the river, Hold F to fish.";
        if (Application::IsKeyPressed('E'))
        {
            for (int n = PearlZ; n < position.z + 65; n++)
            {
                PearlZ++;
            }
            if (PearlZ == position.z + 65) position.z = position.z + 65;
        }
        if (Application::IsKeyPressed('F'))
        {
            if (fishingrod == true)
            {
                updatetext = "*You cast the hook, and reeled in... a small fry*";
                caught_fish = true;
            }
            else updatetext = "*You do not have a fishing rod*";
        }
    }
    else if (position.z > prosstartz && position.z < prosendz && position.x > prosstartx && position.x < prosendx)
    {
        if (phase_prospector <= 7) updatetext = "Press E to interact with the miner";
        else updatetext = "You have already interacted with this character";
        if (Application::IsKeyPressed('E'))
        {
            talk_prospector = true;
        }
        if (talk_prospector == true)
        {
            if (phase_prospector == 0) updatetext = " ";
            if (phase_prospector == 1) updatetext = "Ye caught me off guard!";
            if (phase_prospector == 2) updatetext = "Say... I like me a gamble.";
            if (phase_prospector == 3) updatetext = "Iffen ye can pick a Boulder that has gold in it...";
            if (phase_prospector == 4) updatetext = "ye can keep it!";
            if (phase_prospector == 5) updatetext = "*in front of you are 3 small boulders.*";
            if (phase_prospector == 6) updatetext = "Show me where to Strike!";
            if (phase_prospector == 7) updatetext = "*Pick a boulder to strike (press 1, 2 or 3)*";
            if (phase_prospector == 8) updatetext = "*The Prospector brings down his heavy pick to strike*";
            if (phase_prospector == 9) updatetext = "*A yellow glimmer shines through the cracks.*";
            if (phase_prospector == 10) updatetext = "Heeeeeeee-haw! 'Tis gold!";
            if (phase_prospector == 11) updatetext = "I can barely abide giving it to ye...";
            if (phase_prospector == 12) updatetext = "but a promise is a promise where I'm from.";
            if (phase_prospector == 13)
            {
                updatetext = "Here! Take this too.";
                ProspectorCard = true;
                got_teeth = true;
            }
            if (phase_prospector == 14) updatetext = "*The prospector hands you a gold block, and a card*";
            if (phase_prospector == 15) updatetext = "*On the card inscribes an angry looking stoat*";
            if (phase_prospector == 16) updatetext = "Im sure leshy would love that one...";

            if (phase_prospector == 18) updatetext = "*The Prospector brings down his heavy pick to strike*";
            if (phase_prospector == 19) updatetext = "*Inside lies not gold, but a strange card.*";
            if (phase_prospector == 20) updatetext = "Dag nab it... no gold.";
            if (phase_prospector == 21) updatetext = "But that is a funny lookin' varmint. Keep it.";
            if (phase_prospector == 22)
            {
                updatetext = "*He hands you the card.*";
                ProspectorCard = true;
                got_teeth = false;
            }
            if (phase_prospector == 23) updatetext = "*On the card inscribes an angry looking stoat*";
            if (phase_prospector == 24) updatetext = "Im sure leshy would love that one...";

            if (phase_prospector <= 16 && phase_prospector != 7 && Application::IsKeyPressed('E'))
            {
                phase_prospector++;
                Sleep(250);
            }
            if (phase_prospector >= 18 && Application::IsKeyPressed('E'))
            {
                phase_prospector++;
                Sleep(250);
            }
            if (phase_prospector == 7)
            {
                if (Application::IsKeyPressed('1'))
                {
                    // win
                    phase_prospector = 18;
                    Rock = Rock - 3;
                }
                if (Application::IsKeyPressed('2'))
                {
                    // win
                    phase_prospector = 18;
                    Rock2 = Rock2 - 3;
                }
                if (Application::IsKeyPressed('3'))
                {
                    // win
                    phase_prospector++;
                    Rock2 = Rock2 - 3;
                }
            }
        }
    }
    else if (position.z > angstartz && position.z < angendz && position.x > angstartx && position.x < angendx)
    {
        if (phase_angler != 15) updatetext = "Press E to interact with the fisherman";
        else updatetext = "You have already interacted with this character";
        if (Application::IsKeyPressed('E'))
        {
            talk_angler = true;
        }
        if (talk_angler == true)
        {
            if (phase_angler == 0) updatetext = " ";
            if (phase_angler == 1) updatetext = "Fresh Fish? Easy choose";
            if (phase_angler == 2) updatetext = "...";
            if (phase_angler == 3) updatetext = "No fish, No pass";
            if (phase_angler == 4) updatetext = "Take Rod, Go Fish";
            if (phase_angler == 5)
            {
                updatetext = "*He hands you a rod*";
                fishingrod = true;
            }
            if (phase_angler == 6) updatetext = "You bring fresh fish?";
            if (phase_angler == 7) updatetext = "Yes... Fresh fish, good";
            if (phase_angler == 8) updatetext = "*The angler seems satisfied.*";
            if (phase_angler == 9) updatetext = "*Suddenly, his hook catches something*";
            if (phase_angler == 10) updatetext = "*He reels it in. Its not a fish, but a card";
            if (phase_angler == 11) updatetext = "No fish, You can take";
            if (phase_angler == 12)
            {
                updatetext = "*He hands you the card*";
                AnglerCard = true;
            }
            if (phase_angler == 13) updatetext = "*On it inscribes a Stinkbug*";
            if (phase_angler == 14)
            {
                updatetext = "Leshy Like. Bring to him";
            }


            if (phase_angler == 17) updatetext = "No fish. No pass";


            if (phase_angler <= 6 && Application::IsKeyPressed('E'))
            {
                phase_angler++;
                Sleep(250);
            }
            if (phase_angler >= 7 && phase_angler <= 14 && Application::IsKeyPressed('E'))
            {
                phase_angler++;
                Sleep(250);
            }
            if (phase_angler == 17 && Application::IsKeyPressed('E'))
            {
                phase_angler--;
                Sleep(250);
            }
            if (phase_angler == 6 || phase_angler == 16)
            {
                if (caught_fish == true)
                {
                    phase_angler = 7;
                }
                else phase_angler = 17;
            }
        }
    }
    else if (position.z > trapstartz && position.z < trapendz && position.x > trapstartx && position.x < trapendx)
    {
        if (phase_trapper == 14 || phase_trapper == 24)updatetext = "You have already interacted with this character";
        else updatetext = "Press E to interact with the hunter";
        if (Application::IsKeyPressed('E'))
        {
            talk_trapper = true;
        }
        if (talk_trapper == true)
        {
            if (phase_trapper == 0) updatetext = " ";
            if (phase_trapper == 1) updatetext = "I sell the finest pelts";
            if (phase_trapper == 2) updatetext = "...";

            if (phase_trapper == 3) updatetext = "You do not have gold.";
            if (phase_trapper == 4) updatetext = "The prospector might have some, go talk to him.";

            if (phase_trapper == 16) updatetext = "Ah, i see you brought gold. Have a look at me pelts";
            if (phase_trapper == 17) updatetext = "*the trader offers you a few hare pelts*";
            if (phase_trapper == 18) updatetext = "*you decide to trade a pelt for your gold*";
            if (phase_trapper == 19) updatetext = "As a token of me gratitude, have this";
            if (phase_trapper == 20)
            {
                updatetext = "*He hands you a card*";
                TrapperCard = true;
            }

            if (phase_trapper == 21) updatetext = "*its a card with a wolf inscribed on it.";
            if (phase_trapper == 22) updatetext = "*The wolf's right eye is missing.";
            if (phase_trapper == 23) updatetext = "Leshy might be interested in your wares.";


            if (phase_trapper == 2 && Application::IsKeyPressed('E'))
            {
                if (got_teeth == false);
                else phase_trapper = 15;
            }
            if (phase_trapper == 5 && Application::IsKeyPressed('E'))
            {
                phase_trapper = 1;
            }
            if (phase_trapper != 14 && Application::IsKeyPressed('E') || phase_trapper != 23 && Application::IsKeyPressed('E'))
            {
                phase_trapper++;
                Sleep(250);
            }

        }
    }
    else if (position.z > leshystartz && position.z < leshyendz && position.x > leshystartx && position.x < leshyendx)
    {
        if (phase_leshy == 14 || phase_leshy >= 12)updatetext = "You have already interacted with this character";
        else updatetext = "Press E to interact with the photographer";
        if (Application::IsKeyPressed('E'))
        {
            talk_leshy = true;
        }
        if (talk_leshy == true)
        {
            if (phase_leshy == 0) updatetext = " ";
            if (phase_leshy == 1) updatetext = "Another challenger? It has been ages.";
            if (phase_leshy == 2) updatetext = "...";

            if (phase_leshy == 3) updatetext = "You do not have at least 3 cards.";
            if (phase_leshy == 4) updatetext = "You can find them from my subordinates.";

            if (phase_leshy == 6) updatetext = "So you wish to challenge me in a card battle?";
            if (phase_leshy == 7) updatetext = "Oh how I will relish this moment... step inside.";
            if (phase_leshy == 8) updatetext = "*You play a round of cards*";
            if (phase_leshy == 9) updatetext = "*Through sheer luck, you managed to beat him*";
            if (phase_leshy == 10) updatetext = "You beat me fair. Good game.";
            if (phase_leshy == 11) updatetext = "*Thats the end of the 'game'*";


            if (phase_leshy == 2 && Application::IsKeyPressed('E'))
            {
                if (ProspectorCard == false || AnglerCard == false || TrapperCard == false);
                else phase_leshy = 5;
            }
            if (phase_leshy == 4 && Application::IsKeyPressed('E'))
            {
                phase_leshy = 1;
            }
            if (phase_leshy != 4 && Application::IsKeyPressed('E'))
            {
                phase_leshy++;
                Sleep(250);
            }

        }
    }




    else if (position.z > 220 && position.z < 260 && position.x > 125 && position.x < 165)
    {
        if (phase_rock != 7)updatetext = "Press E to interact with this pile of rocks";
        else updatetext = "You have already picked up the gold";

        if (Application::IsKeyPressed('E'))
        {
            talk_leshy = true;
        }
        if (talk_leshy == true)
        {
            if (phase_rock == 0) updatetext = " ";
            if (phase_rock == 1) updatetext = "Its a pile of rocks, where the miner usually goes";
            if (phase_rock == 2) updatetext = "...";

            if (phase_rock == 3) updatetext = "*There is a shiny block sticking out of it*";
            if (phase_rock == 4) updatetext = "*pick it up? (y/n)*";

            if (phase_rock == 5) updatetext = "...";
            if (phase_rock == 6)
            {
                updatetext = "*You pick up the gold block*";
                got_teeth = true;
            }
            if (phase_rock == 8) updatetext = "*You decide to leave the block alone*";




            if (phase_rock == 4 && Application::IsKeyPressed('Y'))
            {
                phase_rock++;
            }
            if (phase_rock == 4 && Application::IsKeyPressed('N'))
            {
                phase_rock = 8;
                Sleep(250);
            }
            if (phase_rock == 4 && Application::IsKeyPressed('N'))
            {
                phase_rock = 0;
                Sleep(250);
            }
            if (Application::IsKeyPressed('E'))
            {
                phase_rock++;
                Sleep(250);
            }
        }
    }

    else updatetext = " ";


}

void Camera3::Reset()
{
    position = defaultPosition;
    target = defaultTarget;
    up = defaultUp;
}
