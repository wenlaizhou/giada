/* -----------------------------------------------------------------------------
 *
 * Giada - Your Hardcore Loopmachine
 *
 * ge_channel
 *
 * -----------------------------------------------------------------------------
 *
 * Copyright (C) 2010-2015 Giovanni A. Zuliani | Monocasual
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


#include "ge_channel.h"
#include "ge_sampleChannel.h"
#include "gd_mainWindow.h"
#include "gd_keyGrabber.h"
#include "gd_midiGrabber.h"
#include "gd_editor.h"
#include "gd_actionEditor.h"
#include "gd_warnings.h"
#include "gd_browser.h"
#include "gd_midiOutputSetup.h"
#include "gg_keyboard.h"
#include "pluginHost.h"
#include "mixer.h"
#include "conf.h"
#include "patch.h"
#include "graphics.h"
#include "channel.h"
#include "wave.h"
#include "sampleChannel.h"
#include "midiChannel.h"
#include "glue.h"
#include "gui_utils.h"

#ifdef WITH_VST
#include "gd_pluginList.h"
#endif


extern Mixer 		     G_Mixer;
extern Conf  		     G_Conf;
extern Patch 		     G_Patch;
extern gdMainWindow *mainWin;


gChannel::gChannel(int X, int Y, int W, int H, int type)
 : Fl_Group(X, Y, W, H, NULL), type(type)
{
}


/* -------------------------------------------------------------------------- */


int gChannel::getColumnIndex()
{
	return ((gColumn*)parent())->getIndex();
}


/* -------------------------------------------------------------------------- */


#ifdef WITH_VST

void gChannel::lightUpFx()
{
  //fx->full = ch->plugins.size > 0;
}

#endif


/* -------------------------------------------------------------------------- */
/* -------------------------------------------------------------------------- */
/* -------------------------------------------------------------------------- */


gStatus::gStatus(int x, int y, int w, int h, SampleChannel *ch, const char *L)
: Fl_Box(x, y, w, h, L), ch(ch) {}

void gStatus::draw()
{
  fl_rect(x(), y(), w(), h(), COLOR_BD_0);              // reset border
  fl_rectf(x()+1, y()+1, w()-2, h()-2, COLOR_BG_0);     // reset background

  if (ch != NULL) {
    if (ch->status    & (STATUS_WAIT | STATUS_ENDING | REC_ENDING | REC_WAITING) ||
        ch->recStatus & (REC_WAITING | REC_ENDING))
    {
      fl_rect(x(), y(), w(), h(), COLOR_BD_1);
    }
    else
    if (ch->status == STATUS_PLAY)
      fl_rect(x(), y(), w(), h(), COLOR_BD_1);
    else
      fl_rectf(x()+1, y()+1, w()-2, h()-2, COLOR_BG_0);     // status empty


    if (G_Mixer.chanInput == ch)
      fl_rectf(x()+1, y()+1, w()-2, h()-2, COLOR_BG_3);     // take in progress
    else
    if (recorder::active && recorder::canRec(ch))
      fl_rectf(x()+1, y()+1, w()-2, h()-2, COLOR_BG_4);     // action record

    /* equation for the progress bar:
     * ((chanTracker - chanStart) * w()) / (chanEnd - chanStart). */

    int pos = ch->getPosition();
    if (pos == -1)
      pos = 0;
    else
      pos = (pos * (w()-1)) / (ch->end - ch->begin);
    fl_rectf(x()+1, y()+1, pos, h()-2, COLOR_BG_2);
  }
}


/* -------------------------------------------------------------------------- */
/* -------------------------------------------------------------------------- */
/* -------------------------------------------------------------------------- */


gModeBox::gModeBox(int x, int y, int w, int h, SampleChannel *ch, const char *L)
  : Fl_Menu_Button(x, y, w, h, L), ch(ch)
{
  box(G_BOX);
  textsize(11);
  textcolor(COLOR_TEXT_0);
  color(COLOR_BG_0);

  add("Loop . basic",      0, cb_change_chanmode, (void *)LOOP_BASIC);
  add("Loop . once",       0, cb_change_chanmode, (void *)LOOP_ONCE);
  add("Loop . once . bar", 0, cb_change_chanmode, (void *)LOOP_ONCE_BAR);
  add("Loop . repeat",     0, cb_change_chanmode, (void *)LOOP_REPEAT);
  add("Oneshot . basic",   0, cb_change_chanmode, (void *)SINGLE_BASIC);
  add("Oneshot . press",   0, cb_change_chanmode, (void *)SINGLE_PRESS);
  add("Oneshot . retrig",  0, cb_change_chanmode, (void *)SINGLE_RETRIG);
  add("Oneshot . endless", 0, cb_change_chanmode, (void *)SINGLE_ENDLESS);
}


/* -------------------------------------------------------------------------- */


void gModeBox::draw() {
  fl_rect(x(), y(), w(), h(), COLOR_BD_0);    // border
  switch (ch->mode) {
    case LOOP_BASIC:
      fl_draw_pixmap(loopBasic_xpm, x()+1, y()+1);
      break;
    case LOOP_ONCE:
      fl_draw_pixmap(loopOnce_xpm, x()+1, y()+1);
      break;
    case LOOP_ONCE_BAR:
      fl_draw_pixmap(loopOnceBar_xpm, x()+1, y()+1);
      break;
    case LOOP_REPEAT:
      fl_draw_pixmap(loopRepeat_xpm, x()+1, y()+1);
      break;
    case SINGLE_BASIC:
      fl_draw_pixmap(oneshotBasic_xpm, x()+1, y()+1);
      break;
    case SINGLE_PRESS:
      fl_draw_pixmap(oneshotPress_xpm, x()+1, y()+1);
      break;
    case SINGLE_RETRIG:
      fl_draw_pixmap(oneshotRetrig_xpm, x()+1, y()+1);
      break;
    case SINGLE_ENDLESS:
      fl_draw_pixmap(oneshotEndless_xpm, x()+1, y()+1);
      break;
  }
}


/* -------------------------------------------------------------------------- */


void gModeBox::cb_change_chanmode(Fl_Widget *v, void *p) { ((gModeBox*)v)->__cb_change_chanmode((intptr_t)p); }


/* -------------------------------------------------------------------------- */


void gModeBox::__cb_change_chanmode(int mode)
{
  ch->mode = mode;

  /* what to do when the channel is playing and you change the mode?
   * Nothing, since v0.5.3. Just refresh the action editor window, in
   * case it's open */

  gu_refreshActionEditor();
}


/* -------------------------------------------------------------------------- */
/* -------------------------------------------------------------------------- */
/* -------------------------------------------------------------------------- */


gChannelButton::gChannelButton(int x, int y, int w, int h, const char *L)
  : gClick(x, y, w, h, L) {}


/* -------------------------------------------------------------------------- */


int gChannelButton::handle(int e)
{
	int ret = gClick::handle(e);
	switch (e) {
		case FL_DND_ENTER:
		case FL_DND_DRAG:
		case FL_DND_RELEASE: {
			ret = 1;
			break;
		}
		case FL_PASTE: {
      gChannel *p = (gChannel*) parent();   // parent is g[Sample|Midi]Channel
      if (p->type == CHANNEL_SAMPLE) {
        SampleChannel *c = ((gSampleChannel*)p)->ch;
        int result = glue_loadChannel(c, gTrim(gStripFileUrl(Fl::event_text())).c_str());
  			if (result != SAMPLE_LOADED_OK)
  				mainWin->keyboard->printChannelMessage(result);
      }
      // else dnd on a MIDI channel, nothing to do so far (load MIDI tab in
      // the future)
			ret = 1;
			break;
		}
	}
	return ret;
}
