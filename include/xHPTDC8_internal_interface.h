#ifndef XHPTDC8_INTERNAL_INTERFACE_H
#define XHPTDC8_INTERNAL_INTERFACE_H

// approx 41 usec @ 6.6ns clock cycles
#define XHPTDC8_ADC_WATCHDOG_DEFAULT_CNT 6144

#define XHPTDC8_DEFAULT_BUFFER_SIZE 0x1000000 // 16 MB

#ifdef __cplusplus
extern "C" {
#endif
typedef void(__stdcall *progress_callback_t)(size_t done, size_t total);
XHPTDC8_API int xhptdc8_flash_firmware(int index, uint8_t *firmware,
                                       size_t size, uint32_t flashOffset,
                                       progress_callback_t callback);
XHPTDC8_API int xhptdc8_flash_calibration(int index);
XHPTDC8_API int xhptdc8_read_flash(int index, uint8_t *memory, size_t size,
                                   size_t flashOffset);
#ifdef __cplusplus
}
#endif
#endif
