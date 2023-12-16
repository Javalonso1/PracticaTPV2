#include "MainMenuState.h"
#include "GameState.h"
#include "Button.h"
#include "Game.h"

MainMenuState::MainMenuState(Game* e) : GameState(e), barry(Button(myGame->devuelveText(0), 0, 0)) {}

MainMenuState::~MainMenuState() {}

void MainMenuState::Update() {

}

void MainMenuState::Render() const {
	barry.Render();
}

void MainMenuState::HandleEvents() {

}