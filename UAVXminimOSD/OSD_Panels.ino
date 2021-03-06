
/******* STARTUP PANEL *******/

void startPanels() {  
  do_converts(); // load the unit conversion preferences
}

/******* PANELS - POSITION *******/

void writePanels() {
#if defined(DEBUG)

  osd_roll = 10;




#else
  if ((takeofftime == 1) && (osd_alt_to_home > 10 || osd_groundspeed > 1
    || osd_throttle > 1 || osd_home_distance > 100))
    landed = millis();

  //Base panel selection
  //No mavlink data available panel
  if (millis() > (lastMAVBeat + 2200)) {
    if (currentBasePanel != 2) {
      osd.clear();
      currentBasePanel = 2;
    }
    panWaitMAVBeats(5, 10); //Waiting for MAVBeats...
  }
  else if ((millis() - 7000) > landed) { 
    if (currentBasePanel != 1) {
      osd.clear();
      currentBasePanel = 1;
    }
    panFdata(); // flight summary
  }
  //Normal osd panel
  else 
#endif
  {
    if (ISd(0, Warn_BIT))
      panWarn(panWarn_XY[0][0], panWarn_XY[1][0]); // this must be here so warnings are always checked
    //Check for panel toggle
    if (ch_toggle > 3)
      panOff(); // This must be first so you can always toggle
    if ((osd_clear) || (currentBasePanel != 0)) {
      osd.clear();
      osd_clear = 0;
      currentBasePanel = 0;
    }
    if (panel != npanels) {
      //Testing bits from 8 bit register A 
      //if(ISa(panel,Cen_BIT)) panCenter(panCenter_XY[0][panel], panCenter_XY[1][panel]);   //4x2
      //if(ISd(panel,Warn_BIT)) panWarn(panWarn_XY[0][panel], panWarn_XY[1][panel]); // this must be here so warnings are always checked
      if (ISa(panel, Pit_BIT))
        panPitch(panPitch_XY[0][panel], panPitch_XY[1][panel]); //5x1
      if (ISa(panel, Rol_BIT))
        panRoll(panRoll_XY[0][panel], panRoll_XY[1][panel]); //5x1
      if (ISa(panel, BatA_BIT))
        panBatt_A(panBatt_A_XY[0][panel], panBatt_A_XY[1][panel]); //7x1
      //if(ISa(panel,BatB_BIT)) panBatt_B(panBatt_B_XY[0], panBatt_B_XY[1][panel]); //7x1
      if (ISa(panel, GPSats_BIT))
        panGPSats(panGPSats_XY[0][panel], panGPSats_XY[1][panel]); //5x1
      if (ISa(panel, GPS_BIT))
        panGPS(panGPS_XY[0][panel], panGPS_XY[1][panel]); //12x3
      if (ISa(panel, Bp_BIT))
        panBatteryPercent(panBatteryPercent_XY[0][panel],
        panBatteryPercent_XY[1][panel]); //
      if (ISa(panel, COG_BIT))
        panCOG(panCOG_XY[0][panel], panCOG_XY[1][panel]); //

      //Testing bits from 8 bit register B
      if (ISb(panel, Rose_BIT))
        panRose(panRose_XY[0][panel], panRose_XY[1][panel]); //13x3
      if (ISb(panel, Head_BIT))
        panHeading(panHeading_XY[0][panel], panHeading_XY[1][panel]); //13x3
      //if(ISb(panel,MavB_BIT)) panMavBeat(panMavBeat_XY[0][panel], panMavBeat_XY[1][panel]); //13x3

      if (osd_got_home) {
        if (ISb(panel, HDis_BIT))
          panHomeDis(panHomeDis_XY[0][panel], panHomeDis_XY[1][panel]); //13x3
        if (ISb(panel, HDir_BIT))
          panHomeDir(panHomeDir_XY[0][panel], panHomeDir_XY[1][panel]); //13x3
      }

      if (ISb(panel, Time_BIT))
        panTime(panTime_XY[0][panel], panTime_XY[1][panel]);
      //if(ISb(panel,WDir_BIT)) panWPDir(panWPDir_XY[0][panel], panWPDir_XY[1][panel]); //??x??
      if (wp_number > 0) {
        if (ISb(panel, WDis_BIT))
          panWPDis(panWPDis_XY[0][panel], panWPDis_XY[1][panel]); //??x??
      }
      //Testing bits from 8 bit register C 
      if (ISc(panel, Alt_BIT))
        panAlt(panAlt_XY[0][panel], panAlt_XY[1][panel]); //
      if (ISc(panel, Halt_BIT))
        panHomeAlt(panHomeAlt_XY[0][panel], panHomeAlt_XY[1][panel]); //
      if (ISc(panel, Vel_BIT))
        panVel(panVel_XY[0][panel], panVel_XY[1][panel]); //
      if (ISc(panel, As_BIT))
        panAirSpeed(panAirSpeed_XY[0][panel], panAirSpeed_XY[1][panel]); //

      if (ISc(panel, Thr_BIT))
        panThr(panThr_XY[0][panel], panThr_XY[1][panel]); //
      if (ISc(panel, FMod_BIT))
        panFlightMode(panFMod_XY[0][panel], panFMod_XY[1][panel]); //
      if (ISc(panel, Hor_BIT))
        panHorizon(panHorizon_XY[0][panel], panHorizon_XY[1][panel]); //14x5
      if (ISc(panel, CurA_BIT))
        panCur_A(panCur_A_XY[0][panel], panCur_A_XY[1][panel]);

      //Testing bits from 8 bit register D 
      if (ISd(panel, WindS_BIT))
        panWindSpeed(panWindSpeed_XY[0][panel],
        panWindSpeed_XY[1][panel]);
      if (ISd(panel, Climb_BIT))
        panClimb(panClimb_XY[0][panel], panClimb_XY[1][panel]);
      if (ISd(panel, Tune_BIT))
        panTune(panTune_XY[0][panel], panTune_XY[1][panel]);
      if (ISd(panel, RSSI_BIT))
        panRSSI(panRSSI_XY[0][panel], panRSSI_XY[1][panel]); //??x??
      if (ISd(panel, Eff_BIT))
        panEff(panEff_XY[0][panel], panEff_XY[1][panel]);
      if (ISd(panel, CALLSIGN_BIT))
        panCALLSIGN(panCALLSIGN_XY[0][panel], panCALLSIGN_XY[1][panel]);
      if (ISe(panel, TEMP_BIT))
        panTemp(panTemp_XY[0][panel], panTemp_XY[1][panel]);
      //if(ISe(panel,Ch_BIT)) panCh(panCh_XY[0][panel], panCh_XY[1][panel]);
      if (ISe(panel, DIST_BIT))
        panDistance(panDistance_XY[0][panel], panDistance_XY[1][panel]);
    }
  }
  if (ISd(0, CALLSIGN_BIT))
    panCALLSIGN(panCALLSIGN_XY[0][panel], panCALLSIGN_XY[1][panel]); //call sign even in off panel
  timers();
  // OSD debug for development (Shown on top-middle panels) 
#ifdef membug
  osd.setPanel(13,4);
  osd.openPanel();
  osd.printf("%i",freeMem());
  osd.closePanel();
#endif

}
/******* PANELS - DEFINITION *******/

/* **************************************************************** */

// Panel  : COG Course Over Ground
// Needs  : X, Y locations
// Output : 
// Size   : 
// Staus  : done


void panCOG(int first_col, int first_line) {
  osd.setPanel(first_col, first_line);
  osd.openPanel();

  //    osd_COG_arrow_rotate_int = (((int)osd_cog / 100 - (int)osd_heading)/360 * 16 + 16) % 16 + 1; // [1, 16]
  //    osd_COG_arrow_rotate_int = (osd_cog / 100 - osd_heading) / 360 * 16 + 1;
  osd_COG_arrow_rotate_int = round(((osd_cog / 100) - osd_heading) / 360.0
    * 16.0 + 1); //Convert to int 1-16 
  if (osd_COG_arrow_rotate_int < 1)
    osd_COG_arrow_rotate_int += 16;
  //    if(osd_COG_arrow_rotate_int == 0) osd_COG_arrow_rotate_int = 16;    
  else if (osd_COG_arrow_rotate_int > 16)
    osd_COG_arrow_rotate_int -= 16;

  off_course = ((osd_cog / 100) - osd_heading);
  if (off_course > 180)
    off_course -= 360;
  else if (off_course < -180)
    off_course += 360;

  showArrow((uint8_t) osd_COG_arrow_rotate_int, 2);

  osd.closePanel();
}

/* **************************************************************** */
// Panel  : panDistance
// Needs  : X, Y locations
// Output : 
// Size   : 1 x 7Hea  (rows x chars)
// Staus  : done

void panDistance(int first_col, int first_line) {
  osd.setPanel(first_col, first_line);
  osd.openPanel();
  //do_converts();
  if ((tdistance * converth) > 9999.0)
    osd.printf("%c%5.2f%c", 0x8f, ((tdistance * converth) / distconv),
    distchar);
  else
    osd.printf("%c%5.0f%c", 0x8f, (tdistance * converth), high);

  osd.closePanel();
}

/* **************************************************************** */
// Panel  : panFdata
// Needs  : X, Y locations
// Output : 
// Size   : 
// Staus  : done
void panFdata() {
  osd.setPanel(11, 3);
  osd.openPanel();
  osd.printf(
  "%c%3i%c%02i|%c%5.0f%c|%c%5.0f%c|%c%5i%c|%c%5i%c|%c%5i%c|%c%5i%c|%c%5.0f%c|%c%11.6f|%c%11.6f",
  0x08, ((int) (start_Time / 60)), 0x3A, (int) start_Time % 60, 0x0b,
  ((max_home_distance) * converth), high, 0x8f,
  (tdistance * converth), high, 0x13, (int) (max_osd_airspeed
    * converts), spe, 0x14, (int) (max_osd_groundspeed
    * converts), spe, 0x12,
  (int) (max_osd_home_alt * converth), high, 0x1d,
  (int) (max_osd_windspeed * converts), spe, 0x17, mah_used, 0x01,
  0x03, (double) osd_lat, 0x04, (double) osd_lon);
  osd.closePanel();
}

/* **************************************************************** */
// Panel  : pantemp
// Needs  : X, Y locations
// Output : 
// Size   : 1 x 7Hea  (rows x chars)
// Staus  : done

void panTemp(int first_col, int first_line) {
  osd.setPanel(first_col, first_line);
  osd.openPanel();
  osd.printf("%5.1f%c", (float(temperature * tempconv + tempconvAdd) / 1000), temps);
  osd.closePanel();
}

/* **************************************************************** */
// Panel  : efficiency
// Needs  : X, Y locations
// Output : 
// Size   : 1 x 7Hea  (rows x chars)
// Staus  : done

void panEff(int first_col, int first_line) {
  osd.setPanel(first_col, first_line);
  osd.openPanel();
  if (osd_throttle >= 1) {
    if (!ma)
      ma = true;

    if (osd_groundspeed != 0) eff = (float(osd_curr_A * 10.0) / 
    (osd_groundspeed * converts))* 0.1 + eff * 0.9;
    if (eff > 0 && eff <= 9999)
      osd.printf("%c%4.0f%c", 0x16, eff, 0x01);
    else
      osd.printf_P(PSTR("\x16\x20\x20\x20\x20\x20"));
  } 
  else {

    if ((osd_throttle < 1)) {
      if (ma) {
        palt = osd_alt_to_home;
        //              descendt = millis();
        ddistance = tdistance;
        ma = false;
      }
    }
    if (osd_climb < -0.05) {
      //            glide = ((osd_alt_to_home / (palt - osd_alt_to_home)) * ((millis() - descendt) / 1000)) * osd_groundspeed;
      glide = ((osd_alt_to_home / (palt - osd_alt_to_home)) * (tdistance
        - ddistance)) * converth;
      if (glide > 9999)
        glide = 9999;
      if (glide != 'inf' && glide > -0)
        osd.printf("%c%4.0f%c", 0x18, glide, high);
    } 
    else if (osd_climb >= -0.05 && osd_pitch < 0)
      osd.printf_P(PSTR("\x18\x20\x20\x90\x91\x20"));
    else
      osd.printf_P(PSTR("\x18\x20\x20\x20\x20\x20"));

  }
  osd.closePanel();
}

/* **************************************************************** */
// Panel  : panRSSI
// Needs  : X, Y locations
// Output : Alt symbol and altitude value in meters from MAVLink
// Size   : 1 x 7Hea  (rows x chars)
// Staus  : done

void panRSSI(int first_col, int first_line) {
  osd.setPanel(first_col, first_line);
  osd.openPanel();

  if ((rssiraw_on % 2 == 0)) {
    if (osd_rssi < rssipersent)
      osd_rssi = rssipersent;
    if (osd_rssi > rssical)
      osd_rssi = rssical;
    if (rssiraw_on == 0)
      rssi = (int16_t)((float) ((int16_t) osd_rssi - rssipersent)
        / (float) (rssical - rssipersent) * 100.0f);
    if (rssiraw_on == 8)
      rssi = (int16_t)((float) (chan_raw[8] / 10 - rssipersent)
        / (float) (rssical - rssipersent) * 100.0f);
  }
  if (rssiraw_on == 1)
    rssi = (int16_t) osd_rssi;
  if (rssiraw_on == 9)
    rssi = chan_raw[8];

  if (rssi > 100.0)
    rssi = 100;

  osd.printf("%c%3i%c", 0x09, rssi, 0x25);
  osd.closePanel();
}

/* **************************************************************** */
// Panel  : panCALLSIGN
// Needs  : X, Y locations
// Output : Call sign identification
// Size   : 1 x 6Hea  (rows x chars)
// Staus  : done

void panCALLSIGN(int first_col, int first_line) {
  osd.setPanel(first_col, first_line);
  osd.openPanel();
  if (((millis() / 1000) % 60) < 2)
    osd.printf("%s", char_call);
  else
    osd.printf("%s", strclear);
  osd.closePanel();
}


/* **************************************************************** */
// Panel  : pan wind speed
// Needs  : X, Y locations
// Output : Wind direction symbol (arrow) and velocity
// Size   : 1 x 7  (rows x chars)
// Staus  : done

void panWindSpeed(int first_col, int first_line) {
  osd.setPanel(first_col, first_line);
  osd.openPanel();

  if (osd_winddirection < 0)
    osd_wind_arrow_rotate_int = round(((osd_winddirection + 360)
      - osd_heading) / 360.0 * 16.0) + 9; //Convert to int 1-16
  else
    osd_wind_arrow_rotate_int = round((osd_winddirection - osd_heading)
      / 360.0 * 16.0) + 9; //Convert to int 1-16

  if (osd_wind_arrow_rotate_int > 16)
    osd_wind_arrow_rotate_int -= 16; //normalize
  else if (osd_wind_arrow_rotate_int < 1)
    osd_wind_arrow_rotate_int += 16; //normalize
  nor_osd_windspeed = osd_windspeed * 0.010 + nor_osd_windspeed * 0.990;

  showArrow((uint8_t) osd_wind_arrow_rotate_int, 1); //print data to OSD
  osd.closePanel();
}

/* **************************************************************** */
// Panel  : panOff
// Needs  : X, Y locations
// Output : OSD off
// Size   : 1 x 7Hea  (rows x chars)
// Staus  : done

void panOff() {
  boolean rotatePanel = false;

  raw_ch = chan_raw[ch_toggle];

  //If there is a warning force switch to panel 0
  if (!canswitch) {
    if (panel != panel_auto_switch)
      osd_clear = true;

    panel = panel_auto_switch;
  } 
  else {
    //Flight mode switching
    if (ch_toggle == 4) {
      if ((osd_mode != 6) && (osd_mode != 7)) { // TODO:
        if (osd_off_switch != osd_mode) {
          osd_off_switch = osd_mode;
          osd_switch_time = millis();
          if (osd_off_switch == osd_switch_last)
            rotatePanel = true;
        }
        if ((millis() - osd_switch_time) > 2000)
          osd_switch_last = osd_mode;
      }
    } 
    else {

      //Switch mode by value
      if (!switch_mode) {
        //First panel
        if (raw_ch < 1233 && panel != 0) {
          osd_clear = true;
          panel = 0;
        }
        //Second panel
        else if (raw_ch >= 1233 && raw_ch <= 1467 && panel != 1) { //second panel
          osd_clear = true;
          panel = 1;
        }
        //Panel off
        else if (raw_ch > 1467 && panel != npanels) {
          osd_clear = true;
          panel = npanels; //off panel
        }
      }
      //Rotation switch
      else {
        if (raw_ch > 1200)
          if (osd_switch_time + 1000 < millis()) {
            rotatePanel = true;
            osd_switch_time = millis();
          }
      }
    }
    if (rotatePanel) {
      osd_clear = true;
      panel++;
      if (panel > npanels)
        panel = 0;
    }
  }
}
//* **************************************************************** */
// Panel  : panTune
// Needs  : X, Y locations
// Output : Current symbol and altitude value in meters from MAVLink
// Size   : 1 x 7Hea  (rows x chars)
// Staus  : done

void panTune(int first_col, int first_line) {
  osd.setPanel(first_col, first_line);
  osd.openPanel();
  osd.printf("%c%3.0f%c%c|%c%3.0f%c%c", 0xb0, (alt_error * converth * -1),
  high, 0x20, 0xb1, ((aspd_error * 0.01f) * converts), spe, 0x20);
  osd.closePanel();
}

/* **************************************************************** */
// Panel  : panCur_A
// Needs  : X, Y locations
// Output : Current symbol and altitude value in meters from MAVLink
// Size   : 1 x 7Hea  (rows x chars)
// Staus  : done

void panCur_A(int first_col, int first_line) {
  osd.setPanel(first_col, first_line);
  osd.openPanel();
  osd.printf("%5.2f%c", (float(osd_curr_A) * 0.01), 0x0e);
  osd.closePanel();
}

/* **************************************************************** */
// Panel  : panAlt
// Needs  : X, Y locations
// Output : Alt symbol and altitude value in meters from MAVLink
// Size   : 1 x 7Hea  (rows x chars)
// Staus  : done

void panAlt(int first_col, int first_line) {
  osd.setPanel(first_col, first_line);
  osd.openPanel();
  //    osd.printf("%c%5.0f%c",0x11, (double)(osd_alt * converth), high);
  //    if (iconMSL == 1) 
  if (EEPROM.read(SIGN_MSL_ON_ADDR) != 0)
    osd.printf_P(PSTR("\x11"));
  osd.printf("%5.0f%c", (double) (osd_alt * converth), high);
  osd.closePanel();
}

/* **************************************************************** */
// Panel  : panClimb
// Needs  : X, Y locations
// Output : Alt symbol and altitude value in meters from MAVLink
// Size   : 1 x 7Hea  (rows x chars)
// Staus  : done

void panClimb(int first_col, int first_line) {
  osd.setPanel(first_col, first_line);
  osd.openPanel();
  vs = (osd_climb * converth * 60) * 0.1 + vs * 0.9;
  osd.printf("%c%4.0f%c%c", 0x15, int(vs * 0.1) * 10.0, climbchar, 0x20);
  osd.closePanel();
}

/* **************************************************************** */
// Panel  : panHomeAlt
// Needs  : X, Y locations
// Output : Alt symbol and home altitude value in meters from MAVLink
// Size   : 1 x 7Hea  (rows x chars)
// Staus  : done

void panHomeAlt(int first_col, int first_line) {
  osd.setPanel(first_col, first_line);
  osd.openPanel();
  //    osd.printf("%c%5.0f%c",0x12, (double)(osd_alt_to_home * converth), high);
  //    if (iconHA ) 
  if (EEPROM.read(SIGN_HA_ON_ADDR) != 0)
    osd.printf_P(PSTR("\x12"));
  osd.printf("%5.0f%c", (double) (osd_alt_to_home * converth), high);
  osd.closePanel();
}

/* **************************************************************** */
// Panel  : panVel
// Needs  : X, Y locations
// Output : Velocity value from MAVlink with symbols
// Size   : 1 x 7  (rows x chars)
// Staus  : done

void panVel(int first_col, int first_line) {
  osd.setPanel(first_col, first_line);
  osd.openPanel();
  //    osd.printf("%c%3.0f%c",0x14,(double)(osd_groundspeed * converts),spe);
  //    if (iconGS ) 
  if (EEPROM.read(SIGN_GS_ON_ADDR) != 0)
    osd.printf_P(PSTR("\x14"));
  osd.printf("%3.0f%c", (double) (osd_groundspeed * converts), spe);
  osd.closePanel();
}

/* **************************************************************** */
// Panel  : panAirSpeed
// Needs  : X, Y locations
// Output : Airspeed value from MAVlink with symbols
// Size   : 1 x 7  (rows x chars)
// Staus  : done

void panAirSpeed(int first_col, int first_line) {
  osd.setPanel(first_col, first_line);
  osd.openPanel();
  //    osd.printf("%c%3.0f%c", 0x13, (double)(osd_airspeed * converts), spe);
  //    if (iconAS ) 
  if (EEPROM.read(SIGN_AS_ON_ADDR) != 0)
    osd.printf_P(PSTR("\x13"));
  osd.printf("%3.0f%c", (double) (osd_airspeed * converts), spe);
  osd.closePanel();
}

/* **************************************************************** */
// Panel  : panWarn
// Needs  : X, Y locations
// Output : Airspeed value from MAVlink with symbols
// Size   : 1 x 7  (rows x chars)
// Staus  : done

void panWarn(int first_col, int first_line) {
#if defined(YYY)
  boolean warning[6];
  const char warn_mess[][13] = { 
    "            ", " NO GPS FIX!",
    "HIGH VSPEED!", " OVERSPEED! ", "BATTERY LOW!", "  LOW RSSI  ",
    "  EPH HIGH  "             };

  if (one_sec_timer_switch) {
    osd.setPanel(first_col, first_line);
    osd.openPanel();

    // check all warnings at once - reverse priority order?
    warning[0] = true;
    warning[1] = osd_fix_type < 2;
    warning[2] = abs(vs) > (stall * 10);
    warning[3] = (osd_airspeed * converts) > (float) overspeed;
    warning[4] = osd_vbat_A < ((float) (battv) * 0.01)
      || (osd_battery_remaining_A < batt_warn_level
        && batt_warn_level != 0);
    warning[5] = rssi < rssi_warn_level && rssi != -99 && !rssiraw_on;
    warning[6] = eph > 150;

    rotation = 6; //  7
    do {
    } 
    while (!(warning[--rotation] || (rotation <= 0)));
    osd.printf("%s", warn_mess[rotation]);

    // Auto switch decision
    if (warning[0] && panel_auto_switch < 3)
      canswitch = false;
    else if (raw_ch < 1200)
      canswitch = true;

    osd.closePanel();
  }
#endif
}
/* **************************************************************** */
// Panel  : panThr
// Needs  : X, Y locations
// Output : Throttle value from MAVlink with symbols
// Size   : 1 x 7  (rows x chars)
// Staus  : done

void panThr(int first_col, int first_line) {
  osd.setPanel(first_col, first_line);
  osd.openPanel();
  osd.printf("%3.0i%c", osd_throttle, 0x25);
  osd.closePanel();
}

/* **************************************************************** */
// Panel  : panBatteryPercent
// Needs  : X, Y locations
// Output : Battery state from MAVlink with symbols
// Size   : 1 x 7  (rows x chars)
// Staus  : done

void panBatteryPercent(int first_col, int first_line) {
  osd.setPanel(first_col, first_line);
  osd.openPanel();
  if (EEPROM.read(OSD_BATT_SHOW_PERCENT_ADDR) == 1)
    osd.printf("%c%3.0i%c", 0x17, osd_battery_remaining_A, 0x25);
  else
    osd.printf("%c%4.0f%c", 0x17, mah_used, 0x01);
  osd.closePanel();
}

/* **************************************************************** */
// Panel  : panTime
// Needs  : X, Y locations
// Output : Time from start with symbols
// Size   : 1 x 7  (rows x chars)
// Staus  : done

void panTime(int first_col, int first_line) {
  osd.setPanel(first_col, first_line);
  osd.openPanel();

  start_Time = (millis() / 1000) - FTime;
  //    osd.printf("%c%2i%c%02i", 0x08,((int)start_Time/60)%60,0x3A,(int)start_Time%60);
  //    osd.printf("%2i%c%02i",((int)start_Time/60)%60,0x3A,(int)start_Time%60);


  //    if((int)start_Time < 36000) oszt=60; {
  osd.printf("%3i%c%02i", ((int) start_Time / 60), 0x3A, (int) start_Time
    % 60);
  //    }else{
  //    osd.printf("%2i%c%02i", ((int)start_Time/3600)%60, 0x3A, ((int)start_Time/60)%60);
  //    }
  osd.closePanel();
}

/* **************************************************************** */
// Panel  : panHomeDis
// Needs  : X, Y locations
// Output : Home Symbol with distance to home in meters
// Size   : 1 x 7  (rows x chars)
// Staus  : done

void panHomeDis(int first_col, int first_line) {
  osd.setPanel(first_col, first_line);
  osd.openPanel();
  //    osd.printf("%c%5.0f%c", 0x0b, (double)((osd_home_distance) * converth), high);
  if ((osd_home_distance * converth) > 9999.0)
    osd.printf("%c%5.2f%c", 0x0b, ((osd_home_distance * converth)
      / distconv), distchar);
  else
    osd.printf("%c%5.0f%c", 0x0b, (osd_home_distance * converth), high);
  osd.closePanel();
}

/* **************************************************************** */
// Panel  : panCenter
// Needs  : X, Y locations
// Output : 2 row croshair symbol created by 2 x 4 chars
// Size   : 2 x 4  (rows x chars)
// Staus  : done

//void panCenter(int first_col, int first_line){
//    osd.setPanel(first_col, first_line);
//    osd.openPanel();
//    osd.printf_P(PSTR("\x05\x03\x04\x05|\x15\x13\x14\x15"));
//    osd.closePanel();
//}

/* **************************************************************** */
// Panel  : panHorizon
// Needs  : X, Y locations
// Output : 12 x 4 Horizon line surrounded by 2 cols (left/right rules)
// Size   : 14 x 4  (rows x chars)
// Staus  : done

void panHorizon(int first_col, int first_line) {
  osd.setPanel(first_col, first_line);
  osd.openPanel();
  osd.printf_P(
  PSTR(
  "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20|\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20|\xc6\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\xc5|\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20|\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20|"));
  osd.closePanel();
  showHorizon((first_col + 1), first_line);
  //Show ILS on  HUD
  //    showILS(first_col, first_line);
}

/* **************************************************************** */
// Panel  : panPitch
// Needs  : X, Y locations
// Output : -+ value of current Pitch from vehicle with degree symbols and pitch symbol
// Size   : 1 x 6  (rows x chars)
// Staus  : done

void panPitch(int first_col, int first_line) {
  osd.setPanel(first_col, first_line);
  osd.openPanel();
  osd.printf("%4i%c%c", osd_pitch, 0x05, 0x07);
  osd.closePanel();
}

/* **************************************************************** */
// Panel  : panRoll
// Needs  : X, Y locations
// Output : -+ value of current Roll from vehicle with degree symbols and roll symbol
// Size   : 1 x 6  (rows x chars)
// Staus  : done

void panRoll(int first_col, int first_line) {
  osd.setPanel(first_col, first_line);
  osd.openPanel();
  osd.printf("%4i%c%c", osd_roll, 0x05, 0x06);
  osd.closePanel();
}

/* **************************************************************** */
// Panel  : panBattery A (Voltage 1)
// Needs  : X, Y locations
// Output : Voltage value as in XX.X and symbol of over all battery status
// Size   : 1 x 8  (rows x chars)
// Staus  : done

void panBatt_A(int first_col, int first_line) {
  osd.setPanel(first_col, first_line);
  osd.openPanel();
  /*************** This commented code is for the next ArduPlane Version
   * 	 * if(osd_battery_remaining_A > 100){
   * 	 * osd.printf(" %c%5.2f%c", 0xbc, (double)osd_vbat_A, 0x0d);
   * 	 * else osd.printf("%c%5.2f%c%c", 0xbc, (double)osd_vbat_A, 0x0d, osd_battery_pic_A);
   	 */
  //    osd.printf("%c%5.2f%c", 0xbc, (double)osd_vbat_A, 0x0d);
  osd.printf("%5.2f%c", (double) osd_vbat_A, 0x0d);
  osd.closePanel();
}

//------------------ Panel: Waiting for MAVLink HeartBeats -------------------------------

void panWaitMAVBeats(int first_col, int first_line) {
  //panLogo();
  osd.setPanel(first_col, first_line);
  osd.openPanel();
  osd.printf_P(PSTR("No mav data!"));
  osd.closePanel();
}


/* **************************************************************** */
// Panel  : panGPSats
// Needs  : X, Y locations
// Output : 1 symbol and number of locked satellites
// Size   : 1 x 5  (rows x chars)
// Staus  : done

void panGPSats(int first_col, int first_line) {
  osd.setPanel(first_col, first_line);
  osd.openPanel();

  byte gps_str = 0x2a;
  if(osd_fix_type == 2) 
    gps_str = 0x1f;
  else if (osd_fix_type == 3)
    gps_str = 0x0f;

  if ((eph >= 200) && blinker)
    gps_str = 0x20;

  osd.printf("%c%2i", gps_str, osd_satellites_visible);
  osd.closePanel();
}

/* **************************************************************** */
// Panel  : panGPS
// Needs  : X, Y locations
// Output : two row numeric value of current GPS location with LAT/LON symbols as on first char
// Size   : 2 x 12  (rows x chars)
// Staus  : done

void panGPS(int first_col, int first_line) {
  osd.setPanel(first_col, first_line);
  osd.openPanel();
  //    osd.printf("%c%10.6f|%c%10.6f", 0x03, (double)osd_lat, 0x04, (double)osd_lon);
  osd.printf("%11.6f|%11.6f", (double) osd_lat, (double) osd_lon);
  //    if (!blinker) osd.printf("%c%10.6f", 0x03, (double)osd_lat);
  //    else osd.printf("%c%10.6f", 0x04, (double)osd_lon);
  osd.closePanel();
}

/* **************************************************************** */
// Panel  : panHeading
// Needs  : X, Y locations
// Output : Symbols with numeric compass heading value
// Size   : 1 x 5  (rows x chars)
// Staus  : not ready

void panHeading(int first_col, int first_line) {
  osd.setPanel(first_col, first_line);
  osd.openPanel();
  osd.printf("%4.0f%c", (double) osd_heading, 0x05);
  osd.closePanel();
}

/* **************************************************************** */
// Panel  : panRose
// Needs  : X, Y locations
// Output : a dynamic compass rose that changes along the heading information
// Size   : 2 x 13  (rows x chars)
// Staus  : done

void panRose(int first_col, int first_line) {
  osd.setPanel(first_col, first_line);
  osd.openPanel();
  //osd_heading  = osd_yaw;
  //if(osd_yaw < 0) osd_heading = 360 + osd_yaw;
  //    osd.printf("%s|%c%s%c", "\x20\xc0\xc0\xc0\xc0\xc0\xc7\xc0\xc0\xc0\xc0\xc0\x20", 0xc3, buf_show, 0x87);
  osd.printf("%c%s%c", 0xc3, buf_show, 0x87);
  osd.closePanel();
}

/* **************************************************************** */
// Panel  : panBoot
// Needs  : X, Y locations
// Output : Booting up text and empty bar after that
// Size   : 1 x 21  (rows x chars)
// Staus  : done

//void panBoot(int first_col, int first_line){
//    osd.setPanel(first_col, first_line);
//    osd.openPanel();
//    osd.printf_P(PSTR("Booting up:\x88\x8d\x8d\x8d\x8d\x8d\x8d\x8d\x8e")); 
//    osd.closePanel();
//}

/* **************************************************************** */
// Panel  : panMavBeat
// Needs  : X, Y locations
// Output : 2 symbols, one static and one that blinks on every 50th received 
//          mavlink packet.
// Size   : 1 x 2  (rows x chars)
// Staus  : done

//void panMavBeat(int first_col, int first_line){
//    osd.setPanel(first_col, first_line);
//    osd.openPanel();
//    if(mavbeat){
//        osd.printf_P(PSTR("\xEA\xEC"));
//        mavbeat = false;
//    }
//    else{
//        osd.printf_P(PSTR("\xEA\xEB"));
//    }
//    osd.closePanel();
//}


/* **************************************************************** */
// Panel  : panWPDir
// Needs  : X, Y locations
// Output : 2 symbols that are combined as one arrow, shows direction to next waypoint
// Size   : 1 x 2  (rows x chars)
// Staus  : not ready

//void panWPDir(int first_col, int first_line){
//    osd.setPanel(first_col, first_line);
//    osd.openPanel();

//    wp_target_bearing_rotate_int = round(((float)wp_target_bearing - osd_heading)/360.0 * 16.0) + 1; //Convert to int 0-16 
//    if(wp_target_bearing_rotate_int < 0 ) wp_target_bearing_rotate_int += 16; //normalize  

//    showArrow((uint8_t)wp_target_bearing_rotate_int,0);
//    osd.closePanel();
//}

/* **************************************************************** */
// Panel  : panWPDis
// Needs  : X, Y locations
// Output : W then distance in Km - Distance to next waypoint
// Size   : 1 x 2  (rows x chars)
// Staus  : not ready TODO - CHANGE the Waypoint symbol - Now only a W!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

void panWPDis(int first_col, int first_line) {
  osd.setPanel(first_col, first_line);
  osd.openPanel();

  if (wp_target_bearing > 0)
    wp_target_bearing_rotate_int = round((wp_target_bearing - osd_heading)
      / 360 * 16.0) + 1;
  else if (wp_target_bearing < 0)
    wp_target_bearing_rotate_int = round(((360 + wp_target_bearing)
      - osd_heading) / 360 * 16.0) + 1;

  if (wp_target_bearing_rotate_int < 0)
    wp_target_bearing_rotate_int += 16;
  if (wp_target_bearing_rotate_int == 0)
    wp_target_bearing_rotate_int = 16;

  xtrack_error = constrain(xtrack_error, -999, 999);

  osd.printf("%c%c%2i%c%4.0f%c|", 0x57, 0x70, wp_number, 0x0,
  (double) ((float) (wp_dist) * converth), high);
  showArrow((uint8_t) wp_target_bearing_rotate_int, 0);
  if ((osd_mode == Transiting) || (osd_mode == ReturningHome))
    osd.printf("%c%c%c%4.0f%c", 0x20, 0x58, 0x65,
    (xtrack_error * converth), high);
  else
    osd.printf_P(PSTR("        "));
  osd.closePanel();
}

/* **************************************************************** */
// Panel  : panHomeDir
// Needs  : X, Y locations
// Output : 2 symbols that are combined as one arrow, shows direction to home
// Size   : 1 x 2  (rows x chars)
// Status : not tested

void panHomeDir(int first_col, int first_line) {
  osd.setPanel(first_col, first_line);
  osd.openPanel();
  showArrow((uint8_t) osd_home_direction, 0);
  osd.closePanel();
}

/* **************************************************************** */
// Panel  : panFlightMode 
// Needs  : X, Y locations
// Output : 2 symbols, one static name symbol and another that changes by flight modes
// Size   : 1 x 2  (rows x chars)
// Status : done

void panFlightMode(int first_col, int first_line) {
  osd.setPanel(first_col, first_line);
  osd.openPanel();
  //char c1 = 0x7f ;//"; char c2; char c3; char c4; char c5; 

  const char NavStateName[][5] = { 
    "hold", "rth ", "home", "desc", "down", "tran",
    "loit", "circ", "prch", "toff", "stab", "acqa", "thrm", "ridg",
    "wave", "bst ", "alim", "glid", "rate", "man ", "????"             };
  osd.printf("%s", NavStateName[osd_mode]);
  osd.closePanel();
}

// ---------------- EXTRA FUNCTIONS ----------------------
// Show those fancy 2 char arrows

void showArrow(uint8_t rotate_arrow, uint8_t method) {
  char arrow_set1 = 0x0;

  if (rotate_arrow == 0)
    rotate_arrow = 1;

  arrow_set1 = rotate_arrow * 2 + 0x8E;

  if (method == 1)
    osd.printf("%c%3.0f%c|%c%c%2.0f%c", 0x1d, (double) (osd_windspeed
      * converts), spe, arrow_set1, arrow_set1 + 1,
    (double) (nor_osd_windspeed * converts), spe);
  else if (method == 2)
    osd.printf("%c%c%4i%c", arrow_set1, arrow_set1 + 1, off_course, 0x05);
  else
    osd.printf("%c%c", arrow_set1, arrow_set1 + 1);
}

// Calculate and shows Artificial Horizon
// Smooth horizon by Jörg Rothfuchs
// with different factors we can adapt do different cam optics
#define AH_PITCH_FACTOR		0.010471976		// conversion factor for pitch
#define AH_ROLL_FACTOR		0.017453293		// conversion factor for roll
#define AH_COLS			12			// number of artificial horizon columns
#define AH_ROWS			5			// number of artificial horizon rows
#define CHAR_COLS		12			// number of MAX7456 char columns
#define CHAR_ROWS		18			// number of MAX7456 char rows
#define CHAR_SPECIAL		9			// number of MAX7456 special chars for the artificial horizon
#define AH_TOTAL_LINES		AH_ROWS * CHAR_ROWS	// helper define
#define LINE_SET_STRAIGHT__	(0xC7 - 1)		// code of the first MAX7456 straight char -1
#define LINE_SET_STRAIGHT_O	(0xD0 - 3)		// code of the first MAX7456 straight overflow char -3
#define LINE_SET_P___STAG_1	(0xD1 - 1)		// code of the first MAX7456 positive staggered set 1 char -1
#define LINE_SET_P___STAG_2	(0xDA - 1)		// code of the first MAX7456 positive staggered set 2 char -1
#define LINE_SET_N___STAG_1	(0xE3 - 1)		// code of the first MAX7456 negative staggered set 1 char -1
#define LINE_SET_N___STAG_2	(0xEC - 1)		// code of the first MAX7456 negative staggered set 2 char -1
#define LINE_SET_P_O_STAG_1	(0xF5 - 2)		// code of the first MAX7456 positive overflow staggered set 1 char -2
#define LINE_SET_P_O_STAG_2	(0xF9 - 1)		// code of the first MAX7456 positive overflow staggered set 2 char -1
#define LINE_SET_N_O_STAG_1	(0xF7 - 2)		// code of the first MAX7456 negative overflow staggered set 1 char -2
#define LINE_SET_N_O_STAG_2	(0xFC - 1)		// code of the first MAX7456 negative overflow staggered set 2 char -1
#define OVERFLOW_CHAR_OFFSET	6			// offset for the overflow subvals
#define ANGLE_1			9			// angle above we switch to line set 1
#define ANGLE_2			25			// angle above we switch to line set 2

// Calculate and show artificial horizon
// used formula: y = m * x + n <=> y = tan(a) * x + n
void showHorizon(int start_col, int start_row) {
  int col, row, pitch_line, middle, hit, subval;
  int roll;
  int line_set = LINE_SET_STRAIGHT__;
  int line_set_overflow = LINE_SET_STRAIGHT_O;
  int subval_overflow = 9;

  // preset the line char attributes
  roll = osd_roll;
  if ((roll >= 0 && roll < 90) || (roll >= -179 && roll < -90)) { // positive angle line chars
    roll = roll < 0 ? roll + 179 : roll;
    if (abs(roll) > ANGLE_2) {
      line_set = LINE_SET_P___STAG_2;
      line_set_overflow = LINE_SET_P_O_STAG_2;
      subval_overflow = 7;
    } 
    else if (abs(roll) > ANGLE_1) {
      line_set = LINE_SET_P___STAG_1;
      line_set_overflow = LINE_SET_P_O_STAG_1;
      subval_overflow = 8;
    }
  } 
  else { // negative angle line chars
    roll = roll > 90 ? roll - 179 : roll;
    if (abs(roll) > ANGLE_2) {
      line_set = LINE_SET_N___STAG_2;
      line_set_overflow = LINE_SET_N_O_STAG_2;
      subval_overflow = 7;
    } 
    else if (abs(roll) > ANGLE_1) {
      line_set = LINE_SET_N___STAG_1;
      line_set_overflow = LINE_SET_N_O_STAG_1;
      subval_overflow = 8;
    }
  }

  pitch_line = round(tan(-AH_PITCH_FACTOR * osd_pitch) * AH_TOTAL_LINES)
    + AH_TOTAL_LINES / 2; // 90 total lines
  for (col = 1; col <= AH_COLS; col++) {
    middle = col * CHAR_COLS - (AH_COLS / 2 * CHAR_COLS) - CHAR_COLS / 2; // -66 to +66	center X point at middle of each column
    hit = tan(AH_ROLL_FACTOR * osd_roll) * middle + pitch_line; // 1 to 90	calculating hit point on Y plus offset
    if (hit >= 1 && hit <= AH_TOTAL_LINES) {
      row = (hit - 1) / CHAR_ROWS; // 0 to 4 bottom-up
      subval = (hit - (row * CHAR_ROWS) + 1) / (CHAR_ROWS / CHAR_SPECIAL); // 1 to 9

      // print the line char
      osd.openSingle(start_col + col - 1, start_row + AH_ROWS - row - 1);
      osd.printf("%c", line_set + subval);

      // check if we have to print an overflow line char
      if (subval >= subval_overflow && row < 4) { // only if it is a char which needs overflow and if it is not the upper most row
        osd.openSingle(start_col + col - 1, start_row + AH_ROWS - row
          - 2);
        osd.printf("%c", line_set_overflow + subval
          - OVERFLOW_CHAR_OFFSET);
      }
    }
  }
}

// Calculate and shows ILS
/*
void showILS(int start_col, int start_row) { 
 //Vertical calculation
 int currentAngleDisplacement = atan(osd_alt_to_home / osd_home_distance) * 57.2957795 - 10;
 //Calc current char position 
 //int numberOfPixels = CHAR_ROWS * AH_ROWS;
 int totalNumberOfLines = 9 * AH_ROWS; //9 chars in chartset for vertical line
 int linePosition = totalNumberOfLines * currentAngleDisplacement / 10 + (totalNumberOfLines / 2); //+-5 degrees
 int charPosition = linePosition / 9;
 int selectedChar = 9 - (linePosition % 9) + 0xC7;
 if(charPosition >= 0 && charPosition <= CHAR_ROWS)
 {
 osd.openSingle(start_col + AH_COLS + 2, start_row + charPosition);
 osd.printf("%c", selectedChar);
 }
 
 //Horizontal calculation
 currentAngleDisplacement = osd_home_direction - takeoff_heading;
 //Horizontal calculation
 totalNumberOfLines = 6 * AH_COLS; //6 chars in chartset for vertical line
 linePosition = totalNumberOfLines * currentAngleDisplacement / 10 + (totalNumberOfLines / 2); //+-5 degrees
 charPosition = linePosition / 6;
 selectedChar = (linePosition % 6) + 0xBF;
 if(charPosition >= 0 && charPosition <= CHAR_COLS)
 {
 osd.openSingle(start_col + charPosition, start_row + AH_ROWS + 1);
 osd.printf("%c", selectedChar);
 }
 }
 */
void do_converts() {
  //  if(EEPROM.read(SIGN_MSL_ON_ADDR) == 0) EEPROM.write(876, 1);
  //  if(EEPROM.read(SIGNS_ON_ADDR) != 0) iconGS = true;
  //  if(EEPROM.read(SIGNS_ON_ADDR) != 0) iconHA = true;
  //  if(EEPROM.read(SIGNS_ON_ADDR) != 0) iconMSL = true;
  //      signDist = 0x8f;
  //     signTemp = 0x0a;
  //     signEff = 0x16;
  //     signRssi = 0x09;
  //     signCurr = 0xbd;
  //     signAlt = 0x11;
  //     signClimb = 0x15;
  //     signHomeAlt = 0x12;
  //     signVel = 0x14;
  //      signASpeed = 0x13;
  //      signThrot = 0x02;
  //      signBat = 0x17;
  //     signTime = 0x08;
  //      signHomeDist = 0x0b;
  //      signBatA = 0xbc;
  //      signMode = 0x7f;
  //      signLat = 0x03;
  //      signLon = 0x04;

  if (EEPROM.read(measure_ADDR) == 0) {
    converts = 3.6;
    converth = 1.0;
    spe = 0x10;
    high = 0x0c;
    temps = 0xba;
    tempconv = 10;
    tempconvAdd = 0;
    distchar = 0x1b;
    distconv = 1000;
    climbchar = 0x1a;
  } 
  else {
    converts = 2.23;
    converth = 3.28;
    spe = 0x19;
    high = 0x66;
    temps = 0xbb;
    tempconv = 18;
    tempconvAdd = 32000;
    distchar = 0x1c;
    distconv = 5280;
    climbchar = 0x1e;
  }
}

void timers() {
  if (one_sec_timer_switch) {
    one_sec_timer = millis() + 1000;
    one_sec_timer_switch = false;
    blinker = !blinker;
  }
  if (millis() > one_sec_timer)
    one_sec_timer_switch = true;

}









