#ifndef OUPTUT_H
#define OUPTUT_H
#include "Input.h"

class Output	//The application manager should have a pointer to this class
{
private:	
	window* pWind;	//Pointer to the Graphics Window
	
	void setDrawToolBarImagesPath(std::string paths[]) const; 
	//the funcion is const to be compatable with the const function CreaterawToolBar 
	//but it will not take a data member at all
	void setPlayToolBarImagesPath(std::string paths[]) const; 
	//same as the above function but for play mode

public:
	Output();		

	window* CreateWind(int, int, int , int) const; //creates the application window
	void CreateDrawToolBar() const;	//creates Draw mode toolbar & menu
	void CreatePlayToolBar() const;	//creates Play mode toolbar & menu
	void CreateStatusBar() const;	//create the status bar

	Input* CreateInput() const; //creates a pointer to the Input object	
	void ClearStatusBar() const;	//Clears the status bar
	void ClearDrawArea() const;	//Clears the drawing area
	
	// -- Figures Drawing functions
	void DrawRect(Point P1, Point P2, GfxInfo RectGfxInfo, bool selected=false) const;  //Draw a rectangle
	void DrawLine(Point P1, Point P2, GfxInfo RectGfxInfo, bool selected=false) const;  //Draw a Line
	void DrawTriangle(Point P1, Point P2, Point P3, GfxInfo RectGfxInfo, bool selected=false) const;  //Draw a Triangle
	void DrawCircle(Point P1, int Radius, GfxInfo RectGfxInfo, bool selected=false) const;  //Draw a Circle
	
	///Make similar functions for drawing all other figures.
	
	void PrintMessage(string msg) const;	//Print a message on Status bar

	color getCrntDrawColor() const;	//get current drwawing color
	color getCrntFillColor() const;	//get current filling color
	int getCrntPenWidth() const;		//get current pen width

	
	~Output();
};

#endif