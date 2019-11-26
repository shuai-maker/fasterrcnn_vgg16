/**
* @file faster_rcnn_engine.h
*
* Copyright (C) 2018. Huawei Technologies Co., Ltd. All rights reserved.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*/

#ifndef FASTER_RCNN_ENGINE_H_
#define FASTER_RCNN_ENGINE_H_

#include <string>
#include <vector>
#include <map>

#include "inc/common.h"
#include "hiaiengine/api.h"
#include "hiaiengine/ai_model_manager.h"

// FasterRcnn Engine port size
#define FASTERRCNN_ENGINE_INPUT_SIZE    1
#define FASTERRCNN_ENGINE_OUTPUT_SIZE   2

class FasterRcnnEngine : public hiai::Engine
{
 public:
    /**
    * @ingroup FasterRcnnEngine
    * @brief FasterRcnnEngine Initialization function
    * @param [in]:config, Configuration parameters
    * @param [in]: model_desc, Model Description
    * @param [out]: HIAI_StatusT
    */
    HIAI_StatusT Init(const hiai::AIConfig &config,
        const std::vector<hiai::AIModelDescription>& model_desc);

    /**
    * @ingroup FasterRcnnEngine
    * @brief FasterRcnnEngine Execute the function.
    * @param [in]:FASTERRCNN_ENGINE_INPUT_SIZE, Number of In Port
    * @param [in]: FASTERRCNN_ENGINE_OUTPUT_SIZE, Number of out ports
    * @param [out]: HIAI_StatusT
    */
    HIAI_DEFINE_PROCESS(FASTERRCNN_ENGINE_INPUT_SIZE, FASTERRCNN_ENGINE_OUTPUT_SIZE);
 private:
    std::map<std::string, std::string> config_;                 // config map
    std::shared_ptr<hiai::AIModelManager> ai_model_manager_;    // Model Manager Instance
};

#endif  // FASTER_RCNN_ENGINE_H_

/* EOF */

