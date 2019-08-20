#include "mytransmission.h"
#include "serial_handle.h"

myTransmission::myTransmission()
{
    /*创建串口处理对象*/
    serial = new Serial_Handle();
    /*将串口对向放到子进程中运行*/
    serial->moveToThread(&SerialThread);
    /*线程结束后，删除子进程*/
    connect(&SerialThread, &QThread::finished, serial, &QObject::deleteLater);

    /*运行串口处理子进程*/
    SerialThread.start();

    /*连接串口打开信号槽*/
    QObject::connect(serial,   &Serial_Handle::Open_Serial, serial,&Serial_Handle::Open);

    qDebug()<<"from Transmission:" << QThread::currentThreadId();//打印主线程ID

    /*开启一个10ms的定时器，定时解析串口数据*/
    Timer_ReadData = new QTimer(this);
    connect(Timer_ReadData, SIGNAL(timeout()), this, SLOT(Read_Serial()));
    Timer_ReadData->start(1);

   //初始化反馈变量
   memset(&feedbackdata,0,sizeof(feedbackdata));
}


void myTransmission::Open_Serial(QString Com, int Baud, uint8_t databits, uint8_t Parity, uint8_t stopbits)
{
  /*发送打开串口的信号*/
    emit serial->Open_Serial(Com,Baud,databits,Parity,stopbits);
}

void myTransmission::Close_Serial()
{
    /*发送关闭串口的信号*/
    emit serial->Close_Serial();
}

void myTransmission::Send_cmd(uint8_t cmy_type,uint16_t data)
{

    char send_buff[20];
    uint16_t crc16;

    send_buff[0] = 0xA5;
    send_buff[1] = 0x5A;
    send_buff[2] = 9;
    send_buff[3] = 0;
    send_buff[4] = cmy_type;
    send_buff[5] = data;
    send_buff[6] = data >> 8;
    /*crc16校验*/
    crc16 = crc16_calc((uint8_t *)send_buff,7);

    send_buff[7] = crc16;
    send_buff[8] = crc16 >> 8;

    /*将要发送的数据放入发送循环缓冲区，并发送串口发送数据信号*/
    QByteArray temp;
    temp.append(send_buff,send_buff[2]);
    emit serial->WriteData(temp);
    qDebug("发送控制数据成功,命令类型:0x%x,数据:%d",cmy_type,(int8_t)data);
}

unsigned short myTransmission::crc16_calc(unsigned char *buf, int length)
{
     /*crc校验初始值:0x2B3B*/
        unsigned short Result = 0x2B3B;

      /*查表法产生crc16校验值*/
        for (int i = 0; i < length; i++)
        {
            Result = (Result >> 8) ^ CRC16_Table[(Result ^ buf[i]) & 0xff];
        }
        return Result;
}

/**
*@brief read the data from the rx circle buff
*@param in : crtl_value
*@param out :none
**/
void myTransmission::Read_Serial()
{
    QByteArray temp;
    uint8_t buffer[100];
    unsigned int len =  serial->GetDataCount();

   // qDebug()<<"接收到" <<len <<"data";

    if(len >= (sizeof(feedbackdata) +7 ) * 2)
    {
        if((serial->at(0) == 'A' && serial->at(1) == '5'\
         && serial->at(2) == '5' && serial->at(3) == 'A') || (serial->at(0) == 'a' && serial->at(1) == '5'\
         && serial->at(2) == '5' && serial->at(3) == 'a') )
        {
             //   qDebug()<<"帧头校验成功";

                /*解析帧长度*/
                uint16_t length = ((convertCharToHex(serial->at(4)) << 4 )+ convertCharToHex(serial->at(5))) |\
                        (((convertCharToHex(serial->at(6)) << 4 )+ convertCharToHex(serial->at(7)))<< 8);

               //  qDebug()<<"帧长度为："<<length<<"缓冲区长度" << len;

                 /*只有当缓冲区中的数据大于帧长度时才将帧内容从缓冲区中移出*/
                 if(len >= length * 2 )
                 {

                         if(length != sizeof(feedbackdata) +7 )
                         {
                             qDebug()<< "...无效包！";
                             serial->Drop(len);
                             return;
                         }

                       //  qDebug()<< "数据正常";
                         serial->Rec(&temp,length * 2);
                 }
                 else
                 {
                      qDebug()<< "无效包！";
                      serial->Drop(len);
                      return;
                 }


                // qDebug()<<"rx data"<<temp;

                 /*将字符数据转化为实际的数据*/
                for(uint8_t i=0;i< length ; i++)
                {
                   buffer[i] = (convertCharToHex(temp.at( 2 * i )) << 4 )+ convertCharToHex(temp.at(2*i + 1));
                }


                /*对转化后的数据进行CRC16校验*/
                uint16_t crc_result;
                crc_result = crc16_calc(buffer,length);
               // qDebug()<<"帧校验结果为："<<crc_result;

               /*如果校验成功，则将解析到的数据显示到UI上*/
                if( crc_result== 0)
                {
                   // qDebug()<<"crc校验成功";

                    connect_cnt = 0;
                    connect_status  = 1;

                    switch(buffer[4])
                    {
                        case 0xa1:
                           memcpy(&feedbackdata.steering_mode,&buffer[5],sizeof(feedbackdata.steering_mode));
                           memcpy(&feedbackdata.steering_value,&buffer[6],sizeof(feedbackdata.steering_value));
                          break;
                        case 0xb1:
                            memcpy(&feedbackdata.accel_mode,&buffer[5],sizeof(feedbackdata.accel_mode));
                            memcpy(&feedbackdata.accel_value,&buffer[6],sizeof(feedbackdata.accel_value));
                          break;
                        case 0xc1:
                            memcpy(&feedbackdata.brake_mode,&buffer[5],sizeof(feedbackdata.brake_mode));
                            memcpy(&feedbackdata.brake_value,&buffer[6],sizeof(feedbackdata.brake_value));
                          break;
                        case 0xd1:
                            memcpy(&feedbackdata.gear_mode,&buffer[5],sizeof(feedbackdata.gear_mode));
                            memcpy(&feedbackdata.gear_value,&buffer[6],sizeof(feedbackdata.gear_value));
                          break;
                        case 0xe1:
                            memcpy(&feedbackdata.parking_mode,&buffer[5],sizeof(feedbackdata.parking_mode));
                            memcpy(&feedbackdata.parking_value,&buffer[6],sizeof(feedbackdata.parking_value));
                          break;
                        case 0xf1:
                            memcpy(&feedbackdata.light_mode,&buffer[5],sizeof(feedbackdata.light_mode));
                            memcpy(&feedbackdata.light_value,&buffer[6],sizeof(feedbackdata.light_value));
                          break;
                        case 0xf2:
                            memcpy(&feedbackdata.battery_vol,&buffer[5],sizeof(feedbackdata.battery_vol));
                            //memcpy(&feedbackdata.speed,&buffer[7],sizeof(feedbackdata.speed));
                            memcpy(&can_bus_status,&buffer[9],sizeof(can_bus_status));
                          break;
                        case 0xf3:
                           memcpy(&feedbackdata,&buffer[5],sizeof(feedbackdata));
                            break;
                        default:
                          break;
                      }
                }
            }
            else
            {
               /*没有找到帧头则将不断丢弃缓冲区中的数据直到找到真正的帧头*/
                serial->Drop(1);
                for(;;)
                {
                    if(serial->GetDataCount() >= (sizeof(feedbackdata) +7) * 2)//读至下一帧帧头
                    {
                        if((serial->at(0) == 'A' && serial->at(1) == '5'\
                           && serial->at(2) == '5' && serial->at(3) == 'A') || (serial->at(0) == 'a' && serial->at(1) == '5'\
                           && serial->at(2) == '5' && serial->at(3) == 'a') )
                         {
                             break;
                         }
                         else
                         {
                            qDebug()<<"正在寻找帧头";
                             serial->Drop(1);
                         }
                    }
                    else
                    {
                         break;
                    }
                }
             }
    }
}

unsigned char myTransmission::convertCharToHex(unsigned char ch)
{
    /*
    0x30等于十进制的48，48也是0的ASCII值，，
    1-9的ASCII值是49-57，，所以某一个值－0x30，，
    就是将字符0-9转换为0-9
    */
    if((ch >= '0') && (ch <= '9'))
         return ch-0x30;
     else if((ch >= 'A') && (ch <= 'F'))
         return ch-'A'+10;
     else if((ch >= 'a') && (ch <= 'f'))
         return ch-'a'+10;
     else return (-1);
}

