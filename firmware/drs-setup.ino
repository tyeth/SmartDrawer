/*Seting up DRS
copyright (c) 2016 Tyler Spadgenske
MIT License
This code takes the authentication code from the registration
website and requests and access_code. The code is printed to
the serial terminal.
*/

void setup()
{
  delay(1000);

  Serial.begin(9600);
  Serial.println("Welcome to DRS Setup");
  Particle.subscribe("hook-response/drs_auth", DRS_Auth, MY_DEVICES);
}

void DRS_Auth(const char *name, const char *data) {
    Serial.print("Your Access code is:");
    Serial.println(String(data));
}

void loop() {
  // 20 digit code from registration URL (spadgenske.github.io/smartdrawer/redirect)
  String authentication_code = "ANLHxSEbKYwpfSnqeWzH";
  Serial.println("Getting Access Code...");
  Particle.publish("drs_auth", authentication_code, PRIVATE);
  // Wait really long time
  Serial.println("Done.");
  delay(6000000);
}
