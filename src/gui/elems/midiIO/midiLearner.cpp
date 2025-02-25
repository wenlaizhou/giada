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

#include "gui/elems/midiIO/midiLearner.h"
#include "core/const.h"
#include "gui/elems/basics/box.h"
#include "gui/elems/basics/boxtypes.h"
#include "gui/elems/basics/textButton.h"
#include "gui/ui.h"
#include "utils/string.h"
#include <cassert>

extern giada::v::Ui g_ui;

namespace giada::v
{
geMidiLearner::geMidiLearner(int x, int y, int w, int h, std::string l, int param)
: geFlex(x, y, w, h, Direction::HORIZONTAL, G_GUI_INNER_MARGIN)
, onStartLearn(nullptr)
, onStopLearn(nullptr)
, onClearLearn(nullptr)
, m_param(param)
{
	m_text     = new geBox(l.c_str());
	m_valueBtn = new geTextButton("");
	m_button   = new geTextButton(g_ui.langMapper.get(LangMap::COMMON_LEARN));

	add(m_text);
	add(m_valueBtn, 80);
	add(m_button, 50);
	end();

	m_text->box(G_CUSTOM_BORDER_BOX);

	m_valueBtn->box(G_CUSTOM_BORDER_BOX);
	m_valueBtn->when(FL_WHEN_RELEASE);
	m_valueBtn->onClick = [this]() {
		assert(onClearLearn != nullptr);

		if (Fl::event_button() == FL_RIGHT_MOUSE)
			onClearLearn(m_param);
	};

	m_button->type(FL_TOGGLE_BUTTON);
	m_button->onClick = [this]() {
		assert(onStartLearn != nullptr);
		assert(onStopLearn != nullptr);

		if (m_button->getValue() == 1)
			onStartLearn(m_param);
		else
			onStopLearn();
	};
}

/* -------------------------------------------------------------------------- */

void geMidiLearner::update(uint32_t value)
{
	std::string tmp = g_ui.langMapper.get(LangMap::COMMON_NOTSET);

	if (value != 0x0)
	{
		tmp = "0x" + u::string::iToString(value, /*hex=*/true);
		tmp.pop_back(); // Remove last two digits, useless in MIDI messages
		tmp.pop_back(); // Remove last two digits, useless in MIDI messages
	}

	m_valueBtn->copy_label(tmp.c_str());
	m_button->setValue(0);
}

/* -------------------------------------------------------------------------- */

void geMidiLearner::update(const std::string& s)
{
	m_valueBtn->copy_label(s.c_str());
	m_button->setValue(0);
}

/* -------------------------------------------------------------------------- */

void geMidiLearner::activate()
{
	Fl_Group::activate();
	m_valueBtn->activate();
	m_button->activate();
}

void geMidiLearner::deactivate()
{
	Fl_Group::deactivate();
	m_valueBtn->deactivate();
	m_button->deactivate();
}
} // namespace giada::v