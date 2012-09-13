/*
 * Stellarium Location List Editor
 * Copyright (C) 2012  Bogdan Marinov
 * 
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street,
 * Fifth Floor, Boston, MA  02110-1301, USA.
*/

#ifndef LOCATIONLISTEDITOR_HPP
#define LOCATIONLISTEDITOR_HPP

#include <QMainWindow>

#include <QString>

namespace Ui {
class LocationListEditor;
}
class LocationListModel;
class QSortFilterProxyModel;

//! Main class of the %Location List Editor.
class LocationListEditor : public QMainWindow
{
	Q_OBJECT
	
public:
	explicit LocationListEditor(QWidget *parent = 0);
	~LocationListEditor();
	
protected:
	void changeEvent(QEvent* event);
	//! Reimplemented to prompt for saving.
	void closeEvent(QCloseEvent* event);
	
private:
	Ui::LocationListEditor *ui;
	LocationListModel* locations;
	QSortFilterProxyModel* proxyModel;
	
	//! Path to the currently opened list.
	QString openFilePath;
	//! Path to the /data/base_locations.txt file of the curret project.
	//! The "current" is the project from which's /utils the app is run.
	//! Empty if not found.
	QString projectFilePath;
	//! Path to the user_locations.txt in the curren user data directory.
	//! Empty if not found.
	QString userFilePath;
	
	//! Used in system file dialogs.
	QString fileFilters;
	
	//! If there's no file loaded, hide the table and show a message.
	bool checkIfFileIsLoaded();
	//! If the file is modified, prompt to save it.
	//! @returns true if the save operation was succcessful or if the file 
	//! was not modified.
	bool checkIfFileIsSaved();
	
	//! Load a list from the specified path.
	bool loadFile(const QString& path);
	//! Save the current list to the specified path.
	bool saveFile(const QString& path);
	//! Save the current list in binary form.
	//! (The binary format used by Stellarium to speed up the base location
	//! list loading.)
	//! @param path The path to the \b text file. The function will
	//! use the same path and file name, but with ".bin.gz" suffix.
	bool saveBinary(const QString& path);
	
private slots:
	//! Prompts for file location and opens that file.
	void open();
	//! Tries to open the base location list of the current project.
	//! Assumes that it is run from <project_dir>/utils/location-editor/.
	void openProjectLocations();
	//! Tries to open the location list in the current user's data directory.
	void openUserLocations();
	//! Save the currently opened file.
	//! @returns true if the file has been saved successfully.
	bool save();
	//! Save the currently opened file in another location.
	//! Propmts for a path to the new location.
	bool saveAs();
	//! Shows a window with author and copyright information.
	void showAboutWindow();
	
	//! Sets the view column affected by the search/filter field.
	void setFilteredColumn(int column);
};

#endif // LOCATIONLISTEDITOR_HPP
