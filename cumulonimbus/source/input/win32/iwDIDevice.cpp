/* 
 * - Cumulonimbus - ☁
 * File: iwDIDevice.cpp
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
#include <cb/input/win32/DIDevice.h>

#include <cb/base/Exception.h>
#include <cb/base/Log.h>

namespace cb {
	namespace input {
		LPDIRECTINPUT8 DirectInput::_direct_input = nullptr;
		size_t DirectInput::_device_count = 0;

		void DirectInput::reg() {
			if(!_direct_input) {
				if(DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (LPVOID*)&_direct_input, NULL) != DI_OK) {
					Throw(tokurei::CreateError);
				}
			}
			_device_count++;
		}

		void DirectInput::unreg() {
			_device_count--;
			if(_device_count == 0) {
				if(_direct_input) {
					_direct_input->Release();
					_direct_input = NULL;
				}
			}
		}

		DIDevice::DIDevice(HWND iwindow, REFGUID iguid, LPCDIDATAFORMAT idataformat)
		:_device(NULL)
		,_buffer_size(0) {
			DirectInput::reg();

			if(DirectInput::directinput()->CreateDevice(iguid, &_device, NULL) != DI_OK) {
				Throw(tokurei::CreateError);
			}

			_device->SetCooperativeLevel(iwindow, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
			_device->SetDataFormat(idataformat);

			_buffer_size = (DWORD)getProperty(DIPROP_BUFFERSIZE, 0, DIPH_DEVICE);
		}

		DIDevice::~DIDevice() {
			if(_device) {
				_device->Release();
				_device = NULL;
			}
			DirectInput::unreg();
		}

		void DIDevice::setBufferSize(DWORD isize) {
			_buffer_size = isize;
			setProperty(DIPROP_BUFFERSIZE, 0, DIPH_DEVICE, _buffer_size);
		}

		DWORD DIDevice::getData(DIDEVICEOBJECTDATA **odata) {
			_device->Acquire();

			(*odata) = new DIDEVICEOBJECTDATA[_buffer_size];

			DWORD n = _buffer_size;
			_device->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), *odata, &n, 0);

			return n;
		}

		void DIDevice::setProperty(REFGUID iprop, DWORD iobj, DWORD ihow, DWORD idata) {
			DIPROPDWORD prop;
			prop.diph.dwSize = sizeof(DIPROPDWORD);
			prop.diph.dwHeaderSize = sizeof(DIPROPHEADER);
			prop.diph.dwObj = iobj;
			prop.diph.dwHow = ihow;
			prop.dwData = idata;

			HRESULT result = _device->SetProperty(iprop, &prop.diph);
			if(FAILED(result)) {
				Throw(tokurei::SetFailed);
			}
		}

		UINT_PTR DIDevice::getProperty(REFGUID iprop, DWORD iobj, DWORD ihow) const {
			DIPROPDWORD prop;
			prop.diph.dwSize = sizeof(DIPROPDWORD);
			prop.diph.dwHeaderSize = sizeof(DIPROPHEADER);
			prop.diph.dwObj = iobj;
			prop.diph.dwHow = ihow;
			prop.dwData = 0;

			HRESULT result = _device->GetProperty(iprop, &prop.diph);
			if(FAILED(result)) {
				Throw(tokurei::GetFailed);
			}

			return prop.dwData;
		}
	}  // namespace input
}  // namespace cb
