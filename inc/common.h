/**
* @file common.h
*
* Copyright (C) 2018. Huawei Technologies Co., Ltd. All rights reserved.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*/

#ifndef COMMON_H_
#define COMMON_H_

#include <iostream>
#include <string>

#include "hiaiengine/data_type_reg.h"

// Defines the global value.
// Defines the file path.
static const std::string TEST_SRC_FILE_PATH  =
        "./test_data/data/faster_rcnn.bin";
static const std::string TEST_DEST_DATA_NUM_PATH =
        "./test_data/result_data_num_file";
static const std::string TEST_DEST_DATA_BBOX_PATH =
        "./test_data/result_data_bbox_file";
// Clear text for direct viewing by the user

static const std::string GRAPH_CONFIG_FILE_PATH =
        "./test_data/config/sample.prototxt";
static const std::string GRAPH_MODEL_PATH =
        "./test_data/model/FasterRCNN-vgg16.om";

// Defines Graph,Engine ID
static const uint32_t GRAPH_ID = 100;
static const uint32_t SRC_ENGINE_ID = 1001;
static const uint32_t SRC_PORT_ID = 0;
static const uint32_t DST_ENGINE_ID = 1002;
static const uint32_t DEST_PORT_ID_0 = 0;
static const uint32_t DEST_PORT_ID_1 = 1;

static std::mutex local_test_mutex;
static std::condition_variable local_test_cv_;

// Defines Output shape
const std::vector<uint32_t> DATA_NUM = {32};
const std::vector<uint32_t> DATA_BBOX = {32,608,8};

// Defines the global value.
static const uint32_t MAX_SLEEP_TIMER = 30 * 60;

// Defines image parameters.
static const float IMG_HEIGHT = 374.0;
static const float IMG_WIDTH = 500.0;
static const float IMG_DEPTH = 1.0;

static const uint32_t FASTER_RCNN_OUTPUT_SIZE = 2;

// Defines the message_type character string.
static const std::string message_type_engine_trans = "EngineTransT";

#define IMAGE_INFO_DATA_NUM         (3)

// Defines the transmission structure.
typedef struct EngineTrans
{
    std::string trans_buff;
    uint32_t buffer_size;
    HIAI_SERIALIZE(trans_buff, buffer_size);
}EngineTransT;

#endif  // COMMON_H_

/* EOF */

