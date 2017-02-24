/*!
 * @file TAerialVehicle.h
 *
 * @brief Representation of an aerial vehicle
 *
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

#ifndef SINS_AERIAL_VEHICLE_H
#define SINS_AERIAL_VEHICLE_H

#include <QObject>

class TAerialVehicle : public QObject
{
    Q_OBJECT

public:
    TAerialVehicle(QObject *parent = nullptr);

private:
    TAerialVehicle(const TAerialVehicle &other) = delete;
    TAerialVehicle &operator=(const TAerialVehicle &other) = delete;
};

#endif  // SINS_AERIAL_VEHICLE_H
