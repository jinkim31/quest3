#include "inc/OVR_CAPI.h"
#include <iostream>
#include <thread>
#include <vector>
#include <iostream>
#include <fstream>

int main()
{
    ovrResult result = ovr_Initialize(nullptr);
    if (OVR_FAILURE(result))
        return result;

    ovrSession session;
    ovrGraphicsLuid luid;
    result = ovr_Create(&session, &luid);
    std::cout<<result<<std::endl;
    if (OVR_FAILURE(result))
    {
        ovr_Shutdown();
        return result;
    }

    ovrHmdDesc desc = ovr_GetHmdDesc(session);
    std::cout<<desc.ProductName<<std::endl;
    ovrSizei resolution = desc.Resolution;

    std::vector<ovrPosef> poses;

    for(int i=0; i<1000; i++)
    {
        ovrTrackingState ts = ovr_GetTrackingState(session, ovr_GetTimeInSeconds(), ovrTrue);
        if (ts.StatusFlags & (ovrStatus_OrientationTracked | ovrStatus_PositionTracked))
        {
            auto& pose = ts.HeadPose.ThePose;
            poses.emplace_back(pose);
            std::cout << pose.Position.x << ", " << pose.Position.y << ", " << pose.Position.z << "\n";
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    ovr_Destroy(session);
    ovr_Shutdown();

    std::ofstream csv;
    csv.open ("poses.csv");

    for(const auto& pose : poses)
    {
        csv << pose.Position.x << ", " << pose.Position.y << ", " << pose.Position.z << "\n";
    }

    csv.close();
}
