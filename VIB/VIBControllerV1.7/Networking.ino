void networkHandler(int x){
  int8_t temp=x;
  if (trellis.isLED(x)){
    bitWrite(temp,7,1);
  }
  client.write(temp);
  Serial.println("sending");
}






















//void ethernetHandler() {
//  // if there's data available, read a packet
//  int packetSize = Udp.parsePacket();
//  remoteClient = server.available();
//  if (remoteClient) {
//    host();
//  }
//  if (packetSize) {
//    udpSender(4);
//  }
//}
//
//void host() {
//  Serial.println("new remoteClient");
//  // an http request ends with a blank line
//  boolean currentLineIsBlank = true;
//  while (remoteClient.connected()) {
//    if (remoteClient.available()) {
//      char c = remoteClient.read();
//      Serial.write(c);
//      // if you've gotten to the end of the line (received a newline
//      // character) and the line is blank, the http request has ended,
//      // so you can send a reply
//      if (c == '\n' && currentLineIsBlank) {
//        // send a standard http response header
//        remoteClient.println("HTTP/1.1 200 OK");
//        remoteClient.println("Content-Type: text/html");
//        remoteClient.println("Connection: close");  // the connection will be closed after completion of the response
//        remoteClient.println("Refresh: 5");  // refresh the page automatically every 5 sec
//        remoteClient.println();
//        remoteClient.println("<!DOCTYPE HTML>");
//        remoteClient.println("<html>");
//
//        String oneRow = "";
//        remoteClient.print("For main vib: ");
//        for (int i = 0; i < 8; i++) {
//          for (int j = 0; j < 8; j++) {
//            oneRow += mainV[i][j];
//            if (mainV[i][j])
//              oneRow += ",  ";
//            else {
//              oneRow += ", ";
//            }
//          }
//
//          remoteClient.println("<br />");
//          remoteClient.print(oneRow);
//        }
//        remoteClient.println("<br />");
//        remoteClient.println("</html>");
//        break;
//      }
//      if (c == '\n') {
//        // you're starting a new line
//        currentLineIsBlank = true;
//      } else if (c != '\r') {
//        // you've gotten a character on the current line
//        currentLineIsBlank = false;
//      }
//    }
//  }
//  // give the web browser time to receive the data
//  delay(1);
//}
//
//void arrConverterM(boolean x[],  int howBig){
//  for (int i =0; i<howBig; i++){
//    replyBuffer[i]=(char)((int)x[i]+48);
//  }
//  if (howBig<mainVD){
//    for (int j = focusD; j<mainVD; j++){
//      replyBuffer[j]=32;
//    }
//  }
//}



