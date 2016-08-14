#ifndef MENUS_HPP
#define MENUS_HPP

int mainMenu            ();
int highscoresMenu      (int highlight = -1);
int creditsMenu         ();
int errorScreen         (int errorCode);
int graphicsOptionsMenu ();
int optionsMenu         ();
int pauseMenu           ();
int splashScreen        ();
int waitScreen          ();
int gameOverScreen      ();
int newHighscoreScreen  ();

#ifdef DEVMODE
int devMenu();
#endif // DEVMODE

#endif // MENUS_HPP

