#include "progressModule.hpp"

ProgressCircle::ProgressCircle() {
	ProgressBar.setPrimitiveType (sf::PrimitiveType::TrianglesFan);
	//            ProgressBar.setPrimitiveType(sf::PrimitiveType::LinesStrip);
	Radius = 50;
	Angle = 0;
	Separation = 0;
	progressDegrees = 0;
	Colour = sf::Color (0, 255, 0, 255);
	}

ProgressCircle &ProgressCircle::setSize (float pRadius) {
	Radius = pRadius;
	return *this;
	}

float ProgressCircle::getSize() {
	return Radius;
	}

ProgressCircle &ProgressCircle::setSeparation (int Sep) {
	Separation = Sep;
	return *this;
	}

ProgressCircle &ProgressCircle::setPosition (sf::Vector2f Pos) {
	Position = Pos;
	return *this;
	}

sf::Vector2f ProgressCircle::getPosition() {
	return Position;
	}

ProgressCircle &ProgressCircle::setColor (sf::Color newColour) {
	Colour = newColour;
	return *this;
	}

sf::Color ProgressCircle::getColor () {
	return Colour;
	}

float ProgressCircle::getPercentage() {
	return (progressDegrees / 360) * 100;
	}

ProgressCircle &ProgressCircle::setPercentage (float percentage) {
	progressDegrees = (percentage / 100) * 360;
	return *this;
	}

void ProgressCircle::draw (sf::RenderWindow &Window) {
	ProgressBar.clear();
	Angle = 0;
	ProgressBar.append (sf::Vertex (sf::Vector2f (Position.x, Position.y), Colour) );

	while (Angle <= progressDegrees) {
		float pAngle = Angle - 180;
		pAngle *= (3.14 / 180.0);
		double x = Position.x + (Radius * sin (pAngle) );
		double y = Position.y + (Radius * cos (pAngle) );
		pAngle *= (180.0 / 3.14);
		//            if ((int)Angle % (int)(sqrt(Radius)) == 0) ProgressBar.append(sf::Vertex (sf::Vector2f(x, y), sf::Color::Black));
		if (Separation > 0) {
			if ( (int) Angle % Separation == 0)
				ProgressBar.append (sf::Vertex (sf::Vector2f (x, y), sf::Color::Black) );
			else ProgressBar.append (sf::Vertex (sf::Vector2f (x, y), Colour) );
			Angle += 0.1;
			}
		else ProgressBar.append (sf::Vertex (sf::Vector2f (x, y), Colour) );
		}
	Window.draw (ProgressBar);
	}


ProgressBar::ProgressBar() {
	Percentage = 0;
	Outline.setFillColor (sf::Color::Black);
	Outline.setSize (sf::Vector2f (100, 800) );
	Outline.setOutlineThickness (8);
	}

ProgressBar::ProgressBar (sf::Vector2f size) {
	Percentage = 0;
	Outline.setFillColor (sf::Color::Black);
	Outline.setSize (size);
	Outline.setOutlineThickness (8);
	}

void ProgressBar::draw (sf::RenderWindow &Window) {
	Bar.setSize (sf::Vector2f (Outline.getSize().x * (Percentage / 100), Outline.getSize().y) );
	Bar.setPosition (Outline.getPosition().x, Outline.getPosition().y);
	Window.draw (Outline);
	Window.draw (Bar);
	}

ProgressBar &ProgressBar::setSize (sf::Vector2f size) {
	Outline.setSize (size);
	return *this;
	}

sf::Vector2f ProgressBar::getSize () {
	return Outline.getSize();
	}

ProgressBar &ProgressBar::setPosition (sf::Vector2f Pos) {
	Outline.setPosition (Pos);
	return *this;
	}

sf::Vector2f ProgressBar::getPosition() {
	return Outline.getPosition();
	}

ProgressBar &ProgressBar::setBarColor (sf::Color newColour) {
	Bar.setFillColor (newColour);
	return *this;
	}

ProgressBar &ProgressBar::setBackgroundColor (sf::Color newColour) {
	Outline.setFillColor (newColour);
	return *this;
	}

ProgressBar &ProgressBar::setOutlineColor (sf::Color newColour) {
	Outline.setOutlineColor (newColour);
	return *this;
	}

sf::Color ProgressBar::getBarColor () {
	return Bar.getFillColor();
	}

sf::Color ProgressBar::getBackgroundColor() {
	return Outline.getFillColor();
	}

sf::Color ProgressBar::getOutlineColor () {
	return Outline.getOutlineColor();
	}

float ProgressBar::getPercentage () {
	return Percentage;
	}

ProgressBar &ProgressBar::setPercentage (double percentage) {
	Percentage = percentage;
	return *this;
	}

void saveLoadScreen (string Text, function <bool (int &progress) > procedure) {
	bool success = false,  failed = false;
	int progress = 0;

	sf::Sprite tempBackground = Background;
	tempBackground.setColor (sf::Color (100, 100, 210) );

	sf::Text savingText (Text, Font, MENU_FONT_SIZE * 2);
	savingText.setStyle (sf::Text::Bold);
	savingText.setPosition (APP_WIDTH / 2 - 150, APP_HEIGHT / 2 - 200);

	ProgressBar bar (sf::Vector2f (800, 70) );
	bar.setBarColor (sf::Color::Green)
	.setOutlineColor (sf::Color::White)
	.setBackgroundColor (sf::Color::White)
	.setPosition (sf::Vector2f (APP_WIDTH / 2 - bar.getSize().x / 2,
	                            APP_HEIGHT / 2) );

	thread startSave ( [&] {
		success = procedure (progress);
		if (!success)
			failed = true;
		});

	while (!success && !failed) {
		mtx.lock();
		bar.setPercentage (progress);
		mtx.unlock();
		App.clear();
		App.draw (tempBackground );
		App.draw (savingText);
		bar.draw (App);
		App.display();
		}

	startSave.join();
	}
