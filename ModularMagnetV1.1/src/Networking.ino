void emptyPacketBuffer(){
  for (int i =0; i<eArrSize; i++){
    packetBuffer[i]=0;
  }
}
void cantParse(){
  client.println("up");
}
void parseInput(){
  for (int i =0;client.available()&&i<eArrSize; i++){
    packetBuffer[i]=client.read();
  }
  if (packetBuffer[0]==1){
    if (packetBuffer[1]==1){
      client.write(readings[0]);
    }
    else if (packetBuffer[1]==2){
      client.write(readings[1]);
    }
    else{
      cantParse();
    }
    emptyPacketBuffer();
  }
  else if(packetBuffer[0]==2){
    if (packetBuffer[1]==1){
      if (enableCoil()){
        client.write('s');
      }
      else{
        client.write('f');
      }
    }
    else if (packetBuffer[1]==2){
      disableCoil();
    }
    else{
      cantParse();
    }
    emptyPacketBuffer();
  }
  else{
    cantParse();
  }
  /*************************************
  * MODES:
  * 1: send back full state of each Magnet
  * 2: enable or disable the coil
  *
  * PAYLOADS:
  *   For Mode 1:
  *     1-4 each corner
  *     5 all corners
  *   For Mode 2:
  *     1 enable
  *     2 disable
  **************************************/

}
