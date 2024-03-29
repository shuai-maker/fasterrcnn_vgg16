﻿/**
* @file data_recv.cpp
*
* Copyright(c)<2018>, <Huawei Technologies Co.,Ltd>
*
* @version 1.0
*
* @date 2018-6-7
*/

#include <fstream>
#include <iostream>
#include <algorithm>
#include <string>

#include "inc/data_recv.h"
#include "inc/error_code.h"
#include "inc/common.h"
#include "inc/util.h"

/**
* @ingroup FasterRcnnDataRecvInterface
* @brief RecvData RecvData callback,save file
* @param [in]
*/
HIAI_StatusT FasterRcnnDataRecvInterface::RecvData(const std::shared_ptr<void>& message)
{
    std::shared_ptr<std::string> data =
        std::static_pointer_cast<std::string>(message);
    if (nullptr == data)
    {
        HIAI_ENGINE_LOG("Fail to receive data");
        return HIAI_INVALID_INPUT_MSG;
    }

    Util::FasterRcnnDump(file_name_, data);
    return HIAI_OK;
}

/* EOF */

