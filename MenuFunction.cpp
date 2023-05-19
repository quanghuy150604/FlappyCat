#include "MenuFunction.h"
#include "ImgFunction.h"
#include "TextFunction.h"
#include "General.h"



int Menu::ShowMenu(SDL_Renderer* screen, TTF_Font* font, std::string path,
	int xt, int yt, std::string path1, std::string path2, int result, int high_score)
{
	
	SDL_Rect button1_pos;

	button1_pos.x = xt;
	button1_pos.y = yt;

	SDL_Rect button2_pos;
	button2_pos.x = xt;
	button2_pos.y = yt + 40;

	Text button1;
	button1.setColor(Text::WHITE_TEXT);
	button1.SetText(path1);

	Text button2;
	button2.setColor(Text::WHITE_TEXT);
	button2.SetText(path2);
	
	ImgFunction menu;
	menu.LoadImg(path, screen);
	SDL_SetRenderDrawColor(gRenderer, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
	menu.Render(screen, NULL);

	SDL_Event m_event;
	while (true)
	{
		button1.LoadFromRenderedText(font, screen);
		button1.RenderText(screen, button1_pos.x, button1_pos.y);
		int h1 = button1.getHeight();
		int w1 = button1.getWidth();

		button2.LoadFromRenderedText(font, screen);
		button2.RenderText(screen, button2_pos.x, button2_pos.y);
		int h2 = button2.getHeight();
		int w2 = button2.getWidth();

		if(path1=="Play Again")
		{ 
			Text end;
			std::string score = "Score: ";
			std::string str_val = std::to_string(result/8);
			score += str_val;
			end.SetText(score);
			end.setColor(Text::WHITE_TEXT);
			end.LoadFromRenderedText(font, screen);
			end.RenderText(screen, xt + 400, yt);

			std::string best = "Best: ";
			std::string str_val1 = std::to_string(high_score);
			best += str_val1;
			end.SetText(best);
			end.setColor(Text::WHITE_TEXT);
			end.LoadFromRenderedText(font, screen);
			end.RenderText(screen, xt + 400, yt + 40);
		}
		else
		{
			Text tutorial;
			std::string tur = "Tutorial: Right click to jump";
			tutorial.SetText(tur);
			tutorial.LoadFromRenderedText(font, screen);
			tutorial.RenderText(screen, xt, yt + 80);
		}
		SDL_RenderPresent(screen);

		while (SDL_PollEvent(&m_event) != 0)
		{
			if (m_event.type == SDL_QUIT)
			{
				return 1;
			}
			else if (m_event.type == SDL_MOUSEMOTION || m_event.type == SDL_MOUSEBUTTONDOWN)
			{
				int x, y;
				SDL_GetMouseState(&x, &y);
				
				if (x > button1_pos.x && x < button1_pos.x + w1 && y > button1_pos.y && y < button1_pos.y + h1)
				{
					button1.setColor(Text::RED_TEXT);
					if (m_event.button.button == SDL_BUTTON_LEFT)
					{
						return 0;
					}
				}
				else
				{
					button1.setColor(Text::WHITE_TEXT);
				}

				if (x > button2_pos.x && x < button2_pos.x + w2 && y > button2_pos.y && y < button2_pos.y + h2)
				{
					button2.setColor(Text::RED_TEXT);
					if (m_event.button.button == SDL_BUTTON_LEFT)
					{
						return 1;
					}
				}
				else
				{
					button2.setColor(Text::WHITE_TEXT);
				}
			}
		}
	}

	return 1;
}
