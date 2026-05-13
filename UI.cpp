#include "UI.h"
#include<iostream>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

UI::UI(): mFontLoaded(false),mPanelSprite(nullptr),m_showEndScreen(false), m_isWin(false), m_playAgainHover(false), m_mainMenuHover(false)
{
    if (mFont.openFromFile("assets/Arial.ttf"))
    {
        mFontLoaded = true;
    }
    // sirf panel texture load karo
    if (!mPanelTex.loadFromFile("assets/ui2.png"))   

        // loadFromFile() returns  TRUE (file mil gayi)
        // !true = false 
        // if (FALSE) .... ANDAR NAHIN JAYEGA
        // Result: Texture load ho chuki hai (from file)
    {   // Image is class in sfml that handles pixels .... img is name of object 
        // { 320u, 900u }, sf::Color(80, 50, 20))   is the constructor call of the iamge class 
        // if image is not found then we will load a dark rectangle 

        Image img({ 320u, 900u },Color(80, 50, 20));
        mPanelTex.loadFromImage(img);  // means fallback yani rectangle bana do 
    }
    mPanelSprite = new Sprite(mPanelTex);
    auto size = mPanelTex.getSize();

    // exact pixels mein fit karo - no stretch
    float scaleX = 320.f / size.x;
    float scaleY = 900.f / size.y;

    mPanelSprite->setScale({ scaleX, scaleY });    // scale change karo
    mPanelSprite->setPosition({ 1100.f, 0.f });    // position change karo

    // ===== EXIT BUTTON (Top Right) =====
    if (!mExitBtnTex.loadFromFile("assets/back txt.png"))
    {
        // Fallback - red square with X
        sf::Image img({ 40u, 40u }, sf::Color(200, 50, 50));
        mExitBtnTex.loadFromImage(img);
    }
    mExitBtnSprite = new sf::Sprite(mExitBtnTex);
    mExitBtnSprite->setScale({ 0.5f, 0.5f });
    mExitBtnSprite->setPosition({ 1300.f, 0.f });

    // Exit button ka clickable rectangle (invisible but clickable)
    mExitBtnRect = sf::FloatRect({ 1330.f, 30.f }, { 50.f, 50.f });

    // ===== EXIT PANEL (Popup) =====
    if (!mExitPanelTex.loadFromFile("assets/e1.png"))
    {
        // Fallback - dark gray panel
        sf::Image img({ 300u, 200u }, sf::Color(30, 30, 40));
        mExitPanelTex.loadFromImage(img);
    }
    mExitPanelSprite = new sf::Sprite(mExitPanelTex);
    mExitPanelSprite->setScale({ 0.5f, 0.5f });
    mExitPanelSprite->setPosition({ 350.f, 150.f });  // Center of screen

    // YES button rectangle (based on your exit_panel.png)
    // Tumhari image ke hisaab se coordinates adjust karo
   
    mYesBtnRect = sf::FloatRect({ 472.f, 585.f }, { 145.f, 50.f });
    mNoBtnRect = sf::FloatRect({ 673.f, 585.f }, { 145.f, 50.f });


    // button for box 
    mBtnSprite = nullptr;

    if (!mBtnTex.loadFromFile("assets/entername.png"))
    {
        sf::Image img({ 200u, 60u }, sf::Color(180, 130, 0));
        mBtnTex.loadFromImage(img);
    }
    mBtnSprite = new sf::Sprite(mBtnTex);

    // size aur position tum change kar sakte ho
    mBtnSprite->setPosition({ 1150.f,130.f });
    mBtnSprite->setScale({ 0.65f, 0.5f });

    // coin
    mCoinSprite = nullptr;
    if (!mCoinTex.loadFromFile("assets/coin.png"))
    {
        sf::Image img({ 32u, 32u }, sf::Color(220, 180, 0));
        mCoinTex.loadFromImage(img);
    }
    mCoinSprite = new Sprite(mCoinTex);
    mCoinSprite->setScale({ 0.09f, 0.09f });      // size change karo

    // heart
    mHeartSprite = nullptr;
    if (!mHeartTex.loadFromFile("assets/heart.png"))
    {
        sf::Image img({ 32u, 32u }, sf::Color(220, 50, 50));
        mHeartTex.loadFromImage(img);
    }
    mHeartSprite = new sf::Sprite(mHeartTex);
    mHeartSprite->setScale({ 0.07f, 0.07f });     // size change karo

    // towers sprites 

    const char* towerFiles[5] = 
    {
     "assets/can4.png","assets/arch2.png","assets/wiz3.png","assets/elec2.png","assets/inf2.png"
    };

    for (int i = 0; i < 5; i++)
    {
        mTowerSprite[i] = nullptr;
        if (!mTowerTex[i].loadFromFile(towerFiles[i]))
        {
            sf::Image img({ 64u, 64u }, sf::Color(80, 80, 100));
            mTowerTex[i].loadFromImage(img);
        }
        mTowerSprite[i] = new sf::Sprite(mTowerTex[i]);
       mTowerTex[i].setSmooth(false);
        // square ratio maintain karo - stretch nahi
        auto size = mTowerTex[i].getSize();
        float minDim = (float)std::min(size.x, size.y);
        float scale = 80.f / minDim;  // 80x80 box mein fit
        mTowerSprite[i]->setScale({ 1.f, 1.f});
    }

    // endgame(victory or defeat ) 
    m_endScreenSprite = new Sprite(m_endScreenTex);
    m_endScreenSprite->setScale({ 1.f, 1.f });
    m_endScreenSprite->setPosition({ 0.f, 0.f });  // Full screen

    // ===== SIRF DO RECTANGLES (Dono screens ke liye same) =====
    // Play Again button
    m_playAgainRect = sf::FloatRect({ 435.f, 607.f }, { 180.f, 68.f });

    // Main Menu button
    m_mainMenuRect = sf::FloatRect({ 655.f, 607.f }, { 180.f, 68.f });
}

void UI::draw(RenderWindow& window, int currentWave, int totalWaves,int gold, int lives,int selectedTower)
{
    // sirf panel draw karo
    window.draw(*mPanelSprite);
        // Hover effect - glow/outline
        if (mExitButtonHover)
        {
            RectangleShape glow;
            glow.setSize({ 44.f, 44.f });
            glow.setFillColor(sf::Color(255, 100, 100, 80));
            glow.setOutlineColor(sf::Color(255, 50, 50));
            glow.setOutlineThickness(2.f);
            glow.setPosition({ 1328.f, 13.f });
            window.draw(glow);
        }
    window.draw(*mExitBtnSprite);

    //DRAW EXIT PANEL IF VISIBLE
    if (m_showExitPanel)
    {
        // Dark overlay (screen ko dark karo)
        RectangleShape overlay;
        overlay.setSize({ 1400.f, 900.f });
        overlay.setFillColor(sf::Color(0, 0, 0, 180));
        window.draw(overlay);

        // Draw panel
        window.draw(*mExitPanelSprite);

        // YES button with hover effect
        RectangleShape yesBtn({ mYesBtnRect.size.x, mYesBtnRect.size.y });
        yesBtn.setPosition({ mYesBtnRect.position.x, mYesBtnRect.position.y });
        if (mYesHover)
        {
            yesBtn.setFillColor(sf::Color(100, 255, 100, 80));
           
        }
        else
        {
            yesBtn.setFillColor(sf::Color(0, 0, 0, 0));
        }
        window.draw(yesBtn);

        // NO button with hover effect
        RectangleShape noBtn({ mNoBtnRect.size.x, mNoBtnRect.size.y });
        noBtn.setPosition({ mNoBtnRect.position.x, mNoBtnRect.position.y });
        if (mNoHover)
        {
            noBtn.setFillColor(sf::Color(255, 100, 100, 80));
            noBtn.setOutlineColor(sf::Color(255,100,100,80));
            noBtn.setOutlineThickness(2.f);
        }
        else
        {
            noBtn.setFillColor(sf::Color(0, 0, 0, 0));
        }
        window.draw(noBtn);
    }


    // wave button image
   // mBtnSprite->setPosition({ 1100.f, 400.f });
    window.draw(*mBtnSprite);

    // wave text upar se - bounds se center mein
    FloatRect btnBounds = mBtnSprite->getGlobalBounds();
    float textX = btnBounds.position.x + btnBounds.size.x / 2.f;
    float textY = btnBounds.position.y + btnBounds.size.y / 4.f;

    drawText(window,"Wave " + std::to_string(currentWave + 1) +" / " + std::to_string(totalWaves),1180,145,35,sf::Color(0, 0, 0));

    // coin - wave ke neeche
    FloatRect waveBounds = mBtnSprite->getGlobalBounds();
    //float coinY = waveBounds.position.y + waveBounds.size.y + 20.f;
    mCoinSprite->setPosition({ 1170.f, 210.f });
    window.draw(*mCoinSprite);

    // coin ke saath gold text
    FloatRect coinBounds = mCoinSprite->getGlobalBounds();
    drawText(window,"X" +to_string(gold),coinBounds.position.x + coinBounds.size.x + 10.f,coinBounds.position.y+10.f,24,Color(220, 180, 0));

    // hearts - coin ke neeche
    float heartY = 280.f;
    float heartX = 1150.f;

    for (int i = 0; i < lives && i < 7; i++)
    {
        mHeartSprite->setPosition({ heartX, heartY });  // loop chal raha hay or heart draw ho ray hain 
        window.draw(*mHeartSprite);

        FloatRect hb = mHeartSprite->getGlobalBounds();
        heartX += hb.size.x + 5.f;  // firstly pichal heart draw jab ho jay ga to x coordinate inctrease ho jay ga phir doosra heart draw ho ga 
    }

    // towers draw 
    // tower positions - 2+2+1 layout
// tum position khud change karo
    float positions[5][2] = {
        {1160.f, 380.f},   // tower 1 - left
        {1270.f, 380.f},   // tower 2 - right
        {1160.f, 540.f},   // tower 3 - left
        {1270.f, 540.f},   // tower 4 - right
        {1200.f, 680.f},   // tower 5 - center
    };

    int costs[5] = { 100, 75, 150, 80, 90 };

    for (int i = 0; i < 5; i++)
    {
        float tx = positions[i][0];
        float ty = positions[i][1];

        // selected tower ka glow - exact boundary
        if (i == selectedTower)
        {
            FloatRect bounds = mTowerSprite[i]->getGlobalBounds();

            // thoda bahar wali outline
            RectangleShape glow;
            glow.setSize({ bounds.size.x + 6.f, bounds.size.y + 6.f });
            glow.setFillColor(Color(0, 0, 0, 0));  // transparent inside
            glow.setOutlineColor(Color(255, 0, 0, 180));
            glow.setOutlineThickness(3.f);
            glow.setPosition({
                bounds.position.x - 3.f,
                bounds.position.y - 3.f });
            window.draw(glow);
        }

        // tower image
        mTowerSprite[i]->setPosition({ tx, ty });
        window.draw(*mTowerSprite[i]);

        // cost text neeche
        drawText(window,
            std::to_string(costs[i]),
            tx + 10.f, ty + 100.f,
            24, sf::Color(220, 180, 0));
    }
}
void UI::drawText(RenderWindow& window,const std::string& str,float x, float y, int size,sf::Color color)
{
    if (!mFontLoaded) return;
    sf::Text text(mFont);
    text.setString(str);
    text.setCharacterSize(size);
    text.setFillColor(color);
    text.setPosition({ x, y });
    window.draw(text);
}
// hover effects of buttons 
void UI::handleExitButtonHover(float mouseX, float mouseY)
{
    mExitButtonHover = mExitBtnRect.contains({ mouseX, mouseY });
}

bool UI::isExitButtonClicked(float mouseX, float mouseY)
{
    return mExitBtnRect.contains({ mouseX, mouseY });
}

void UI::showExitPanel(bool show)
{
    m_showExitPanel = show;
    if (!show) {
        mYesHover = false;
        mNoHover = false;
    }
}

int UI::handleExitPanelClick(float mouseX, float mouseY)
{
    if (!m_showExitPanel) return -1;

    // Update hover states
    mYesHover = mYesBtnRect.contains({ mouseX, mouseY });
    mNoHover = mNoBtnRect.contains({ mouseX, mouseY });

    // Check clicks
    if (mYesBtnRect.contains({ mouseX, mouseY }))
        return 1;  // YES - exit to main menu
    if (mNoBtnRect.contains({mouseX, mouseY}))
        return 0;  // NO - close panel, stay in game

    return -1;
}
void UI::showEndScreen(bool isWin)
{
    m_isWin = isWin;
    m_showEndScreen = true;
    m_playAgainHover = false;
    m_mainMenuHover = false;

    string filename = isWin ? "assets/win.png" : "assets/loose.png";

    if (!m_endScreenTex.loadFromFile(filename))
    {
        Color bgColor = isWin ?Color(0, 50, 0) :Color(50, 0, 0);
        Image img({ 1400u, 900u }, bgColor);
        m_endScreenTex.loadFromImage(img);
    }

    // SFML 3 mein setTexture nahi - naya sprite banao
    delete m_endScreenSprite;
    m_endScreenSprite = new Sprite(m_endScreenTex);
    m_endScreenSprite->setScale({ 0.6f, 0.6f });
    m_endScreenSprite->setPosition({ 300.f, 38.f });
}

void UI::updateEndScreenHover(float mouseX, float mouseY)
{
    if (!m_showEndScreen) return;

    m_playAgainHover = m_playAgainRect.contains({ mouseX, mouseY });
    m_mainMenuHover = m_mainMenuRect.contains({ mouseX, mouseY });
}

int UI::handleEndScreenClick(float mouseX, float mouseY)
{
    if (!m_showEndScreen) return -1;

    if (m_playAgainRect.contains({ mouseX, mouseY }))
        return 1;  // Play Again
    if (m_mainMenuRect.contains({ mouseX, mouseY }))
        return 2;  // Main Menu

    return -1;
}

void UI::drawEndScreen(RenderWindow& window)
{
    if (!m_showEndScreen) 
        return;

    // Draw overlay first 
    RectangleShape overlay;
    overlay.setSize({ 1400.f, 900.f });
    overlay.setFillColor(sf::Color(0, 0, 0, 220));  // 220 = dark
    overlay.setPosition({ 0.f, 0.f });
    window.draw(overlay);

    // now draw sprite 

    window.draw(*m_endScreenSprite);

    // PLAY AGAIN BUTTON 
    sf::RectangleShape playAgainBtn;
    playAgainBtn.setSize({ m_playAgainRect.size.x, m_playAgainRect.size.y });
    playAgainBtn.setPosition({ m_playAgainRect.position.x, m_playAgainRect.position.y });

    if (m_playAgainHover)
    {
        playAgainBtn.setFillColor(sf::Color(100, 255, 100, 100));
    }
    else
    {
        playAgainBtn.setFillColor(sf::Color(0, 0, 0,0));
    }
    window.draw(playAgainBtn);

    // MAIN MENU BUTTON 
    RectangleShape mainMenuBtn;
    mainMenuBtn.setSize({ m_mainMenuRect.size.x, m_mainMenuRect.size.y });
    mainMenuBtn.setPosition({ m_mainMenuRect.position.x, m_mainMenuRect.position.y });

    if (m_mainMenuHover)
    {
        mainMenuBtn.setFillColor(Color(255, 100, 100, 100));
    }
    else
    {
        mainMenuBtn.setFillColor(Color(0, 0, 0, 0));
    }
    window.draw(mainMenuBtn);

}