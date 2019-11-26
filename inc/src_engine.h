/**
* @file src_engine.h
*
* Copyright (C) 2018. Huawei Technologies Co., Ltd. All rights reserved.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*/

#ifndef SRC_ENGINE_H_
#define SRC_ENGINE_H_

#include "hiaiengine/api.h"
#include "hiaiengine/multitype_queue.h"
#include "inc/common.h"

// Source Engine port size
#define SRC_ENGINE_INPUT_SIZE    1
#define SRC_ENGINE_OUTPUT_SIZE   1

/*
* Source Engine
*/
class SrcEngine : public hiai::Engine
{
    /**
    * @ingroup SrcEngine
    * @brief SrcEngine Process function
    * @param [in]: SOURCE_ENGINE_INPUT_SIZE, Source Engine in port
    * @param [in]: SOURCE_ENGINE_OUTPUT_SIZE, Source Engine out port
    * @param [out]: HIAI_StatusT
    */
    HIAI_DEFINE_PROCESS(SRC_ENGINE_INPUT_SIZE, SRC_ENGINE_OUTPUT_SIZE)
};

#endif  // SRC_ENGINE_H_

/* EOF */

