/**
* @file error_code.h
*
* Copyright (C) 2018. Huawei Technologies Co., Ltd. All rights reserved.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*/

#ifndef ERROR_CODE_H_
#define ERROR_CODE_H_

#include "hiaiengine/status.h"

#define MODID_FASTERRCNN_VGG 0x801

enum
{
	HIAI_INVALID_INPUT_MSG_CODE = 0x801,
	HIAI_AI_MODEL_MANAGER_INIT_FAIL_CODE,
	HIAI_AI_MODEL_MANAGER_PROCESS_FAIL_CODE,
	HIAI_SEND_DATA_FAIL_CODE,
	HIAI_AI_MODEL_CREATE_OUTPUT_FAIL_CODE,
	HIAI_AI_MODEL_WRONG_OUTPUT_SIZE_CODE
};

HIAI_DEF_ERROR_CODE(MODID_FASTERRCNN_VGG, HIAI_ERROR, HIAI_INVALID_INPUT_MSG, \
    "invalid input message pointer");
HIAI_DEF_ERROR_CODE(MODID_FASTERRCNN_VGG, HIAI_ERROR, HIAI_AI_MODEL_MANAGER_INIT_FAIL, \
    "ai model manager init failed");
HIAI_DEF_ERROR_CODE(MODID_FASTERRCNN_VGG, HIAI_ERROR, HIAI_AI_MODEL_MANAGER_PROCESS_FAIL, \
    "ai model manager process failed");
HIAI_DEF_ERROR_CODE(MODID_FASTERRCNN_VGG, HIAI_ERROR, HIAI_SEND_DATA_FAIL, \
    "send data failed");
HIAI_DEF_ERROR_CODE(MODID_FASTERRCNN_VGG, HIAI_ERROR, HIAI_AI_MODEL_CREATE_OUTPUT_FAIL,
    "Failed to create output tensor");
HIAI_DEF_ERROR_CODE(MODID_FASTERRCNN_VGG, HIAI_ERROR, HIAI_AI_MODEL_WRONG_OUTPUT_SIZE,
    "Faster rcnn output size is wrong");

#endif  // ERROR_CODE_H_

/* EOF */

