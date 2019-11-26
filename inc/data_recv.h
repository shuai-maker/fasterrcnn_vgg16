/**
* @file data_recv.h
*
* Copyright (C) 2018. Huawei Technologies Co., Ltd. All rights reserved.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*/

#ifndef DATA_RECV_H_
#define DATA_RECV_H_

#include <string>

#include "hiaiengine/api.h"

class FasterRcnnDataRecvInterface : public hiai::DataRecvInterface
{
public:
    /**
    * @ingroup FasterRcnnDataRecvInterface
    * @brief construct function
    * @param [in]desc:std::string
    */
    FasterRcnnDataRecvInterface(const std::string& filename) :
        file_name_(filename) {}

    /**
    * @ingroup FasterRcnnDataRecvInterface
    * @brief RecvData RecvDataRecvData Callback, save the file.
    * @param [in]
    */
    HIAI_StatusT RecvData(const std::shared_ptr<void>& message);

private:
    std::string file_name_;     // Target Save File
};
#endif  // DATA_RECV_H_

/* EOF */
