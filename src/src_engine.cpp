/**
* @file src_engine.cpp
*
* Copyright (C) 2018. Huawei Technologies Co., Ltd. All rights reserved.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*/

#include <unistd.h>
#include <thread>
#include <vector>
#include <fstream>
#include <algorithm>
#include <iostream>
#include <string>

#include "inc/src_engine.h"
#include "inc/util.h"
#include "inc/common.h"
#include "inc/error_code.h"
#include "hiaiengine/data_type.h"

void CharArrayDeleter(unsigned char* ptr)
{
    delete[] ptr;
}

// Source Engine
HIAI_IMPL_ENGINE_PROCESS("SrcEngine", SrcEngine, SRC_ENGINE_INPUT_SIZE)
{
    HIAI_ENGINE_LOG(this, HIAI_OK, "SrcEngine Process");
    // Obtain the path of the original file.
    std::shared_ptr<std::string> input_arg =
        std::static_pointer_cast<std::string>(arg0);
    if (nullptr == input_arg)
    {
        HIAI_ENGINE_LOG(this, HIAI_INVALID_INPUT_MSG,
            "fail to process invalid message");
        return HIAI_INVALID_INPUT_MSG;
    }

    // Reads data and generates information.
    uint32_t bufSize = 0;
    char* bufData = Util::ReadBinFile(input_arg, &bufSize);

    std::shared_ptr<hiai::RawDataBuffer> raw_data_ptr =
        std::make_shared<hiai::RawDataBuffer>();
    raw_data_ptr->len_of_byte = bufSize;
    raw_data_ptr->data = std::shared_ptr<uint8_t>((unsigned char*)bufData, CharArrayDeleter);

    // Transferred to FasterRcnn Engine
    SendData(0, "RawDataBuffer", std::static_pointer_cast<void>(raw_data_ptr));

    HIAI_ENGINE_LOG(this, HIAI_OK, "SrcEngine Process Success");
    return HIAI_OK;
}

/* EOF */

