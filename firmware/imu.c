/**
 * @file imu.c
 *
 * @brief Inertial Measurement Unit
 *
 * This is to separate code generated by the CubeMX
 *
 * Copyright © 2017 Oleksii Aliakin. All rights reserved.
 * Author: Oleksii Aliakin (alex@nls.la)
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "imu.h"

static float buffer[3] = { 0 };

HAL_StatusTypeDef imu_init()
{
    HAL_StatusTypeDef result = HAL_OK;

    if (BSP_GYRO_Init() != HAL_OK) {
        BSP_LED_On(LED_RED);  // TODO: better error reporting
        result = HAL_ERROR;
    }
    return result;
}

int imu_read(mavlink_raw_imu_t *imu_data)
{
    BSP_GYRO_GetXYZ(buffer);

    imu_data->time_usec = HAL_GetTick();
    imu_data->xgyro = (int16_t)buffer[0];
    imu_data->ygyro = (int16_t)buffer[1];
    imu_data->zgyro = (int16_t)buffer[2];

    return true;
}
