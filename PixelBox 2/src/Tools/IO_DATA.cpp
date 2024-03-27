#include "IO_DATA.h"


//=============

/*
   nr_file_name: 0 = all*
				 1 = board,all*
				 2 = struct,all*
				 3 = josefistdumm,all*
*/


//std::string IO_DATA::choose_open_file() {//returns path to file
//	OPENFILENAMEA saveFileDialog;
//	char szSaveFileName[MAX_PATH] = "";
//	ZeroMemory(&saveFileDialog, sizeof(saveFileDialog));
//	saveFileDialog.lStructSize = sizeof(saveFileDialog);
//	saveFileDialog.hwndOwner = NULL;
//	saveFileDialog.lpstrFilter = "Josef ist dumm! (*.josefistdumm)\0*josefistdumm\0All Files (*.*)\0*.*\0";
//	saveFileDialog.lpstrFile = szSaveFileName;
//	saveFileDialog.nMaxFile = MAX_PATH;
//	saveFileDialog.Flags = OFN_EXPLORER | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT;
//	saveFileDialog.lpstrDefExt = "josefistdumm";
//	GetOpenFileNameA(&saveFileDialog);
//	return saveFileDialog.lpstrFile;
//}

std::string IO_DATA::chooseOpenFile(int nrFileName) {//returns path to file
	OPENFILENAMEA openFileDialog;
	char szSaveFileName[MAX_PATH] = "";
	ZeroMemory(&openFileDialog, sizeof(openFileDialog));
	openFileDialog.lStructSize = sizeof(openFileDialog);
	openFileDialog.hwndOwner = NULL;

	openFileDialog.lpstrFilter = "All Files (*.*)\0*.*\0";
	openFileDialog.lpstrDefExt = "All";
	if (nrFileName == 1) {
		openFileDialog.lpstrFilter = "Board (*.board)\0*board\0All Files (*.*)\0*.*\0";
		openFileDialog.lpstrDefExt = "board";
	}
	else if (nrFileName == 2) {
		openFileDialog.lpstrFilter = "Structure (*.struct)\0*struct\0All Files (*.*)\0*.*\0";
		openFileDialog.lpstrDefExt = "struct";
	}
	else if (nrFileName == 3) {
		openFileDialog.lpstrFilter = "Josef ist dumm! (*.josefistdumm)\0*josefistdumm\0All Files (*.*)\0*.*\0";
		openFileDialog.lpstrDefExt = "josefistdumm";
	}
	openFileDialog.lpstrFile = szSaveFileName;
	openFileDialog.nMaxFile = MAX_PATH;
	openFileDialog.Flags = OFN_EXPLORER | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT;
	if (!GetOpenFileNameA(&openFileDialog))
		return "";
	return openFileDialog.lpstrFile;

}


std::string IO_DATA::chooseSaveFile(int nrFileName) {
	OPENFILENAMEA saveFileDialog;
	char szSaveFileName[MAX_PATH] = "";
	ZeroMemory(&saveFileDialog, sizeof(saveFileDialog));
	saveFileDialog.lStructSize = sizeof(saveFileDialog);
	saveFileDialog.hwndOwner = NULL;

	saveFileDialog.lpstrFilter = "All Files (*.*)\0*.*\0";
	saveFileDialog.lpstrDefExt = "All";
	if (nrFileName == 1) {
		saveFileDialog.lpstrFilter = "Board (*.board)\0*board\0All Files (*.*)\0*.*\0";
		saveFileDialog.lpstrDefExt = "board";
	}
	else if (nrFileName == 2) {
		saveFileDialog.lpstrFilter = "Structure (*.struct)\0*struct\0All Files (*.*)\0*.*\0";
		saveFileDialog.lpstrDefExt = "struct";
	}
	else if (nrFileName == 3) {
		saveFileDialog.lpstrFilter = "Josef ist dumm! (*.josefistdumm)\0*josefistdumm\0All Files (*.*)\0*.*\0";
		saveFileDialog.lpstrDefExt = "josefistdumm";
	}

	saveFileDialog.lpstrFile = szSaveFileName;
	saveFileDialog.nMaxFile = MAX_PATH;
	saveFileDialog.Flags = OFN_EXPLORER | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT;
	if (!GetSaveFileNameA(&saveFileDialog))
		return "";
	return saveFileDialog.lpstrFile;
}


bool IO_DATA::saveToFile(std::string fileName, const char *outputData, const size_t dataSize, bool appendData) {
	if (fileName == "")
		return false;

	auto myfile = std::fstream(fileName, std::ios::out | std::ios::binary | (appendData ? std::ios_base::app : 0));
	myfile.write((char*)outputData, dataSize);
	myfile.close();
	return true;

}

bool IO_DATA::readFromFile(std::string fileName, std::vector<char>& inputData) {
	if (fileName == "")
		return false;
	std::ifstream input(fileName, std::ios::binary);
	inputData = std::vector<char>((std::istreambuf_iterator<char>(input)), (std::istreambuf_iterator<char>()));
	input.close();
	return true;
}

//=============