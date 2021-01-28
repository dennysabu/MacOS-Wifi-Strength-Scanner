# MacOS Wifi Scanner
 A much more complicated and less efficient way of finding signal strength on a Mac.

### Compiling:
----
You can use the included makefile, which has definitions for *all* and *clean*.

```bash
     $ make 
 ```

 Which will compile using the following gcc command:
 ```bash 
     $ gcc -Werror -o scanner scanner.c
 ```
 It will need scanner.c and scanner.h to be present.

### Running:
----
 This will create an exectuable called scanner, which you can invoke using:
 ```bash
     $ ./scanner
 ```

 It will report to you the command it will run: 

 ```bash
     Command to run /System/Library/PrivateFrameworks/Apple80211.framework/Versions/Current/Resources/airport -I
 ```

and then beginning querying every 2 seconds for the signal data:

```bash

Strength: -56
Strength: -53
Strength: -55
Strength: -52
Strength: -54
Strength: -55
Strength: -53
Strength: -56
Strength: -55

```

It will continue forever, or you can press ctrl + c to stop.