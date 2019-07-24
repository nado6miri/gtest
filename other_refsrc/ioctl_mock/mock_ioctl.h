#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#ifdef __cplusplus
}
#endif // __cplusplus
#include <linux/v4l2-controls.h>
#include <linux/v4l2-ext/v4l2-controls-ext.h>
#include <linux/videodev2.h>
#include <linux/v4l2-ext/videodev2-ext.h>

#include "gmock/gmock.h"

class IoctlInterface {
public:
    virtual ~IoctlInterface() {}
    virtual int MOCK_ioctl1(int fd,  unsigned long int ctrl, v4l2_ext_controls *ext_control) = 0;
};

// HAL_AUDIO_InitializeModule 에 대한 mock-up class
class IoctlMock : public IoctlInterface {
    public:
        MOCK_METHOD3(MOCK_ioctl1, int(int fd,  unsigned long int ctrl, v4l2_ext_controls *ext_control));
};