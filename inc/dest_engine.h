/**
* @file dest_engine.h
*
* Copyright (C) 2018. Huawei Technologies Co., Ltd. All rights reserved.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*/

#ifndef DEST_ENGINE_H_
#define DEST_ENGINE_H_

#include "inc/common.h"
#include "hiaiengine/api.h"
#include "hiaiengine/multitype_queue.h"

// Dest Engine port size
#define DEST_ENGINE_INPUT_SIZE      2
#define DEST_ENGINE_OUTPUT_SIZE     2

/*
* Dest Engine
*/
class DestEngine : public hiai::Engine
{
 public:
    DestEngine() :
        input_que_(DEST_ENGINE_INPUT_SIZE) {}
    /**
    * @ingroup SourceEngine
    * @brief SourceEngine Process function
    * @param [in]: DEST_ENGINE_INPUT_SIZE, Source Engine in port
    * @param [in]: DEST_ENGINE_OUTPUT_SIZE, Source Engine out port
    * @param [out]: HIAI_StatusT
    */
    HIAI_DEFINE_PROCESS(DEST_ENGINE_INPUT_SIZE, DEST_ENGINE_OUTPUT_SIZE)

 private:
    hiai::MultiTypeQueue input_que_;
};
#endif  // DEST_ENGINE_H_

/* EOF */

