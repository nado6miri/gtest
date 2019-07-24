How to mock ioctl
=======
*본 page는 Linux Driver의 interface인 ioctl을 mocking하는 방법을 기술한다.* <br/>
*테스트 코드는 extinput-integration module을 기반으로 작성&검증되었으나*<br/>
*내용은 일반적인 상황을 상정하여 작성하였다.*<br/>

<br/>
*ioctl을 mock하기 위해 3개의 파일이 필요하다.* <br/>
`mock_ioctl.hpp`, `mock_ioctl.cpp`, `gtest_TVDEVTC-0.cpp` <br/>
*아래에서는 이 파일들의 동작에 대한 설명을 주석을 통해 작성하였다.* <br/>


# 1. Mock-up Class 정의
*mock-up method의 형태는 사용할 `ioctl`의 형태를 참고로 한다.* <br/>
*여기서는 통상적인 3개의 인자들을 받는 `ioctl`을 가정하였다.* <br/> <br/>
*만약 4개의 인자들을 `ioctl`을 혼용해서 사용한다면* </br>
*입력받는 인자 수를 1개 추가하고 MOCK_METHOD4 를 사용하면 된다.*

## mock_ioctl.hpp
### - Location : tests/fake/
```c++
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

// IoctlInterface 에 대한 mock-up class 
class IoctlMock : public IoctlInterface {
    public:
        // 아직 구현안된 MOCK_ioctl1을 MOCK_METHOD3 로 Wrapping하여 googlemock에서 조작할 수 있도록 한다.
        MOCK_METHOD3(MOCK_ioctl1, int(int fd,  unsigned long int ctrl, v4l2_ext_controls *ext_control));
};
```

<br/>

# 2. fake ioctl 정의

## component_service.cpp (Test 대상 function)
```c++
pbnjson::JValue ComponentService::getTimingInfo(LSUtils::LunaRequest &request)
{
    int ret = 0;
    LOG_INFO("ComponentService", 0, "getTimingInfo request");

    v4l2_ext_controls ext_controls;
    v4l2_ext_control ext_control;
    struct v4l2_ext_adc_timing_info adc_timing_info;

    memset(&ext_controls, 0, sizeof(v4l2_ext_controls));
    memset(&ext_control, 0, sizeof(v4l2_ext_control));
    memset(&adc_timing_info, 0, sizeof(struct v4l2_ext_adc_timing_info));

    ext_controls.ctrl_class     = V4L2_CTRL_CLASS_USER;
    ext_controls.count          = 1;
    ext_controls.controls       = &ext_control;
    ext_controls.controls->id   = V4L2_CID_EXT_ADC_TIMING_INFO;
    ext_controls.controls->size = sizeof(struct v4l2_ext_adc_timing_info);
    ext_controls.controls->ptr  = (void *)&adc_timing_info;

    ret = ioctl(fd, VIDIOC_G_EXT_CTRLS, &ext_controls);
    LOG_INFO("ComponentService", 0, "[ADC] h_freq : %d",
             adc_timing_info.h_freq);
    LOG_INFO("ComponentService", 0, "[ADC] v_freq : %d",
             adc_timing_info.v_freq);
    LOG_INFO("ComponentService", 0, "[ADC] h_total : %d",
             adc_timing_info.h_total);
    LOG_INFO("ComponentService", 0, "[ADC] v_total : %d",
             adc_timing_info.v_total);
    LOG_INFO("ComponentService", 0, "[ADC] h_porch : %d",
             adc_timing_info.h_porch);
    LOG_INFO("ComponentService", 0, "[ADC] v_porch : %d",
             adc_timing_info.v_porch);
    LOG_INFO("ComponentService", 0, "[ADC] active.w : %d",
             adc_timing_info.active.w);
    LOG_INFO("ComponentService", 0, "[ADC] active.h : %d",
             adc_timing_info.active.h);
    LOG_INFO("ComponentService", 0, "[ADC] scan_type : %d",
             adc_timing_info.scan_type);
    LOG_INFO("ComponentService", 0, "getTimingInfo result : %d", ret);

    return true;
}
```



## mock_ioctl.cpp
### - Location : tests/fake/
*가장 중요한 코드는* <br/>
*`ret = ioctlMockObj->MOCK_ioctl1(__fd,__request, &ext_controls_rcv);`이다.* <br/>
*이를 통해서 원하는 결과값을 테스트 시점에 결정할 수 있게된다.* <br/> 
*(방법은 아래 gtest_TVDEVTC-0.cpp에서 참조)* <br/>



```c++
#include "mock_ioctl.h"  // for using mock-up class
#include <sys/ioctl.h>   // 없으면 아래 fake ioctl이 호출 안됨.
#include <stdarg.h>      // 가변인자.처리

#include <linux/v4l2-controls.h>
#include <linux/v4l2-ext/v4l2-controls-ext.h>
#include <linux/videodev2.h>
#include <linux/v4l2-ext/videodev2-ext.h>

extern IoctlMock *ioctlMockObj;

int ioctl (int __fd, unsigned long int __request, ...)
{
    int ret = 0;

    // 가변인자 중 call by reference로 처리하기 위한 구조체 인자를 받아옴.
    v4l2_ext_controls *ext_controls;
    va_list ap;
    va_start(ap, __request);
    ext_controls = va_arg(ap, v4l2_ext_controls *); // <== 여기
    va_end(ap);


    // googlemock으로부터 data를 받아 올 structure 정의
    // 윗 단의 ext_controls을 사용하게 되면 ext_controls의 member pointer들이 
    // 덮어씌여저 실제 ioctol의 조작방법과 상이해진다. 

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

    // 위에 임시로 만든 data structure를 이용해 googlemock으로부터 data를 받아 옴.
    ret = ioctlMockObj->MOCK_ioctl1(__fd,__request, &ext_controls_rcv);

    // 받아온 data를  argument로 넘어온 ext_controls에 copy한다. (deep copy)
    v4l2_ext_control *tmp_ext_control_rcv;
    void  *tmp_adc_timing_info;

    // memory copy 과정에서 memeber pointer 들이 덮어씌여지는 것을 막기 위해
    // member pointer들의 주소를 임시 변수에 저장한다. 
    tmp_ext_control_rcv = ext_controls->controls;
    tmp_adc_timing_info = ext_controls->controls->ptr;
    
    memcpy(ext_controls, &ext_controls_rcv, sizeof(v4l2_ext_controls));
    ext_controls->controls = tmp_ext_control_rcv;
    memcpy(ext_controls->controls, ext_controls_rcv.controls, sizeof(v4l2_ext_control));    
    ext_controls->controls->ptr = tmp_adc_timing_info;
    memcpy(ext_controls->controls->ptr,ext_controls_rcv.controls->ptr, sizeof(v4l2_ext_adc_timing_info));

    return ret;
}
```

<br/>

# 3. mocking된 ioctl을 사용하는 방법

## gtest_TVDEVTC-0.cpp
### - Location : tests/src/

```c++
#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "../../src/av/av_service.h"
#include "component_service.h"
#include "mock_ioctl.h"

IoctlMock *ioctlMockObj;

using ::testing::Return;
using ::testing::_;
using ::testing::DoAll;

// ioctl을 mocking하는 mock-up class를 Test 마다 활성화하기 위해 
// Test용 Class를 생성한다. 
class EXTINPUT_INTEGRATION : public ::testing::Test
{
    public:
        v4l2_ext_controls ext_controls;
        v4l2_ext_control ext_control;
        struct v4l2_ext_adc_timing_info adc_timing_info;
    public:
        virtual void SetUp(){ // called right before each TEST_F()
            // ioctl을 mocking하는 mock-up class를 Test 마다 활성화
            ioctlMockObj = new IoctlMock();
        }

        virtual void TearDown(){ // called right after each TEST_F()
            delete ioctlMockObj; 
        }

        // Test 시 전달 받을 구조체를 정의한다.
        void init_V4L2_CID_EXT_ADC_TIMING_INFO()
        {
            memset(&ext_controls, 0, sizeof(v4l2_ext_controls));
            memset(&ext_control, 0, sizeof(v4l2_ext_control));
            memset(&adc_timing_info, 0, sizeof(struct v4l2_ext_adc_timing_info));            

            ext_controls.ctrl_class     = V4L2_CTRL_CLASS_USER;
            ext_controls.count          = 1;
            ext_controls.controls       = &ext_control;
            ext_controls.controls->id   = V4L2_CID_EXT_ADC_TIMING_INFO;
            ext_controls.controls->size = sizeof(struct v4l2_ext_adc_timing_info);
            ext_controls.controls->ptr  = (void *)&adc_timing_info;
        }
};


TEST_F(EXTINPUT_INTEGRATION, test) {
    pbnjson::JValue json;
    LS::Message *msg = new LS::Message();
    LSUtils::LunaRequest *ls = new LSUtils::LunaRequest(NULL, *msg,json);
    ComponentService cs; 

    // Test 시 ioctl을 통해 전달 받을 구조체를 정의한다.
    init_V4L2_CID_EXT_ADC_TIMING_INFO();

    // Test 시 ioctl을 통해 전달 받을 값을 정의한다.
    adc_timing_info.h_freq = 1;
    adc_timing_info.v_freq = 2;
    adc_timing_info.h_total = 3;
    adc_timing_info.v_total = 4;
    adc_timing_info.h_porch = 5;
    adc_timing_info.active.w = 6;
    adc_timing_info.active.h = 7;
    adc_timing_info.scan_type = 8;


    // googlemock을 사용한 기대값을 정의하는 구문    
    // EXPECT_CALL, WillRepeatedly, DoAll, SetArgPointee, Return 등은 
    // goolemock library에서 제공하는 것들이며 아래 경로들에서 사용법을 참조할 수 있다.
    // https://github.com/google/googletest/blob/master/googlemock/docs/ForDummies.md
    // https://github.com/google/googletest/blob/master/googlemock/docs/CheatSheet.md

    // 간단히 설명하자면 
    // ioctl을 호출할때마다( WillRepeatedly ) 
    // 2번째 인자인 ext_controls을 call by pointer( testing::SetArgPointee<2>(ext_controls) )로 반환하고 
    // return값을 17로 반환한다.(Return(17)). 이 두가지 동작을 동시 실행(DoAll)

    EXPECT_CALL(*ioctlMockObj, MOCK_ioctl1(_,_,_)).WillRepeatedly(DoAll(testing::SetArgPointee<2>(ext_controls), Return(17)));

    // getTimingInfo function 내부에서 ioctl이 호출되면 위에서 정의한 값들이 전달된다.
    json = cs.getTimingInfo(*ls);


    ASSERT_TRUE(1); 
}
```
