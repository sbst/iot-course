void setup() 
{
  system("cp /etc/inittab /etc/inittab.bak");  // Back up inittab
  // Replace all "S:2345" with "S0:2345"'s (switching serial ports):
  system("sed -i 's/S:2345/S0:2345/g' /etc/inittab");
  // Replace all "ttyS1" with "ttyGS0"'s (switching serial ports):
  system("sed -i 's/ttyS1/ttyGS0/g' /etc/inittab");
  // Replace all "grst" with "#grst"'s to comment that line out:
  system("sed -i 's/grst/#grst/g' /etc/inittab");
  // Replace all "clld" with "#clld"'s to comment that line out:
  system("sed -i 's/clld/#clld/g' /etc/inittab");
  system("kill -SIGHUP 1");
}
void loop() 
{

}
