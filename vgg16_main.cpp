/**
* @file vgg16_main.cpp
*
* Copyright (C) 2018. Huawei Technologies Co., Ltd. All rights reserved.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*/

#include <unistd.h>
#include <thread>
#include <fstream>
#include <algorithm>
#include <string>

#include "hiaiengine/api.h"
#include "inc/error_code.h"
#include "inc/common.h"
#include "inc/data_recv.h"
#include "inc/util.h"

const int MAX_SLEEP_TIMES = 16;
static bool is_test_result_ready = false;

/**
* @ingroup HIAI_InitAndStartGraph
* @brief Initializing and Creating Graph
* @param [in]
*/
HIAI_StatusT HIAI_InitAndStartGraph()
{
    // Step1: init HiaiEngine
    HIAI_StatusT status = HIAI_Init(0);

    // Step2: Create Graph based on the configuration of the proto file.
    status = hiai::Graph::CreateGraph(GRAPH_CONFIG_FILE_PATH);
    if (status != HIAI_OK)
    {
        HIAI_ENGINE_LOG(status, "Fail to start graph");
        return status;
    }

    // Step3: Set the callback function for the DST Engine.
    std::shared_ptr<hiai::Graph> graph = hiai::Graph::GetInstance(GRAPH_ID);
    if (nullptr == graph)
    {
        HIAI_ENGINE_LOG("Fail to get the graph-%u", GRAPH_ID);
        return status;
    }

    // Configure the target data. Target Graph, Target Engine, and Target Port
    hiai::EnginePortID target_port_config;
    target_port_config.graph_id = GRAPH_ID;
    target_port_config.engine_id = DST_ENGINE_ID;
    target_port_config.port_id = DEST_PORT_ID_0;
    graph->SetDataRecvFunctor(target_port_config,
        std::shared_ptr<FasterRcnnDataRecvInterface>(
            new FasterRcnnDataRecvInterface(TEST_DEST_DATA_NUM_PATH)));

    target_port_config.port_id = DEST_PORT_ID_1;
    graph->SetDataRecvFunctor(target_port_config,
        std::shared_ptr<FasterRcnnDataRecvInterface>(
            new FasterRcnnDataRecvInterface(TEST_DEST_DATA_BBOX_PATH)));
    return HIAI_OK;
}

/**
* @ingroup CheckAllFileExist
* @brief Check whether all files are generated.
*/
void CheckAllFileExist()
{
    for (int i = 0; i < MAX_SLEEP_TIMES; ++i) {
        if (Util::CheckFileExist(TEST_DEST_DATA_NUM_PATH)
            && Util::CheckFileExist(TEST_DEST_DATA_BBOX_PATH)) {
            std::unique_lock <std::mutex> lck(local_test_mutex);
            is_test_result_ready = true;
            printf("File %s generated\n", TEST_DEST_DATA_NUM_PATH.c_str());
            printf("File %s generated\n", TEST_DEST_DATA_BBOX_PATH.c_str());
            HIAI_ENGINE_LOG("Check Result success");
            return;
        }

        printf("Check Result, go into sleep 1 sec\n");

        HIAI_ENGINE_LOG("Check Result, go into sleep 1 sec");

        sleep(1);
    }

    printf("Check Result failed, timeout\n");

    HIAI_ENGINE_LOG("Check Result failed, timeout");
}

/**
* @ingroup main
* @brief main function
* @param [in]: argc, argv
*/
int main(int argc, char* argv[])
{
    printf("========== Test Start ==========\n");
    HIAI_StatusT ret = HIAI_OK;

    // Delete the target file.
    remove(TEST_DEST_DATA_NUM_PATH.c_str());
    remove(TEST_DEST_DATA_BBOX_PATH.c_str());

    for (int i = 0; i < MAX_SLEEP_TIMES; ++i) {
        if (Util::CheckFileExist(GRAPH_MODEL_PATH)) {
            printf("File %s is ready\n", GRAPH_MODEL_PATH.c_str());
            break;
        }
        sleep(1);
        if (i == MAX_SLEEP_TIMES-1) {
            printf("model file:%s is not existence, timeout\n", GRAPH_MODEL_PATH.c_str());
        }
    }

    // Initializing and Creating Graph
    ret = HIAI_InitAndStartGraph();
    if (HIAI_OK != ret)
    {
        HIAI_ENGINE_LOG("Fail to start graph");
        return -1;
    }

    printf("Init and start graph succeed\n");

    std::shared_ptr<hiai::Graph> graph = hiai::Graph::GetInstance(GRAPH_ID);
    if (nullptr == graph)
    {
        HIAI_ENGINE_LOG("Fail to get the graph-%u", GRAPH_ID);
        return -1;
    }

    // Send data to Source Engine
    hiai::EnginePortID target_engine;
    target_engine.graph_id = GRAPH_ID;
    target_engine.engine_id = SRC_ENGINE_ID;
    target_engine.port_id = SRC_PORT_ID;

    std::shared_ptr<std::string> src_string =
        std::shared_ptr<std::string>(new std::string(TEST_SRC_FILE_PATH));
    ret = graph->SendData(target_engine, "string", std::static_pointer_cast<void>(src_string));

    if (HIAI_OK != ret)
    {
        HIAI_ENGINE_LOG("Fail to send data to source engine");
        return -1;
    }

    printf("Succeed to send data to source engine\n");

    // Waiting for processing result
    std::thread check_thread(CheckAllFileExist);
    check_thread.join();

    if (is_test_result_ready) {
        printf("========== Test Succeed ==========\n");
    } else {
        printf("========== Test Failed ==========\n");
    }

    // destroy Graph
    hiai::Graph::DestroyGraph(GRAPH_ID);
    return 0;
}

/* EOF */

