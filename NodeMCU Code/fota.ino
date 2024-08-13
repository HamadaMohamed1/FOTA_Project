/**
  ******************************************************************************
  * @file           : FOTA_NodeMCU.ino
  * @brief          : Main program body of NodeMCU 
  ******************************************************************************
  *  Created on: Aug 2, 2024
  *      Author: Eng : Hamada El-Sayed
  ******************************************************************************/

/******************************** Includes *************************************/
#include <SoftwareSerial.h>
#include <string>
#include <ESP8266WiFi.h>
#include "BL_Tool.h"
#include <Firebase_ESP_Client.h>
#include "config.h"
/******************************** Firebase *************************************/
// Provide the token generation process info.
#include <addons/TokenHelper.h>
/* 1. Define the WiFi credentials */
#define WIFI_SSID "MY_WIFI_SSD"                    /* Your Wifi SSID */
#define WIFI_PASSWORD "MY_WIFI_PASSWORD"            /* Your Wifi Password */
/* 2. Define the API Key */
#define API_KEY "AIzaSyBMoWu0M8TkQrZgj4Ul18dNlYA6xiyTOKA"
/* 3. Define the user Email and password that alreadey registerd or added in your project */
#define USER_EMAIL "hamada@gmail.com"      /* your gmail */
#define USER_PASSWORD "123456"              /* your password */
/* 4. Define the Firebase storage bucket ID e.g bucket-name.appspot.com */
#define STORAGE_BUCKET_ID "fota-4d7bd.appspot.com"
// Define Firebase Data object
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;
bool taskCompleted = false;
#if defined(ARDUINO_RASPBERRY_PI_PICO_W)
WiFiMulti multi;
#endif
/******************************** mySerial *************************************/
#define RX_PIN 14 // D5 on NodeMCU
#define TX_PIN 12 // D6 on NodeMCU
SoftwareSerial mySerial(RX_PIN, TX_PIN);/*Create SoftwareSerial object*/
uint8_t data_buf[266];
/******************************** adafruit io **********************************/
// set up the 'digital' feeds
AdafruitIO_Feed *download_file_feed = io.feed("download_file_feed");
AdafruitIO_Feed *update_app_feed = io.feed("update_app_feed");
AdafruitIO_Feed *cid_feed = io.feed("cid_feed");
AdafruitIO_Feed *ver_feed = io.feed("ver_feed");
AdafruitIO_Feed *flash_erase_feed = io.feed("flash_erase_feed");
AdafruitIO_Feed *read_protection_level_feed = io.feed("read_protection_level_feed");
AdafruitIO_Feed *jump_to_app_feed = io.feed("jump_to_app_feed");
// set up the response feed
AdafruitIO_Feed *response_feed = io.feed("response_feed"); 

uint16_t _u16_value_to_send_to_dashboard =0;
String _faild_message = "Faild";
String _string_to_send_to_dashboard ="";
/******************************** void setup *************************************/
void setup() 
{
  Serial.begin(115200);/*Start hardware serial communication for debugging*/
  while (!Serial);/*Wait for Serial to be ready*/
  mySerial.begin(115200);
  while (!mySerial);

  WiFi.begin(WIFI_SSID , WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED)
  {
   Serial.println(".");
   delay(500);
  }
  Serial.println("Connected");

  io.connect();
  download_file_feed->onMessage(handle_download_request);
  update_app_feed->onMessage(handle_update_app_request);
  cid_feed->onMessage(handle_get_CID_request);
  ver_feed->onMessage(handle_get_VER_request);
  flash_erase_feed->onMessage(handle_flash_erase_request);
  jump_to_app_feed->onMessage(handle_jump_to_app_request);
  read_protection_level_feed->onMessage(handle_read_protection_level_request);
   // wait for a connection
  while(io.status() < AIO_CONNECTED) 
  {
    Serial.print(".");
    delay(500);
  }
  // we are connected
  Serial.println();
  Serial.println(io.statusText());
  download_file_feed->get();
  update_app_feed->get();
  cid_feed->get();
  ver_feed->get();
  flash_erase_feed->get();

  jump_to_app_feed->get();
  read_protection_level_feed->get();
}
/******************************** void loop *************************************/
void loop() 
{
   io.run();

  if(Serial.available()) /*if we want to execute the command from serial monitor*/
  {
      
     char Choice = Serial.read();
      //memset(data_buf , 0 , 266); /*buffer clearing*/
      switch (Choice) 
      {
        case 'V':
                  Handle_GET_VER_CMD();
        break;
        case 'I':
                  Handle_GET_CID_CMD();
        break;
        case 'L':
                  Handle_Read_Protection_Level_CMD();
        break;
        case 'E':
                  Handle_Flash_Erase_CMD( 2 , 4);
        break;
        case 'W':
             //   Handle_Memory_Write_CMD();
        break;
        case 'J':
            //    Handle_Jump_To_Address_CMD();
        break;
        case 'R':
                Handle_System_Reset_CMD();
        break;
      }
  }

  delay(10); /* Small delay to stabilize serial communication */
}

/******************************** Firebase functions *********************************************/
void download_file_from_firebase()
{
    Serial.printf("Firebase Client v%s\n\n", FIREBASE_CLIENT_VERSION);
    /* Assign the api key (required) */
    config.api_key = API_KEY;
    /* Assign the user sign in credentials */
    auth.user.email = USER_EMAIL;
    auth.user.password = USER_PASSWORD;
    // The WiFi credentials are required for Pico W
    // due to it does not have reconnect feature.
#if defined(ARDUINO_RASPBERRY_PI_PICO_W)
    config.wifi.clearAP();
    config.wifi.addAP(WIFI_SSID, WIFI_PASSWORD);
#endif

    /* Assign the callback function for the long running token generation task */
    config.token_status_callback = tokenStatusCallback; // see addons/TokenHelper.h
    // Comment or pass false value when WiFi reconnection will control by your code or third party library e.g. WiFiManager
    Firebase.reconnectNetwork(true);
    // Since v4.4.x, BearSSL engine was used, the SSL buffer need to be set.
    // Large data transmission may require larger RX buffer, otherwise connection issue or data read time out can be occurred.
    fbdo.setBSSLBufferSize(4096 /* Rx buffer size in bytes from 512 - 16384 */, 1024 /* Tx buffer size in bytes from 512 - 16384 */);
    /* Assign download buffer size in byte */
    // Data to be downloaded will read as multiple chunks with this size, to compromise between speed and memory used for buffering.
    // The memory from external SRAM/PSRAM will not use in the TCP client internal rx buffer.
    config.fcs.download_buffer_size = 2048;
    Firebase.begin(&config, &auth);
// Firebase.ready() should be called repeatedly to handle authentication tasks.
    if (Firebase.ready() && !taskCompleted)
    {
        taskCompleted = true;
        Serial.println("\nDownload file...\n");
        // The file systems for flash and SD/SDMMC can be changed in FirebaseFS.h.
        if (!Firebase.Storage.download(&fbdo, STORAGE_BUCKET_ID /* Firebase Storage bucket id */, "Application.bin" /* path of remote file stored in the bucket */, "/new.bin" /* path to local file */, mem_storage_type_flash /* memory storage type, mem_storage_type_flash and mem_storage_type_sd */, fcsDownloadCallback /* callback function */))
            Serial.println(fbdo.errorReason());
     //   readFile("/new.bin");
    }
}

// The Firebase Storage download callback function
void fcsDownloadCallback(FCS_DownloadStatusInfo info)
{
    if (info.status == firebase_fcs_download_status_init)
    {
        Serial.printf("Downloading file %s (%d) to %s\n", info.remoteFileName.c_str(), info.fileSize, info.localFileName.c_str());
    }
    else if (info.status == firebase_fcs_download_status_download)
    {
        Serial.printf("Downloaded %d%s, Elapsed time %d ms\n", (int)info.progress, "%", info.elapsedTime);
    }
    else if (info.status == firebase_fcs_download_status_complete)
    {
        Serial.println("Download completed\n");
    }
    else if (info.status == firebase_fcs_download_status_error)
    {
        Serial.printf("Download failed, %s\n", info.errorMsg.c_str());
    }
}

void readFile(const char *path)
{
  File file = LittleFS.open(path, "r");
  if(!file)
  {
    Serial.println("Failed to open file");
    return;
  }
  Serial.println("Read from file:");
  while(file.available())
  {
    uint8_t bytesRead =0;
    uint8_t arr[100] = {0}; uint32_t local_address = SECTOR_2_BASE;
    
    while ((bytesRead = file.readBytes((char*)arr, 100)) > 0)
    {
        for (uint8_t i = 0; i < bytesRead; i++) 
        {
          Serial.print(arr[i], HEX);
          Serial.print(" ");
        }
        Serial.println();
        
        do
        {
          Handle_Memory_Write_CMD(local_address, bytesRead , &arr[0]);
          delay(150);
        }while(_u16_value_to_send_to_dashboard != 1);
        local_address += bytesRead;
        
    }
  // Handle_Memory_Write_CMD();
    
  }


  file.close();
}
/******************************** adafruit functions *********************************************/
void handle_get_VER_request(AdafruitIO_Data *data) 
{
  _string_to_send_to_dashboard = ""; /*Clear string to be send*/
  Serial.print("received <- ");
  if(data->toPinLevel() == HIGH)
  {
    Serial.println("Get VER Request");
    Handle_GET_VER_CMD();
    if(_u16_value_to_send_to_dashboard != 0)
    {
      _string_to_send_to_dashboard = "BL Version : ";
      _string_to_send_to_dashboard.concat(_u16_value_to_send_to_dashboard);
      response_feed->save(_string_to_send_to_dashboard);
    }
    else
    {
      response_feed->save(_faild_message);
    }
  }
  else
  {
    //Serial.println("LOW");
  }
}

void handle_download_request(AdafruitIO_Data *data) 
{
  Serial.print("received <- ");
  if(data->toPinLevel() == HIGH)
  {
    Serial.println("Download Request");
    download_file_from_firebase();
    response_feed->save("Downloaded Successfully");
  }
  else
  {
    //Serial.println("LOW");
  }
 // digitalWrite(LED_BUILTIN, data->toPinLevel());
}

void handle_update_app_request(AdafruitIO_Data *data) 
{
  Serial.print("received <- ");
  if(data->toPinLevel() == HIGH)
  {
    Serial.println("Read Request");
    readFile("/new.bin");
    response_feed->save("Read successfully");
  }
  else
  {
    //Serial.println("LOW");
  }
  if(_u16_value_to_send_to_dashboard == 1)
  {
    _string_to_send_to_dashboard = "Update Done";
  }
  else
  {
    _string_to_send_to_dashboard = "Update Faild";
  }
   response_feed->save(_string_to_send_to_dashboard);
}

void handle_get_CID_request(AdafruitIO_Data *data) 
{
  _string_to_send_to_dashboard = ""; /*Clear string to be send*/
  Serial.print("received <- ");
  if(data->toPinLevel() == HIGH)
  {
    Serial.println("Get CID Request");
    Handle_GET_CID_CMD();
    if(_u16_value_to_send_to_dashboard != 0)
    {
      _string_to_send_to_dashboard = "CID : 0x";
      _string_to_send_to_dashboard.concat(String(_u16_value_to_send_to_dashboard,HEX));
      response_feed->save(_string_to_send_to_dashboard);
    }
    else
    {
      response_feed->save(_faild_message);
    }
  }
  else
  {
    //Serial.println("LOW");
  }
}

void handle_flash_erase_request(AdafruitIO_Data *data) 
{
  _string_to_send_to_dashboard = ""; /*Clear string to be send*/
  Serial.print("received <- ");
  if(data->toPinLevel() == HIGH)
  {
    Serial.println("Flash Erase Request");
    Handle_Flash_Erase_CMD(2,4);  /*Erasing from sector (2) to sector (5)*/
    // if(_u16_value_to_send_to_dashboard != 0)
    // {
    //   response_feed->save("Erasing Done");
    // }
    // else
    // {
    //   response_feed->save(_faild_message);
    // }
    response_feed->save("Erasing Done");
  }
  else
  {
    //Serial.println("LOW");
  }
} 

void handle_jump_to_app_request(AdafruitIO_Data *data) 
{
  _string_to_send_to_dashboard = ""; /*Clear string to be send*/
  Serial.print("received <- ");
  if(data->toPinLevel() == HIGH)
  {
    Serial.println("Jump to APP Request");
    Handle_System_Reset_CMD();
    if(_u16_value_to_send_to_dashboard != 0)
    {
      response_feed->save("Done");
    }
    else
    {
      response_feed->save(_faild_message);
    }
  }
  else
  {
    //Serial.println("LOW");
  }
}

void handle_read_protection_level_request(AdafruitIO_Data *data) 
{
  _string_to_send_to_dashboard = ""; /*Clear string to be send*/
  Serial.print("received <- ");
  if(data->toPinLevel() == HIGH)
  {
    Serial.println("Read protection level Request");
    Handle_Read_Protection_Level_CMD();
    if(_u16_value_to_send_to_dashboard != 0)
    {
      if(_u16_value_to_send_to_dashboard == 0xaa)
      {
        _string_to_send_to_dashboard = "Level 0";
      }else if(_u16_value_to_send_to_dashboard == 0xcc)
      {
        _string_to_send_to_dashboard = "Level 2";
      }
      else
      {
        _string_to_send_to_dashboard = "Level 1";
      }
      response_feed->save(_string_to_send_to_dashboard);
    }
    else
    {
      response_feed->save(_faild_message);
    }
  }
  else
  {
    //Serial.println("LOW");
  }
}

/******************************** Bootloader functions *********************************************/
void Handle_GET_VER_CMD()
{
  Send_Get_Ver_CMD(); 
  while(!mySerial.available());
  //Receive_Get_Ver_Response();
  BL_Global_Receive(3);
  /*printing*/
  if(data_buf[0] == BL_ACK)
  {
      Serial.println("ACK"); 
      Serial.print("Length : ");  Serial.println(data_buf[1],HEX);
      Serial.print("Ver : ");     Serial.println(data_buf[2],HEX);
      _u16_value_to_send_to_dashboard = data_buf[2];
  }
  else 
  {
    _u16_value_to_send_to_dashboard =0;
      Serial.println("NACK");
  }
}

void Handle_GET_CID_CMD()
{
  Send_Get_CID_CMD(); 
  while(!mySerial.available());
  //Receive_Get_CID_Response();
  BL_Global_Receive(4);
  /*printing*/
  if(data_buf[0] == BL_ACK)
  {
    Serial.println("ACK"); 
    Serial.print("Length : 0x");  Serial.println(data_buf[1],HEX);
    uint16_t id = (data_buf[3] << 8)|(data_buf[2]);
    Serial.print("CID : 0x");     Serial.println(id,HEX);
    _u16_value_to_send_to_dashboard = id;
  }
  else 
  {
    _u16_value_to_send_to_dashboard =0;
    Serial.println("NACK");
  }
}

void Handle_Read_Protection_Level_CMD()
{
  Send_ReadProtectionLevel_CMD();
  while(!mySerial.available());
  //Receive_ReadProtectionLevel_Response();
  BL_Global_Receive(3);
  /*printing*/
  if(data_buf[0] == BL_ACK)
  {
    Serial.println("ACK"); 
    Serial.print("Length : 0x");  Serial.println(data_buf[1],HEX);
    Serial.print("Protection Level : 0x");   Serial.println(data_buf[2],HEX);
    _u16_value_to_send_to_dashboard = data_buf[2];
  }
  else 
  {
    _u16_value_to_send_to_dashboard = 0;
    Serial.println("NACK");
  }
}

void Handle_Flash_Erase_CMD(uint8_t SectorNumber , uint8_t NumberOfSectors)
{
  Send_Flash_Erase_CMD(SectorNumber,NumberOfSectors);
  while(!mySerial.available());
  //Receive_Flash_Erase_Response();
    BL_Global_Receive(3);
    /*printing*/
      if(data_buf[0] == BL_ACK)
      {
        Serial.println("ACK"); 
        Serial.print("Length : 0x");  Serial.println(data_buf[1],HEX);
        Serial.print("Erasing Status : 0x");   Serial.println(data_buf[2],HEX);
        if(data_buf[2] == ERASING_DONE)
        {
          Serial.println("ERASING DONE");
          _u16_value_to_send_to_dashboard = 1;
        }
        else if(data_buf[2] == ERASING_ERROR)
        {
          Serial.println("ERASING ERROR ");
          _u16_value_to_send_to_dashboard = 0;
        }
      }
      else 
      {
        _u16_value_to_send_to_dashboard = 0;
        Serial.println("NACK");
      }

}

void Handle_Enable_RW_Protect_CMD(uint8_t SectorNumber)
{
  uint8_t local_sectors_details = (1 << SectorNumber);
  Send_Enable_RW_Protect_CMD(local_sectors_details,1);
  while(!mySerial.available());
 // Receive_Enable_RW_Protect_Response();
   BL_Global_Receive(3);
    /*printing*/
    if(data_buf[0] == BL_ACK)
    {
      Serial.println("ACK"); 
      Serial.print("Length : 0x");  Serial.println(data_buf[1],HEX);
      Serial.print("Protect Status : 0x");   Serial.println(data_buf[2],HEX);
      if(data_buf[2] == RET_OK)
      {
        Serial.println("RET OK");
      }
      else if(data_buf[2] == RET_ERROR)
      {
        Serial.println("RET ERROR ");
      }
    }
    else 
    {
      Serial.println("NACK");
    }
}

void Handle_Memory_Write_CMD(uint32_t BaseAddress , uint8_t Length , uint8_t* Data )
{
  Send_MemoryWrite_CMD(BaseAddress , Length, Data );  /*sector 2 base 0x08008000*/
  while(!mySerial.available());
 // Receive_MemoryWrite_Response();
   BL_Global_Receive(3);
    /*printing*/
    if(data_buf[0] == BL_ACK)
    {
      Serial.println("ACK"); 
      Serial.print("Length : 0x");  Serial.println(data_buf[1],HEX);
      Serial.print("Writing Status : 0x");   Serial.println(data_buf[2],HEX);
      if(data_buf[2] == WRITING_SUCCESS)
      {
        _u16_value_to_send_to_dashboard = 1;
        Serial.println("WRITING_SUCCESS");
      }
      else if(data_buf[2] == WRITING_ERROR)
      {
        _u16_value_to_send_to_dashboard =0;
        Serial.println("WRITING_ERROR");
      }
    }
    else 
    {
      _u16_value_to_send_to_dashboard = 0;
      Serial.println("NACK");
    }

}

void Handle_System_Reset_CMD()
{
  Send_SystemReset_CMD();
  while(!mySerial.available());
  //Receive_SystemReset_Response();
  BL_Global_Receive(3);
  /*printing*/
  if(data_buf[0] == BL_ACK)
  {
    Serial.println("ACK"); 
    Serial.print("Length : 0x");           Serial.println(data_buf[1],HEX);
    if(data_buf[2] == RET_OK)
    {
      _u16_value_to_send_to_dashboard = 1;
      Serial.print("Status : RET_OK,");Serial.println("  Reset was Done");
    }
    else if(data_buf[2] == RET_ERROR)
    {
      Serial.println("Status : RET_ERROR");
    }
  }
  else 
  {
    _u16_value_to_send_to_dashboard = 0;
    Serial.println("NACK");
  }

}