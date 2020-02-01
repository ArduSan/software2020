float upid() {
  float errorP, errorI,
errorD, delta;
  delta = spompaciuccioapalloncino;
  if (delta > 180) delta = delta - 360;
  errorP = delta * KP;
  errorI = KD * (delta - deltaPRE);
  deltaPRE = delta;
  integral = 0.5 * integral + delta;
  errorI = KI * integral;
  return errorP + errorI + errorD;
}
