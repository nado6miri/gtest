#include "mock_ioctl.h"
//#include <sys/ioctl.h>   // 이상하게 없으면 호출 안됨.
#include <stdarg.h>      // 가변인자.처리.
#include <linux/v4l2-controls.h>
#include <linux/v4l2-ext/v4l2-controls-ext.h>
#include <linux/videodev2.h>
#include <linux/v4l2-ext/videodev2-ext.h>

extern IoctlMock *ioctlMockObj;

int ioctl (int __fd, unsigned long int __request, ...)
{
    int ret = 0;
    // Getting structure argument with ext_controls
    v4l2_ext_controls *ext_controls;
    va_list ap;
    va_start(ap, __request);
    ext_controls = va_arg(ap, v4l2_ext_controls *);
    va_end(ap);

    // Setting temporal data structure which is same with structure argument.
    v4l2_ext_controls ext_controls_rcv;
    v4l2_ext_control ext_control_rcv;
    struct v4l2_ext_adc_timing_info adc_timing_info;

    memset(&ext_controls_rcv, 0, sizeof(v4l2_ext_controls));
    memset(&ext_control_rcv, 0, sizeof(v4l2_ext_control));
    memset(&adc_timing_info, 0, sizeof(struct v4l2_ext_adc_timing_info));

    ext_controls_rcv.ctrl_class     = V4L2_CTRL_CLASS_USER;
    ext_controls_rcv.count          = 1;
    ext_controls_rcv.controls       = &ext_control_rcv;
    ext_controls_rcv.controls->id   = V4L2_CID_EXT_ADC_TIMING_INFO;
    ext_controls_rcv.controls->size = sizeof(struct v4l2_ext_adc_timing_info);
    ext_controls_rcv.controls->ptr  = (void *)&adc_timing_info;    

    // Receving data value from mock-up with temporal data structure
    ret = ioctlMockObj->MOCK_ioctl1(__fd,__request, &ext_controls_rcv);

    // Copying temporal data structure to structure arguement
    v4l2_ext_control *tmp_ext_control_rcv;
    void  *tmp_adc_timing_info;

    tmp_ext_control_rcv = ext_controls->controls;
    tmp_adc_timing_info = ext_controls->controls->ptr;
    
    memcpy(ext_controls, &ext_controls_rcv, sizeof(v4l2_ext_controls));
    ext_controls->controls = tmp_ext_control_rcv;
    memcpy(ext_controls->controls, ext_controls_rcv.controls, sizeof(v4l2_ext_control));    
    ext_controls->controls->ptr = tmp_adc_timing_info;
    memcpy(ext_controls->controls->ptr,ext_controls_rcv.controls->ptr, sizeof(v4l2_ext_adc_timing_info));

    return ret;
}