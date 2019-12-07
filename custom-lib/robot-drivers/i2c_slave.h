// #ifndef I2C_SLAVE_H
// #define I2C_SLAVE_H

// enum Device {
//   ENCODER,
//   ULTRASONIC,
//   MOTOR_DRIVER,
//   IMU
// };

// class I2CSlave {
//   public:
//     I2CSlave(uint8_t my_address);
//     int getMotorDriverCmd();

//     struct RequestHolder {
//       float encoder_speed;
//       float ranger_dist;
//       float imu_data;
//     };

//   private:
//     void SendDataToMaster();
//     void ReceiveMasterCommand();
//     int motor_driver_cmd;
// };


// #endif // I2C_SLAVE_H