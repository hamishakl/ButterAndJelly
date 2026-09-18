// SPDX-License-Identifier: GPL-2.0-or-later

// settings.h: choices that outlive a session.
//
// Separate from the Jellyfin session, which holds credentials and is dropped
// on sign out.

#pragma once

#include <string>

// The interface lays itself out 720 tall. Only the width changes with the
// shape of the television, and only the Xbox 360 has a choice to make.
inline constexpr int kLayoutHeight        = 720;
inline constexpr int kLayoutWidthWide     = 1280;
inline constexpr int kLayoutWidthStandard = 960;

struct Settings {
    // Which screens the app draws to. Only the Wii U has more than one.
    enum class Display { TvAndGamepad, TvOnly, GamepadOnly };

    Display display = Display::TvAndGamepad;

    // How playback is asked for. 0 means direct: the server sends what it
    // has and nothing is re-encoded. Any other value is a height to transcode
    // down to. Each console clamps this to what it can decode, and one that
    // cannot decode the source has no direct option at all.
    int playbackHeight = 720;

    // kbit/s, or 0 to let the height decide.
    int videoBitrate = 0;

    // Frames per second ceiling, or 0 for whatever the source runs at.
    int maxFramerate = 0;

    // Automatic is whatever this build decodes best.
    enum class AudioFormat { Automatic, Aac, Mp3 };
    AudioFormat audioFormat = AudioFormat::Automatic;

    // Audio bitrate in kbit/s, for the transcoded case.
    int audioBitrate = 192;

    // The shape of the television. Automatic follows the console's own
    // setting, which is right until the dashboard disagrees with the set it
    // is plugged into, and then there is no way to say so but this.
    enum class ScreenShape { Automatic, Widescreen, Standard };
    ScreenShape screenShape = ScreenShape::Automatic;

    // Keeps the per frame timing out of the log unless it is wanted.
    bool diagnostics = false;

    // Stops the client looking for Seerr beside Jellyfin.
    bool requestServerElsewhere = false;

    // Where the window was last left. Zero until one is stored.
    int windowWidth  = 0;
    int windowHeight = 0;
    bool fullscreen  = false;


    // The width the interface should lay out in, for the shape chosen above.
    // Always the widescreen one off the 360, which is the only console that
    // is handed a frame of a different shape than it asked for.
    int layoutWidth() const;

    void load();
    void save() const;
};
