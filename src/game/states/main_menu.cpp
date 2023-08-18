#include "main_menu.h"

MainMenu::MainMenu(Game& game, Window& window)
{
	int width = window.GetTerminalWidth();
	int height = window.GetTerminalHeight();

	surface.SetDimensions(width, height);
	
	SetBorder(surface, BorderStyle::Double, Colors::White);

	int center_y = height / 2;
	
	menu.AddButton(Button(Point(NULL, center_y), "NEW WORLD", {AlignCenter, 0}));
	menu.AddButton(Button(Point(NULL, center_y + 1), "LOAD GAME", { AlignCenter, 0 }));
	menu.AddButton(Button(Point(NULL, center_y + 2), "QUIT", { AlignCenter, -3 }));

	ui.Add(&menu);

	Glyph g;
	g.character = 'a';
	g.color = Colors::White;
	g.bg_color = { 0, 0, 255 };
	surface.Set(2, 2, g);
}

void MainMenu::Update(Game& game, Input& input)
{
	ui.Update(input);
}

void MainMenu::Draw(Window& window)
{
	ui.Draw(surface);
	window.DrawSurface(surface);
}
