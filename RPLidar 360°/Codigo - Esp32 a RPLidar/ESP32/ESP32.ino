#include <RPLidar.h>

// This sketch code is based on the RPLIDAR driver library provided by RoboPeak
// include library // 加载库
#include <RPLidar.h>

RPLidar lidar;

#define RPLIDAR_MOTOR 14
 

void setup() {
  Serial.begin(115200);
  // bind the RPLIDAR driver to the arduino hardware serial

  Serial2.begin(115200, SERIAL_8N1, 16, 17);
  lidar.begin(Serial2);
  // set pin modes

  pinMode(RPLIDAR_MOTOR, OUTPUT);
  delay(1000);

  digitalWrite(RPLIDAR_MOTOR, HIGH);
}

void loop() {
  if (IS_OK(lidar.waitPoint())) {
    float distance = lidar.getCurrentPoint().distance; //distance value in mm unit
                                                        //距离值以毫米为单位
    float angle    = lidar.getCurrentPoint().angle;   //anglue value in degree
                                                      //度数的角度值
    bool  startBit = lidar.getCurrentPoint().startBit;  //whether this point is belong to a new scan
                                                        //该点是否属于一个新的扫描点

    byte  quality  = lidar.getCurrentPoint().quality;   //quality of the current measurement
                                                        //当前测量的质量

    //在这里进行数据处理...
    // - 1 -
    // perform data processing here...
    // Output all data in the serial port  
    //在串口中输出所有数据

    //    for(int i = 0;i < 6 - String(angle).length(); i++){
    //      Serial.print(" ");
    //    }
    //    Serial.print(String(angle));
    //    Serial.print(" | ");
    //    for(int i = 0;i < 8 - String(distance).length(); i++){
    //      Serial.print(" ");
    //    }
    //    Serial.print(distance);
    //    Serial.print(" | ");
    //    Serial.print(startBit);
    //    Serial.print(" | ");
    //    for(int i = 0;i < 2 - String(quality).length(); i++){
    //      Serial.print(" ");
    //    }
    //    Serial.println(quality);

    // - 2 - 
    // Output the specified angle data
    // 输出指定角度
    if(angle > 0 and angle < 100 ){
      Serial.print(angle);
      Serial.print(" | ");
      Serial.println(distance);
    }
  } else {
    digitalWrite(RPLIDAR_MOTOR, LOW); //stop the rplidar motor
                                   //停止rplidar马达

    // try to detect RPLIDAR...
    // 尝试检测RPLIDAR... 
    rplidar_response_device_info_t info;
    if (IS_OK(lidar.getDeviceInfo(info, 100))) {
       // detected...
       // 检测到
       lidar.startScan();

       // start motor rotating at max allowed speed
       // 启动电机以最大允许速度旋转
       digitalWrite(RPLIDAR_MOTOR, HIGH);
       delay(1000);
    }
  }
}
