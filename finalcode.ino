/*
 * This example plays every .WAV file it finds on the SD card in a loop
 */
#include <WaveHC.h>
#include <WaveUtil.h>
#include <CapacitiveSensor.h>

SdReader card;    // This object holds the information for the card
FatVolume vol;    // This holds the information for the partition on the card
FatReader root;   // This holds the information for the volumes root directory
WaveHC wave;      // This is the only wave (audio) object, since we will only play one at a time

uint8_t dirLevel; // indent level for file/dir names    (for prettyprinting)
dir_t dirBuf;     // buffer for directory reads
int led = 13;
CapacitiveSensor   cs_1_6 = CapacitiveSensor(8, A0);       // 10M resistor between pins 4 & 2, pin 2 is sensor pin, add a wire and or foil if desired
CapacitiveSensor   cs_2_6 = CapacitiveSensor(8, A1);
CapacitiveSensor   cs_3_6 = CapacitiveSensor(8, A2);
CapacitiveSensor   cs_4_6 = CapacitiveSensor(8, A3);
CapacitiveSensor   cs_5_6 = CapacitiveSensor(8, A4);
CapacitiveSensor   cs_6_6 = CapacitiveSensor(8, A5);

/*
 * Define macro to put error messages in flash memory
 */
#define error(msg) error_P(PSTR(msg))

// Function definitions (we define them here, but the code is below)
void play(FatReader &dir);

//////////////////////////////////// SETUP
void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps for debugging
cs_1_6.set_CS_AutocaL_Millis(0xFFFFFFFF); 
  cs_2_6.set_CS_AutocaL_Millis(0xFFFFFFFF);
  cs_3_6.set_CS_AutocaL_Millis(0xFFFFFFFF);
  cs_4_6.set_CS_AutocaL_Millis(0xFFFFFFFF);
  cs_5_6.set_CS_AutocaL_Millis(0xFFFFFFFF);
  cs_6_6.set_CS_AutocaL_Millis(0xFFFFFFFF);// turn off autocalibrate on channel 1 - just as an example
  putstring_nl("\nWave test!");  // say we woke up!

  putstring("Free RAM: ");       // This can help with debugging, running out of RAM is bad
  Serial.println(FreeRam());

  //  if (!card.init(true)) { //play with 4 MHz spi if 8MHz isn't working for you
  if (!card.init()) {         //play with 8 MHz spi (default faster!)
    error("Card init. failed!");  // Something went wrong, lets print out why
  }

  // enable optimize read - some cards may timeout. Disable if you're having problems
  card.partialBlockRead(true);

  // Now we will look for a FAT partition!
  uint8_t part;
  for (part = 0; part < 5; part++) {   // we have up to 5 slots to look in
    if (vol.init(card, part))
      break;                           // we found one, lets bail
  }
  if (part == 5) {                     // if we ended up not finding one  :(
    error("No valid FAT partition!");  // Something went wrong, lets print out why
  }

  // Lets tell the user about what we found
  putstring("Using partition ");
  Serial.print(part, DEC);
  putstring(", type is FAT");
  Serial.println(vol.fatType(), DEC);     // FAT16 or FAT32?

  // Try to open the root directory
  if (!root.openRoot(vol)) {
    error("Can't open root dir!");      // Something went wrong,
  }

  // Whew! We got past the tough parts.
  putstring_nl("Files found (* = fragmented):");

  // Print out all of the files in all the directories.
  root.ls(LS_R | LS_FLAG_FRAGMENTED);
}

FatReader file;
//////////////////////////////////// LOOP
void loop() {
//  root.rewind();
  long start = millis();
long total1 =  cs_1_6.capacitiveSensor(30);
  long total2 =  cs_2_6.capacitiveSensor(30);
  long total3 =  cs_3_6.capacitiveSensor(30);
  long total4 =  cs_4_6.capacitiveSensor(30);
  long total5 =  cs_5_6.capacitiveSensor(30);
  long total6 =  cs_6_6.capacitiveSensor(30);

  Serial.print(millis() - start);        // check on performance in milliseconds
  Serial.print("\t");                    // tab character for debug windown spacing

 Serial.print(total1);                  // print sensor output 1
 Serial.print("\t");
  Serial.print(total2);                  // print sensor output 1
  Serial.print("\t");
  Serial.print(total3);                  // print sensor output 1
  Serial.print("\t");
  Serial.print(total4);                  // print sensor output 1
  Serial.print("\t");
  Serial.print(total5);                  // print sensor output 1
  Serial.print("\t");
  Serial.print(total6);                  // print sensor output 1
  Serial.println("\t");
  delay(10);
  
 if (total3 > 40) {
 Serial.println("Playing Japan");
  file.open(root, "JAPAN.WAV");
  if (!wave.create(file)) {
    error("can't play japan!");
   }
   wave.play();
    uint8_t n = 0;
   while (wave.isplaying) {// playing occurs in interrupts, so we print dots in realtime
     putstring(".");
     if (!(++n % 32))Serial.println();
    delay(100);
  }
 }
  if (total2 > 40) {
    Serial.println("Playing Iran");
    file.open(root, "IRAN.WAV");
    if (!wave.create(file)) {
      error("can't play Iran!");
    }
    wave.play();
    uint8_t n = 0;
    while (wave.isplaying) {// playing occurs in interrupts, so we print dots in realtime
      putstring(".");
      if (!(++n % 32))Serial.println();
      delay(100);
    }
  }
  if (total1 > 40) {
 Serial.println("Playing Indonesia ");
  file.open(root, "INDO.WAV");
  if (!wave.create(file)) {
    error("can't play Indonesia!");
   }
   wave.play();
    uint8_t n = 0;
   while (wave.isplaying) {// playing occurs in interrupts, so we print dots in realtime
     putstring(".");
     if (!(++n % 32))Serial.println();
    delay(100);
  }
 }
 if (total4 > 40) {
 Serial.println("Playing Mongolia");
  file.open(root, "MONGOLIA.WAV");
  if (!wave.create(file)) {
    error("can't play Mongolia!");
   }
   wave.play();
    uint8_t n = 0;
   while (wave.isplaying) {// playing occurs in interrupts, so we print dots in realtime
     putstring(".");
     if (!(++n % 32))Serial.println();
    delay(100);
  }
 }
 if (total5 > 40) {
 Serial.println("Playing Russia");
  file.open(root, "RUSSIA.WAV");
  if (!wave.create(file)) {
    error("can't play Russia!");
   }
   wave.play();
    uint8_t n = 0;
   while (wave.isplaying) {// playing occurs in interrupts, so we print dots in realtime
     putstring(".");
     if (!(++n % 32))Serial.println();
    delay(100);
  }
 }
 if (total6 > 40) {
 Serial.println("Playing India");
  file.open(root, "INDIA.WAV");
  if (!wave.create(file)) {
    error("can't play India!");
   }
   wave.play();
    uint8_t n = 0;
   while (wave.isplaying) {// playing occurs in interrupts, so we print dots in realtime
     putstring(".");
     if (!(++n % 32))Serial.println();
    delay(100);
  }
 }
}
//root.rewind();
// int cs_value1 = cs_4.read();
//int cs_value2 = cs_5.read();
//if (cs_value1 > 300) {
//  play(root); // maybe "JAPAN";
//} else if (cs_value2 > 300) {
//   play(root2); // maybe "indonesia"
//delay(1000);
// }
//}

/////////////////////////////////// HELPERS
/*
 * print error message and halt
 */
void error_P(const char *str) {
  PgmPrint("Error: ");
  SerialPrint_P(str);
  sdErrorCheck();
  while (1);
}
/*
 * print error message and halt if SD I/O error, great for debugging!
 */
void sdErrorCheck(void) {
  if (!card.errorCode()) return;
  PgmPrint("\r\nSD I/O error: ");
  Serial.print(card.errorCode(), HEX);
  PgmPrint(", ");
  Serial.println(card.errorData(), HEX);
  while (1);
}
/*
 * play recursively - possible stack overflow if subdirectories too nested
 */
void play(FatReader &dir) {
  FatReader file;
  while (dir.readDir(dirBuf) > 0) {    // Read every file in the directory one at a time

    // Skip it if not a subdirectory and not a .WAV file
    if (!DIR_IS_SUBDIR(dirBuf)
        && strncmp_P((char *)&dirBuf.name[8], PSTR("WAV"), 3)) {
      continue;
    }

    Serial.println();            // clear out a new line

    for (uint8_t i = 0; i < dirLevel; i++) {
      Serial.write(' ');       // this is for prettyprinting, put spaces in front
    }
    if (!file.open(vol, dirBuf)) {        // open the file in the directory
      error("file.open failed");          // something went wrong
    }

    if (file.isDir()) {                   // check if we opened a new directory
      putstring("Subdir: ");
      printEntryName(dirBuf);
      Serial.println();
      dirLevel += 2;                      // add more spaces
      // play files in subdirectory
      play(file);                         // recursive!
      dirLevel -= 2;
    }
    else {
      // Aha! we found a file that isnt a directory
      putstring("Playing ");
      printEntryName(dirBuf);              // print it out
      if (!wave.create(file)) {            // Figure out, is it a WAV proper?
        putstring(" Not a valid WAV");     // ok skip it
      } else {
        Serial.println();                  // Hooray it IS a WAV proper!
        wave.play();                       // make some noise!

        uint8_t n = 0;
        while (wave.isplaying) {// playing occurs in interrupts, so we print dots in realtime
          putstring(".");
          if (!(++n % 32))Serial.println();
          delay(100);
        }
        sdErrorCheck();                    // everything OK?
        // if (wave.errors)Serial.println(wave.errors);     // wave decoding errors
      }
    }
  }
}
