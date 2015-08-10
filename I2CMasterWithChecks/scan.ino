
//checks status of a node
int scanStatus(uint8_t target)
{
    switch(Wire.status())
    {
    case I2C_WAITING:
        return 0;
        break;
    case I2C_ADDR_NAK:
        return 1;
        break;
    default:
        break;
    }
    return 2;
}

//scans all nodes to see if any have died.
void comboBreaker(){

  for(uint8_t target = 1; target <= 5; target++){
    Wire.beginTransmission(target);       // slave addr
    Wire.endTransmission();               // no data, just addr
    if (scanStatus(target)==1){
      digitalWrite(target, HIGH);
      Wire.resetBus();
    }
    
  }
}
