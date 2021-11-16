#include<Wire.h>
#include <ros.h>
#include <std_msgs/Float32.h>
ros::NodeHandle nh;
std_msgs::Float32 yaw_angel;
double y;
double x;
double z;

ros::Publisher Yaw("Yaw", &yaw_angel);

const int MPU_addr=0x68;
int AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;
 
int minVal=265;
int maxVal=402;
 

HardwareSerial Serial1(PA_7, PA_6);
HardwareSerial Serial3(PA_11, PA_10);

 
void setup(){
 nh.initNode();
 nh.advertise(Yaw);
Wire.begin();
Wire.beginTransmission(MPU_addr);
Wire.write(0x6B);
Wire.write(0);
Wire.endTransmission(true);
 Serial1.begin(115200);
 Serial3.begin(115200);
}
void loop(){
Wire.beginTransmission(MPU_addr);
Wire.write(0x3B);
Wire.endTransmission(false);
Wire.requestFrom(MPU_addr,14,true);
/*AcX=Wire.read()<<8|Wire.read();
AcY=Wire.read()<<8|Wire.read();*/
AcZ=Wire.read()<<8|Wire.read();
int xAng = map(AcX,minVal,maxVal,-90,90);
int yAng = map(AcY,minVal,maxVal,-90,90);
int zAng = map(AcZ,minVal,maxVal,-90,0);
 
/*x= RAD_TO_DEG * (atan2(-yAng, -zAng)+PI);
y= RAD_TO_DEG * (atan2(-xAng, -zAng)+PI);*/
z=(float) RAD_TO_DEG * (float)(atan2(-yAng, -xAng)+PI);
//z=u;
  
Serial1.print("Yaw ");
Serial1.println(z);

 yaw_angel.data = z;
 Yaw.publish( &yaw_angel);
 nh.spinOnce();
  
delay(400);

}
