/*
#include <iostream>
#include <windows.h>

// Fuction to get the current brightness level.
int get_brightness(){
    // Get a handle to the display device.
    DISPLAY_DEVICE device;
    device.cb = sizeof(device);
    EnumDisplayDevices(NULL, 0, &device, 0);

    // Get the current brightness level.
    int brightness;
    DWORD dwBytesReturned;
    callNtDeviceControl(DEVICE_GET_BRIGHTNESS, &device, &brightness, sizeof(brightness), NULL, 0, %dwBytesReturned);

    return brightness;
}
*/

// Have to understand the following lines of code.
#include <iostream>
#include <windows.h>

using namespace std;

// Function to get the current brightness level.
int get_brightness() {
    // Get a handle to the display device.
    HDC hDC = GetDC(NULL);

    // Get the current gamma ramp.
    WORD ramp[3][256];
    if (GetDeviceGammaRamp(hDC, ramp)) {
        // The red, green, and blue ramps are the same, so we'll just use the red one.
        int brightness = ramp[0][128]; // Assuming 8-bit color, adjust as needed.
        ReleaseDC(NULL, hDC);
        return brightness;
    } else {
        ReleaseDC(NULL, hDC);
        // Handle error
        return -1;
    }
}

int main() {
    int brightness = get_brightness();
    if (brightness != -1) {
        cout << "Current brightness level: " << brightness << endl;
    } else {
        cout << "Failed to retrieve brightness level." << endl;
    }

    return 0;
}