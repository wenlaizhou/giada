/* -----------------------------------------------------------------------------
 *
 * Giada - Your Hardcore Loopmachine
 *
 * -----------------------------------------------------------------------------
 *
 * Copyright (C) 2010-2022 Giovanni A. Zuliani | Monocasual Laboratories
 *
 * This file is part of Giada - Your Hardcore Loopmachine.
 *
 * Giada - Your Hardcore Loopmachine is free software: you can
 * redistribute it and/or modify it under the terms of the GNU General
 * Public License as published by the Free Software Foundation, either
 * version 3 of the License, or (at your option) any later version.
 *
 * Giada - Your Hardcore Loopmachine is distributed in the hope that it
 * will be useful, but WITHOUT ANY WARRANTY; without even the implied
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Giada - Your Hardcore Loopmachine. If not, see
 * <http://www.gnu.org/licenses/>.
 *
 * -------------------------------------------------------------------------- */

#ifndef GD_WINDOW_H
#define GD_WINDOW_H

#include "deps/geompp/src/rect.hpp"
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_SVG_Image.H>
#include <vector>

namespace giada::v
{
class gdWindow : public Fl_Double_Window
{
public:
	gdWindow(int x, int y, int w, int h, const char* title = nullptr, int id = 0);
	gdWindow(geompp::Rect<int>, const char* title = nullptr, int id = 0);
	~gdWindow();

	static void cb_closeChild(Fl_Widget* /*w*/, void* p);

	/* rebuild, refresh
	Rebuild() is called by the View Updater when something structural changes
	(e.g. a new channel added). Refresh() is called periodically by the View 
	Updater during the refresh loop. */

	virtual void rebuild(){};
	virtual void refresh(){};

	/* hasWindow
	True if the window with id 'id' exists in the stack. */

	bool hasWindow(int id) const;

	int  getId() const;
	void debug() const;

	/* getContentBounds
	Returns {0, 0, w(), h()}. */

	geompp::Rect<int> getContentBounds() const;

	/* getBounds
	Returns {x(), y(), w(), h()}. */

	geompp::Rect<int> getBounds() const;

	void      addSubWindow(gdWindow* w);
	void      delSubWindow(gdWindow* w);
	void      delSubWindow(int id);
	void      setId(int id);
	void      setParent(gdWindow* w);
	gdWindow* getParent();
	gdWindow* getChild(int id);

	void setBounds(geompp::Rect<int>);

protected:
	std::vector<gdWindow*> subWindows;
	int                    id;
	gdWindow*              parent;

private:
	Fl_SVG_Image m_icon;
};
} // namespace giada::v

#endif
