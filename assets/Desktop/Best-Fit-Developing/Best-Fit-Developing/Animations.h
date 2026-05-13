#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
using namespace sf;

#pragma once

void LeftRun(vector<IntRect> allFrames, Sprite RunAnim, Texture Running, int &frameindex, RenderWindow &window, float &anim_timer, float anim_speed)
{
    if (anim_timer >= anim_speed)
    {
        anim_timer = 0.0f;
        if (frameindex > 7 || frameindex < 0)
        {
            frameindex = 0;
        }
        else
        {
            frameindex++;
        }
    }
    RunAnim.setTextureRect(allFrames[frameindex]);
    window.draw(RunAnim);
}

void RightRun(vector<IntRect> allFrames, Sprite RunAnim, Texture Running, int &frameindex, RenderWindow &window, float &anim_timer, float anim_speed)
{
    if (anim_timer >= anim_speed)
    {
        anim_timer = 0.0f;
        if (frameindex > 15 || frameindex < 7)
        {
            frameindex = 8;
        }
        else
        {
            frameindex++;
        }
    }
    RunAnim.setTextureRect(allFrames[frameindex]);
    window.draw(RunAnim);
}


int frameindex = 0;
float anim_timer = 0.5f;
float const anim_speed = 0.5f;
float xPosition = 0.0f;
bool Left = 0;
void RunAnim(RenderWindow &window, Clock &clock, float delta_time)
{
    if (xPosition <= 0.0f)
    {
        Left = 0;
    }
    else if (xPosition >= 371.f)
    {
        Left = 1;
    }
#ifdef _WIN32
    // Windows OS: Use a simple relative path assuming font is in the EXE directory,
    // or specify the assets folder structure typical for Windows/IDE builds.
    Texture Running("C:\\assets\\run.png");
#elif __linux__
    // Linux OS: Use the relative path common for Linux builds, or a system font path.
    Texture Running("Best-Fit/assets/run.png");
#endif
    
    Sprite RunAnim(Running);

    RunAnim.setPosition(Vector2f{xPosition, 50.f});

    // left Running
    IntRect frame1({18, 80}, {29, 46});
    IntRect frame2({84, 81}, {23, 46});
    IntRect frame3({84, 81}, {23, 46});
    IntRect frame4({210, 79}, {29, 44});
    IntRect frame5({273, 81}, {30, 45});
    IntRect frame6({404, 80}, {22, 47});
    IntRect frame7({404, 80}, {22, 47});
    IntRect frame8({466, 78}, {29, 47});
    // right frame
    IntRect frame9({17, 208}, {29, 46});
    IntRect frame10({85, 209}, {22, 46});
    IntRect frame11({150, 208}, {22, 47});
    IntRect frame12({209, 206}, {29, 45});
    IntRect frame13({273, 208}, {29, 46});
    IntRect frame14({342, 208}, {22, 47});
    IntRect frame15({406, 208}, {20, 48});
    IntRect frame16({465, 205}, {29, 48});

    vector<IntRect> all_frames;
    all_frames.push_back(frame1);
    all_frames.push_back(frame2);
    all_frames.push_back(frame3);
    all_frames.push_back(frame4);
    all_frames.push_back(frame5);
    all_frames.push_back(frame6);
    all_frames.push_back(frame7);
    all_frames.push_back(frame8);
    all_frames.push_back(frame9);
    all_frames.push_back(frame10);
    all_frames.push_back(frame11);
    all_frames.push_back(frame12);
    all_frames.push_back(frame13);
    all_frames.push_back(frame14);
    all_frames.push_back(frame15);
    all_frames.push_back(frame16);

    anim_timer += delta_time;

    if (Left == 0)
    {
        if (frameindex > 15 || frameindex < 7){
            frameindex = 8;
        } 
        RightRun(all_frames, RunAnim, Running, frameindex, window, anim_timer, anim_speed);
        xPosition += 0.8f;
    }
    else
    {
        if (frameindex > 7 || frameindex < 0){
            frameindex = 0;
        } 
        LeftRun(all_frames, RunAnim, Running, frameindex, window, anim_timer, anim_speed);
        xPosition -= 0.8f;
    }
}
