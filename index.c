#include <windows.h>
#include <stdio.h>
#include <string.h>

// Function to copy text to the clipboard
void CopyToClipboard(const char* text) {
    // Open the clipboard
    if (!OpenClipboard(NULL)) {
        printf("Failed to open clipboard.\n");
        return;
    }

    // Empty the clipboard
    EmptyClipboard();

    // Allocate global memory for the text
    size_t len = strlen(text) + 1;
    HGLOBAL hClipboardData = GlobalAlloc(GMEM_MOVEABLE, len);
    if (hClipboardData == NULL) {
        printf("Failed to allocate memory.\n");
        CloseClipboard();
        return;
    }

    // Copy the text to the allocated memory
    memcpy(GlobalLock(hClipboardData), text, len);
    GlobalUnlock(hClipboardData);

    // Set the clipboard data
    SetClipboardData(CF_TEXT, hClipboardData);

    // Close the clipboard
    CloseClipboard();
}

void PasteAndSend() {
    // Simulate Ctrl+V (paste)
    keybd_event(VK_CONTROL, 0, 0, 0); // Press Ctrl
    keybd_event('V', 0, 0, 0);        // Press V
    keybd_event('V', 0, KEYEVENTF_KEYUP, 0); // Release V
    keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0); // Release Ctrl

    Sleep(50); // Small delay to ensure paste completes
}

int main() {
    int repetitions = 12;

    printf("Preparing to send the message...\n");

    // Copy the message to the clipboard

    // Wait for the user to position the cursor in the text input area
    Sleep(3000);  // 3 seconds delay

    // Send the message multiple times
    for (int i = 0; i < repetitions; i++) {
        PasteAndSend();
        Sleep(50);  // 0.5-second delay between messages
    }

    printf("Done sending the messages!\n");
    return 0;
}
