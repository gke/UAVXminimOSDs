
#define ASCII_NUL 0
#define ASCII_SOH 1
#define ASCII_EOT 4
#define ASCII_ACK 6
#define ASCII_HT 9
#define ASCII_LF 10
#define ASCII_CR 13
#define ASCII_NAK 21
#define ASCII_ESC 27

static uint8_t crlf_count = 0;

static int packet_drops = 0;
static int parse_error = 0;
boolean telemetry_active = false;

enum PacketTags {
  UnknownPacketTag = 0,
  LevPacketTag,
  NavPacketTag,
  MicropilotPacketTag,
  WayPacketTag,
  AirframePacketTag,
  NavUpdatePacketTag,
  BasicPacketTag,
  RestartPacketTag,
  TrimblePacketTag,
  MessagePacketTag,
  EnvironmentPacketTag,
  BeaconPacketTag,

  UAVXFlightPacketTag,
  UAVXNavPacketTag,
  UAVXStatsPacketTag,
  UAVXControlPacketTag,
  UAVXParamPacketTag,
  UAVXMinPacketTag,
  UAVXOriginPacketTag,
  UAVXWPPacketTag,
  UAVXMissionPacketTag,
  UAVXRCChannelsPacketTag,

  UAVXRequestPacketTag = 50,
  UAVXAckPacketTag = 51,
  UAVXMiscPacketTag = 52,
  UAVXDFTPacketTag = 53,
  UAVXBBPacketTag = 54,
  UAVXInertialPacketTag = 55,
  UAVXMinimOSDPacketTag = 56,

  FrSkyPacketTag = 99
};

enum RxPacketStates {
  WaitRxSentinel,
  WaitRxBody,
  WaitRxESC,
  WaitRxCheck,
  WaitRxCopy,
  WaitUPTag,
  WaitUPLength,
  WaitUPBody,
  WaitRxTag
};

uint8_t nav_state, airframe_type;

uint8_t ReceivedPacketTag, RxPacketTag, PacketRxState, RxPacketLength,
RxPacketByteCount, RxCheckSum;
boolean PacketReceived, RxPacketError, CheckSumError, TelemetryActive;
uint8_t UAVXPacket[256];

uint16_t RxCheckSumErrors = 0;

inline uint8_t UAVXPacketu8(uint8_t p) {
  return UAVXPacket[p];
} // UAVXPacketu8

inline int16_t UAVXPacketi8(uint8_t p) {
  int16_t temp;

  temp = (int8_t) UAVXPacket[p];
  //if (temp > 127)
  //	temp -= 256;

  return temp;
} // UAVXPacketi8

int16_t UAVXPacketi16(uint8_t p) {
  int16_t temp;

  temp = (int16_t) (UAVXPacket[p + 1] << 8);
  temp |= (int16_t) UAVXPacket[p];

  return temp;
} // UAVXPacketi16

int32_t UAVXPacketi24(uint8_t p) {
  int32_t temp;

  temp = ((int32_t) UAVXPacket[p + 2] << 24);
  temp |= ((int32_t) UAVXPacket[p + 1] << 16);
  temp |= (int32_t) UAVXPacket[p] << 8;
  temp /= 256;
  return temp;
} // UAVXPacketi24

int32_t UAVXPacketi32(uint8_t p) {
  int32_t temp;

  temp = (int32_t) (UAVXPacket[p + 3] << 24);
  temp |= ((int32_t) UAVXPacket[p + 2] << 16);
  temp |= ((int32_t) UAVXPacket[p + 1] << 8);
  temp |= (int32_t) UAVXPacket[p];
  return temp;
} // UAVXPacketi32


void InitPollRxPacket() {

  RxPacketByteCount = 0;
  RxCheckSum = 0;

  RxPacketTag = UnknownPacketTag;

  RxPacketLength = 2; // set as minimum
  PacketRxState = WaitRxSentinel;
} // InitRxPollPacket

void AddToRxPacketBuffer(uint8_t ch) {
  boolean RxPacketError;

  UAVXPacket[RxPacketByteCount++] = ch;
  if (RxPacketByteCount == 1) {
    RxPacketTag = ch;
    PacketRxState = WaitRxBody;
  } 
  else if (RxPacketByteCount == 2) {
    RxPacketLength = ch;
    PacketRxState = WaitRxBody;
  } 
  else if (RxPacketByteCount >= (RxPacketLength + 3)) {
    RxPacketError = CheckSumError = !((RxCheckSum == 0) || (RxCheckSum
      == ASCII_ESC));

    if (CheckSumError)
      parse_error++;

    if (!RxPacketError) {
      PacketReceived = true;
      ReceivedPacketTag = RxPacketTag;
    }
    PacketRxState = WaitRxSentinel;
    //   InitPollPacket();
  } 
  else
    PacketRxState = WaitRxBody;
} // AddToRxPacketBuffer

void ParseRxPacket(uint8_t ch) {

  RxCheckSum ^= ch;
  switch (PacketRxState) {
  case WaitRxSentinel:
    if (ch == ASCII_SOH) {
      InitPollRxPacket();
      CheckSumError = false;
      PacketRxState = WaitRxBody;
    }
    break;
  case WaitRxBody:
    if (ch == ASCII_ESC)
      PacketRxState = WaitRxESC;
    else if (ch == ASCII_SOH) // unexpected start of packet
    {
      parse_error++;

      InitPollRxPacket();
      PacketRxState = WaitRxBody;
    } 
    else if (ch == ASCII_EOT) // unexpected end of packet
    {
      packet_drops++;
      PacketRxState = WaitRxSentinel;
    } 
    else
      AddToRxPacketBuffer(ch);
    break;
  case WaitRxESC:
    AddToRxPacketBuffer(ch);
    break;
  default:
    PacketRxState = WaitRxSentinel;
    break;
  }
} // ParseRxPacket


void ProcessPacket() {
  byte b, c;
  uint16_t i;

  PacketReceived = false;
  TelemetryActive = true;

  switch (RxPacketTag) {
  case UAVXMinimOSDPacketTag:

    osd_vbat_A = UAVXPacketi16(2);
    osd_curr_A = UAVXPacketi16(4);
    osd_battery_remaining_A = UAVXPacketi16(6);

    osd_roll = UAVXPacketi16(8);
    osd_pitch = UAVXPacketi16(10);

    osd_alt_rel = UAVXPacketi24(12);
    osd_climb = UAVXPacketi16(15);

    osd_groundspeed = UAVXPacketi16(17);

    osd_heading = UAVXPacketi16(19);
    osd_lat = UAVXPacketi32(21) * 1e-7;
    osd_lon = UAVXPacketi32(25) * 1e-7;

    osd_satellites_visible = UAVXPacketu8(29);
    osd_fix_type =  UAVXPacketu8(30);

    wp_number =  UAVXPacketu8(31);
    wp_target_bearing = UAVXPacketi16(32);
    wp_dist = UAVXPacketi16(34);
    xtrack_error = UAVXPacketi16(36); 

    motor_armed =  UAVXPacketu8(38);
    osd_throttle = UAVXPacketi16(39);

    airframe_type = UAVXPacketi16(41);
    nav_state = UAVXPacketi16(42);
    break;

  case UAVXRCChannelsPacketTag:    
    chan5_raw = UAVXPacketi16(10); 
    chan6_raw = UAVXPacketi16(12);
    chan7_raw = UAVXPacketi16(14);
    chan8_raw = UAVXPacketi16(16);
    break;
  default: 
    break;
  } // switch
}

void read_uavxlink() {
  uint8_t c;

  while (Serial.available() > 0) {

    c = Serial.read();

    /* allow CLI to be started by hitting enter 3 times, if no
     heartbeat packets have been received */
    if (!telemetry_active && millis() < 20000 && millis() > 5000) {
      if (c == '\n' || c == '\r')
        crlf_count++;
      else
        crlf_count = 0;

      if (crlf_count == 3)
        uploadFont();
    }

    ParseRxPacket(c);
    if (PacketReceived) {
      telemetry_active = true;
      ProcessPacket();

      osd_nav_mode = 0;
      osd_cog = 0;
      eph = 0;
      //osd_airspeed = 0;
      //wp_dist = 0;
      osd_rssi = 0;
      osd_winddirection = 0;
      osd_windspeed = 0;
      temperature = 20;

      delayMicroseconds(138);
    }
  }
} // read_uavxlink





