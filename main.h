#include <windows.h>
#include <tchar.h>
#include "nwpwin.h"
#include "nwpdlg.h"


class size_dialog : public vsite::nwp::dialog {
protected:
	int idd() const override;
	bool on_init_dialog() override;
	bool on_ok() override;
public:

	int newBoardSize;
	int BOARD_SIZE_W ;
	int BOARD_SIZE_H ;

	
	
};

class main_window : public vsite::nwp::window {
protected:
	void on_paint(HDC hdc) override;
	void on_command(int id) override;
	void on_destroy() override;
public:

	COLORREF squareColor= RGB(0, 0, 0);
	int boardWidth=8;
	int boardHeight=8;

};

