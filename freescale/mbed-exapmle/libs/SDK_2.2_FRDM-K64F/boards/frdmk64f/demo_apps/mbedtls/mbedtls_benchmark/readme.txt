Overview
========
The mbdedTLS Benchmark demo application performs cryptographic algorithm benchmarking and prints results to the
terminal.


Toolchain supported
===================
- IAR embedded Workbench 7.80.4
- Keil MDK 5.21a
- GCC ARM Embedded 2016-5.4-q3
- Kinetis Development Studio IDE 3.2.0
- MCUXpresso0.8

Hardware requirements
=====================
- Mini/micro USB cable
- FRDM-K64F board
- Personal Computer

Board settings
==============
No special settings are required.
Prepare the Demo
================
Connect a serial cable from the debug UART port of the target board to the PC. Start TeraTerm (http://ttssh2.osdn.jp)
and make a connection to the virtual serial port.

1. Start TeraTerm.

2. New connection -> Serial.

3. Set the appropriate COMx port (where x is port number) in the port context menu. The number is provided by the operating
   system, and could be different from computer to computer. Select the COM number related to the virtual
   serial port. Confirm the selected port by clicking the "OK" button.

4. Set following connection parameters in menu Setup -> Serial port.
        Baud rate:    115200
        Data:         8
        Parity:       none
        Stop:         1
        Flow control: none

5.  Confirm selected parameters by clicking the "OK" button.

Running the demo
================
When the demo runs successfully, which takes a couple of minutes, the terminal displays similar information like the following:

mbedTLS version 2.3.0
fsys=120000000
Using following implementations:
  SHA: MMCAU HW accelerated
  AES: MMCAU HW accelerated
  AES GCM: MMCAU HW accelerated
  DES: MMCAU HW accelerated
  Asymmetric encryption: Software implementation


  MD5                      :  7160.47 KB/s,   16.14 cycles/byte
  SHA-1                    :  3857.61 KB/s,   30.15 cycles/byte
  SHA-256                  :  2543.23 KB/s,   45.87 cycles/byte
  SHA-512                  :  789.87 KB/s,  148.33 cycles/byte
  3DES                     :  1325.74 KB/s,   88.24 cycles/byte
  DES                      :  2622.42 KB/s,   44.47 cycles/byte
  AES-CBC-128              :  2842.23 KB/s,   41.02 cycles/byte
  AES-CBC-192              :  2660.79 KB/s,   43.83 cycles/byte
  AES-CBC-256              :  2517.95 KB/s,   46.33 cycles/byte
  AES-GCM-128              :  818.67 KB/s,  143.08 cycles/byte
  AES-GCM-192              :  804.44 KB/s,  145.62 cycles/byte
  AES-GCM-256              :  790.74 KB/s,  148.17 cycles/byte
  AES-CCM-128              :  1087.19 KB/s,  107.66 cycles/byte
  AES-CCM-192              :  1044.11 KB/s,  112.12 cycles/byte
  AES-CCM-256              :  993.71 KB/s,  117.82 cycles/byte
  AES-CTR-128              :  2698.71 KB/s,   43.22 cycles/byte
  AES-CTR-192              :  2534.63 KB/s,   46.04 cycles/byte
  AES-CTR-256              :  2404.68 KB/s,   48.54 cycles/byte
  CAMELLIA-CBC-128         :  673.79 KB/s,  173.95 cycles/byte
  CAMELLIA-CBC-192         :  524.56 KB/s,  223.58 cycles/byte
  CAMELLIA-CBC-256         :  524.62 KB/s,  223.58 cycles/byte
  CTR_DRBG (NOPR)          :  2674.09 KB/s,   43.61 cycles/byte
  CTR_DRBG (PR)            :  1869.33 KB/s,   62.49 cycles/byte
  HMAC_DRBG SHA-1 (NOPR)   :  253.28 KB/s,  464.28 cycles/byte
  HMAC_DRBG SHA-1 (PR)     :  234.75 KB/s,  501.11 cycles/byte
  HMAC_DRBG SHA-256 (NOPR) :  275.84 KB/s,  426.16 cycles/byte
  HMAC_DRBG SHA-256 (PR)   :  242.44 KB/s,  485.13 cycles/byte
  RSA-2048                 :   45.00  public/s
  RSA-2048                 :    1.33 private/s
  DHE-2048                 :    0.33 handshake/s
  DH-2048                  :    0.33 handshake/s
  ECDSA-secp384r1          :    2.33 sign/s
  ECDSA-secp256r1          :    4.00 sign/s
  ECDSA-secp224r1          :    5.67 sign/s
  ECDSA-secp192r1          :    7.33 sign/s
  ECDSA-secp384r1          :    1.33 verify/s
  ECDSA-secp256r1          :    2.33 verify/s
  ECDSA-secp224r1          :    3.00 verify/s
  ECDSA-secp192r1          :    4.00 verify/s
  ECDHE-secp384r1          :    1.33 handshake/s
  ECDHE-secp256r1          :    2.33 handshake/s
  ECDHE-secp224r1          :    3.33 handshake/s
  ECDHE-secp192r1          :    4.33 handshake/s
  ECDH-secp384r1           :    2.33 handshake/s
  ECDH-secp256r1           :    4.33 handshake/s
  ECDH-secp224r1           :    6.00 handshake/s
  ECDH-secp192r1           :    7.67 handshake/s

Customization options
=====================

