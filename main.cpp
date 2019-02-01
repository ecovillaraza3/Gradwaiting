#include <SDL2/SDL.h>
#include "MainMenu.h"
#include "Game.h"
#include "Story.h"
#include <iostream>
#include <fstream>
#include <string>
#include "RetryWindow.h"
#include "ContinueWindow.h"
#include "StoryRetryWindow.h"
#include "HighschoolWindow.h"
#include "ContinueHighSchool.h"
#include "HighschoolRetryWindow.h"
#include "CollegeWindow.h"
#include "CollegeContinue.h"
#include "RetryCollege.h"

using namespace std;

void mainMenu();
void endlessRunnerGame();
void elementaryStory();
void highschoolStory();
void collegeStory();

MainMenu *menu = new MainMenu();
Game *game = new Game();
Story *elementary = new Story();
HighschoolWindow *highchool = new HighschoolWindow();
CollegeWindow *college = new CollegeWindow();

RetryWindow *endlessRet = new RetryWindow();
StoryRetryWindow *elemRet = new StoryRetryWindow();
ContinueWindow *continueWindow = new ContinueWindow();
ContinueHighSchool *continueHSWindow = new ContinueHighSchool();
HighschoolRetryWindow *highRet = new HighschoolRetryWindow();
CollegeContinue *contineCollWindow = new CollegeContinue();
RetryCollege *collRet = new RetryCollege();


int main( int argc, char * argv[])
{
    string savedYear;
    ifstream getSavedYear;
    getSavedYear.open("mainyear.txt");
    getSavedYear >> savedYear;
    getSavedYear.close();

    mainMenu();
    while(true){
        if(Game::windowName == "endless"){
            RetryWindow::windowName = "endless";
            while(RetryWindow::windowName == "endless"){
            endlessRunnerGame();
            endlessRet->clean();
            }
        }else if(savedYear == "elementary"){
            ContinueWindow::windowName = "elementary";
            while(ContinueWindow::windowName == "elementary" || StoryRetryWindow::windowName == "elementary"){
                elementaryStory();
                elemRet->clean();
                continueWindow->clean();
            }
        }else if(savedYear == "highschool"){
            ContinueHighSchool::windowName = "highschool";
            while(ContinueHighSchool::windowName == "highschool" || HighschoolRetryWindow::windowName == "highschool"){
                highschoolStory();
                highRet->clean();
                continueHSWindow->clean();
            }
        }else if(savedYear == "college"){
            CollegeContinue::windowName = "college";
            while(CollegeContinue::windowName == "college" || RetryCollege::windowName == "college"){
                collegeStory();
                collRet->clean();
                contineCollWindow->clean();
            }
        }else if(savedYear == "Finish"){
            string savedYear = "elementary";
            ofstream setSavedYear;
            setSavedYear.open("mainyear.txt");
            setSavedYear << savedYear;
            setSavedYear.close();

            int level = 1;
            ofstream setSaveLevel;
            setSaveLevel.open("yearlevel.txt");
            setSaveLevel << level;
            setSaveLevel.close();
            Story::isFinishStory = true;
        }
        if(Story::isFinishStory){
            mainMenu();
        }


        ifstream getSavedYear;
        getSavedYear.open("mainyear.txt");
        getSavedYear >> savedYear;
        getSavedYear.close();
    }

    return 0;
}

void mainMenu(){

    const int FPS = 60;
    const int frameDelay = 1000/FPS;

    Uint32 frameStart;
    int frameTime;

    menu->init("GradWaiting",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,800,500,false);
    while(menu->running()){

        frameStart = SDL_GetTicks();


        menu->handlerEvent();
        menu->update();
        menu->render();

        frameTime = SDL_GetTicks() - frameStart;
        if(frameDelay > frameTime){
            SDL_Delay(frameDelay - frameTime);
        }
    }
    menu->clean();
}

void endlessRunnerGame(){
    // ENDLESS RUNNER GAME
    const int FPS = 60;
    const int frameDelay = 1000/FPS;

    Uint32 frameStart;
    int frameTime;
    game->init("Endless Mode",SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1030,500,false);

    while(game->running()){

        frameStart = SDL_GetTicks();
        game->handlerEvent();
        game->update();
        game->render();

        frameTime = SDL_GetTicks() - frameStart;
        if(frameDelay > frameTime){
            SDL_Delay(frameDelay - frameTime);
        }
    }
    game->clean();
}

void elementaryStory(){

    // STORY MODE
    const int FPS = 60;
    const int frameDelay = 1000/FPS;

    Uint32 frameStart;
    int frameTime;

    elementary->init("Elementary",SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1030,500,false);
    while(elementary->running()){

        frameStart = SDL_GetTicks();
        elementary->handlerEvent();
        elementary->update();
        elementary->render();

        frameTime = SDL_GetTicks() - frameStart;
        if(frameDelay > frameTime){
            SDL_Delay(frameDelay - frameTime);
        }
    }

    elementary->clean();
}

void highschoolStory(){


    const int FPS = 60;
    const int frameDelay = 1000/FPS;

    Uint32 frameStart;
    int frameTime;

    highchool->init("High School",SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1030,500,false);
    while(highchool->running()){

        frameStart = SDL_GetTicks();
        highchool->handlerEvent();
        highchool->update();
        highchool->render();

        frameTime = SDL_GetTicks() - frameStart;
        if(frameDelay > frameTime){
            SDL_Delay(frameDelay - frameTime);
        }
    }

    highchool->clean();

}

void collegeStory(){

    const int FPS = 60;
    const int frameDelay = 1000/FPS;

    Uint32 frameStart;
    int frameTime;

    college->init("College",SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1030,500,false);
    while(college->running()){

        frameStart = SDL_GetTicks();
        college->handlerEvent();
        college->update();
        college->render();

        frameTime = SDL_GetTicks() - frameStart;
        if(frameDelay > frameTime){
            SDL_Delay(frameDelay - frameTime);
        }
    }

    college->clean();

}

