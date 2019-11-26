/**
* @file util.cpp
*
* Copyright (C) 2018. Huawei Technologies Co., Ltd. All rights reserved.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*/

#include <fstream>
#include <algorithm>
#include <iostream>
#include <string>

#include "inc/util.h"
#include "inc/tensor.h"
#include "inc/common.h"

/**
* @ingroup Util
* @brief ReadBinFile Read the file and return the buffer.;
* @param [in]: file_name
* @param [in]: file_size
* @param [out]: std::string
*/
char* Util::ReadBinFile(std::shared_ptr<std::string> file_name, 
    uint32_t* file_size)
{
    std::filebuf *pbuf;
    std::ifstream filestr;
    size_t size;
    filestr.open(file_name->c_str(), std::ios::binary);
    if (!filestr)
    {
        return NULL;
    }

    pbuf = filestr.rdbuf();
    size = pbuf->pubseekoff(0, std::ios::end, std::ios::in);
    pbuf->pubseekpos(0, std::ios::in);
    char * buffer = new char[size];
    if (NULL == buffer)
    {
        return NULL;
    }

    pbuf->sgetn(buffer, size);
    *file_size = size;

    filestr.close();
    return buffer;
}

/**
* @ingroup Util
* @brief CheckFileExist 
* @param [in]:  file_name
* @param [out]: std::string
*/
bool Util::CheckFileExist(const std::string& file_name)
{
    std::ifstream f(file_name.c_str());
    return f.good();
}
/**
* @ingroup Util
* @brief FasterRcnnDump
* @param [in]:  file_name
* @param [in]:  data
*/
void Util::FasterRcnnDump(const std::string& file_name, std::shared_ptr<std::string> data)
{
    if (file_name == TEST_DEST_DATA_NUM_PATH) {
        ddk::Tensor<uint32_t> num;
        num.fromarray(reinterpret_cast<uint32_t*>(const_cast<char*>(data->c_str())), DATA_NUM);
        (void)num.dump(TEST_DEST_DATA_NUM_PATH);
    }
    if (file_name == TEST_DEST_DATA_BBOX_PATH) {
        ddk::Tensor<float> bbox;
        bbox.fromarray(reinterpret_cast<float*>(const_cast<char*>(data->c_str())), DATA_BBOX);
        (void)bbox.dump(TEST_DEST_DATA_BBOX_PATH);
    }

}
/* EOF */

