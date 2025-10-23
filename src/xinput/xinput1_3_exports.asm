.code
extern xinput_imports:QWORD

XInputDllMain proc
	jmp xinput_imports[0*8]
XInputDllMain endp

XInputGetState proc
	jmp xinput_imports[1*8]
XInputGetState endp

XInputSetState proc
	jmp xinput_imports[2*8]
XInputSetState endp

XInputGetCapabilities proc
	jmp xinput_imports[3*8]
XInputGetCapabilities endp

XInputEnable proc
	jmp xinput_imports[4*8]
XInputEnable endp

XInputGetDSoundAudioDeviceGuids proc
	jmp xinput_imports[5*8]
XInputGetDSoundAudioDeviceGuids endp

XInputGetBatteryInformation proc
	jmp xinput_imports[6*8]
XInputGetBatteryInformation endp

XInputGetKeystroke proc
	jmp xinput_imports[7*8]
XInputGetKeystroke endp

Ordinal100 proc
	jmp xinput_imports[8*8]
Ordinal100 endp

Ordinal101 proc
	jmp xinput_imports[9*8]
Ordinal101 endp

Ordinal102 proc
	jmp xinput_imports[10*8]
Ordinal102 endp

Ordinal103 proc
	jmp xinput_imports[11*8]
Ordinal103 endp
end