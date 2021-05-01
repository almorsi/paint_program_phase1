#include "Output.h"



Output::Output()
{
	//Initialize user interface parameters
	UI.InterfaceMode      = MODE_DRAW;
	UI.MaxNumberItems     = (DRAW_ITM_COUNT > PLAY_ITM_COUNT) ? DRAW_ITM_COUNT : PLAY_ITM_COUNT;
	UI.FreeSpaceInToolBar = 5;
	UI.MenuItemWidth      = 48;
	UI.MenuItemHeight     = 48;
	UI.MenuItemPadding    = 2;

	UI.width	= UI.MaxNumberItems*UI.MenuItemWidth + UI.FreeSpaceInToolBar*UI.MenuItemWidth;
	UI.height	= UI.MenuItemHeight*UI.MaxNumberItems - UI.FreeSpaceInToolBar * UI.MenuItemWidth;
	UI.wx		= 50;
	UI.wy		=50;

	
	UI.StatusBarHeight	= UI.MenuItemHeight + UI.MenuItemPadding;
	UI.ToolBarHeight	= UI.MenuItemHeight + 2 * UI.MenuItemPadding;
	
	UI.ToolBarColor		= color(250, 255, 204);
	UI.DrawColor		= BLUE;		//Drawing color
	UI.FillColor		= GREEN;	//Filling color
	UI.MsgColor			= BLACK;	//Messages color
	UI.BkGrndColor		= WHITE;	//Background color
	UI.HighlightColor	= color(163, 255, 252);	//This color should NOT be used to draw figures. use if for highlight only
	UI.StatusBarColor	= color(250, 255, 204);
	UI.PenWidth			= 3;		//width of the figures frames

	//setting the path for the images
	setDrawToolBarImagesPath();
	setPlayToolBarImagesPath();

	//Create the output window
	pWind = CreateWind(UI.width, UI.height, UI.wx, UI.wy);
	//Change the title
	pWind->ChangeTitle("Paint for Kids - Programming Techniques Project");
	CreateDrawToolBar();
	CreateStatusBar();
}


Input* Output::CreateInput() const
{
	Input* pIn = new Input(pWind);
	return pIn;
}

//======================================================================================//
//								Interface Functions										//
//======================================================================================//

window* Output::CreateWind(int w, int h, int x, int y) const
{ 
	window* pW = new window(w, h, x, y);
	pW->SetBrush(UI.BkGrndColor);
	pW->SetPen(UI.BkGrndColor, 1);
	pW->DrawRectangle(0, UI.ToolBarHeight, w, h);	
	return pW;
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::CreateStatusBar() const
{
	ClearStatusBar();

	pWind->SetPen(UI.StatusBarColor, 1);
	pWind->SetBrush(UI.StatusBarColor);
	pWind->DrawRectangle(0, UI.height - UI.StatusBarHeight, UI.width, UI.height);
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::ClearStatusBar() const
{

	//Clear Status bar by drawing a filled white rectangle
	pWind->SetPen(UI.StatusBarColor, 1);
	pWind->SetBrush(UI.StatusBarColor);
	pWind->DrawRectangle(0, UI.height - UI.StatusBarHeight, UI.width, UI.height);

	//Draw a line above the status bar
	pWind->SetPen(BLACK, UI.MenuItemPadding);
	pWind->DrawLine(0, UI.height - UI.MenuItemHeight,
		UI.width, UI.height - UI.MenuItemHeight);
}
void Output::ClearToolBar() const
{
	pWind->SetPen(UI.ToolBarColor, 1);
	pWind->SetBrush(UI.ToolBarColor);
	pWind->DrawRectangle(0, 0, UI.width, UI.ToolBarHeight);


	//Draw a line under the toolbar
	pWind->SetPen(BLACK, UI.MenuItemPadding);
	pWind->DrawLine(0, UI.ToolBarHeight - UI.MenuItemPadding,
		UI.width, UI.ToolBarHeight - UI.MenuItemPadding);
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::CreateDrawToolBar(int which_is_hi) const
{
	UI.InterfaceMode = MODE_DRAW;

	//You can draw the tool bar icons in any way you want.
	//Below is one possible way
	ClearToolBar();

	//First prepare List of images for each menu item
	//To control the order of these images in the menu, 
	//reoder them in UI_Info.h ==> enum DrawMenuItem

	

	//TODO: Prepare images for each menu item and add it to the list
	//I added member function to do that

	//Draw menu item one image at a time
	for (int i = 0; i < DRAW_ITM_COUNT; i++)
	{
		if(i == which_is_hi)
			pWind->DrawImage(DrawToolBarImagesHi[i], i*UI.MenuItemWidth,0
				,UI.MenuItemWidth,   UI.MenuItemHeight);
		else																					 
			pWind->DrawImage(DrawToolBarImagesNorm[i], i*UI.MenuItemWidth,0
				,UI.MenuItemWidth, UI.MenuItemHeight);

	}



	//Draw a line under the toolbar
	// I implented is the clear tool bar function

}
//////////////////////////////////////////////////////////////////////////////////////////

void Output::CreatePlayToolBar() const
{
	UI.InterfaceMode = MODE_PLAY;
	///TODO: write code to create Play mode menu
	ClearToolBar();

	//Draw menu item one image at a time
	for (int i = 0; i < PLAY_ITM_COUNT; i++)
		pWind->DrawImage(PlayToolBarImages[i], i * UI.MenuItemWidth, 0, UI.MenuItemWidth, UI.MenuItemHeight);


}
//////////////////////////////////////////////////////////////////////////////////////////

void Output::ClearDrawArea() const
{
	pWind->SetPen(UI.BkGrndColor, 1);
	pWind->SetBrush(UI.BkGrndColor);
	pWind->DrawRectangle(0, UI.ToolBarHeight, UI.width, UI.height - UI.StatusBarHeight);
	
}
//////////////////////////////////////////////////////////////////////////////////////////

void Output::PrintMessage(string msg) const	//Prints a message on status bar
{
	ClearStatusBar();	//First clear the status bar
	
	pWind->SetPen(UI.MsgColor, 50);
	pWind->SetFont(20, BOLD , BY_NAME, "Arial");   
	pWind->DrawString(10, UI.height - (int)(UI.StatusBarHeight * 0.8f), msg);
}
//////////////////////////////////////////////////////////////////////////////////////////

color Output::getCrntDrawColor() const	//get current drwawing color
{	return UI.DrawColor;	}
//////////////////////////////////////////////////////////////////////////////////////////

color Output::getCrntFillColor() const	//get current filling color
{	return UI.FillColor;	}
//////////////////////////////////////////////////////////////////////////////////////////
	
int Output::getCrntPenWidth() const		//get current pen width
{	return UI.PenWidth;	}

//======================================================================================//
//								Figures Drawing Functions								//
//======================================================================================//

void Output::DrawRect(Point P1, Point P2, GfxInfo RectGfxInfo, bool selected) const
{
	color DrawingClr;
	if(selected)	
		DrawingClr = UI.HighlightColor; //Figure should be drawn highlighted
	else			
		DrawingClr = RectGfxInfo.DrawClr;
	
	pWind->SetPen(DrawingClr, RectGfxInfo.BorderWdth);	//Set Drawing color & width

	drawstyle style;
	if (RectGfxInfo.isFilled)	
	{
		style = FILLED;		
		pWind->SetBrush(RectGfxInfo.FillClr);
	}
	else	
		style = FRAME;

	
	pWind->DrawRectangle(P1.x, P1.y, P2.x, P2.y, style);
	
}

void Output::DrawLine(Point P1, Point P2, GfxInfo RectGfxInfo, bool selected) const
{
	color DrawingClr;
	if(selected)	
		DrawingClr = UI.HighlightColor; //Figure should be drawn highlighted
	else			
		DrawingClr = RectGfxInfo.DrawClr;
	
	pWind->SetPen(DrawingClr, RectGfxInfo.BorderWdth);	//Set Drawing color & width

	drawstyle style = FRAME;

	
	pWind->DrawLine(P1.x, P1.y, P2.x, P2.y, style);
}

void Output::DrawTriangle(Point P1, Point P2, Point P3, GfxInfo RectGfxInfo, bool selected) const
{
	color DrawingClr;
	if (selected)
		DrawingClr = UI.HighlightColor; //Figure should be drawn highlighted
	else
		DrawingClr = RectGfxInfo.DrawClr;

	pWind->SetPen(DrawingClr, RectGfxInfo.BorderWdth);	//Set Drawing color & width

	drawstyle style;
	if (RectGfxInfo.isFilled)
	{
		style = FILLED;
		pWind->SetBrush(RectGfxInfo.FillClr);
	}
	else
		style = FRAME;


	pWind->DrawTriangle(P1.x, P1.y, P2.x, P2.y, P3.x, P3.y, style);
}

void Output::DrawCircle(Point P1, int Radius, GfxInfo RectGfxInfo, bool selected) const
{
	color DrawingClr;
	if (selected)
		DrawingClr = UI.HighlightColor; //Figure should be drawn highlighted
	else
		DrawingClr = RectGfxInfo.DrawClr;

	pWind->SetPen(DrawingClr, RectGfxInfo.BorderWdth);	//Set Drawing color & width

	drawstyle style;
	if (RectGfxInfo.isFilled)
	{
		style = FILLED;
		pWind->SetBrush(RectGfxInfo.FillClr);
	}
	else
		style = FRAME;


	pWind->DrawCircle(P1.x, P1.y, Radius, style);
}


void Output::setDrawToolBarImagesPath()
{
	//setting the normal
	DrawToolBarImagesNorm[ITM_TO_PLAY	] = "images\\draw-tool-bar-minue-items\\NORM\\to_play.jpg";
	DrawToolBarImagesNorm[ITM_LINE		] = "images\\draw-tool-bar-minue-items\\NORM\\draw_line.jpg";
	DrawToolBarImagesNorm[ITM_RECT		] = "images\\draw-tool-bar-minue-items\\NORM\\draw_rect.jpg";
	DrawToolBarImagesNorm[ITM_TRI		] = "images\\draw-tool-bar-minue-items\\NORM\\draw_tri.jpg";
	DrawToolBarImagesNorm[ITM_CIRC		] = "images\\draw-tool-bar-minue-items\\NORM\\draw_circ.jpg";
	DrawToolBarImagesNorm[ITM_DRAW_CLR	] = "images\\draw-tool-bar-minue-items\\NORM\\chng_draw_clr.jpg";
	DrawToolBarImagesNorm[ITM_FILL_CLR	] = "images\\draw-tool-bar-minue-items\\NORM\\chng_fill_clr.jpg";
	DrawToolBarImagesNorm[ITM_BK_CLR	] = "images\\draw-tool-bar-minue-items\\NORM\\chng_bk_clr.jpg";
	DrawToolBarImagesNorm[ITM_SELECT	] = "images\\draw-tool-bar-minue-items\\NORM\\select.jpg";
	DrawToolBarImagesNorm[ITM_DEL		] = "images\\draw-tool-bar-minue-items\\NORM\\del.jpg";
	DrawToolBarImagesNorm[ITM_MOVE		] = "images\\draw-tool-bar-minue-items\\NORM\\move.jpg";
	DrawToolBarImagesNorm[ITM_RESIZE	] = "images\\draw-tool-bar-minue-items\\NORM\\resize.jpg";
	DrawToolBarImagesNorm[ITM_ROTATE	] = "images\\draw-tool-bar-minue-items\\NORM\\rotate.jpg";
	DrawToolBarImagesNorm[ITM_SEND_BACK	] = "images\\draw-tool-bar-minue-items\\NORM\\send_back.jpg";
	DrawToolBarImagesNorm[ITM_BRNG_FRNT	] = "images\\draw-tool-bar-minue-items\\NORM\\brng_frnt.jpg";
	DrawToolBarImagesNorm[ITM_SAVE		] = "images\\draw-tool-bar-minue-items\\NORM\\save.jpg";
	DrawToolBarImagesNorm[ITM_LOAD		] = "images\\draw-tool-bar-minue-items\\NORM\\load.jpg";
	DrawToolBarImagesNorm[ITM_UNDO		] = "images\\draw-tool-bar-minue-items\\NORM\\undo.jpg";
	DrawToolBarImagesNorm[ITM_REDO		] = "images\\draw-tool-bar-minue-items\\NORM\\redo.jpg";
	DrawToolBarImagesNorm[ITM_EXIT		] = "images\\draw-tool-bar-minue-items\\NORM\\exit.jpg";
	//setting the hilighted
	DrawToolBarImagesHi[ITM_TO_PLAY		] = "images\\draw-tool-bar-minue-items\\HI\\h_to_play.jpg";
	DrawToolBarImagesHi[ITM_LINE		] = "images\\draw-tool-bar-minue-items\\HI\\h_draw_line.jpg";
	DrawToolBarImagesHi[ITM_RECT		] = "images\\draw-tool-bar-minue-items\\HI\\h_draw_rect.jpg";
	DrawToolBarImagesHi[ITM_TRI			] = "images\\draw-tool-bar-minue-items\\HI\\h_draw_tri.jpg";
	DrawToolBarImagesHi[ITM_CIRC		] = "images\\draw-tool-bar-minue-items\\HI\\h_draw_circ.jpg";
	DrawToolBarImagesHi[ITM_DRAW_CLR	] = "images\\draw-tool-bar-minue-items\\HI\\h_chng_draw_clr.jpg";
	DrawToolBarImagesHi[ITM_FILL_CLR	] = "images\\draw-tool-bar-minue-items\\HI\\h_chng_fill_clr.jpg";
	DrawToolBarImagesHi[ITM_BK_CLR		] = "images\\draw-tool-bar-minue-items\\HI\\h_chng_bk_clr.jpg";
	DrawToolBarImagesHi[ITM_SELECT		] = "images\\draw-tool-bar-minue-items\\HI\\h_select.jpg";
	DrawToolBarImagesHi[ITM_DEL			] = "images\\draw-tool-bar-minue-items\\HI\\h_del.jpg";
	DrawToolBarImagesHi[ITM_MOVE		] = "images\\draw-tool-bar-minue-items\\HI\\h_move.jpg";
	DrawToolBarImagesHi[ITM_RESIZE		] = "images\\draw-tool-bar-minue-items\\HI\\h_resize.jpg";
	DrawToolBarImagesHi[ITM_ROTATE		] = "images\\draw-tool-bar-minue-items\\HI\\h_rotate.jpg";
	DrawToolBarImagesHi[ITM_SEND_BACK	] = "images\\draw-tool-bar-minue-items\\HI\\h_send_back.jpg";
	DrawToolBarImagesHi[ITM_BRNG_FRNT	] = "images\\draw-tool-bar-minue-items\\HI\\h_brng_frnt.jpg";
	DrawToolBarImagesHi[ITM_SAVE		] = "images\\draw-tool-bar-minue-items\\HI\\h_save.jpg";
	DrawToolBarImagesHi[ITM_LOAD		] = "images\\draw-tool-bar-minue-items\\HI\\h_load.jpg";
	DrawToolBarImagesHi[ITM_UNDO		] = "images\\draw-tool-bar-minue-items\\HI\\h_undo.jpg";
	DrawToolBarImagesHi[ITM_REDO		] = "images\\draw-tool-bar-minue-items\\HI\\h_redo.jpg";
	DrawToolBarImagesHi[ITM_EXIT		] = "images\\draw-tool-bar-minue-items\\HI\\h_exit.jpg";
}

void Output::setPlayToolBarImagesPath()
{
	PlayToolBarImages[ITM_TO_DRAW		] = "images\\play-tool-bar-minue-items\\NORM\\to_draw.jpg";
	PlayToolBarImages[ITM_SHAPE_ONLY	] = "images\\play-tool-bar-minue-items\\NORM\\ITM_SHAPE_ONLY.jpg";
	PlayToolBarImages[ITM_CLR_ONLY		] = "images\\play-tool-bar-minue-items\\NORM\\ITM_CLR_ONLY.jpg";
	PlayToolBarImages[ITM_SHAPE_N_CLR	] = "images\\play-tool-bar-minue-items\\NORM\\ITM_SHAPE_N_CLR.jpg";
	PlayToolBarImages[ITM_AREA			] = "images\\play-tool-bar-minue-items\\NORM\\ITM_AREA.jpg";
}


//////////////////////////////////////////////////////////////////////////////////////////
Output::~Output()
{
	delete pWind;
}

