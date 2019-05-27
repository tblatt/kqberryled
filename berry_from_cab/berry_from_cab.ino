/**
   BasicHTTPSClient.ino

    Created on: 20.08.2018

*/

#include <Arduino.h>
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

#include <ESP8266HTTPClient.h>

#include <WiFiClientSecureBearSSL.h>


ESP8266WiFiMulti WiFiMulti;

void setup() {


  Serial.begin(115200);
  // Serial.setDebugOutput(true);

  Serial.println();
  Serial.println();
  Serial.println();

  for (uint8_t t = 4; t > 0; t--) {
    Serial.printf("[SETUP] WAIT %d...\n", t);
    Serial.flush();
    delay(1000);
  }

  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP("ToscheStation", "fourwordsalluppercase");
}

void loop() {
  // wait for WiFi connection
  if ((WiFiMulti.run() == WL_CONNECTED)) {

    std::unique_ptr<BearSSL::WiFiClientSecure>client(new BearSSL::WiFiClientSecure);

    client->setFingerprint("b197b3967056d666e1996793cc4da082fc7c452b");

    HTTPClient https;

    Serial.print("[HTTPS] begin...\n");
   // if (https.begin(*client, "https://bmorekq.com/api/current_match/berries")) {  // HTTPS
   if (https.begin(*client, "https://bmorekq.com/api/matches/5/berries")) {  // HTTPS

      Serial.print("[HTTPS] GET...\n");
      // start connection and send HTTP header
      https.setTimeout(15000);
      int httpCode = https.GET();

      // httpCode will be negative on error
      if (httpCode > 0) {
        // HTTP header has been send and Server response header has been handled
        Serial.printf("[HTTPS] GET... code: %d\n", httpCode);
        
        Serial.println(HTTP_CODE_OK);
        
        // file found at server
       
        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
        Serial.println("dude"); 
                  
         //  DynamicJsonDocument jsonBuffer(1024);
       //    deserializeJson(jsonBuffer, https.getString());
       // const char* sensor = jsonBuffer[""];
        //  Serial.println(sensor);
        DynamicJsonBuffer jsonBuffer(500);
        JsonArray& root = jsonBuffer.parseArray(https.getString());
     
      
      int goldBerries = 0;
      int blueBerries = 0;
      int berrytest = 0;
      for (int i = 0; i < root.size(); i++){
     root[i]["playerId"].prettyPrintTo(Serial);
       
       
       int berrytest = root[i]["playerId"];
       Serial.println("size of");
       Serial.println(root.size());
        Serial.println("berrytest");
        Serial.println(berrytest);
        Serial.println(berrytest % 2);
        if (berrytest % 2 == 0){
          blueBerries++;
        }
        else {
          goldBerries++;
        }
        
        Serial.println("Blue Berries");
        Serial.println(blueBerries);
        Serial.println("");
        Serial.println("Gold Berries");
        Serial.println(goldBerries);
        Serial.println("");
      }
      

/*
 * 
 * h
 * 
 * 
 * 
 * 
 */

/* const String json = https.getString();
const size_t capacity = JSON_ARRAY_SIZE(5) + 2*JSON_ARRAY_SIZE(10) + JSON_ARRAY_SIZE(198) + 56*JSON_OBJECT_SIZE(3) + 50*JSON_OBJECT_SIZE(4) + 87*JSON_OBJECT_SIZE(5) + 96*JSON_OBJECT_SIZE(6) + 215*JSON_OBJECT_SIZE(11) + 61000;
DynamicJsonBuffer jsonBuffer(capacity);
JsonObject& root = jsonBuffer.parseObject(json);
int id = root["id"]; // 5
const char* startTime = root["startTime"]; // "2019-02-06T00:57:15.920Z"
const char* endTime = root["endTime"]; // "2019-02-06T00:58:50.017Z"
const char* winCondition = root["winCondition"]; // "military"
const char* winningTeam = root["winningTeam"]; // "blue"
const char* map = root["map"]; // "map_dusk"
const char* events = root["events"]; // "1549414625953 = ![k[spawn],v[4,False]]!\n1549414626756 = ![k[spawn],v[1,False]]!\n1549414626757 = ![k[spawn],v[2,False]]!\n1549414626758 = ![k[playernames],v[,,,,,,,,,]]!\n1549414628115 = ![k[spawn],v[10,False]]!\n1549414629921 = ![k[spawn],v[3,False]]!\n1549414630180 = ![k[spawn],v[5,False]]!\n1549414630235 = ![k[spawn],v[9,False]]!\n1549414635872 = ![k[spawn],v[6,True]]!\n1549414635919 = ![k[spawn],v[7,True]]!\n1549414635920 = ![k[spawn],v[8,True]]!\n1549414635920 = ![k[gamestart],v[map_dusk,False,0,False]]!\n1549414636480 = ![k[carryFood],v[4]]!\n1549414636513 = ![k[blessMaiden],v[310,620,Blue]]!\n1549414636943 = ![k[blessMaiden],v[1610,620,Red]]!\n1549414637321 = ![k[reserveMaiden],v[340,140,4]]!\n1549414637521 = ![k[carryFood],v[3]]!\n1549414638707 = ![k[reserveMaiden],v[1580,140,3]]!\n1549414638832 = ![k[carryFood],v[5]]!\n1549414638898 = ![k[carryFood],v[9]]!\n1549414639209 = ![k[carryFood],v[10]]!\n1549414639368 = ![k[glance],v[9,6]]!\n1549414640091 = ![k[blessMaiden],v[1610,620,Blue]]!\n1549414640290 = ![k[reserveMaiden],v[960,140,9]]!\n1549414640389 = ![k[useMaiden],v[340,140,maiden_speed,4]]!\n1549414640555 = ![k[unreserveMaiden],v[960,140,,9]]!\n1549414640588 = ![k[reserveMaiden],v[310,620,10]]!\n1549414640686 = ![k[reserveMaiden],v[960,140,9]]!\n1549414641092 = ![k[getOnSnail: ],v[960,11,8]]!\n1549414641150 = ![k[carryFood],v[4]]!\n1549414641348 = ![k[carryFood],v[6]]!\n1549414641785 = ![k[useMaiden],v[1580,140,maiden_speed,3]]!\n1549414642182 = ![k[carryFood],v[7]]!\n1549414643217 = ![k[carryFood],v[3]]!\n1549414643645 = ![k[blessMaiden],v[1610,620,Red]]!\n1549414643663 = ![k[useMaiden],v[310,620,maiden_wings,10]]!\n1549414643764 = ![k[useMaiden],v[960,140,maiden_wings,9]]!\n1549414644706 = ![k[getOffSnail: ],v[884,11,,8]]!\n1549414644749 = ![k[playerKill],v[884,11,9,8,Worker]]!\n1549414644839 = ![k[reserveMaiden],v[310,620,4]]!\n1549414645743 = ![k[blessMaiden],v[960,140,Blue]]!\n1549414645811 = ![k[playerKill],v[944,139,2,3,Worker]]!\n1549414646045 = ![k[reserveMaiden],v[1580,140,5]]!\n1549414646078 = ![k[unreserveMaiden],v[1580,140,,5]]!\n1549414646144 = ![k[reserveMaiden],v[1580,140,5]]!\n1549414646968 = ![k[berryDeposit],v[1159,589,7]]!\n1549414647910 = ![k[useMaiden],v[310,620,maiden_wings,4]]!\n1549414648042 = ![k[blessMaiden],v[960,140,Red]]!\n1549414649227 = ![k[useMaiden],v[1580,140,maiden_speed,5]]!\n1549414649512 = ![k[berryDeposit],v[774,743,6]]!\n1549414650653 = ![k[getOnSnail: ],v[884,11,8]]!\n1549414650816 = ![k[carryFood],v[5]]!\n1549414651149 = ![k[playerKill],v[757,981,2,1,Queen]]!\n1549414651361 = ![k[getOffSnail: ],v[869,11,,8]]!\n1549414651362 = ![k[playerKill],v[869,11,9,8,Worker]]!\n1549414652486 = ![k[carryFood],v[3]]!\n1549414653494 = ![k[blessMaiden],v[960,140,Blue]]!\n1549414653627 = ![k[playerKill],v[984,140,2,5,Worker]]!\n1549414654661 = ![k[reserveMaiden],v[1580,140,3]]!\n1549414655134 = ![k[playerKill],v[835,69,2,9,Soldier]]!\n1549414655468 = ![k[carryFood],v[7]]!\n1549414655670 = ![k[glance],v[10,7]]!\n1549414655957 = ![k[carryFood],v[6]]!\n1549414657295 = ![k[getOnSnail: ],v[869,11,8]]!\n1549414657704 = ![k[useMaiden],v[1580,140,maiden_speed,3]]!\n1549414658364 = ![k[blessMaiden],v[340,140,Blue]]!\n1549414658681 = ![k[glance],v[6,1]]!\n1549414658847 = ![k[carryFood],v[3]]!\n1549414658878 = ![k[carryFood],v[5]]!\n1549414659861 = ![k[playerKill],v[633,375,10,7,Worker]]!\n1549414659928 = ![k[reserveMaiden],v[1580,140,5]]!\n1549414661653 = ![k[snailEat],v[778,11,8,9]]!\n1549414662993 = ![k[useMaiden],v[1580,140,maiden_speed,5]]!\n1549414664149 = ![k[carryFood],v[5]]!\n1549414664627 = ![k[snailEscape],v[728,11,9]]!\n1549414664669 = ![k[getOffSnail: ],v[778,11,,8]]!\n1549414664670 = ![k[playerKill],v[778,11,1,8,Worker]]!\n1549414665469 = ![k[berryDeposit],v[730,711,6]]!\n1549414665501 = ![k[playerKill],v[1125,24,4,5,Worker]]!\n1549414666014 = ![k[carryFood],v[9]]!\n1549414666312 = ![k[blessMaiden],v[340,140,Red]]!\n1549414667338 = ![k[carryFood],v[7]]!\n1549414667920 = ![k[playerKill],v[1478,62,10,7,Worker]]!\n1549414669021 = ![k[blessMaiden],v[310,620,Red]]!\n1549414669173 = ![k[carryFood],v[6]]!\n1549414669355 = ![k[glance],v[6,9]]!\n1549414669764 = ![k[blessMaiden],v[1610,620,Blue]]!\n1549414670029 = ![k[getOnSnail: ],v[778,11,6]]!\n1549414670665 = ![k[snailEat],v[765,11,6,5]]!\n1549414670666 = ![k[glance],v[5,6]]!\n1549414671942 = ![k[glance],v[1,2]]!\n1549414672039 = ![k[carryFood],v[7]]!\n1549414672758 = ![k[playerKill],v[963,140,10,9,Worker]]!\n1549414673528 = ![k[reserveMaiden],v[310,620,3]]!\n1549414674160 = ![k[playerKill],v[780,20,6,5,Worker]]!\n1549414675406 = ![k[berryDeposit],v[1127,639,7]]!\n1549414676605 = ![k[useMaiden],v[310,620,maiden_wings,3]]!\n1549414678956 = ![k[carryFood],v[8]]!\n1549414679364 = ![k[playerKill],v[36,538,1,10,Soldier]]!\n1549414679695 = ![k[carryFood],v[9]]!\n1549414679763 = ![k[playerKill],v[525,996,2,3,Soldier]]!\n1549414680191 = ![k[carryFood],v[7]]!\n1549414681141 = ![k[blessMaiden],v[310,620,Blue]]!\n1549414682144 = ![k[getOffSnail: ],v[608,11,,6]]!\n1549414682145 = ![k[playerKill],v[608,11,1,6,Worker]]!\n1549414682259 = ![k[playerKill],v[614,73,1,8,Worker]]!\n1549414682462 = ![k[playerKill],v[1342,380,4,7,Worker]]!\n1549414683621 = ![k[carryFood],v[3]]!\n1549414683689 = ![k[blessMaiden],v[960,140,Red]]!\n1549414683986 = ![k[carryFood],v[5]]!\n1549414684335 = ![k[getOnSnail: ],v[608,11,9]]!\n1549414684611 = ![k[reserveMaiden],v[1580,140,3]]!\n1549414685078 = ![k[blessMaiden],v[340,140,Blue]]!\n1549414687452 = ![k[glance],v[5,6]]!\n1549414687658 = ![k[useMaiden],v[1580,140,maiden_speed,3]]!\n1549414688399 = ![k[blessMaiden],v[960,140,Blue]]!\n1549414688400 = ![k[glance],v[8,5]]!\n1549414688430 = ![k[blessMaiden],v[1610,620,Red]]!\n1549414688803 = ![k[carryFood],v[10]]!\n1549414689071 = ![k[carryFood],v[3]]!\n1549414689452 = ![k[getOffSnail: ],v[697,11,,9]]!\n1549414689549 = ![k[glance],v[2,9]]!\n1549414689907 = ![k[getOnSnail: ],v[697,11,8]]!\n1549414690274 = ![k[carryFood],v[6]]!\n1549414690355 = ![k[snailEat],v[688,11,8,9]]!\n1549414690540 = ![k[carryFood],v[7]]!\n1549414690880 = ![k[blessMaiden],v[1580,140,Red]]!\n1549414692065 = ![k[glance],v[3,8]]!\n1549414692464 = ![k[glance],v[5,4]]!\n1549414692465 = ![k[playerKill],v[595,20,2,3,Worker]]!\n1549414693459 = ![k[berryDeposit],v[857,641,10]]!\n1549414693824 = ![k[playerKill],v[614,20,8,9,Worker]]!\n1549414694802 = ![k[berryDeposit],v[1093,642,7]]!\n1549414695724 = ![k[reserveMaiden],v[1580,140,5]]!\n1549414695890 = ![k[berryDeposit],v[762,589,6]]!\n1549414697334 = ![k[blessMaiden],v[960,140,Red]]!\n1549414698037 = ![k[carryFood],v[3]]!\n1549414698788 = ![k[useMaiden],v[1580,140,maiden_speed,5]]!\n1549414699811 = ![k[carryFood],v[10]]!\n1549414700075 = ![k[playerKill],v[1086,260,4,9,Worker]]!\n1549414700141 = ![k[carryFood],v[5]]!\n1549414700274 = ![k[glance],v[3,10]]!\n1549414700570 = ![k[blessMaiden],v[960,140,Blue]]!\n1549414701218 = ![k[carryFood],v[7]]!\n1549414702117 = ![k[glance],v[3,6]]!\n1549414702247 = ![k[playerKill],v[932,164,2,3,Worker]]!\n1549414702466 = ![k[glance],v[5,8]]!\n1549414702522 = ![k[snailEat],v[518,11,8,5]]!\n1549414703263 = ![k[carryFood],v[6]]!\n1549414705559 = ![k[reserveMaiden],v[340,140,10]]!\n1549414705971 = ![k[playerKill],v[469,54,8,5,Worker]]!\n1549414706696 = ![k[berryDeposit],v[1080,599,7]]!\n1549414706770 = ![k[carryFood],v[9]]!\n1549414708554 = ![k[blessMaiden],v[1610,620,Blue]]!\n1549414708653 = ![k[useMaiden],v[340,140,maiden_speed,10]]!\n1549414708752 = ![k[carryFood],v[3]]!\n1549414709180 = ![k[blessMaiden],v[310,620,Red]]!\n1549414709311 = ![k[playerKill],v[340,630,1,6,Worker]]!\n1549414709759 = ![k[carryFood],v[10]]!\n1549414711315 = ![k[blessMaiden],v[310,620,Blue]]!\n1549414711712 = ![k[blessMaiden],v[340,140,Red]]!\n1549414712972 = ![k[carryFood],v[7]]!\n1549414713304 = ![k[getOffSnail: ],v[374,11,,8]]!\n1549414713306 = ![k[playerKill],v[374,11,1,8,Worker]]!\n1549414713567 = ![k[blessMaiden],v[340,140,Blue]]!\n1549414715457 = ![k[playerKill],v[580,128,2,1,Queen]]!\n1549414715611 = ![k[carryFood],v[5]]!\n1549414716439 = ![k[getOnSnail: ],v[374,11,9]]!\n1549414716565 = ![k[glance],v[5,6]]!\n1549414716638 = ![k[carryFood],v[6]]!\n1549414717001 = ![k[reserveMaiden],v[310,620,10]]!\n1549414717002 = ![k[getOffSnail: ],v[383,11,,9]]!\n1549414717003 = ![k[playerKill],v[383,11,2,9,Worker]]!\n1549414719603 = ![k[blessMaiden],v[960,140,Red]]!\n1549414720070 = ![k[useMaiden],v[310,620,maiden_wings,10]]!\n1549414720593 = ![k[getOnSnail: ],v[383,11,5]]!\n1549414720627 = ![k[glance],v[4,7]]!\n1549414721222 = ![k[snailEat],v[388,11,5,8]]!\n1549414721792 = ![k[blessMaiden],v[960,140,Blue]]!\n1549414722353 = ![k[carryFood],v[9]]!\n1549414722933 = ![k[blessMaiden],v[1610,620,Red]]!\n1549414723031 = ![k[reserveMaiden],v[1580,140,3]]!\n1549414723640 = ![k[snailEscape],v[438,11,8]]!\n1549414723642 = ![k[getOffSnail: ],v[388,11,,5]]!\n1549414723642 = ![k[playerKill],v[388,11,10,5,Worker]]!\n1549414723728 = ![k[berryDeposit],v[1050,642,7]]!\n1549414724354 = ![k[carryFood],v[8]]!\n1549414724554 = ![k[getOnSnail: ],v[388,11,8]]!\n1549414724954 = ![k[playerKill],v[1067,282,4,9,Worker]]!\n1549414726104 = ![k[useMaiden],v[1580,140,maiden_speed,3]]!\n1549414727487 = ![k[carryFood],v[3]]!\n1549414727660 = ![k[berryDeposit],v[869,707,6]]!\n1549414728741 = ![k[blessMaiden],v[1610,620,Blue]]!\n1549414728773 = ![k[playerKill],v[1445,777,1,4,Soldier]]!\n1549414729193 = ![k[carryFood],v[5]]!\n1549414729281 = ![k[snailEat],v[290,11,8,3]]!\n1549414730012 = ![k[playerKill],v[1685,930,2,1,Queen]]!\n1549414730017 = ![k[gameend],v[map_dusk,False,94.25678,False]]!\n1549414730017 = ![k[victory],v[Blue,military]]!\n"
JsonObject& data = root["data"];
const char* data_map = data["map"]; // "map_dusk"
int data_snail = data["snail"]; // 960
JsonArray& data_events = data["events"];

root["data"].prettyPrintTo(Serial);

*/

        
        }
      } else {
        Serial.printf("[HTTPS] GET... failed, error: %s\n", https.errorToString(httpCode).c_str());
      }

      https.end();
    } else {
      Serial.printf("[HTTPS] Unable to connect\n");
    }
  }

  Serial.println("Wait 10s before next round...");
  delay(10000);
}
