void compassCalibrate() {
  MagnetometerScaled valueMax = { 0, 0, 0 };
  MagnetometerScaled valueMin = { 0, 0, 0 };
  int xcount = 0;
  int ycount = 0;
  int zcount = 0;
  boolean xZero = false;
  boolean yZero = false;
  boolean zZero = false;
  MagnetometerScaled value;
  while (xcount < 3 || ycount < 3 || zcount < 3) {
    value = compass.readScaledAxis();
    if ((fabs(value.XAxis) > 600) || (fabs(value.YAxis) > 600) || (fabs(value.ZAxis) > 600)) {
      continue;
    }
 
    if (valueMin.XAxis > value.XAxis) {
      valueMin.XAxis = value.XAxis;
    } else if (valueMax.XAxis < value.XAxis) {
      valueMax.XAxis = value.XAxis;
    }
 
    if (valueMin.YAxis > value.YAxis) {
      valueMin.YAxis = value.YAxis;
    } else if (valueMax.YAxis < value.YAxis) {
      valueMax.YAxis = value.YAxis;
    }
 
    if (valueMin.ZAxis > value.ZAxis) {
      valueMin.ZAxis = value.ZAxis;
    } else if (valueMax.ZAxis < value.ZAxis) {
      valueMax.ZAxis = value.ZAxis;
    }
 
    if (xZero) {
      if (fabs(value.XAxis) > 50) {
        xZero = false;
        xcount++;
      }
    } else {
      if (fabs(value.XAxis) < 40) {
        xZero = true;
      }
    }
 
    if (yZero) {
      if (fabs(value.YAxis) > 50) {
        yZero = false;
        ycount++;
      }
    } else {
      if (fabs(value.YAxis) < 40) {
        yZero = true;
      }
    }
 
    if (zZero) {
      if (fabs(value.ZAxis) > 50) {
        zZero = false;
        zcount++;
      }
    } else {
      if (fabs(value.ZAxis) < 40) {
        zZero = true;
      }
    }
 
    delay(30);
  }
 
  valueOffset.XAxis = (valueMax.XAxis + valueMin.XAxis) / 2;
  valueOffset.YAxis = (valueMax.YAxis + valueMin.YAxis) / 2;
  valueOffset.ZAxis = (valueMax.ZAxis + valueMin.ZAxis) / 2;
}


void compas_handler(){
  MagnetometerRaw raw = compass.readRawAxis();
  MagnetometerScaled scaled = compass.readScaledAxis();
 
  scaled.XAxis -= valueOffset.XAxis;
  scaled.YAxis -= valueOffset.YAxis;
  scaled.ZAxis -= valueOffset.ZAxis;
 
  int MilliGauss_OnThe_XAxis = scaled.XAxis;
  float yxHeading = atan2(scaled.YAxis, scaled.XAxis);
  float zxHeading = atan2(scaled.ZAxis, scaled.XAxis);
 
  float heading = yxHeading;
 
  float declinationAngle = (11 + (59.0 / 60.0)) / (180 / M_PI);
  heading += declinationAngle;
 
  if (heading < 0) {
    heading += 2 * PI;
  }
 
  if (heading > 2 * PI) {
    heading -= 2 * PI;
  }

  float headingDegrees = heading * 180 / M_PI;
 
  float yxHeadingDegrees = yxHeading * 180 / M_PI;
  float zxHeadingDegrees = zxHeading * 180 / M_PI;
  current_angle = scaled.XAxis;
}