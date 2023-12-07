#include "Engine.h"
#include "Header/Time.h"

#include "../Core/Header/Window.h"
#include "../Logic/Header/Timer.h"

owl::Time::Time()
    : m_pTimer(nullptr)
{
    m_pTimer = new owl::Timer();
    m_DeltaTime = 0.0f;
}

owl::Time::~Time()
{
    delete m_pTimer;
}

void owl::Time::DeltaTimeMonitor()
{
#ifdef WL_DEBUG
    static float totalTime = 0.0f;
    static uint  frameCount = 0;
#endif !WL_DEBUG

    m_DeltaTime = m_pTimer->Reset();

#ifdef WL_DEBUG
    totalTime += m_DeltaTime;
    frameCount++;

    if (totalTime >= 1.0f)
    {
        std::stringstream text;
        text << std::fixed;
        text.precision(1);

        text << Window::GetTitle().c_str() << " | FPS: " << frameCount << " | MS: " << m_DeltaTime * 1000 << " | D3D11";
        Window::SetTitle(text.str());

        frameCount = 0;
        totalTime -= 1.0f;
    }
#endif !WL_DEBUG
}
