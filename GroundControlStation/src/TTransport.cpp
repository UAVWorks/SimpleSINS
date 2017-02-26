/*!
 * @file TTransport.cpp
 *
 * @brief Transport for connectivity with the vehicle
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

#include "TTransport.h"

#include <mavlink.h>

#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <sys/ioctl.h>

#include <QDebug>

TTransport::TTransport(QObject *parent)
    : QObject(parent)
{
    connect(&mTimer, &QTimer::timeout, this, &TTransport::onReadyRead);

    mPort = open(mDeviceName.toStdString().c_str(), O_RDWR | O_NOCTTY | O_NDELAY | O_FSYNC);

    if (mPort == -1) {
        qDebug() << "open_port: Unable to open " << mDeviceName;
    } else {
        fcntl(mPort, F_SETFL, 0);
        qDebug() << "Port has been sucessfully opened";

        struct termios terminalAttributes;
        memset(&terminalAttributes, 0, sizeof(struct termios));

        terminalAttributes.c_cflag = B9600 | CS8 | CLOCAL | CREAD;
        terminalAttributes.c_iflag = 0;
        terminalAttributes.c_oflag = 0;
        terminalAttributes.c_cc[VTIME] = 5;
        terminalAttributes.c_cc[VMIN] = 1;

        tcsetattr(mPort, TCSANOW, &terminalAttributes);
        mTimer.start(100);
    }
}

TTransport::~TTransport()
{
    qDebug() << "Close port";
    close(mPort);
}

void TTransport::onReadyRead()
{
    int bytes = 0;
    ioctl(mPort, FIONREAD, &bytes);

    if (bytes < 1)
        return;

    mTimer.stop();

    QByteArray arr;
    mavlink_message_t message;
    mavlink_status_t status;

    arr.resize(bytes);
    read(mPort, arr.data(), bytes);

    for (const auto &byteVal : arr) {
        uint8_t msgReceived = mavlink_parse_char(MAVLINK_COMM_1, byteVal, &message, &status);

        if (msgReceived) {
            qDebug() << "Received message with ID " << message.msgid;

            switch (message.msgid) {
                case MAVLINK_MSG_ID_HEARTBEAT:
                    mavlink_heartbeat_t heartbeat;
                    mavlink_msg_heartbeat_decode(&message, &heartbeat);
                    qDebug() << "heartbeat. Custom mode = " << heartbeat.custom_mode;
                    break;
                default:
                    qDebug() << "Unknown message";
            }
        }
    }

    mTimer.start(100);
}
