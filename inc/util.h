/**
* @file util.h
*
* Copyright (C) 2018. Huawei Technologies Co., Ltd. All rights reserved.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*/

#ifndef UTIL_H_
#define UTIL_H_

#include <iostream>
#include <memory>

class Util
{
public:
    static char* ReadBinFile(std::shared_ptr<std::string> file_name_ptr, uint32_t* file_size);
    static bool CheckFileExist(const std::string& file_name);
    static void FasterRcnnDump(const std::string& file_name, std::shared_ptr<std::string> data);
};

#endif //UTIL_H_

/* EOF */
