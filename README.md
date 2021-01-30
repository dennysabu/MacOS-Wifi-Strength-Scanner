# MacOS Wifi Scanner
 A much more complicated and less efficient way of finding signal strength on a Mac.
 
 This program will query the Mac airport utility repeatly report the signal strenght by default. This should work on most modern Macs with WiFi. 

 ### Options
 ----

#### Verbosity 
***-v [0/1/2]*** 

-v0 minimal output: '-59' [** Default **]

-v1 standard output: 'Stength: -59'

-v2 maximum output: 
```bash
agrCtlRSSI: -58
agrExtRSSI: 0
agrCtlNoise: -91
agrExtNoise: 0
state: running
op mode: station
lastTxRate: 585
maxRate: 1300
lastAssocStatus: 0
802.11 auth: open
link auth-psk: wpa2-psk
BSSID: de:ad:be:ef:de:ad
SSID: your_wifi_here
MCS: 5
channel: 161,80
```


#### Repetition

***-o [0/1]*** 

-o0 prints only once

-o1 prints continuously [** Default **]

ex:

```bash
./scanner
```
Will print the standard output, continuously. 

```bash
./scanner -v1
```
Will print the standard output, continuously. 

```bash
./scanner -o1
```
Will print the standard output, continuously. 

```bash
./scanner -v2 -o0 
```
Will print entire output, once.


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
 This will create an executable called scanner, which you can invoke using:
 ```bash
     $ ./scanner
 ```

 It will begin querying every 2 seconds for the signal data:

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