#include <stdio.h>

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "../../src/av/av_service.h"
#include "component_service.h"
#include "mock_ioctl.h"

IoctlMock *ioctlMockObj;

using ::testing::Return;
using ::testing::_;
using ::testing::DoAll;

class EXTINPUT_INTEGRATION : public ::testing::Test
{
    public:
        v4l2_ext_controls ext_controls;
        v4l2_ext_control ext_control;
        struct v4l2_ext_adc_timing_info adc_timing_info;

    public:
        virtual void SetUp(){
            ioctlMockObj = new IoctlMock();
            //init_V4L2_CID_EXT_ADC_TIMING_INFO();
            //printf("SetUp!!!!!\n");
        }

        virtual void TearDown(){
            delete ioctlMockObj;
        }

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
init_V4L2_CID_EXT_ADC_TIMING_INFO();
    // setting data which TEST want to get from ioctl.

    // v4l2_ext_controls ext_controls;
    // v4l2_ext_control ext_control;
    // struct v4l2_ext_adc_timing_info adc_timing_info;

    // memset(&ext_controls, 0, sizeof(v4l2_ext_controls));
    // memset(&ext_control, 0, sizeof(v4l2_ext_control));
    // memset(&adc_timing_info, 0, sizeof(struct v4l2_ext_adc_timing_info));

    // ext_controls.ctrl_class     = V4L2_CTRL_CLASS_USER;
    // ext_controls.count          = 1;
    // ext_controls.controls       = &ext_control;
    // ext_controls.controls->id   = V4L2_CID_EXT_ADC_TIMING_INFO;
    // ext_controls.controls->size = sizeof(struct v4l2_ext_adc_timing_info);
    // ext_controls.controls->ptr  = (void *)&adc_timing_info;
    adc_timing_info.h_freq = 1;
    adc_timing_info.v_freq = 2;
    adc_timing_info.h_total = 3;
    adc_timing_info.v_total = 4;
    adc_timing_info.h_porch = 5;
    adc_timing_info.active.w = 6;
    adc_timing_info.active.h = 7;
    adc_timing_info.scan_type = 8;
   
    pbnjson::JValue json;
    LS::Message *msg = new LS::Message();
    LSUtils::LunaRequest *ls = new LSUtils::LunaRequest(NULL, *msg,json);
    ComponentService cs; 

// call by reference 
    EXPECT_CALL(*ioctlMockObj, MOCK_ioctl1(_,_,_)).WillRepeatedly(DoAll(testing::SetArgPointee<2>(ext_controls), Return(18)));


    json = cs.getTimingInfo(*ls);
     ASSERT_TRUE(1); 
    printf("===== adc_timing_info.scan_type : %d (test2)\n", adc_timing_info.scan_type);
}


TEST_F(EXTINPUT_INTEGRATION, test2) 
{
    printf("===== adc_timing_info.scan_type : %d (test2)\n", adc_timing_info.scan_type);
}