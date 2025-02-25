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

#include "core/conf.h"
#include "core/const.h"
#include "core/types.h"
#include "utils/fs.h"
#include "utils/log.h"
#include <FL/Fl.H>
#include <cassert>
#include <fstream>
#include <nlohmann/json.hpp>
#include <string>

namespace nl = nlohmann;

namespace giada::m
{
Conf::Conf()
{
	m_confFilePath = u::fs::join(u::fs::getHomePath(), CONF_FILENAME);
	m_confDirPath  = u::fs::getHomePath();
}

/* -------------------------------------------------------------------------- */

bool Conf::read()
{
	data = Data(); // Reset it first

	std::ifstream ifs(m_confFilePath);
	if (!ifs.good())
		return false;

	nl::json j = nl::json::parse(ifs);

	data.logMode                    = j.value(CONF_KEY_LOG_MODE, data.logMode);
	data.showTooltips               = j.value(CONF_KEY_SHOW_TOOLTIPS, data.showTooltips);
	data.langMap                    = j.value(CONF_KEY_LANGMAP, data.langMap);
	data.soundSystem                = j.value(CONF_KEY_SOUND_SYSTEM, data.soundSystem);
	data.soundDeviceOut             = j.value(CONF_KEY_SOUND_DEVICE_OUT, data.soundDeviceOut);
	data.soundDeviceIn              = j.value(CONF_KEY_SOUND_DEVICE_IN, data.soundDeviceIn);
	data.channelsOutCount           = j.value(CONF_KEY_CHANNELS_OUT_COUNT, data.channelsOutCount);
	data.channelsOutStart           = j.value(CONF_KEY_CHANNELS_OUT_START, data.channelsOutStart);
	data.channelsInCount            = j.value(CONF_KEY_CHANNELS_IN_COUNT, data.channelsInCount);
	data.channelsInStart            = j.value(CONF_KEY_CHANNELS_IN_START, data.channelsInStart);
	data.samplerate                 = j.value(CONF_KEY_SAMPLERATE, data.samplerate);
	data.buffersize                 = j.value(CONF_KEY_BUFFER_SIZE, data.buffersize);
	data.limitOutput                = j.value(CONF_KEY_LIMIT_OUTPUT, data.limitOutput);
	data.rsmpQuality                = j.value(CONF_KEY_RESAMPLE_QUALITY, data.rsmpQuality);
	data.midiSystem                 = j.value(CONF_KEY_MIDI_SYSTEM, data.midiSystem);
	data.midiPortOut                = j.value(CONF_KEY_MIDI_PORT_OUT, data.midiPortOut);
	data.midiPortIn                 = j.value(CONF_KEY_MIDI_PORT_IN, data.midiPortIn);
	data.midiMapPath                = j.value(CONF_KEY_MIDIMAP_PATH, data.midiMapPath);
	data.lastFileMap                = j.value(CONF_KEY_LAST_MIDIMAP, data.lastFileMap);
	data.midiSync                   = j.value(CONF_KEY_MIDI_SYNC, data.midiSync);
	data.midiTCfps                  = j.value(CONF_KEY_MIDI_TC_FPS, data.midiTCfps);
	data.chansStopOnSeqHalt         = j.value(CONF_KEY_CHANS_STOP_ON_SEQ_HALT, data.chansStopOnSeqHalt);
	data.treatRecsAsLoops           = j.value(CONF_KEY_TREAT_RECS_AS_LOOPS, data.treatRecsAsLoops);
	data.inputMonitorDefaultOn      = j.value(CONF_KEY_INPUT_MONITOR_DEFAULT_ON, data.inputMonitorDefaultOn);
	data.overdubProtectionDefaultOn = j.value(CONF_KEY_OVERDUB_PROTECTION_DEFAULT_ON, data.overdubProtectionDefaultOn);
	data.pluginPath                 = j.value(CONF_KEY_PLUGINS_PATH, data.pluginPath);
	data.patchPath                  = j.value(CONF_KEY_PATCHES_PATH, data.patchPath);
	data.samplePath                 = j.value(CONF_KEY_SAMPLES_PATH, data.samplePath);
	data.mainWindowBounds.x         = j.value(CONF_KEY_MAIN_WINDOW_X, data.mainWindowBounds.x);
	data.mainWindowBounds.y         = j.value(CONF_KEY_MAIN_WINDOW_Y, data.mainWindowBounds.y);
	data.mainWindowBounds.w         = j.value(CONF_KEY_MAIN_WINDOW_W, data.mainWindowBounds.w);
	data.mainWindowBounds.h         = j.value(CONF_KEY_MAIN_WINDOW_H, data.mainWindowBounds.h);
	data.browserBounds.x            = j.value(CONF_KEY_BROWSER_X, data.browserBounds.x);
	data.browserBounds.y            = j.value(CONF_KEY_BROWSER_Y, data.browserBounds.y);
	data.browserBounds.w            = j.value(CONF_KEY_BROWSER_W, data.browserBounds.w);
	data.browserBounds.h            = j.value(CONF_KEY_BROWSER_H, data.browserBounds.h);
	data.browserPosition            = j.value(CONF_KEY_BROWSER_POSITION, data.browserPosition);
	data.browserLastPath            = j.value(CONF_KEY_BROWSER_LAST_PATH, data.browserLastPath);
	data.browserLastValue           = j.value(CONF_KEY_BROWSER_LAST_VALUE, data.browserLastValue);
	data.actionEditorBounds.x       = j.value(CONF_KEY_ACTION_EDITOR_X, data.actionEditorBounds.x);
	data.actionEditorBounds.y       = j.value(CONF_KEY_ACTION_EDITOR_Y, data.actionEditorBounds.y);
	data.actionEditorBounds.w       = j.value(CONF_KEY_ACTION_EDITOR_W, data.actionEditorBounds.w);
	data.actionEditorBounds.h       = j.value(CONF_KEY_ACTION_EDITOR_H, data.actionEditorBounds.h);
	data.actionEditorZoom           = j.value(CONF_KEY_ACTION_EDITOR_ZOOM, data.actionEditorZoom);
	data.actionEditorSplitH         = j.value(CONF_KEY_ACTION_EDITOR_SPLIT_H, data.actionEditorSplitH);
	data.actionEditorGridVal        = j.value(CONF_KEY_ACTION_EDITOR_GRID_VAL, data.actionEditorGridVal);
	data.actionEditorGridOn         = j.value(CONF_KEY_ACTION_EDITOR_GRID_ON, data.actionEditorGridOn);
	data.actionEditorPianoRollY     = j.value(CONF_KEY_ACTION_EDITOR_PIANO_ROLL_Y, data.actionEditorPianoRollY);
	data.sampleEditorBounds.x       = j.value(CONF_KEY_SAMPLE_EDITOR_X, data.sampleEditorBounds.x);
	data.sampleEditorBounds.y       = j.value(CONF_KEY_SAMPLE_EDITOR_Y, data.sampleEditorBounds.y);
	data.sampleEditorBounds.w       = j.value(CONF_KEY_SAMPLE_EDITOR_W, data.sampleEditorBounds.w);
	data.sampleEditorBounds.h       = j.value(CONF_KEY_SAMPLE_EDITOR_H, data.sampleEditorBounds.h);
	data.sampleEditorGridVal        = j.value(CONF_KEY_SAMPLE_EDITOR_GRID_VAL, data.sampleEditorGridVal);
	data.sampleEditorGridOn         = j.value(CONF_KEY_SAMPLE_EDITOR_GRID_ON, data.sampleEditorGridOn);
	data.pluginListBounds.x         = j.value(CONF_KEY_PLUGIN_LIST_X, data.pluginListBounds.x);
	data.pluginListBounds.y         = j.value(CONF_KEY_PLUGIN_LIST_Y, data.pluginListBounds.y);
	data.pluginListBounds.w         = j.value(CONF_KEY_PLUGIN_LIST_W, data.pluginListBounds.w);
	data.pluginListBounds.h         = j.value(CONF_KEY_PLUGIN_LIST_H, data.pluginListBounds.h);
	data.midiInputBounds.x          = j.value(CONF_KEY_MIDI_INPUT_X, data.midiInputBounds.x);
	data.midiInputBounds.y          = j.value(CONF_KEY_MIDI_INPUT_Y, data.midiInputBounds.y);
	data.midiInputBounds.w          = j.value(CONF_KEY_MIDI_INPUT_W, data.midiInputBounds.w);
	data.midiInputBounds.h          = j.value(CONF_KEY_MIDI_INPUT_H, data.midiInputBounds.h);
	data.recTriggerMode             = j.value(CONF_KEY_REC_TRIGGER_MODE, data.recTriggerMode);
	data.recTriggerLevel            = j.value(CONF_KEY_REC_TRIGGER_LEVEL, data.recTriggerLevel);
	data.inputRecMode               = j.value(CONF_KEY_INPUT_REC_MODE, data.inputRecMode);
	data.midiInEnabled              = j.value(CONF_KEY_MIDI_IN, data.midiInEnabled);
	data.midiInFilter               = j.value(CONF_KEY_MIDI_IN_FILTER, data.midiInFilter);
	data.midiInRewind               = j.value(CONF_KEY_MIDI_IN_REWIND, data.midiInRewind);
	data.midiInStartStop            = j.value(CONF_KEY_MIDI_IN_START_STOP, data.midiInStartStop);
	data.midiInActionRec            = j.value(CONF_KEY_MIDI_IN_ACTION_REC, data.midiInActionRec);
	data.midiInInputRec             = j.value(CONF_KEY_MIDI_IN_INPUT_REC, data.midiInInputRec);
	data.midiInMetronome            = j.value(CONF_KEY_MIDI_IN_METRONOME, data.midiInMetronome);
	data.midiInVolumeIn             = j.value(CONF_KEY_MIDI_IN_VOLUME_IN, data.midiInVolumeIn);
	data.midiInVolumeOut            = j.value(CONF_KEY_MIDI_IN_VOLUME_OUT, data.midiInVolumeOut);
	data.midiInBeatDouble           = j.value(CONF_KEY_MIDI_IN_BEAT_DOUBLE, data.midiInBeatDouble);
	data.midiInBeatHalf             = j.value(CONF_KEY_MIDI_IN_BEAT_HALF, data.midiInBeatHalf);

	data.keyBindings[KEY_BIND_PLAY]           = j.value(CONF_KEY_BIND_PLAY, 0);
	data.keyBindings[KEY_BIND_REWIND]         = j.value(CONF_KEY_BIND_REWIND, 0);
	data.keyBindings[KEY_BIND_RECORD_ACTIONS] = j.value(CONF_KEY_BIND_RECORD_ACTIONS, 0);
	data.keyBindings[KEY_BIND_RECORD_INPUT]   = j.value(CONF_KEY_BIND_RECORD_INPUT, 0);
	data.keyBindings[KEY_BIND_EXIT]           = j.value(CONF_KEY_BIND_EXIT, 0);

	data.pluginChooserBounds.x = j.value(CONF_KEY_PLUGIN_CHOOSER_X, data.pluginChooserBounds.x);
	data.pluginChooserBounds.y = j.value(CONF_KEY_PLUGIN_CHOOSER_Y, data.pluginChooserBounds.y);
	data.pluginChooserBounds.w = j.value(CONF_KEY_PLUGIN_CHOOSER_W, data.pluginChooserBounds.w);
	data.pluginChooserBounds.h = j.value(CONF_KEY_PLUGIN_CHOOSER_H, data.pluginChooserBounds.h);
	data.pluginSortMethod      = j.value(CONF_KEY_PLUGIN_SORT_METHOD, data.pluginSortMethod);

	data.uiScaling = j.value(CONF_KEY_UI_SCALING, data.uiScaling);

	sanitize();

	return true;
}

/* -------------------------------------------------------------------------- */

bool Conf::write() const
{
	if (!createConfigFolder())
		return false;

	nl::json j;

	j[CONF_KEY_HEADER]                        = "GIADACFG";
	j[CONF_KEY_LOG_MODE]                      = data.logMode;
	j[CONF_KEY_SHOW_TOOLTIPS]                 = data.showTooltips;
	j[CONF_KEY_LANGMAP]                       = data.langMap;
	j[CONF_KEY_SOUND_SYSTEM]                  = data.soundSystem;
	j[CONF_KEY_SOUND_DEVICE_OUT]              = data.soundDeviceOut;
	j[CONF_KEY_SOUND_DEVICE_IN]               = data.soundDeviceIn;
	j[CONF_KEY_CHANNELS_OUT_COUNT]            = data.channelsOutCount;
	j[CONF_KEY_CHANNELS_OUT_START]            = data.channelsOutStart;
	j[CONF_KEY_CHANNELS_IN_COUNT]             = data.channelsInCount;
	j[CONF_KEY_CHANNELS_IN_START]             = data.channelsInStart;
	j[CONF_KEY_SAMPLERATE]                    = data.samplerate;
	j[CONF_KEY_BUFFER_SIZE]                   = data.buffersize;
	j[CONF_KEY_LIMIT_OUTPUT]                  = data.limitOutput;
	j[CONF_KEY_RESAMPLE_QUALITY]              = data.rsmpQuality;
	j[CONF_KEY_MIDI_SYSTEM]                   = data.midiSystem;
	j[CONF_KEY_MIDI_PORT_OUT]                 = data.midiPortOut;
	j[CONF_KEY_MIDI_PORT_IN]                  = data.midiPortIn;
	j[CONF_KEY_MIDIMAP_PATH]                  = data.midiMapPath;
	j[CONF_KEY_LAST_MIDIMAP]                  = data.lastFileMap;
	j[CONF_KEY_MIDI_SYNC]                     = data.midiSync;
	j[CONF_KEY_MIDI_TC_FPS]                   = data.midiTCfps;
	j[CONF_KEY_MIDI_IN]                       = data.midiInEnabled;
	j[CONF_KEY_MIDI_IN_FILTER]                = data.midiInFilter;
	j[CONF_KEY_MIDI_IN_REWIND]                = data.midiInRewind;
	j[CONF_KEY_MIDI_IN_START_STOP]            = data.midiInStartStop;
	j[CONF_KEY_MIDI_IN_ACTION_REC]            = data.midiInActionRec;
	j[CONF_KEY_MIDI_IN_INPUT_REC]             = data.midiInInputRec;
	j[CONF_KEY_MIDI_IN_METRONOME]             = data.midiInMetronome;
	j[CONF_KEY_MIDI_IN_VOLUME_IN]             = data.midiInVolumeIn;
	j[CONF_KEY_MIDI_IN_VOLUME_OUT]            = data.midiInVolumeOut;
	j[CONF_KEY_MIDI_IN_BEAT_DOUBLE]           = data.midiInBeatDouble;
	j[CONF_KEY_MIDI_IN_BEAT_HALF]             = data.midiInBeatHalf;
	j[CONF_KEY_CHANS_STOP_ON_SEQ_HALT]        = data.chansStopOnSeqHalt;
	j[CONF_KEY_TREAT_RECS_AS_LOOPS]           = data.treatRecsAsLoops;
	j[CONF_KEY_INPUT_MONITOR_DEFAULT_ON]      = data.inputMonitorDefaultOn;
	j[CONF_KEY_OVERDUB_PROTECTION_DEFAULT_ON] = data.overdubProtectionDefaultOn;
	j[CONF_KEY_PLUGINS_PATH]                  = data.pluginPath;
	j[CONF_KEY_PATCHES_PATH]                  = data.patchPath;
	j[CONF_KEY_SAMPLES_PATH]                  = data.samplePath;
	j[CONF_KEY_MAIN_WINDOW_X]                 = data.mainWindowBounds.x;
	j[CONF_KEY_MAIN_WINDOW_Y]                 = data.mainWindowBounds.y;
	j[CONF_KEY_MAIN_WINDOW_W]                 = data.mainWindowBounds.w;
	j[CONF_KEY_MAIN_WINDOW_H]                 = data.mainWindowBounds.h;
	j[CONF_KEY_BROWSER_X]                     = data.browserBounds.x;
	j[CONF_KEY_BROWSER_Y]                     = data.browserBounds.y;
	j[CONF_KEY_BROWSER_W]                     = data.browserBounds.w;
	j[CONF_KEY_BROWSER_H]                     = data.browserBounds.h;
	j[CONF_KEY_BROWSER_POSITION]              = data.browserPosition;
	j[CONF_KEY_BROWSER_LAST_PATH]             = data.browserLastPath;
	j[CONF_KEY_BROWSER_LAST_VALUE]            = data.browserLastValue;
	j[CONF_KEY_ACTION_EDITOR_X]               = data.actionEditorBounds.x;
	j[CONF_KEY_ACTION_EDITOR_Y]               = data.actionEditorBounds.y;
	j[CONF_KEY_ACTION_EDITOR_W]               = data.actionEditorBounds.w;
	j[CONF_KEY_ACTION_EDITOR_H]               = data.actionEditorBounds.h;
	j[CONF_KEY_ACTION_EDITOR_ZOOM]            = data.actionEditorZoom;
	j[CONF_KEY_ACTION_EDITOR_SPLIT_H]         = data.actionEditorSplitH;
	j[CONF_KEY_ACTION_EDITOR_GRID_VAL]        = data.actionEditorGridVal;
	j[CONF_KEY_ACTION_EDITOR_GRID_ON]         = data.actionEditorGridOn;
	j[CONF_KEY_ACTION_EDITOR_PIANO_ROLL_Y]    = data.actionEditorPianoRollY;
	j[CONF_KEY_SAMPLE_EDITOR_X]               = data.sampleEditorBounds.x;
	j[CONF_KEY_SAMPLE_EDITOR_Y]               = data.sampleEditorBounds.y;
	j[CONF_KEY_SAMPLE_EDITOR_W]               = data.sampleEditorBounds.w;
	j[CONF_KEY_SAMPLE_EDITOR_H]               = data.sampleEditorBounds.h;
	j[CONF_KEY_SAMPLE_EDITOR_GRID_VAL]        = data.sampleEditorGridVal;
	j[CONF_KEY_SAMPLE_EDITOR_GRID_ON]         = data.sampleEditorGridOn;
	j[CONF_KEY_PLUGIN_LIST_X]                 = data.pluginListBounds.x;
	j[CONF_KEY_PLUGIN_LIST_Y]                 = data.pluginListBounds.y;
	j[CONF_KEY_PLUGIN_LIST_W]                 = data.pluginListBounds.w;
	j[CONF_KEY_PLUGIN_LIST_H]                 = data.pluginListBounds.h;
	j[CONF_KEY_MIDI_INPUT_X]                  = data.midiInputBounds.x;
	j[CONF_KEY_MIDI_INPUT_Y]                  = data.midiInputBounds.y;
	j[CONF_KEY_MIDI_INPUT_W]                  = data.midiInputBounds.w;
	j[CONF_KEY_MIDI_INPUT_H]                  = data.midiInputBounds.h;
	j[CONF_KEY_REC_TRIGGER_MODE]              = static_cast<int>(data.recTriggerMode);
	j[CONF_KEY_REC_TRIGGER_LEVEL]             = data.recTriggerLevel;
	j[CONF_KEY_INPUT_REC_MODE]                = static_cast<int>(data.inputRecMode);

	j[CONF_KEY_BIND_PLAY]           = data.keyBindings[KEY_BIND_PLAY];
	j[CONF_KEY_BIND_REWIND]         = data.keyBindings[KEY_BIND_REWIND];
	j[CONF_KEY_BIND_RECORD_ACTIONS] = data.keyBindings[KEY_BIND_RECORD_ACTIONS];
	j[CONF_KEY_BIND_RECORD_INPUT]   = data.keyBindings[KEY_BIND_RECORD_INPUT];
	j[CONF_KEY_BIND_EXIT]           = data.keyBindings[KEY_BIND_EXIT];

	j[CONF_KEY_PLUGIN_CHOOSER_X]   = data.pluginChooserBounds.x;
	j[CONF_KEY_PLUGIN_CHOOSER_Y]   = data.pluginChooserBounds.y;
	j[CONF_KEY_PLUGIN_CHOOSER_W]   = data.pluginChooserBounds.w;
	j[CONF_KEY_PLUGIN_CHOOSER_H]   = data.pluginChooserBounds.h;
	j[CONF_KEY_PLUGIN_SORT_METHOD] = data.pluginSortMethod;

	j[CONF_KEY_UI_SCALING] = data.uiScaling;

	std::ofstream ofs(m_confFilePath);
	if (!ofs.good())
	{
		u::log::print("[conf::write] unable to write configuration file!\n");
		return false;
	}

	ofs << j;
	return true;
}

/* -------------------------------------------------------------------------- */

bool Conf::createConfigFolder() const
{
#if defined(__linux__) || defined(__FreeBSD__) || defined(__APPLE__)

	if (u::fs::dirExists(m_confDirPath))
		return true;

	u::log::print("[conf::createConfigFolder] .giada folder not present. Updating...\n");

	if (u::fs::mkdir(m_confDirPath))
	{
		u::log::print("[conf::createConfigFolder] status: ok\n");
		return true;
	}
	else
	{
		u::log::print("[conf::createConfigFolder] status: error!\n");
		return false;
	}

#else // Windows: nothing to do

	return true;

#endif
}

/* -------------------------------------------------------------------------- */

void Conf::sanitize()
{
	data.soundDeviceOut   = std::max(0, data.soundDeviceOut);
	data.channelsOutCount = G_MAX_IO_CHANS;
	data.channelsOutStart = std::max(0, data.channelsOutStart);
	data.channelsInCount  = std::max(1, data.channelsInCount);
	data.channelsInStart  = std::max(0, data.channelsInStart);

	data.midiPortOut = std::max(-1, data.midiPortOut);
	data.midiPortIn  = std::max(-1, data.midiPortIn);

	data.uiScaling = std::clamp(data.uiScaling, G_MIN_UI_SCALING, G_MAX_UI_SCALING);
}
} // namespace giada::m