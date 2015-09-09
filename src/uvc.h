#pragma once
#ifndef LIBREALSENSE_UVC_H
#define LIBREALSENSE_UVC_H

#include "types.h"

#include <functional>

namespace rsimpl
{
    namespace uvc
    {
        struct device_handle
        {
            struct _impl; std::shared_ptr<_impl> impl;
            explicit operator bool () const { return static_cast<bool>(impl); }

            void set_mode(int width, int height, frame_format format, int fps, std::function<void(const void * frame)> callback);
            void start_streaming();
            void stop_streaming();
        };

        struct device
        {
            struct _impl; std::shared_ptr<_impl> impl;
            explicit operator bool () const { return static_cast<bool>(impl); }

            int get_vendor_id() const;
            int get_product_id() const;

            void get_control(uint8_t unit, uint8_t ctrl, void * data, int len) const;
            void set_control(uint8_t unit, uint8_t ctrl, void * data, int len);

            void claim_interface(int interface_number);
            void bulk_transfer(unsigned char endpoint, void * data, int length, int *actual_length, unsigned int timeout);

            device_handle claim_subdevice(int subdevice_index);
        };

        struct context
        {
            struct _impl; std::shared_ptr<_impl> impl;
            explicit operator bool () const { return static_cast<bool>(impl); }

            std::vector<device> query_devices();

            static context create();
        };
    }
}

#endif
