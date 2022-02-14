#ifndef CAMERA_3_H
#define CAMERA_3_H
#include "Camera.h"
class Camera3 : public Camera
{
public:
    float minx, minz, maxx, maxz, waterstart, waterend, prosstartx, prosendx, prosstartz, prosendz, angstartx, angendx, angstartz, angendz, trapstartx, trapendx, trapstartz, trapendz, leshystartx, leshyendx, leshystartz, leshyendz;
    float posx, posz;
    int TpRiver, phase_prospector, phase_angler, phase_trapper, phase_leshy, phase_rock;
    bool talk_prospector, caught_fish, fishingrod, talk_angler, talk_trapper, got_teeth, talk_leshy;
    bool ProspectorCard, AnglerCard, TrapperCard;
    int Rock, Rock2, Rock3;
    float PearlX, PearlZ;
    std::string updatetext;
    //Vector3 position;
    //Vector3 target;
    //Vector3 up;

    Vector3 defaultPosition;
    Vector3 defaultTarget;
    Vector3 defaultUp;

    Camera3();
    ~Camera3();
    virtual void Init(const Vector3& pos, const Vector3& target, const Vector3& up);
    virtual void Update(double dt);
    virtual void Reset();
};

#endif