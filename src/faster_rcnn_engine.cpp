/**
* @file faster_rcnn_ai_engine.cpp
*
* Copyright (C) 2018. Huawei Technologies Co., Ltd. All rights reserved.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*/

#include <unistd.h>
#include <vector>
#include <fstream>
#include <algorithm>
#include <iostream>
#include <string>

#include "inc/faster_rcnn_engine.h"
#include "inc/error_code.h"
#include "hiaiengine/api.h"
#include "hiaiengine/data_type.h"

/**
* @ingroup FasterRcnnEngine
* @brief FasterRcnnEngine init function
* @param [in]:arg0
*/
HIAI_StatusT FasterRcnnEngine::Init(const hiai::AIConfig &config,
    const std::vector<hiai::AIModelDescription>& model_desc)
{
    HIAI_ENGINE_LOG(this, HIAI_OK, "FasterRcnnEngine Init");
    hiai::AIStatus ret = hiai::SUCCESS;

    // Obtaining Configuration Parameters
    config_.clear();
    for (auto item : config.items())
    {
        config_[item.name()] = item.value();
    }
    if (nullptr == ai_model_manager_)
    {
        ai_model_manager_ = std::make_shared<hiai::AIModelManager>();
    }

    // Initialize the model.
    const char* model_path = config_["model_path"].c_str();
    std::vector<hiai::AIModelDescription> model_desc_vec;
    hiai::AIModelDescription model_desc_;
    model_desc_.set_path(model_path);
    model_desc_.set_key("");
    model_desc_vec.push_back(model_desc_);
    ret = ai_model_manager_->Init(config, model_desc_vec);

    if (hiai::SUCCESS != ret)
    {
        HIAI_ENGINE_LOG(this, HIAI_AI_MODEL_MANAGER_INIT_FAIL,
            "hiai ai model manager init fail");
        return HIAI_AI_MODEL_MANAGER_INIT_FAIL;
    }

    HIAI_ENGINE_LOG(this, HIAI_OK, "FasterRcnnEngine init success");
    return HIAI_OK;
}

/**
* @ingroup FasterRcnnEngine
* @brief FasterRcnnEngine Process function
* @param [in]:arg0
*/
HIAI_IMPL_ENGINE_PROCESS("FasterRcnnEngine", FasterRcnnEngine, FASTERRCNN_ENGINE_INPUT_SIZE)
{
    HIAI_ENGINE_LOG(this, HIAI_OK, "FasterRcnnEngine Process");
    HIAI_StatusT ret = HIAI_OK;

    std::shared_ptr<hiai::RawDataBuffer> input_arg =
        std::static_pointer_cast<hiai::RawDataBuffer>(arg0);
    if (nullptr == input_arg)
    {
        HIAI_ENGINE_LOG(this, HIAI_INVALID_INPUT_MSG,
            "fail to process invalid message");
        return HIAI_INVALID_INPUT_MSG;
    }

    // Sets the picture buffer.
    std::shared_ptr<hiai::AINeuralNetworkBuffer> neural_buffer_img =
        std::shared_ptr<hiai::AINeuralNetworkBuffer>(new hiai::AINeuralNetworkBuffer());
    neural_buffer_img->SetBuffer((void*)(input_arg->data.get()),
        (uint32_t)(input_arg->len_of_byte), false);

    // Setting image information
    float info_data[IMAGE_INFO_DATA_NUM] = {IMG_HEIGHT, IMG_WIDTH, IMG_DEPTH };
    std::shared_ptr<hiai::AINeuralNetworkBuffer> neural_buffer_info =
        std::shared_ptr<hiai::AINeuralNetworkBuffer>(new hiai::AINeuralNetworkBuffer());
    neural_buffer_info->SetBuffer((void*)info_data,
        sizeof(float) * IMAGE_INFO_DATA_NUM, false);

    // Convert the data into a smart pointer.
    std::shared_ptr<hiai::IAITensor> input_data_img =
        std::static_pointer_cast<hiai::IAITensor>(neural_buffer_img);
    std::shared_ptr<hiai::IAITensor> input_data_info =
        std::static_pointer_cast<hiai::IAITensor>(neural_buffer_info);

    // AIModelManager Fill in the input data.
    std::vector<std::shared_ptr<hiai::IAITensor>> input_data_vec;
    input_data_vec.push_back(input_data_img);
    input_data_vec.push_back(input_data_info);

    // Creating a out_data_vec
    hiai::AIContext ai_context;
    std::vector<std::shared_ptr<hiai::IAITensor>> output_data_vec;
    ret = ai_model_manager_->CreateOutputTensor(input_data_vec, output_data_vec);
    if (hiai::SUCCESS != ret)
    {
        HIAI_ENGINE_LOG(this, HIAI_AI_MODEL_CREATE_OUTPUT_FAIL,
            "Failed to create output tensor");
        return HIAI_AI_MODEL_CREATE_OUTPUT_FAIL;
    }

    // Process work
    ret = ai_model_manager_->Process(ai_context,
        input_data_vec, output_data_vec, 0);
    if (hiai::SUCCESS != ret)
    {
        HIAI_ENGINE_LOG(this, HIAI_AI_MODEL_MANAGER_PROCESS_FAIL,
            "Fail to process ai model manager");
        return HIAI_AI_MODEL_MANAGER_PROCESS_FAIL;
    }

    // The output is 2.
    if (FASTER_RCNN_OUTPUT_SIZE != output_data_vec.size())
    {
        HIAI_ENGINE_LOG(this, HIAI_AI_MODEL_WRONG_OUTPUT_SIZE,
            "Faster rcnn output size is wrong");
        return HIAI_AI_MODEL_WRONG_OUTPUT_SIZE;
    }

    // Generate the data_num and data_bbox information.
    std::shared_ptr<hiai::AINeuralNetworkBuffer> output_data_num =
        std::static_pointer_cast<hiai::AINeuralNetworkBuffer>(output_data_vec[0]);
    std::shared_ptr<hiai::AINeuralNetworkBuffer> output_data_bbox =
        std::static_pointer_cast<hiai::AINeuralNetworkBuffer>(output_data_vec[1]);

    // Convert the generated data to the buffer of the string type and send the data.
    std::shared_ptr<std::string> output_data_num_ptr =
        std::shared_ptr<std::string>(
            new std::string((char*)output_data_num->GetBuffer(),
            output_data_num->GetSize()));

    std::shared_ptr<std::string> output_data_bbox_ptr =
        std::shared_ptr<std::string>(
            new std::string((char*)output_data_bbox->GetBuffer(),
            output_data_bbox->GetSize()));

    // Send data to output 0 and output 1.
    hiai::Engine::SendData(0, "string",
        std::static_pointer_cast<void>(output_data_num_ptr));
    hiai::Engine::SendData(1, "string",
        std::static_pointer_cast<void>(output_data_bbox_ptr));
    return HIAI_OK;
}

/* EOF */

