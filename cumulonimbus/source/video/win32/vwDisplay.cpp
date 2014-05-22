/* 
 * - Cumulonimbus - ☁
 * File: vwDisplay.cpp
 * 
 * Licence:
 * ============================================================================
 * Copyright (C) Staff 42 Entertainment LTDA ME - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * 
 * Written by Douglas Machado de Freitas <douglas@staff42.com>, May 2014
 * ============================================================================
 */
#include <base/Setup.h>
#ifdef CbWindows

#include <video/Display.h>

#include <base/Exception.h>
#include <base/Log.h>

#include <win32/video/Windows.h>

#include <algorithm>

namespace cb {
	namespace video {
		void Display::activate(disp::Mode idisplay_mode) {
			DEVMODE screen_settings;
			screen_settings.dmSize = sizeof(DEVMODE);
			EnumDisplaySettings(NULL,ENUM_CURRENT_SETTINGS,&screen_settings);
			if(screen_settings.dmPelsWidth != idisplay_mode.width() && screen_settings.dmPelsHeight != idisplay_mode.height()) {

				memset(&screen_settings,0,sizeof(screen_settings));
				screen_settings.dmSize			= sizeof(screen_settings);
				screen_settings.dmPelsWidth		= idisplay_mode.width();
				screen_settings.dmPelsHeight	= idisplay_mode.height();
				screen_settings.dmBitsPerPel	= 32;
				screen_settings.dmFields		= DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

				if (ChangeDisplaySettings(&screen_settings,CDS_FULLSCREEN)!=DISP_CHANGE_SUCCESSFUL) {
					ThrowDet(tokurei::SetFailed, "Resolution: %dx%d.", idisplay_mode.width(), idisplay_mode.height());
				} else {
					base::log.info("Display::activate() : Display resolution setted to: %dx%d.", idisplay_mode.width(), idisplay_mode.height());
				}
			}
		}

		void Display::reset() {
			ChangeDisplaySettings(NULL,0);
		}

		disp::Mode Display::activeMode() {
			DEVMODE screen_settings;
			screen_settings.dmSize = sizeof(DEVMODE);
			EnumDisplaySettings(NULL,ENUM_CURRENT_SETTINGS,&screen_settings);
			return disp::Mode(screen_settings.dmPelsWidth, screen_settings.dmPelsHeight);
		}

		disp::Mode Display::defaultMode() {
			DEVMODE screen_settings;
			screen_settings.dmSize = sizeof(DEVMODE);
			EnumDisplaySettings(NULL,ENUM_REGISTRY_SETTINGS,&screen_settings);
			return disp::Mode(screen_settings.dmPelsWidth, screen_settings.dmPelsHeight);
		}

		void Display::modes(std::vector<disp::Mode> &odisplay_modes_list) {
			int i=0;
			odisplay_modes_list.clear();
			DEVMODE screen_settings;
			screen_settings.dmSize = sizeof(DEVMODE);
			while(EnumDisplaySettings(NULL,i,&screen_settings)) {
				if(screen_settings.dmBitsPerPel == 32) {
					disp::Mode disp(screen_settings.dmPelsWidth, screen_settings.dmPelsHeight);
					size_t k;
					for(k=0 ; k<odisplay_modes_list.size() && (odisplay_modes_list[k].width() != disp.width() || odisplay_modes_list[k].height() != disp.height()); k++);
					if(k == odisplay_modes_list.size() && disp.width() >= 640 && disp.height() >= 480) {
						odisplay_modes_list.push_back(disp);
					}
				}
				i++;
			}

			std::sort(odisplay_modes_list.begin(), odisplay_modes_list.end());
		}
	}  // namespace video
}  // namespace cb

#endif
