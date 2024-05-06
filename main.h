#include <windows.h>
#include <tchar.h>
#include "nwpwin.h"
#include "nwpdlg.h"

int BOARD_SIZE = 8;
int SQUARE_SIZE = 50;

class size_dialog : public vsite::nwp::dialog {
protected:
	int idd() const override;
	bool on_init_dialog() override;
	bool on_ok() override;
public:
	int newBoardSize;
};

class main_window : public vsite::nwp::window {
protected:
	void on_paint(HDC hdc) override;
	void on_command(int id) override;
	void on_destroy() override;

	COLORREF squareColor1;
	COLORREF squareColor2;
	bool useCustomColors;

	void ChooseCustomColor();
};
